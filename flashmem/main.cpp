#include <QtCore>
#include <iostream>
#include <stdint.h>

#include <qserialdevice/abstractserial.h>

//
// Funciones auxiliares
//
uint32_t adler32(uint8_t* data, uint32_t len)
{
    uint32_t a= 1;
    uint32_t b= 0;

    while(len) {
        a = (a + *data) % 65521;
        b = (b + a) % 65521;
        data++;
        len--;
    }
    return (b << 16) | a;
}

void sendData(AbstractSerial& serial, const char* data, int len)
{
    int sent= 0;
    while(sent < len)
        sent += serial.write(data+sent, len-sent);
}

void recivData(AbstractSerial& serial, char* data, int len)
{
    int got= 0;
    while(got < len)
        got += serial.read(data+got, len-got);
}


//
// Funciones principales y main
//

bool setupPort(AbstractSerial& serial, QString portName= "/dev/ttyUSB0")
{
    serial.setDeviceName(portName);

    qDebug() << "setupPort: Opening port" << portName;
    if(!serial.open(AbstractSerial::ReadWrite | AbstractSerial::Unbuffered)) {
        qDebug() << "setupPort: Error opening port.";
        return false;
    }

    bool ok= true;
    ok &= serial.setBaudRate(AbstractSerial::BaudRate115200);
    ok &= serial.setDataBits(AbstractSerial::DataBits8);
    ok &= serial.setParity(AbstractSerial::ParityNone);
    ok &= serial.setStopBits(AbstractSerial::StopBits1);
    ok &= serial.setFlowControl(AbstractSerial::FlowControlOff);
    if(!ok) {
        qDebug() << "setupPort: Error setting up port.";
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    // The W25Q80BV array is organized into 4,096 programmable pages of 256-bytes each
    const int pageSize= 256;
    const int pageCount= 4096;
    qDebug() << "Memory info";
    qDebug() << "  Page size   :" << pageSize << "bytes";
    qDebug() << "  Page count  :" << pageCount;
    qDebug() << "  Total memory:" << pageSize * pageCount << "bytes";

    // Leer samples
    QString samplesDir= (argc>=2) ? QString(argv[1]) : "./samples/";
    qDebug() << "\nReading RAW samples from" << samplesDir;
    QFileInfoList infoList= QDir(samplesDir).entryInfoList(QStringList() << "*.raw", QDir::Files, QDir::Name);

    int samplesCount= infoList.count();
    QStringList samplesNames;
    QList<QByteArray> samplesData;
    QList<int> samplesPages;

    if(!samplesCount) {
        qDebug() << "No samples found.";
        return EXIT_FAILURE;
    }

    uint16_t usedPages= 0;
    foreach(QFileInfo fileInfo, infoList) {
        const QString name= fileInfo.fileName();
        const int pages= qCeil((qreal)fileInfo.size() / pageSize);

        qDebug("  - %s | %6d bytes -> %4d pages | Start page %-4d", name.toLatin1().data(), fileInfo.size(), pages, usedPages);
        samplesNames << name;
        samplesPages << pages;
        usedPages += pages;

        QFile file(fileInfo.filePath());
        file.open(QIODevice::ReadOnly);
        samplesData << file.readAll();
        file.close();
    }
    qDebug("We will use %d pages: %.0f%% of total", usedPages, usedPages*100.0f/pageCount);
    if(usedPages > pageCount) {
        qDebug() << "Data is too big.";
        return EXIT_FAILURE;
    }

    qDebug() << "\nMaking memory image.";
    // Reservar imagen del tamanio de toda la memoria, usada o no
    int imageSize= pageCount * pageSize;
    char* image= (char*)malloc(imageSize);
    // Setear la memoria 0xFF, como la memoria flash despues del bulk erase
    memset(image, 0xFF, imageSize);

    char* imagePtr= image;
    for(int i=0; i<samplesCount; i++) {
        // Copiar dato
        memcpy(imagePtr, samplesData[i].data(), samplesData[i].size());
        imagePtr += samplesData[i].size();
        // Llenar el resto de una pagina con 0's
        int fillSize= samplesPages[i]*pageSize - samplesData[i].size();
        memset(imagePtr, 0, fillSize);
        imagePtr += fillSize;
        qDebug("  - %s, start at 0x%06X, %3d bytes of filling", samplesNames[i].toLatin1().data(), (int)(imagePtr-image), fillSize);
    }
    qDebug() << "Done.";

    qDebug() << "\nFull Image checksum:";
    uint32_t sum= 0;
    for(int i=0; i<pageCount; i++)
        sum += adler32((uint8_t*)(image + i*pageSize), pageSize);
    qDebug("  0x%08X", sum);

    qDebug() << "\nSaving image file...";
    QFile imageFile("flashmem.img");
    imageFile.open(QIODevice::WriteOnly);
    imageFile.write(image, imageSize);
    imageFile.close();
    qDebug() << "Done";

    qDebug() << "\nC code:";
    qDebug() << "#define TRACKS_COUNT " << samplesCount;
    qDebug() << "const uint16_t TRACKS_PAGES[] = {";
    int temp= 0;
    for(int i=0; i<samplesCount; i++) {
        qDebug("    %4d,  // Track Index %2d: \"%s\"",
               temp, i,
               samplesNames[i].toLatin1().data());
        temp += samplesPages[i];
    }
    qDebug("    %4d,  // Not a track, used to calculate the last track's size", temp);
    qDebug() << "};";

    if(argc==3 and QString(argv[2])=="dummy") {
        qDebug() << "\nRunning in dummy mode, quitting.";
        return EXIT_SUCCESS;
    }

    qDebug() << "\nSetting up serial.";
    AbstractSerial serial;
    if(!setupPort(serial))
        return EXIT_FAILURE;
    qDebug() << "Done.";

    qDebug() << "\nWriting data, make sure the MCU is ready.\n";
    // Send flashmem command
    sendData(serial, "flashmem\r", 9);
    sleep(1);
    // Write page number (uint16_t)
    sendData(serial, (char*)&usedPages, 2);
    // Wait for confirmation on page number (uint16_t)
    uint16_t pagesConfirm= 0;
    while(pagesConfirm != usedPages)
        recivData(serial, (char*)&pagesConfirm, 2);
    if(pagesConfirm != usedPages) {
        qDebug() << "Error receiving page count confirmation: " << pagesConfirm;
        return EXIT_FAILURE;
    } else {
        qDebug() << "Page count confirmation OK.";
    }

    imagePtr= image;
    uint16_t index= 0;

    qDebug() << "Sending pages.";
    while(index < usedPages) {
        // Enviar numero de pagina
        sendData(serial, (char*)&index, 2);
        // Enviar pagina
        sendData(serial, imagePtr, pageSize);
        // Recibir checksum
        uint32_t checksumReceiv;
        recivData(serial, (char*)&checksumReceiv, 4);

        uint32_t checksumCalc= adler32((uint8_t*)imagePtr, pageSize);
        if(checksumReceiv == checksumCalc) {
            printf("\rPage %3d of %3d: %2.1f%%  ", index, usedPages, index*100.0f/usedPages);
            fflush(stdout);
            imagePtr += pageSize;
            index++;
        } else {
            std::cout << "Wrong Adler32: " << checksumReceiv << " should be " << checksumCalc << "\n";
        }
    }
    // Enviar numero de pagina 0xFFFF para indicar que terminamos
    index= 0xFFFF;
    serial.write((char*)&index, 2);

    qDebug() << "\nDone!";

    return EXIT_SUCCESS;
}
