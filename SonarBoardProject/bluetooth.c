#include "bluetooth.h"
#include "timer.h"

#include "audioplayer.h" // TODO sacar, usado en la interrupcion del boton

// Variables y configuracion para interactuar con comandos AT
static enum { atLineLen= 16 };
static char atLine[atLineLen]; // Linea finalizada
static uint8_t atLinePos;
// Bluetooth
static bt_state btState;

// Arreglo de MACs de dispositivos encontrados en a busqueda, como strings
static enum { addrLen= 12 }; // 00:00:00:00:00 (sin puntos)
static enum { maxDevsFound= 5 };
static uint8_t devsFound;
static uint8_t devIndex; // Indice del headset en devAddrs
static char devsAddrs[maxDevsFound][addrLen+1]; // Considerar \0 al final

//
// Configuracion
//

void btSetup()
{
    // Inicializar variables de AT
    atLine[0]= 0;
    atLinePos= 0;
    // Inicializar variables de Bluetooth
    btState= BT_DISCONNECTED;
    devsFound= 0;
    devIndex= 0;

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

    // Interrupcion de datos entrantes por USART
    NVIC_InitTypeDef nvicConfig;
    nvicConfig.NVIC_IRQChannel= USART3_IRQn;
    nvicConfig.NVIC_IRQChannelPreemptionPriority= 0;
    nvicConfig.NVIC_IRQChannelSubPriority= 2;
    nvicConfig.NVIC_IRQChannelCmd= ENABLE;
    NVIC_Init(&nvicConfig);
    // Por defecto esta deshabilitada
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

    btState= BT_DISCONNECTED;
    // VERIFICAR MODULO
    if(!btTest()) {
        printf("BT Modulo no encontrado.\r\n");
        return false;
    }

    SB_LedSet(SB_LedY, true);

    atWrite("ATI\r", 4);
    if(!atReadLine(cmd, cmdLen, 1000)) {
        printf("BT El modulo no respodio a ATI.\r\n");
        SB_LedSet(SB_LedY, false);
        return false;
    }
    printf("BT Modulo encontrado: '%s'.\r\n", cmd);

    printf("BT Reiniciando modulo.\r\n");
    atWrite("ATZ\r", 4);
    if(!atReadOK(5000)) {
        printf("BT Error al reiniciar modulo.\r\n");
        SB_LedSet(SB_LedY, true);
        return false;
    }

    // En este estado podriamos configurar el modulo, pero ya deberian estar todas
    // las configuraciones de config_bt.txt hechas y almacenadas con AT&W; ATZ

    // Deshabilitamos la interrup. de USART3 durante la configuracion porque vamos
    // a leer datos con busy-wait
    USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);

    // QUERY
    SB_LedBlinkPeriod(SB_LedY, 1000);
    printf("BT Buscando headsets.\r\n");

    const uint8_t queryRetries= 2;
    uint8_t queryTries= 0;
    while(!devsFound && queryTries < queryRetries) {
        sprintf(cmd, "AT+BTI%s\r", BT_DEVLCASS_STR);
        atWrite(cmd, strlen(cmd));
        if(!atReadMACs(5000)) { // Doy un tiempo de espera mayor al programado en ATS517
            printf("BT Error al leer MACs.");
            SB_LedSet(SB_LedY, false);
            return false;
        }
        if(!devsFound)
            printf("BT No encontre headsets, probando de nuevo.\r\n");
        queryTries++;
    }
    if(!devsFound) {
        printf("BT No se encontro ningun headset.\r\n");
        SB_LedSet(SB_LedY, false);
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
        SB_LedSet(SB_LedY, false);
        return false;
    }
    sleep(200);

    // Iniciar pairing
    SB_LedBlinkPeriod(SB_LedY, 200);
    printf("BT Empezando pairing.\r\n");

    const uint8_t pairRetries= 3;
    uint8_t pairTries= 0;
    bool pairOk= false;
    while(!pairOk && pairTries < pairRetries) {
		sprintf(cmd, "AT+BTW%s\r", devsAddrs[devIndex]);
		atWrite(cmd, strlen(cmd));
		if(!atReadOK(1000)) {
			printf("BT Error, no llego el OK de AT+BTW.\r\n");
			SB_LedSet(SB_LedY, false);
			return false;
		}
		// Esperar algo como "PAIR 0 001A0EE5081D 00" por 8 segundos
		if(!atReadLine(cmd, cmdLen, 8000) || strncmp("PAIR ", cmd, 5) || cmd[5]!='0') {
			printf("BT Error de pairing, recibi linea '%s'.\r\n", cmd);
			pairOk= false;
		} else {
			pairOk= true;
		}
    }
    if(!pairOk) {
    	SB_LedSet(SB_LedY, false);
    	printf("BT Error de pairing.\r\n");
    	return false;
    }
    printf("BT Pairing OK.\r\n");
    sleep(200);

    // CONNECTION
    SB_LedBlinkPeriod(SB_LedY, 50);
    printf("BT Empezando conexion.\r\n");

    const uint8_t connRetries= 5;
    uint8_t connTries= 0;
    bool connOk= false;
    while(!connOk && connTries < connRetries) {
		sprintf(cmd, "AT+HSGD%s\r", devsAddrs[devIndex]);
		atWrite(cmd, strlen(cmd));
		if(!atReadLine(cmd, cmdLen, 8000) || strncmp("CONNECT ", cmd, 8)) {
			printf("BT Error de conexion, recibi linea '%s'.\r\n", cmd);
			connOk= false;
		} else {
			connOk= true;
		}
    }
    if(!connOk) {
		printf("BT Error de conexion.\r\n");
		SB_LedSet(SB_LedY, false);
		return false;
    }
    SB_LedBlinkPeriod(SB_LedY, 700);
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
        SB_LedSet(SB_LedY, true);
        printf("BT Playing.\r\n");
    // HSG"AU0"
    } else if(!strncmp("HSG\"AU0", atLine, 7)) {
        btState= BT_CONNECTED;
        SB_LedBlinkPeriod(SB_LedY, 700);
        printf("BT Stopped.\r\n");
    // NO CARRIER 1112
    } else if(!strncmp("NO CARR", atLine, 7)) {
        SB_LedSet(SB_LedY, false);
        btState= BT_DISCONNECTED;
        printf("BT Disconnected.\r\n");
    }
}

//
// Configuracion persistente del modulo bluetooth
//

// Configuracion persistente del modulo bluetooth
void btSetupModule()
{
	if(!btTest()) {
		printf("Modulo no encontrado.\r\n");
		return;
	} else {
		printf("Configurando modulo.\r\n");
	}

	// Mirar doc/config_btm.txt
	atWrite("ATE0\r", 5);
	atReadOK(300);
	atWrite("AT+BTN=\"Sonar\"\r", 15);
	atReadOK(300);
	atWrite("ATS515=$20020C\r", 15);
	atReadOK(300);
	atWrite("ATS517=4\r", 9);
	atReadOK(300);
	atWrite("ATS518=5\r", 9);
	atReadOK(300);
	atWrite("ATS321=3\r", 9);
	atReadOK(300);
	atWrite("ATS102=$8\r", 10);
	atReadOK(300);
	atWrite("ATS590=2\r", 9);
	atReadOK(300);
	atWrite("ATS415=0\r", 9);
	atReadOK(300);
	atWrite("ATS345=0\r", 9);
	atReadOK(300);
	atWrite("AT&W\r", 5);
	atReadOK(500);

	printf("Reiniciando...\r\n");
	atWrite("ATZ\r", 4);
	atReadOK(5000);

	printf("Listo.\r\n");
}

bt_state btGetState()
{
	return btState;
}
