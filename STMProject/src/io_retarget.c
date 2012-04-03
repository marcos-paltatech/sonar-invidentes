#include "io_retarget.h"

#include <stdio.h>

void setupRetargetUSART1()
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitTypeDef configTx;
    configTx.GPIO_Pin = GPIO_Pin_9; // PA9
    configTx.GPIO_Mode = GPIO_Mode_AF_PP;
    configTx.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &configTx);

    GPIO_InitTypeDef configRx;
    configRx.GPIO_Pin = GPIO_Pin_10; // PA10
    configRx.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    configRx.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &configRx);

    USART_InitTypeDef configUSART;
    configUSART.USART_BaudRate = 115200;
    configUSART.USART_WordLength = USART_WordLength_8b;
    configUSART.USART_StopBits = USART_StopBits_1;
    configUSART.USART_Parity = USART_Parity_No;
    configUSART.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    configUSART.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &configUSART);
    USART_Cmd(USART1, ENABLE);
}


int _write_r(void *reent, uint16_t fd, const char *ptr, uint32_t len)
{
    for(uint32_t i=0; i<len; i++) {
        // Wait for the USART to be ready
        waitWhile(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        USART_SendData(USART1, (char)(*ptr++));
    }
    return len;
}

int _read_r (void *reent, uint16_t fd, char *ptr, uint32_t len)
{
    for(uint32_t i=0; i<len; i++) {
        waitWhile(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
        *ptr= USART_ReceiveData(USART1);
        ptr++;
    }
    return len;
}

int readLine(char *ptr, uint16_t len)
{
    bool endLine= false;
    uint16_t i= 0;
    do {
        // Leer
        waitWhile(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
        ptr[i]= USART_ReceiveData(USART1);
        // Echo
        waitWhile(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
        USART_SendData(USART1, ptr[i]);

        if(ptr[i]==127) {
            i= MAX(i-1, 0);
        } else {
            endLine= ptr[i]=='\r';
            i++;
        }
    } while(i < len && !endLine);

    // Fin de linea
    waitWhile(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    USART_SendData(USART1, '\n');

    const uint16_t readLen= i<len ? i : len-1;
    // Setear fin de linea
    if(i < len)
        ptr[readLen-1]= 0; // Eliminar el \r
    else
        ptr[readLen]= 0;

    return readLen;
}
