
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "STM32vldiscovery.h"
#include "stm32f10x.h"

#include "global.h"
#include "io_retarget.h"
#include "spi_flash.h"
#include "audioplayer.h"

#define TRACKS_COUNT  7
const uint16_t TRACKS_PAGES[] = {
       0,  // Track Index  0: "Track0.raw"
     152,  // Track Index  1: "Track1.raw"
     403,  // Track Index  2: "Track2.raw"
     606,  // Track Index  3: "Track3.raw"
    1004,  // Track Index  4: "Track4.raw"
    1263,  // Track Index  5: "Track5.raw"
    1591,  // Track Index  6: "Track6.raw"
    1722,  // Not a track, used to calculate the last track's size
};

int main(void)
{
    STM32vldiscovery_LEDInit(LED3);
    STM32vldiscovery_LEDInit(LED4);

    STM32vldiscovery_LEDOn(LED3);
    STM32vldiscovery_LEDOff(LED4);

    // USART stdin/stdout
    setupRetargetUSART1();
    // Memoria Flash
    flashSetupSPI();

    for(int i=0; i<20; i++) printf("\r\n");
    printf("-----------------------------------------------------------------------\r\n");
    printf("Proyecto de prueba STM32\r\n\r\n");

    bool quit= false;
    while(!quit) {
        char c;
        _read_r(0, 0, &c, 1);

        STM32vldiscovery_LEDToggle(LED3);
        STM32vldiscovery_LEDToggle(LED4);

        switch(c) {
        case 'q':
            printf("Saliendo, bye!\r\n");
            quit= true;
            break;
        case 'i':
            printf("ID de la memoria flash:\r\n  0x%06X\r\n", flashGetID());
            break;
        case 'w':
            printf("Entrando en modo para programar la flash\r\n");
            flashProgramMode();
            quit= true;
            break;
        case 'c':
            printf("Full memory checksum:\r\n");
            printf("  0x%08X\r\n", flashFullChecksum());
            break;
        case 'p':
            for(int i=0; i<20; i++) printf("\r\n");
            printf("Select track:\r\n");
            for(int i=0; i<TRACKS_COUNT; i++) {
                const uint16_t start= TRACKS_PAGES[i];
                const uint16_t len= TRACKS_PAGES[i+1]-TRACKS_PAGES[i];
                printf("  - Track %2d | Start %3d, Length %3d.\r\n", i, start, len);
            }
            int8_t track;
            do {
                _read_r(0, 0, &c, 1);
                track= c - '0';
            } while(track < 0 || track >= TRACKS_COUNT);
            playerPlay(TRACKS_PAGES[track], TRACKS_PAGES[track+1]-TRACKS_PAGES[track]);
            break;
        case 'a':
            printf("Playing all tracks.\r\n");
            const uint16_t len= TRACKS_PAGES[TRACKS_COUNT]-1;
            playerPlay(0, len);
            break;
        case 's':
            printf("Stopping...\r\n");
            playerStop();
            break;
        default:
            printf("Char '%c' = 0x%02X\r\n", c, c);
            break;
        }
    }

    STM32vldiscovery_LEDOn(LED4);
    STM32vldiscovery_LEDOn(LED3);
}
