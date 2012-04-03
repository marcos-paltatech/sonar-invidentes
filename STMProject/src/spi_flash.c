#include "spi_flash.h"
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "STM32vldiscovery.h"

#include "adler32.h"
#include "io_retarget.h" // Usado por el modo para programar la memoria

static bool setupDone= false;

static inline
void flashSelect()
{
    GPIO_ResetBits(GPIOB, GPIO_Pin_6);
}
static inline
void flashDeselect()
{
    GPIO_SetBits(GPIOB, GPIO_Pin_6);
}

static
uint8_t flashSendByte(uint8_t byte)
{
    waitWhile(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI1, byte);
    waitWhile(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_I2S_ReceiveData(SPI1);
}

static
uint8_t flashReadByte()
{
    return flashSendByte(FLASH_DUMMY_BYTE);
}

static inline
void flashWriteEnable()
{
    flashSelect();
    // Enviar instruccion Write-Enable
    flashSendByte(FLASH_CMD_WREN);
    flashDeselect();
}

static
void flashWaitWriteEnd()
{
    flashSelect();
    // Leer el status register
    flashSendByte(FLASH_CMD_RDSR);

    uint8_t status;
    do {
        // Enviar byte dummy para generar el clock mientras esperamos
        status= flashSendByte(FLASH_DUMMY_BYTE);
    } while((status & FLASH_WIP_FLAG) == SET);

    flashDeselect();
}


void flashSetup()
{
    if(setupDone)
        return;

    // Activar AFIO clock, necesario para setear MAPR
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    // Remapping de los pines de SPI1 a PB3..PB5 (NSS en PA15 no se usa)
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SPI1, ENABLE);

    // Activar clocks para SPI y GPIOB
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_SPI1, ENABLE);

    GPIO_InitTypeDef gpioConfig;
    gpioConfig.GPIO_Speed= GPIO_Speed_50MHz;
    // Config pin SCK: PB3
    gpioConfig.GPIO_Pin= GPIO_Pin_3;
    gpioConfig.GPIO_Mode= GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &gpioConfig);
    // Config pin MOSI: PB5
    gpioConfig.GPIO_Pin= GPIO_Pin_5;
    gpioConfig.GPIO_Mode= GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &gpioConfig);
    // Config pin MISO: PB4
    gpioConfig.GPIO_Pin= GPIO_Pin_4;
    gpioConfig.GPIO_Mode= GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &gpioConfig);

    // Config pin CS: PB6
    gpioConfig.GPIO_Pin= GPIO_Pin_6;
    gpioConfig.GPIO_Mode= GPIO_Mode_Out_PP;
    GPIO_Init(GPIOB, &gpioConfig);

    // Deseleccionar el chip
    flashDeselect();

    // SPI Config
    SPI_InitTypeDef spiConfig;
    spiConfig.SPI_Direction= SPI_Direction_2Lines_FullDuplex;
    spiConfig.SPI_Mode= SPI_Mode_Master;
    spiConfig.SPI_DataSize= SPI_DataSize_8b;
    spiConfig.SPI_CPOL= SPI_CPOL_Low; // Mode 0: CPOL=0, CPHA=0
    spiConfig.SPI_CPHA= SPI_CPHA_1Edge;
    spiConfig.SPI_NSS= SPI_NSS_Soft;
    spiConfig.SPI_BaudRatePrescaler= SPI_BaudRatePrescaler_2; // 24/2= 12Mhz
    spiConfig.SPI_FirstBit= SPI_FirstBit_MSB;
    spiConfig.SPI_CRCPolynomial= 7;
    SPI_Init(SPI1, &spiConfig);
    SPI_Cmd(SPI1, ENABLE);

    setupDone= true;
}

uint32_t flashGetID()
{
    flashSelect();

    flashSendByte(FLASH_CMD_RDID);

    uint32_t id= 0;
    id |= flashReadByte() << 16;
    id |= flashReadByte() << 8;
    id |= flashReadByte() << 0;

    flashDeselect();
    return id;
}

void flashEraseAll()
{
    flashWriteEnable();

    flashSelect();
    flashSendByte(FLASH_CMD_BE);
    flashDeselect();

    flashWaitWriteEnd();
}

void flashWritePage(uint8_t* data, uint16_t len, uint32_t addr)
{
    flashWriteEnable();
    flashSelect();

    // Instruccion "page program" (write)
    flashSendByte(FLASH_CMD_WRITE);
    // Enviar los 24-bits de addr
    flashSendByte((addr & 0xFF0000) >> 16);
    flashSendByte((addr & 0x00FF00) >> 8);
    flashSendByte((addr & 0x0000FF) >> 0);
    // Escribir datos
    while(len--) {
        flashSendByte(*data);
        data++;
    }

    flashDeselect();
    flashWaitWriteEnd();
}

void flashReadBuffer(uint8_t* data, uint16_t len, uint32_t addr)
{
    flashSelect();

    flashSendByte(FLASH_CMD_READ);
    // Enviar los 24-bits de addr
    flashSendByte((addr & 0xFFFFFF) >> 16);
    flashSendByte((addr & 0x00FF00) >> 8);
    flashSendByte((addr & 0x0000FF) >> 0);
    // Leer datos
    while(len--) {
        *data= flashReadByte();
        data++;
    }

    flashDeselect();
}



void flashProgramMode()
{
    STM32vldiscovery_LEDInit(LED3);
    STM32vldiscovery_LEDInit(LED4);

    STM32vldiscovery_LEDOn(LED3);
    STM32vldiscovery_LEDOn(LED4);

    // Leer cantidad de paginas a programar
    uint16_t usedPages;
    _read_r(0, 0, &usedPages, 2);
    // Borrar toda la memoria (necesario para escribir despues)
    flashEraseAll();
    // Responder la misma cantidad de paginas, cuando ya haya
    // terminado de borrar la mem porque empieza enseguida
    _write_r(0, 0, &usedPages, 2);

    STM32vldiscovery_LEDOn(LED3);
    STM32vldiscovery_LEDOff(LED4);

    uint16_t index= 0;
    uint8_t pageBuffer[FLASH_PAGE_SIZE];
    uint32_t checksum;

    while(index != 0xFFFF) {
        // Leer indice de pagina
        _read_r(0, 0, &index, 2);
        if(index == 0xFFFF)
            continue;
        // Leer datos de la pagina
        _read_r(0, 0, pageBuffer, FLASH_PAGE_SIZE);
        // Escribir la pagina a flash
        flashWritePage(pageBuffer, FLASH_PAGE_SIZE, index * FLASH_PAGE_SIZE);
        // Calcular y enviar adler32 checksum
        checksum= adler32(pageBuffer, FLASH_PAGE_SIZE);
        _write_r(0, 0, &checksum, 4);

        STM32vldiscovery_LEDToggle(LED3);
        STM32vldiscovery_LEDToggle(LED4);
    }
    STM32vldiscovery_LEDOn(LED3);
    STM32vldiscovery_LEDOn(LED4);
}

uint32_t flashFullChecksum()
{
    uint8_t pageBuffer[FLASH_PAGE_SIZE];

    uint32_t sum= 0;
    for(int16_t i= 0; i<FLASH_PAGE_COUNT; i++) {
        flashReadBuffer(pageBuffer, FLASH_PAGE_SIZE, i * FLASH_PAGE_SIZE);
        sum += adler32(pageBuffer, FLASH_PAGE_SIZE);
    }

    return sum;
}

bool flashTest()
{
    return flashGetID()==FLASH_ID_W25Q80BV;
}
