#ifndef TIMER_H
#define TIMER_H

#include "global.h"
#include "stm32f10x.h"

// Busywait de una condicion, con timeout en milisegundos
#define waitForCondTimout(cond, timeout) { \
    uint32_t mt=getMsecs()+(timeout); \
    while(!(cond) && getMsecs()<mt); }

void setupTimer();

// Cantidad de milisegundos desde que inicio el programa
uint32_t getMsecs();

// Sleep con busy-wait
void sleep(uint32_t msecs);

void SysTick_Handler(void);

#endif
