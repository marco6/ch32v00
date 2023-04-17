/**
 * Single wire half duplex mode, master/slave mode transceiver routine:
 *  Master:USART1_Tx(PD5)
 *
 * This routine demonstrates the data transmission and reception of two boards in
 * single-wire half-duplex mode. After successful transmission and reception, PD0 is
 * connected to the LED, and the LED light flashes.
 *
 * Hardware connection:
 *  PD5 -- PD5
 *  PDO -- LED
 */
 
#include <ch32v00x/debug.h>
#include <ch32v00x/gpio.h>
#include <ch32v00x/misc.h>
#include <ch32v00x/rcc.h>
#include <ch32v00x/usart.h>

#include <string.h>

#define size(a)    (sizeof(a) / sizeof(*(a)))
#define TxSize1    (size(TxBuffer1))

uint8_t TxBuffer1[] = "*Buffer1 Send from USART1 using DMA!";
uint8_t RxBuffer1[TxSize1] = {0};
uint8_t TxCnt1 = 0, RxCnt1 = 0;
uint8_t Rxfinish1 = 0;

/* USART Mode Definition */
#define USART_HOST_MODE 0
#define USART_SLAVE_MODE 1

/* USART Communication Mode Selection */
#if defined(HOST_MODE)
# define USART_MODE   USART_HOST_MODE
#elif defined(SLAVE_MODE)
# define USART_MODE   USART_SLAVE_MODE
#else
# error Please define either HOST_MODE or SLAVE_MODE macros to select the behavior.
#endif

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
 * Initializes the USART1 peripheral.
 */
void USARTx_CFG(void) {
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);

    USART_HalfDuplexCmd(USART1, ENABLE);
}

int main(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    GPIO_Toggle_INIT();

    USARTx_CFG();
    Delay_Ms(1000);

#if (USART_MODE == USART_HOST_MODE)
    while (TxCnt1 < TxSize1) {
        Delay_Ms(50);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) { }
        USART_SendData(USART1, TxBuffer1[TxCnt1++]);
    }

    while (RxCnt1 < TxSize1) {
        while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET) { }
        RxBuffer1[RxCnt1++] = USART_ReceiveData(USART1);
    }
#elif (USART_MODE == USART_SLAVE_MODE)
    while (RxCnt1 < TxSize1) {
        while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET) { }
        RxBuffer1[RxCnt1++] = USART_ReceiveData(USART1);
    }

    while (TxCnt1 < TxSize1) {
        Delay_Ms(50);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) { }
        USART_SendData(USART1, TxBuffer1[TxCnt1++]);
    }
#endif

    int diff = memcmp(TxBuffer1, RxBuffer1, TxSize1);
    if (!diff) {
        for (uint8_t i = Bit_SET; ; i = (i == Bit_SET) ? Bit_RESET : Bit_SET) {
            GPIO_WriteBit(GPIOD, GPIO_Pin_0, i);
            Delay_Ms(250);
        }
    } else {
        GPIO_ResetBits(GPIOD, GPIO_Pin_0);
    }

    while(1) { } // FIXME outro
}
