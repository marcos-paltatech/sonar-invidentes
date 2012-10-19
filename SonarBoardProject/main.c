#include "sonarboard.h"

#include "timer.h"
#include "io_retarget.h"
#include "spi_flash.h"
#include "audioplayer.h"
#include "bluetooth.h"
#include "cli.h"
#include "distances.h"
#include "srf02_sensor.h"

//
// Auto-prueba de la placa
//
bool selfTest(bool silent)
{
	if(!silent)
		printf(" - Modulo Bluetooth: "); fflush(0);
	bool btOK= btTest();
	if(!silent) {
		printf("%s\r\n", btOK ? "OK" : "ERROR");
		printf(" - Memoria Flash: "); fflush(0);
	}
	bool flashOK= flashTest();
	if(!silent) {
		printf("%s\r\n", flashOK ? "OK" : "ERROR");
		printf(" - Leds\r\n");
	}
    SB_LedTest();

    return btOK && flashOK;
}

bool globalSetup()
{
	SB_LedBlinkPeriod(SB_LedG, 1000);
}

// Interrupcion del boton
void EXTI0_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line0);

	static bool lastPushed= false;
	static uint32_t lastTime= 0;
	uint32_t startTime= getMsecs();
	bool pushed= SB_ButtonState(SB_Button1);

	// Reiniciar si se mantiene el boton por 5 segundos y se suelta
	if(!pushed && getMsecs()-lastTime>5000) {
		NVIC_SystemReset();
		return;
	}

	if(!pushed && btGetState()==BT_DISCONNECTED) {
		SB_LedSet(SB_LedR, false);
		if(btConnect())
			btStartPlaying();
		else
			SB_LedBlinkPeriod(SB_LedR, 100);
	}

	if(pushed && btGetState()==BT_PLAYING) {
		// modo one-shot
		distStartMeasuring(true);
	}

	if(!pushed && btGetState()==BT_PLAYING && getMsecs()-lastTime>2000) {
		// modo continuo
		distStartMeasuring(false);
	}

/*
	static int trackId= 0;
	if(pushed && btGetState()==BT_PLAYING) {
		playerPlayTrack(trackId);
		trackId= (trackId+1) % 24;
	}
*/
	lastPushed= pushed;
	lastTime= startTime;
}

int main(void)
{
	// Configuracion general de la placa, configura tambien al system timer
	SB_Setup();
    // UART stdin/stdout
    retargetSetup();
    // Memoria Flash
    flashSetup();
    // Bluetooth
    btSetup();
    // Sensores
    //srf02_setup();
    // Medicion de distancias
    distSetup();

    for(int i=0; i<20; i++) printf("\r\n");
    printf("SonarBoard   4:24                                                           v0.4\r\n");
    printf("--------------------------------------------------------------------------------\r\n\r\n");
    printf("Usar ? para ayuda.......\r\n\r\n");

    // Configuracion del dispositivo para dejarlo listo en forma autonoma
    globalSetup();

    bool quit= false;
    while(!quit) {
        cmd_type cmd= readCmd();

        uint8_t hablado[10];
        switch(cmd) {
        case CMD_SELFTEST:
        	selfTest(false);
            break;
        case CMD_PLAY:
        	printf ("PLAY\r\n");

        	playerPlayTracks(hablado, 7);
            //playerPlayTrack(0xFF);
            break;
        case CMD_SENSORS:
        	distStartMeasuring(true);
        	break;
        case CMD_BTCONNECT: {
            uint32_t startTime= getMsecs();
            if(!btConnect()) {
                printf("Error al conectarse por Bluetooth.\r\n");
            } else {
                printf("Conexion exitosa en %d segs.\r\n", (getMsecs()-startTime)/1000);
                btStartPlaying();
            }
            break; }
        case CMD_BTCALL:
            btStartPlaying();
            break;
        case CMD_BTHANG:
            btStopPlaying();
            break;
        case CMD_BTCONFIG:
        	btSetupModule();
        	break;
        case CMD_FLASHMEM:
            printf("Entrando en modo para programar memoria flash...");
            flashProgramMode();
            break;
        case CMD_MEMCHECK:
            printf("Calculando checksum total de memoria...\r\n");
            printf("Checksum: 0x%08X\r\n", flashFullChecksum());
            break;
        case CMD_BATTLEVEL:
        	printf("Nivel de la bateria: %d mV\r\n", SB_GetBatteryLevel());
        	break;
        case CMD_RESET:
        	NVIC_SystemReset();
        	break;
        case CMD_HELP:
            cmdHelp();
            break;
        case CMD_EMPTY:
            break;
        case CMD_INVALID:
        default:
            printf("Comando invalido.\r\n\r\n");
            break;
        }
    }
}
