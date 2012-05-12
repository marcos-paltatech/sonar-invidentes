#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "sonarboard.h"

#include "timer.h"
#include "io_retarget.h"
#include "spi_flash.h"
#include "audioplayer.h"
#include "bluetooth.h"
#include "cli.h"

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

int main(void)
{
	// Configuracion general de la placa
	SB_Setup();
    // UART stdin/stdout
    retargetSetup();
    // System timer, usado por varios modulos
    timerSetup();
    // Memoria Flash
    flashSetup();
    // Bluetooth
    btSetup();

    for(int i=0; i<20; i++) printf("\r\n");
    printf("SonarBoard                                                              v0.4\r\n");
    printf("--------------------------------------------------------------------------------\r\n\r\n");
    printf("Type ? for help.\r\n\r\n");

    bool quit= false;
    while(!quit) {
        cmd_type cmd= readCmd();

        switch(cmd) {
        case CMD_SELFTEST:
        	selfTest(false);
            break;
        case CMD_PLAY:
            playerPlayTrack(0xFF);
            break;
        case CMD_BTCONNECT: {
            uint32_t startTime= getMsecs();
            if(!btConnect())
                printf("Error al conectarse por Bluetooth.\r\n");
            else
                printf("Conexion exitosa en %.1f segs.\r\n", (getMsecs()-startTime)/1000.0f);
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
        	printf("Nivel de la bateria: %d mV.\r\n", SB_GetBatteryLevel());
        	break;
        case CMD_QUIT:
            printf("Bye.\r\n\r\n");
            quit= true;
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
