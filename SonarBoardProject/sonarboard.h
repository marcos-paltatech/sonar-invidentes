#ifndef SONARBOARD_H
#define SONARBOARD_H

// Header del MCU
#include "STM32f10x.h"
// Modulos usados
#include "stm32f10x_dac.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
#include "misc.h"
// Global defines
#include "global.h"
// Global includes
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

//
// General setup
//
void SB_Setup();

// Leds
typedef enum {
	SB_LedG= GPIO_Pin_7, // Green led
	SB_LedY= GPIO_Pin_8, // Yellow led
	SB_LedR= GPIO_Pin_9, // Red led
} SB_Led;
void SB_LedSet(SB_Led led, bool value);
void SB_LedToggle(SB_Led led);

// Buttons
typedef enum {
	SB_Button1= GPIO_Pin_0
};
// Implement "void EXTI0_IRQHandler()" to process button events

#endif
