#ifndef SONARBOARD_H
#define SONARBOARD_H

// Header del MCU
#include "STM32f10x.h"
// Modulos usados
#include "stm32f10x_dac.h"
#include "stm32f10x_adc.h"
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
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//
// General setup
//
void SB_Setup();

// Bateria
//
// Devuelve los mv de la bateria
uint16_t SB_GetBatteryLevel();

// Leds
#define SB_LedGPIO	GPIOC
typedef enum {
	SB_LedG= GPIO_Pin_9, // Green led
	SB_LedY= GPIO_Pin_8, // Yellow led
	SB_LedR= GPIO_Pin_7, // Red led
} SB_Led;
// Funciones para setear los sensores en timer.c

// Buttons
#define SB_ButtonGPIO	GPIOA
typedef enum {
	SB_Button1= GPIO_Pin_0
} SB_Button;
// Implement "void EXTI0_IRQHandler()" to process button events
bool SB_ButtonState(SB_Button button); // Devuelve true si esta apretado

#endif
