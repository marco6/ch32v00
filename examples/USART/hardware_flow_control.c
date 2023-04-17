/**
 * Hardware flow control mode, master/slave mode, transceiver routine:
 * USART1_Tx(PD5)\USART1_Rx(PD6)\USART1_CTS(PD3)\USART1_RTS(PC2)
 * 
 * This example demonstrates UART1 hardware flow control data sending and receiving,
 * connect the UART1 Tx and Rx pins to the serial port tool respectively,View through
 * the host computer tool, CTS is connected to VCC, and data cannot be sent, but
 * connected to GND, data can be sent normally.
 */

#include <ch32v00x/debug.h>
#include <ch32v00x/gpio.h>
#include <ch32v00x/misc.h>
#include <ch32v00x/rcc.h>
#include <ch32v00x/usart.h>

#include <stdio.h>

#define size(a)    (sizeof(a) / sizeof(*(a)))
#define TxSize     (size(TxBuffer))

uint8_t TxBuffer[] = 
"USART1 Hardware Flow Control Example: USART1-\
Hyperterminal communication using hardware flow control\n";
uint8_t RxBuffer[TxSize] = {0};
uint8_t TxCnt = 0, RxCnt = 0;

/**
 * Reinitialize the USART1.
 */
void USART1_ReCFG(void) {
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOC | RCC_APB2Periph_USART1, ENABLE);

    /* USART1 TX-->D.5   RX-->D.6 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; /* RTS-->C.2 */
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; /* CTS-->D.3 */
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}

int main(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART1_ReCFG();

    printf("USART1 Hardware Flow Control TEST\n");

    while (TxCnt < TxSize) {
        USART_SendData(USART1, TxBuffer[TxCnt++]);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) { }
    }

    do {
        if ((USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET) && (RxCnt < TxSize)) {
            RxBuffer[RxCnt] = USART_ReceiveData(USART1);
            USART_SendData(USART1, RxBuffer[RxCnt++]); /* send it when receive a byte */
        }
    } while((RxBuffer[RxCnt - 1] != '\n') && (RxCnt != TxSize));

    while (1) { } // FIXME outro
}
