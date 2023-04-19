/**
 * USART interrupt routine:
 *  USART1_Tx(PD5)\USART1_Rx(PD6).
 *
 * This routine demonstrates that two boards use query to send and interrupt to
 * receive. After successful sending and receiving, PD0 is connected to LED,
 * and the LED light flashes.
 *
 * Hardware connection:
 *  PD5 -- PD6
 *  PD6 -- PD5
 *  PD0 -- LED
 */

#include <ch32v00x/gpio.h>
#include <ch32v00x/nvic.h>
#include <ch32v00x/rcc.h>
#include <ch32v00x/usart.h>
#include <string.h>

#define size(a)    (sizeof(a) / sizeof(*(a)))
#define TxSize1    (size(TxBuffer1))

uint8_t TxBuffer1[] = "*Buffer1 Send from USART1 using Interrupt!";
uint8_t RxBuffer1[TxSize1] = {0};

volatile uint8_t TxCnt1 = 0, RxCnt1 = 0;
volatile uint8_t Rxfinish1 = 0;

/**
 * Initializes GPIOA.0
 */
void GPIO_Toggle_INIT(void) {
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_SetBits(GPIOD, GPIO_Pin_0);
}

/**
 * Initializes the USART2 & USART3 peripheral.
 */
void USARTx_CFG(void) {
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};
    NVIC_InitTypeDef  NVIC_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1, ENABLE);

    /* USART1 TX-->D.5   RX-->D.6 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStructure);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);;

    USART_Cmd(USART1, ENABLE);
}

int main(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    GPIO_Toggle_INIT();
    USARTx_CFG();
    Delay_Ms(1000);

    while (TxCnt1 < TxSize1) {
        Delay_Ms(50);
        
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) { }
        USART_SendData(USART1, TxBuffer1[TxCnt1++]);
    }

    Delay_Ms(100);

    while (!Rxfinish1) { }

    int diff = memcmp(TxBuffer1, RxBuffer1, TxSize1);

    if (!diff) {
        for (uint8_t i = Bit_SET; ; i = (i == Bit_SET) ? Bit_RESET : Bit_SET) {
            GPIO_WriteBit(GPIOD, GPIO_Pin_0, i);
            Delay_Ms(250);
        }
    } else {
        GPIO_ResetBits(GPIOD, GPIO_Pin_0);
    }

    while (1) { } // FIXME outro
}

void USART1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void USART1_IRQHandler(void) {
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
        RxBuffer1[RxCnt1++] = USART_ReceiveData(USART1);

        if(RxCnt1 == TxSize1) {
            USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
            Rxfinish1 = 1;
        }
    }
}
