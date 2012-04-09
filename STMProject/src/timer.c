#include "timer.h"

#include "STM32vldiscovery.h"

#define TIMER_FREQ  100 // 10ms
static uint32_t msecs;

#define LEDGREEN   LED3
#define LEDBLUE     LED4

static uint16_t bluePeriod; // 0==Off, 0xFFFF=On
static uint32_t blueLastToggle;
static uint16_t greenPeriod; // 0==Off, 0xFFFF=On
static uint32_t greenLastToggle;

void setupTimer()
{
    msecs= 0;

    // Obtener frecuencia
    RCC_ClocksTypeDef clocks;
    RCC_GetClocksFreq(&clocks);
    uint32_t sysClock= clocks.SYSCLK_Frequency;

    STM32vldiscovery_LEDInit(LEDBLUE);
    STM32vldiscovery_LEDInit(LEDGREEN);
    bluePeriod= 0;
    greenPeriod= 0;
    blueLastToggle= 0;
    greenLastToggle= 0;

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
    if(greenPeriod && greenPeriod!=0xFFFF && msecs-greenLastToggle>=greenPeriod) {
        STM32vldiscovery_LEDToggle(LEDBLUE);
        greenLastToggle= msecs;
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

void ledGreenSet(bool on)
{
    if(on) {
        greenPeriod= 0xFFFF;
        STM32vldiscovery_LEDOn(LEDGREEN);
    } else {
        greenPeriod= 0x0000;
        STM32vldiscovery_LEDOff(LEDGREEN);
    }
}

void ledGreenSetPeriod(uint16_t period)
{
    greenPeriod= period;
}

