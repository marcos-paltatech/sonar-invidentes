#include "stm32f10x_it.h"
#include <stdio.h>

#include "audioplayer.h"

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
    printf("Hard Fault exception.\r\n");
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
    printf("Mem Manage exception.\r\n");
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
    printf("Bus Fault exception.\r\n");
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
    printf("Usage Fault exception.\r\n");
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

// Interrupcion que se ejecuta cuando el DMA1 Channel 3 termina
// de transmitir los datos en memoria.
// Cuando pasa esto empezamos el DMA de otro buffer ya cargado,
// y cargamos el que se utilizo. Asi siempre hay un buffer listo para
// transmitir.
void DMA1_Channel3_IRQHandler()
{
    if(DMA_GetITStatus(DMA1_IT_TC3) == RESET)
        return;

    playerDMATransfer();

    DMA_ClearITPendingBit(DMA1_IT_TC3);
    //printf("DMA %d\r\n", pcmBufferIndex);
}

// Interrupcion del TIM6 al DAC
// Esta interrupcion es la que le indica al DAC que tiene que pedirle
// datos al engine DMA, y se ejecuta una vez por sample de audio.
void TIM6_DAC_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
    return;
}
