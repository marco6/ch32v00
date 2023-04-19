/**
 * SPI DMA, master/slave mode transceiver routine:
 *  Master:PI1_SCK(PC5)\PI1_MISO(PC7)\PI1_MOSI(PC6).
 *  Slave:PI1_SCK(PC5)\PI1_MISO(PC7)\PI1_MOSI(PC6).
 *
 * This example demonstrates simultaneous full-duplex transmission and reception
 * between Master and Slave.
 * 
 * Note: The two boards download the Master and Slave programs respectively,
 * and power on at the same time.
 *
 * Hardware connection:
 *  PC5 -- PC5
 *  PC6 -- PC6
 *  PC7 -- PC7
 */

#include <ch32v00x/dma.h>
#include <ch32v00x/gpio.h>
#include <ch32v00x/rcc.h>
#include <ch32v00x/spi.h>
#include <ch32v00x/usart.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* SPI Mode Definition */
#define SPI_HOST_MODE 0
#define SPI_SLAVE_MODE 1

/* SPI Communication Mode Selection */
#if defined(HOST_MODE)
# define SPI_MODE   SPI_HOST_MODE
#elif defined(SLAVE_MODE)
# define SPI_MODE   SPI_SLAVE_MODE
#else
# error Please define either HOST_MODE or SLAVE_MODE macros to select the behavior.
#endif 

#define Size          18

static uint16_t TxData[Size] = {
    0x0101, 0x0202, 0x0303, 0x0404, 0x0505, 0x0606,
    0x1111, 0x1212, 0x1313, 0x1414, 0x1515, 0x1616,
    0x2121, 0x2222, 0x2323, 0x2424, 0x2525, 0x2626
};
static uint16_t RxData[Size];

/**
 * Configuring the SPI for full-duplex communication.
 */
void SPI_FullDuplex_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    SPI_InitTypeDef  SPI_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_SPI1, ENABLE);

#if (SPI_MODE == SPI_HOST_MODE)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#elif (SPI_MODE == SPI_SLAVE_MODE)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;

#if (SPI_MODE == SPI_HOST_MODE)
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
#elif (SPI_MODE == SPI_SLAVE_MODE)
    SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
#endif

    SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);
    SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Rx, ENABLE);

    SPI_Cmd(SPI1, ENABLE);
}

/**
 * Initializes the DMAy Channelx configuration.
 *
 * @param channel DMA channel among the DMA_CHx macros where x can be 
 * 1 to 7.
 * @param ppadr Peripheral base address.
 * @param memadr Memory base address.
 * @param bufsize DMA channel buffer size.
 */
void DMA_Tx_Init(DMA_Channel_TypeDef *channel, uint32_t ppadr, uint32_t memadr, uint16_t bufsize) {
    DMA_InitTypeDef DMA_InitStructure = {0};

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(channel);

    DMA_InitStructure.DMA_PeripheralBaseAddr = ppadr;
    DMA_InitStructure.DMA_MemoryBaseAddr = memadr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = bufsize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(channel, &DMA_InitStructure);
}

/**
 * Initializes the SPI1 DMA Channelx configuration.
 *
 * @param channel DMA channel among the DMA_CHx macros where x can be 
 * 1 to 7.
 * @param ppadr Peripheral base address.
 * @param memadr Memory base address.
 * @param bufsize DMA channel buffer size.
 */
void DMA_Rx_Init(DMA_Channel_TypeDef *channel, uint32_t ppadr, uint32_t memadr, uint16_t bufsize) {
    DMA_InitTypeDef DMA_InitStructure = {0};

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(channel);

    DMA_InitStructure.DMA_PeripheralBaseAddr = ppadr;
    DMA_InitStructure.DMA_MemoryBaseAddr = memadr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = bufsize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(channel, &DMA_InitStructure);
}

int main(void) {
    USART_Printf_Init(460800);
    printf("SystemClk:%"PRIu32"\n", SystemCoreClock);

    SPI_FullDuplex_Init();

#if (SPI_MODE == SPI_SLAVE_MODE)
    printf("Slave Mode\n");
    Delay_Ms(1000);
#elif (SPI_MODE == SPI_HOST_MODE)
    printf("Host Mode\n");
    Delay_Ms(2000);
#endif

    DMA_Tx_Init(DMA1_Channel3, (uint32_t)&SPI1->DATAR, (uint32_t)TxData, Size);
    DMA_Rx_Init(DMA1_Channel2, (uint32_t)&SPI1->DATAR, (uint32_t)RxData, Size);
    DMA_Cmd(DMA1_Channel3, ENABLE);
    DMA_Cmd(DMA1_Channel2, ENABLE);

    while (1) {
        while ((!DMA_GetFlagStatus(DMA1_FLAG_TC2)) && (!DMA_GetFlagStatus(DMA1_FLAG_TC3))) { }

        for (uint8_t i = 0; i < Size; i++) {
            printf(" RxData:%04x\n", RxData[i]);
        }

        while(1) { } // FIXME outro
    }
}
