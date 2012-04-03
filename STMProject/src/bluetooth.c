#include "bluetooth.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <STM32vldiscovery.h> // Usado para el pushbutton
#include "audioplayer.h" // Para la interrupcion

// Variables y configuracion para interactuar con comandos AT
static const int atLineLen= 16;
static char* atLine; // Linea finalizada
static int atLinePos;
// Bluetooth
static bt_state btState;

// Arreglo de MACs de dispositivos encontrados en a busqueda, como strings
static const uint8_t addrLen= 12; // 00:00:00:00:00 (sin puntos)
static const uint8_t maxDevsFound= 5;
static uint8_t devsFound;
static uint8_t devIndex; // Indice del headset en devAddrs
static char** devsAddrs;

//
// Configuracion
//

void setupBluetooth()
{
    // Inicializar variables de AT
    atLine= (char*)malloc(atLineLen);
    atLine[0]= 0;
    atLinePos= 0;
    // Inicializar variables de Bluetooth
    btState= BT_NONE;
    devsFound= 0;
    devIndex= 0;
    // Alloc de la tabla de dispositivos encontrados
    devsAddrs= (char**)malloc(sizeof(char*) * maxDevsFound);
    for(uint8_t i=0; i<maxDevsFound; i++)
        devsAddrs[i]= (char*)malloc(addrLen+1); // Considerar \0 al final

    // Activar clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE );
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    // Remapping de USART3 a PC10/PC11
    GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);

    GPIO_InitTypeDef configTx;
    configTx.GPIO_Pin = GPIO_Pin_10; // PC10
    configTx.GPIO_Mode = GPIO_Mode_AF_PP;
    configTx.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &configTx);

    GPIO_InitTypeDef configRx;
    configRx.GPIO_Pin = GPIO_Pin_11; // PC11
    configRx.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    configRx.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOC, &configRx);

    USART_InitTypeDef configUSART;
    configUSART.USART_BaudRate = 9600;
    configUSART.USART_WordLength = USART_WordLength_8b;
    configUSART.USART_StopBits = USART_StopBits_1;
    configUSART.USART_Parity = USART_Parity_No;
    configUSART.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    configUSART.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &configUSART);
    USART_Cmd(USART3, ENABLE);

    // Interrupcion de datos entrantes por USART !! ver prioridad
    NVIC_InitTypeDef nvicConfig;
    nvicConfig.NVIC_IRQChannel= USART3_IRQn;
    nvicConfig.NVIC_IRQChannelPreemptionPriority= 0;
    nvicConfig.NVIC_IRQChannelSubPriority= 1;
    nvicConfig.NVIC_IRQChannelCmd= ENABLE;
    NVIC_Init(&nvicConfig);
    // Por defecto esta deshabilitada

    STM32vldiscovery_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);
}

//
// Funciones de I/O por USART3
//

static inline
void atPutChar(char c)
{
    waitWhile(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
    USART_SendData(USART3, c);
}

static inline
char atGetChar()
{
    waitWhile(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);
    return USART_ReceiveData(USART3);
}

static void atWrite(const char* data, uint16_t len)
{
    for(uint16_t i=0; i<len; i++)
        atPutChar(data[i]);
}

// Espera OK por hasta timeout msecs. Ignora todos los datos extra que lleguen mientra espera
// Devuelve true si llega OK.
static bool atReadOK(int timeout)
{
    uint32_t finish= getMsecs() + timeout;
    bool gotOK= false;
    char c= 0;
    char cLast= 0;

    // Loop de caracteres hasta no recibir OK, considerando timeout
    while(!gotOK && getMsecs()<finish) {
        waitWhile(USART_GetFlagStatus(USART3, USART_FLAG_RXNE)==RESET && getMsecs()<finish);
        cLast= c;
        c= USART_ReceiveData(USART3); // Si hubo timeout vamos a recibir el ultimo char
        gotOK= cLast=='O' && c=='K';
    }

    return gotOK;
}

// Lee direcciones MACs hasta recibir un OK, sin timeout
// Las va almacenando en devsAddrs e incrementando devsFound
// Devuelve false si hubo algun error con las MACs
static bool atReadMACs(int timeout)
{
    bool gotOK= false;
    bool error= false;
    devsFound= 0;
    uint8_t macOffset= 0;
    char c= 0;
    char cLast= 0;

    while(!gotOK && !error) {
        cLast= c;
        c= atGetChar();

        // Si es un char hex valido almacenarlo
        if((c>='0' && c<='9') || (c>='A' && c<='F')) {
            devsAddrs[devsFound][macOffset]= c;
            macOffset++;
        // Si no ex char hex fijarse que sea parte de OK o \r\n, sino tirar error
        } else if(c!='O' && c!='K' && c!='\r' && c!='\n') {
            error= true;
            printf("BT Char invalido %d.\r\n", c);
        }

        // Si almacenamos un MAC entero pasar al siguiente
        if(macOffset==addrLen) {
            devsAddrs[devsFound][macOffset]= 0; // Fin de linea para cada MAC
            macOffset= 0;
            devsFound++;
            error= devsFound==maxDevsFound;
            if(error) printf("BT Llegaron mas MACs de las esperadas.\r\n");
        }
        gotOK= cLast=='O' && c=='K';
    }
    return !error;
}

// Lee una linea ignorando los caracteres \r\n de prefijo, con timeout msecs
// devuelve true si no hubo errores
static bool atReadLine(char* buf, int maxLen, int timeout)
{
    uint32_t finish= getMsecs() + timeout;
    bool gotEndline= false;
    bool error= false;
    char c= 0;
    char cLast= 0;
    uint16_t len= 0;

    // Loop de caracteres hasta no recibir OK, considerando timeout
    while(!gotEndline && !error && getMsecs()<finish) {
        waitWhile(USART_GetFlagStatus(USART3, USART_FLAG_RXNE)==RESET && getMsecs()<finish);
        cLast= c;
        c= USART_ReceiveData(USART3); // Si hubo timeout vamos a recibir el ultimo char
        // Ignorar \r y \n al principio de la linea
        if(!len && (c=='\r' || c=='\n'))
            continue;

        if(len==maxLen) {
            buf[maxLen-1]= 0;
            error= true;
            printf("BT Linea muy larga.\r\n");
            continue;
        }
        buf[len]= c;

        len++;
        gotEndline= cLast=='\r' && c=='\n';
    }
    if(gotEndline && !error) {
        buf[len-2]= 0; // Si esta todo bien sacar el \r\n del final
        return true;
    } else {
        buf[0]= 0; // Sino devuelvo un string vacio
        return false;
    }
}

//
// Self testing
//
bool btTest()
{
    atWrite("AT\r", 3);
    return atReadOK(2000);
}

//
// Conexion
//

bool btConnect()
{
    // Buffer para comandos y multiproposito
    const uint8_t cmdLen= 50;
    char cmd[cmdLen];

    // VERIFICAR MODULO
    btState= BT_NONE;
    if(!btTest()) {
        printf("BT Modulo no encontrado.\r\n");
        return false;
    }

    atWrite("ATI\r", 4);
    if(!atReadLine(cmd, cmdLen, 1000)) {
        printf("BT El modulo no respodio a ATI.\r\n");
        return false;
    }
    printf("BT Modulo encontrado: '%s'.\r\n", cmd);

    printf("BT Reiniciando modulo.\r\n");
    atWrite("ATZ\r", 4);
    if(!atReadOK(5000)) {
        printf("BT Error al reiniciar modulo.\r\n");
        return false;
    }

    btState= BT_DISCONNECTED;
    // En este estado podriamos configurar el modulo, pero ya deberian estar todas
    // las configuraciones de config_bt.txt hechas y almacenadas con AT&W; ATZ

    // Deshabilitamos la interrup. de USART3 durante la configuracion porque vamos
    // a leer datos con busy-wait
    USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);

    // QUERY
    ledBlueSetPeriod(1000);
    printf("BT Buscando headsets.\r\n");

    const uint8_t queryRetries= 5;
    uint8_t queryTries= 0;
    while(!devsFound && queryTries < queryRetries) {
        sprintf(cmd, "AT+BTI%s\r", BT_DEVLCASS_STR);
        atWrite(cmd, strlen(cmd));
        if(!atReadMACs(5000)) { // Doy un tiempo de espera mayor al programado en ATS517
            printf("BT Error al leer MACs.");
            ledBlueSet(false);
            return false;
        }
        if(!devsFound)
            printf("BT No encontre headsets, probando de nuevo.\r\n");
        queryTries++;
    }
    if(!devsFound) {
        printf("BT No se encontro ningun headset.\r\n");
        ledBlueSet(false);
        return false;
    }

    // Intentar encontrar al headset prefereido, sino usar el primero
    devIndex= 0;
    for(uint8_t i=0; i<devsFound; i++) {
        if(!strcmp(devsAddrs[i], BT_PREF_MAC)) {
            devIndex= i;
            break;
        }
    }
    printf("BT Headsets encontrados:\r\n");
    for(uint8_t i=0; i<devsFound; i++)
        printf("BT   - %s%s\r\n", devsAddrs[i], i==devIndex ? " <- Elegido" : "");

    // PAIRING
    // Setear pin por defecto 0000
    sprintf(cmd, "AT+BTK=\"%s\"\r", BT_DEFAULT_PIN);
    atWrite(cmd, strlen(cmd));
    if(!atReadOK(1000)) {
        printf("BT Error configurando PIN.\r\n");
        ledBlueSet(false);
        return false;
    }
    sleep(200);

    // Iniciar pairing
    ledBlueSetPeriod(200);
    printf("BT Empezando pairing.\r\n");
    sprintf(cmd, "AT+BTW%s\r", devsAddrs[devIndex]);
    atWrite(cmd, strlen(cmd));
    if(!atReadOK(1000)) {
        printf("BT Error, no llego el OK de AT+BTW.\r\n");
        ledBlueSet(false);
        return false;
    }
    // Esperar algo como "PAIR 0 001A0EE5081D 00" por 8 segundos
    if(!atReadLine(cmd, cmdLen, 8000) || strncmp("PAIR ", cmd, 5) || cmd[5]!='0') {
        printf("BT Error de pairing, recibi linea '%s'.\r\n", cmd);
        ledBlueSet(false);
        return false;
    }
    printf("BT Pairing OK.\r\n");
    sleep(500);

    // CONNECTION
    ledBlueSetPeriod(50);
    printf("BT Empezando conexion.\r\n");
    sprintf(cmd, "AT+HSGD%s\r", devsAddrs[devIndex]);
    atWrite(cmd, strlen(cmd));
    if(!atReadLine(cmd, cmdLen, 8000) || strncmp("CONNECT ", cmd, 8)) {
        printf("BT Error de conexion, recibi linea '%s'.\r\n", cmd);
        ledBlueSet(false);
        return false;
    }
    ledBlueSetPeriod(700);
    printf("BT Conexion OK.\r\n");
    btState= BT_CONNECTED;

    // Habilito interrupciones para recibir mensajes HSG"AU1"/HSG"AU0"
    // una vez que se llame btStartPlaying
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

    return true;
}

void btStartPlaying()
{
    if(btState != BT_CONNECTED) {
        printf("BT btStartPlaying: Estado no conectado.\r\n");
        return;
    }
    btState= BT_STARTEDPLAY;
    atWrite("AT+HSGA\r", 8);
    // Cuando el usuario "atienda la llamada" la interrupcion va a recibir HSG"AU1"
}

void btStopPlaying()
{
    if(btState != BT_PLAYING) {
        printf("BT btStopPlaying: No estoy reproduciendo.\r\n");
        return;
    }
    atWrite("AT+HSGR\r", 8);
    // La interrupcion deberia recibir HSG"AU0"
}

// Interrupcion de caracter entrante via USART3
// Vamos almacenando los chars de una linea en un buffer y vemos que hacer
void USART3_IRQHandler(void)
{
    if(USART_GetITStatus(USART3, USART_IT_RXNE) == RESET)
        return;
    char c= USART_ReceiveData(USART3); // Esta funcion tambien marca la interrupcion como atendida

    if((c == '\n' && atLinePos != 0) || atLinePos+1==atLineLen) {
        // Es el fin de una linea, o nos quedamos sin buffer
        atLine[atLinePos]= 0;
        // Aca podriamos hacer algo con toda la linea, pero deberia ser rapido
        atLinePos= 0;
    } else if(c!='\r' && c!='\n') {
        // Si no, ir agregando caracteres en el buffer ignorando \r y \n
        atLine[atLinePos]= c;
        atLinePos++;
    }

    // Usamos los primeros 7 chars para ver que hacer
    if(atLinePos != 7)
        return;

    // HSG"AU1"
    if(!strncmp("HSG\"AU1", atLine, 7)) {
        btState= BT_PLAYING;
        ledBlueSet(true);
        printf("BT Playing.\r\n");
    // HSG"AU0"
    } else if(!strncmp("HSG\"AU0", atLine, 7)) {
        btState= BT_CONNECTED;
        ledBlueSetPeriod(700);
        printf("BT Stopped.\r\n");
    // NO CARRIER 1112
    } else if(!strncmp("NO CARR", atLine, 7)) {
        ledBlueSet(false);
        btState= BT_DISCONNECTED;
        printf("BT Disconnected.\r\n");
    }
}

//
// Manejo del boton
//
void EXTI0_IRQHandler(void)
{
    if(!STM32vldiscovery_PBGetState(BUTTON_USER))
        return;

	static int trackId= 0;
	playerPlayTrack(trackId);
	trackId= (trackId+1) % 7;

    EXTI_ClearITPendingBit(USER_BUTTON_EXTI_LINE);
}
