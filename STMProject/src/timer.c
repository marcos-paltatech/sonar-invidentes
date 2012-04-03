#include "timer.h"

#include "STM32vldiscovery.h"

#define TIMER_FREQ  100 // 10ms
static uint32_t msecs;

#define LEDYELLOW   LED3
#define LEDBLUE     LED4

static uint16_t bluePeriod; // 0==Off, 0xFFFF=On
static uint32_t blueLastToggle;
static uint16_t yellowPeriod; // 0==Off, 0xFFFF=On
static uint32_t yellowLastToggle;

void setupTimer()
{
    msecs= 0;

    // Obtener frecuencia
    RCC_ClocksTypeDef clocks;
    RCC_GetClocksFreq(&clocks);
    uint32_t sysClock= clocks.SYSCLK_Frequency;

    STM32vldiscovery_LEDInit(LEDBLUE);
    STM32vldiscovery_LEDInit(LEDYELLOW);
    bluePeriod= 0;
    yellowPeriod= 0;
    blueLastToggle= 0;
    yellowLastToggle= 0;

    // Iniciar systimer
    SysTick_Config(sysClock/TIMER_FREQ);
}

// Interrupcion
void SysTick_Handler(void)
{
    // Actualizar el timer
    msecs += 1000/TIMER_FREQ;

    // Blinking de leds
    if(bluePeriod && bluePeriod!=0xFFFF && msecs-blueLastToggle>=bluePeriod) {
        STM32vldiscovery_LEDToggle(LEDBLUE);
        blueLastToggle= msecs;
    }
    if(yellowPeriod && yellowPeriod!=0xFFFF && msecs-yellowLastToggle>=yellowPeriod) {
        STM32vldiscovery_LEDToggle(LEDBLUE);
        yellowLastToggle= msecs;
    }
}

uint32_t getMsecs()
{
    return msecs;
}

void sleep(uint32_t msecs)
{
    uint32_t stopTime= getMsecs() + msecs;
    waitWhile(getMsecs() < stopTime);
}

//
// Funciones para manejar LEDs
//

void ledBlueSet(bool on)
{
    if(on) {
        bluePeriod= 0xFFFF;
        STM32vldiscovery_LEDOn(LEDBLUE);
    } else {
        bluePeriod= 0x0000;
        STM32vldiscovery_LEDOff(LEDBLUE);
    }
}

void ledBlueSetPeriod(uint16_t period)
{
    bluePeriod= period;
}

void yellowBlueSet(bool on)
{
    if(on) {
        yellowPeriod= 0xFFFF;
        STM32vldiscovery_LEDOn(LEDYELLOW);
    } else {
        yellowPeriod= 0x0000;
        STM32vldiscovery_LEDOff(LEDYELLOW);
    }
}

void ledYellowSetPeriod(uint16_t period)
{
    yellowPeriod= period;
}

