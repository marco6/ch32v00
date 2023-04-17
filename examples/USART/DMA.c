/**
 * USART DMA, master/slave mode transceiver routine:
 * USART1_Tx(PD5)\USART1_Rx(PD6).
 *
 * This routine demonstrates that two boards use DMA to send and receive.
 * After successful sending and receiving, PD0 is connected to LED,
 * and the LED light flashes.
 *
 * Hardware connection:
 *  PD5 -- PD6
 *  PD6 -- PD5
 *  PDO -- LED
 */

#include <ch32v00x/debug.h>
#include <ch32v00x/dma.h>
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
 * Initializes the USART1peripheral.
 */
void USARTx_CFG(void) {
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};

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

    DMA_Cmd(DMA1_Channel4, ENABLE); /* USART1 Tx */
    DMA_Cmd(DMA1_Channel5, ENABLE); /* USART1 Rx */

    USART_Cmd(USART1, ENABLE);
}

/**
 * Configures the DMA for USART1.
 *
 * FIXME this is called just like `DMA_Init` - that's why they 
 * couldn't call it DMA_Init and they had to break the convention...
 */
void DMA_INIT(void) {
    DMA_InitTypeDef DMA_InitStructure = {0};
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(DMA1_Channel4);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DATAR);
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)TxBuffer1;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = TxSize1;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel4, &DMA_InitStructure);

    DMA_DeInit(DMA1_Channel5);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DATAR);
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RxBuffer1;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = TxSize1;
    DMA_Init(DMA1_Channel5, &DMA_InitStructure);
}

int main(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    GPIO_Toggle_INIT();
    DMA_INIT();
    USARTx_CFG(); /* USART1 */
    USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
    Delay_Ms(1000);
    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
    // Wait until USART1 TX DMA1 Transfer Complete
    while(DMA_GetFlagStatus(DMA1_FLAG_TC4) == RESET) { }
    // Wait until USART1 RX DMA1 Transfer Complete
    while(DMA_GetFlagStatus(DMA1_FLAG_TC5) == RESET) { }

    int diff = memcmp(TxBuffer1, RxBuffer1, TxSize1);
    if (!diff) {
        for (uint8_t i = Bit_SET; ; i = (i == Bit_SET) ? Bit_RESET : Bit_SET) {
            GPIO_WriteBit(GPIOD, GPIO_Pin_0, i);
            Delay_Ms(250);
        }
    } else {
        GPIO_ResetBits(GPIOD, GPIO_Pin_0);
        while(1) { } // FIXME outro
    }
}
