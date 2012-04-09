#ifndef TIMER_H
#define TIMER_H

#include "global.h"
#include "stm32f10x.h"

//
// System timer
// Provee funciones de sleep, timing, etc.
// Tambien maneja los LEDs de la placa.
//

// Busywait de una condicion, con timeout en milisegundos
#define waitForCondTimout(cond, timeout) { \
    uint32_t mt=getMsecs()+(timeout); \
    while(!(cond) && getMsecs()<mt); }

void setupTimer();

// Cantidad de milisegundos desde que inicio el programa
uint32_t getMsecs();

// Sleep con busy-wait
void sleep(uint32_t msecs);

// Interupcion del systimer
void SysTick_Handler(void);

//
// Funciones para manejar LEDs
//

void ledBlueSet(bool on);
void ledBlueSetPeriod(uint16_t period);

void ledGreenSet(bool on);
void ledGreenSetPeriod(uint16_t period);

#endif
