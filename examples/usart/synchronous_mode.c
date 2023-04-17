/**
 * Synchronous mode routine:
 *  Master:USART1_CK(PD4)\USART1_Tx(PD5)\USART1_Rx(PD6).
 *  Slave:SPI1_SCK(PC5)\SPI1_MISO(PC7)\SPI1_MOSI(PC6).
 *
 * This example demonstrates using USART1 as the master and SPI1 as the slave, sending 
 * and receiving data in full-duplex mode, and connecting the LED to PD0 after successful 
 * sending and receiving, and it will blink.
 *
 * UART1-LSB  SPI1-MSB
 *
 * Hardware connection:
 *  PD4 --PC5
 *  PD5--PC6
 *  PD6--PC7
 *  PDO--LED
 */

#include <ch32v00x/debug.h>
#include <ch32v00x/gpio.h>
#include <ch32v00x/misc.h>
#include <ch32v00x/rcc.h>
#include <ch32v00x/spi.h>
#include <ch32v00x/usart.h>

#include <string.h>

#define size(a)    (sizeof(a) / sizeof(*(a)))
#define TxSize1    (size(TxBuffer1))
#define TxSize2    (size(TxBuffer2))

uint8_t TxBuffer1[] = { 0x01, 0x02, 0x03, 0x04, 0x05 }; // Send by UART1
uint8_t TxBuffer2[] = { 0x01, 0x02, 0x03, 0x04, 0x05 }; // Send by SPI1
uint8_t pbuf[] = { 0x80, 0x40, 0xC0, 0x20, 0xA0 };
uint8_t RxBuffer1[TxSize2] = { 0 }; // USART1 Using
uint8_t RxBuffer2[TxSize1] = { 0 }; // SPI1 Using

uint8_t TxCnt1 = 0, RxCnt1 = 0;
uint8_t TxCnt2 = 0, RxCnt2 = 0;
uint8_t Tempdata = 0x00;

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
 * Re-initializes the USART1 peripheral.
 */
void USART1_ReCFG(void) {
    GPIO_InitTypeDef       GPIO_InitStructure = { 0 };
    USART_InitTypeDef      USART_InitStructure = { 0 };
    USART_ClockInitTypeDef USART_ClockInitStructure = { 0 };

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1, ENABLE);

    /* USART1  Ck-->D.4   TX-->D.5   RX-->D.6 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_ClockInitStructure.USART_Clock = USART_Clock_Enable;
    USART_ClockInitStructure.USART_CPOL = USART_CPOL_High;         /* Clock is active High */
    USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;        /* Data is captured on the second edge */
    USART_ClockInitStructure.USART_LastBit = USART_LastBit_Enable;
    USART_ClockInit(USART1, &USART_ClockInitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_Init(USART1, &USART_InitStructure);

    USART_Cmd(USART1, ENABLE);
}

/**
 * Initializes the SPI1 to be Slave Mode.
 */
void SPI1_INIT(void) {
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    SPI_InitTypeDef  SPI_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_SPI1, ENABLE);
    SPI_StructInit(&SPI_InitStructure);
    SPI_I2S_DeInit(SPI1);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; /* SPI1 MISO-->PC.7 */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6; /* SPI1 SCK-->PC.5 MOSI-->PC.6 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_Init(SPI1, &SPI_InitStructure);

    SPI_Cmd(SPI1, ENABLE);
}

int main(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    Delay_Ms(1000);
    GPIO_Toggle_INIT();
    USART1_ReCFG(); /* USART1 ReInitializes */
    SPI1_INIT();

    while(TxCnt1 < TxSize1) {
        USART_SendData(USART1, TxBuffer1[TxCnt1++]);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) { }
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET) { }
        RxBuffer2[RxCnt2++] = SPI_I2S_ReceiveData(SPI1);
    }

    USART_ReceiveData(USART1); // Clear the USART1 Data Register
    while(TxCnt2 < TxSize2) { // SPI1--->USART1
        while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) { }

        SPI_I2S_SendData(SPI1, TxBuffer2[TxCnt2++]);
        USART_SendData(USART1, Tempdata); /* Send Tempdata for SCK */
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) { }
        while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET) { }

        RxBuffer1[RxCnt1++] = USART_ReceiveData(USART1);
    }

    int diff1 = memcmp(pbuf, RxBuffer2, TxSize1);
    int diff2 = memcmp(pbuf, RxBuffer1, TxSize2);

    if (!diff1 && !diff2) {
        for (uint8_t i = Bit_SET; ; i = (i == Bit_SET) ? Bit_RESET : Bit_SET) {
            GPIO_WriteBit(GPIOD, GPIO_Pin_0, i);
            Delay_Ms(250);
        }
    } else {
        GPIO_ResetBits(GPIOD, GPIO_Pin_0);
    }

    while(1) { } // FIXME outro
}
