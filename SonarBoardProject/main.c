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

int main(void)
{
	// Configuracion general de la placa
	SB_Setup();
    // System timer, usado por varios modulos
    setupTimer();
    // UART stdin/stdout
    setupRetarget();
    // Memoria Flash
    flashSetup();
    // Bluetooth
    setupBluetooth();

    for(int i=0; i<20; i++) printf("\r\n");
    printf("SonarBoard                                                              v0.4\r\n");
    printf("--------------------------------------------------------------------------------\r\n\r\n");
    printf("Type ? for help.\r\n\r\n");

    bool quit= false;
    while(!quit) {
        cmd_type cmd= readCmd();

        switch(cmd) {
        case CMD_SELFTEST:
            printf(" - Modulo Bluetooth: "); fflush(0);
            printf("%s\r\n", btTest() ? "OK" : "ERROR");
            printf(" - Memoria Flash: "); fflush(0);
            printf("%s\r\n", flashTest() ? "OK" : "ERROR");
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
        case CMD_FLASHMEM:
            printf("Entrando en modo para programar memoria flash...");
            flashProgramMode();
            break;
        case CMD_MEMCHECK:
            printf("Calculando checksum total de memoria...\r\n");
            printf("Checksum: 0x%08X\r\n", flashFullChecksum());
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
