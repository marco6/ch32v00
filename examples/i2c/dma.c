/**
 * I2C DMA, master/slave mode transceiver routine:
 * I2C1_SCL(PC2)\I2C1_SDA(PC1).
 * This example demonstrates the 7-bit address mode, Master sends via DMA,
 * and Slave receives via DMA.
 *
 * Note: The two boards download the Master and Slave programs respectively,
 * and power on at the same time.
 *
 * Hardware connection:
 *  PC2 -- PC2
 *  PC1 -- PC1
 */

#include <ch32v00x/debug.h>
#include <ch32v00x/dma.h>
#include <ch32v00x/i2c.h>
#include <ch32v00x/gpio.h>
#include <ch32v00x/misc.h>
#include <ch32v00x/rcc.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

/* I2C Mode Definition */
#define I2C_HOST_MODE 0
#define I2C_SLAVE_MODE 1

/* I2C Communication Mode Selection */
#if defined(HOST_MODE)
# define I2C_MODE   I2C_HOST_MODE
#elif defined(SLAVE_MODE)
# define I2C_MODE   I2C_SLAVE_MODE
#else
# error Please define either HOST_MODE or SLAVE_MODE macros to select the behavior.
#endif

#define Size   6
#define Tize   6
#define RXAdderss   0x02
#define TxAdderss   0x02

uint8_t TxData[Size] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };
uint8_t RxData[5][Size];

/**
 * Initializes the IIC peripheral.
 */
void IIC_Init(uint32_t bound, uint16_t address) {
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
    I2C_InitTypeDef I2C_InitTSturcture = { 0 };

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    I2C_InitTSturcture.I2C_ClockSpeed = bound;
    I2C_InitTSturcture.I2C_Mode = I2C_Mode_I2C;
    I2C_InitTSturcture.I2C_DutyCycle = I2C_DutyCycle_16_9;
    I2C_InitTSturcture.I2C_OwnAddress1 = address;
    I2C_InitTSturcture.I2C_Ack = I2C_Ack_Enable;
    I2C_InitTSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C1, &I2C_InitTSturcture);

    I2C_DMACmd(I2C1, ENABLE);
    I2C_Cmd(I2C1, ENABLE);

#if (I2C_MODE == I2C_HOST_MODE)
    I2C_AcknowledgeConfig(I2C1, ENABLE);
#endif
}

/**
 * Initializes the SPI1 DMAy Channelx configuration.
 *
 * @param channel DMA channel among DMAx_Channely where X (1) is the 
 * DMA controller and y is the DMA channel (1-7).
 * @param ppadr Peripheral base address.
 * @param memadr Memory base address.
 * @param bufsize DMA channel buffer size.
 */
void DMA_Tx_Init(DMA_Channel_TypeDef *channel, uint32_t ppadr, uint32_t memadr, uint16_t bufsize) {
    DMA_InitTypeDef DMA_InitStructure = { 0 };
    NVIC_InitTypeDef NVIC_InitStructure = { 0 };

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(channel);

    DMA_InitStructure.DMA_PeripheralBaseAddr = ppadr;
    DMA_InitStructure.DMA_MemoryBaseAddr = memadr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = bufsize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(channel, &DMA_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    DMA_ITConfig(DMA1_Channel6, DMA_IT_TC, ENABLE);
}

/**
 * Initializes the I2C1 DMAy Channelx configuration.
 *
 * @param channel DMA channel among DMAx_Channely where X (1) is the 
 * DMA controller and y is the DMA channel (1-7).
 * @param ppadr Peripheral base address.
 * @param memadr Memory base address.
 * @param bufsize DMA channel buffer size.
 */
void DMA_Rx_Init(DMA_Channel_TypeDef *channel, uint32_t ppadr, uint32_t memadr, uint16_t bufsize) {
    DMA_InitTypeDef DMA_InitStructure = { 0 };

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    DMA_DeInit(channel);

    DMA_InitStructure.DMA_PeripheralBaseAddr = ppadr;
    DMA_InitStructure.DMA_MemoryBaseAddr = memadr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = bufsize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(channel, &DMA_InitStructure);
}

int main(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    Delay_Init();
    USART_Printf_Init(460800);
    printf("SystemClk:%"PRIu32"\n",SystemCoreClock);

#if (I2C_MODE == I2C_HOST_MODE)
    printf("IIC Host mode\n");
    IIC_Init(80000, TxAdderss);

    for (uint8_t j = 0; j < 5; j++) {
        DMA_Tx_Init(DMA1_Channel6, (uint32_t)&I2C1->DATAR, (uint32_t)TxData, Tize);
        while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) != RESET) { }
        
        I2C_GenerateSTART(I2C1, ENABLE);
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) { }

        I2C_Send7bitAddress(I2C1, 0x02, I2C_Direction_Transmitter);
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) { }

        DMA_Cmd(DMA1_Channel6, ENABLE);
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) { }

        I2C_GenerateSTOP(I2C1, ENABLE);
        Delay_Ms(1000);
	} 

#elif (I2C_MODE == SLAVE_MODE)

    printf("IIC Slave mode\n");
    IIC_Init(80000, RXAdderss);

	for (uint8_t t = 0; t < 5; t++) {
        DMA_Rx_Init(DMA1_Channel7, (uint32_t)&I2C1->DATAR, (uint32_t)&RxData[t][0], Tize);
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED)) { }
        
        DMA_Cmd(DMA1_Channel7, ENABLE);
        while((!DMA_GetFlagStatus(DMA1_FLAG_TC7))) { }

        printf("RxData:\n");

        for(uint8_t i = 0; i < 6; i++) {
            printf("%02x ", RxData[t][i]);
            RxData[t][i] = 0;
        }

        printf("\n");
	}
#endif

    while(1) { } // FIXME outro
}

void DMA1_Channel6_IRQHandler() {
    if(DMA_GetITStatus(DMA1_IT_TC6) != RESET) {
        DMA_Cmd(DMA1_Channel6, DISABLE);
        DMA_ClearITPendingBit(DMA1_IT_TC6);
    }
}
