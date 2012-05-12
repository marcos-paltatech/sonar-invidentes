#ifndef TIMER_H
#define TIMER_H

#include "sonarboard.h"

//
// System timer
// Provee funciones de sleep, timing, etc.
// Tambien maneja los LEDs de la placa.
//

// Busywait de una condicion, con timeout en milisegundos
#define waitForCondTimout(cond, timeout) { \
    uint32_t mt=getMsecs()+(timeout); \
    while(!(cond) && getMsecs()<mt); }

void timerSetup();

// Cantidad de milisegundos desde que inicio el programa
uint32_t getMsecs();

// Sleep con busy-wait
void sleep(uint32_t msecs);

// Interupcion del systimer
void SysTick_Handler(void);

//
// Funciones para manejar LEDs
//
void SB_LedSet(SB_Led led, bool value);
void SB_LedBlinkPeriod(SB_Led led, uint16_t period);
void SB_LedToggle(SB_Led led);
// Prende y apaga todos los leds
void SB_LedTest();

#endif
