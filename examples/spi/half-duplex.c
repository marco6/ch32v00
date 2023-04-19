/**
 * Single wire half duplex mode, master/slave mode, data transceiver:
 *  Master:SPI1_SCK(PC5)\SPI1_MOSI(PC6).
 *  Slave:SPI1_SCK(PC5)\SPI1_MISO(PC7).
 *
 * This routine demonstrates that Master sends and Slave receives.
 * 
 * Note: The two boards download the Master and Slave programs respectively,
 * and power on at the same time.
 * 
 * Hardware connection:
 *  PC5 -- PC5
 *  PC7-- PC6
 */

#include <ch32v00x/gpio.h>
#include <ch32v00x/nvic.h>
#include <ch32v00x/rcc.h>
#include <ch32v00x/spi.h>
#include <ch32v00x/usart.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

volatile uint8_t Txval = 0, Rxval = 0;

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

#define Size 18

uint16_t TxData[Size] = {
    0x0101, 0x0202, 0x0303, 0x0404, 0x0505, 0x0606,
    0x1111, 0x1212, 0x1313, 0x1414, 0x1515, 0x1616,
    0x2121, 0x2222, 0x2323, 0x2424, 0x2525, 0x2626
};

uint16_t RxData[Size];

/**
 * Configuring the SPI for half-duplex communication.
 */
void SPI_1Lines_HalfDuplex_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
    SPI_InitTypeDef SPI_InitStructure = { 0 };
    NVIC_InitTypeDef NVIC_InitStructure = { 0 };

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_SPI1, ENABLE);

#if (SPI_MODE == SPI_HOST_MODE)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
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
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
#endif


#if (SPI_MODE == SPI_HOST_MODE)
    SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
#elif (SPI_MODE == SPI_SLAVE_MODE)
    SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Rx;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
#endif

    SPI_InitStructure.SPI_DataSize = SPI_DataSize_16b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

#if (SPI_MODE == SPI_SLAVE_MODE)
    SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);
#endif

    SPI_Cmd(SPI1, ENABLE);
}

int main(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    USART_Printf_Init(115200);
    printf("SystemClk:%"PRIu32"\n",SystemCoreClock);

#if (SPI_MODE == SPI_SLAVE_MODE)
    printf("SLAVE Mode\n");
    Delay_Ms(1000);
#endif

    SPI_1Lines_HalfDuplex_Init();

#if (SPI_MODE == SPI_HOST_MODE)
    printf("HOST Mode\n");
    Delay_Ms(2000);
    SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_TXE , ENABLE);
#endif

    while(1) {

#if (SPI_MODE == SPI_HOST_MODE)
        while (Txval < 18) { }

        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) != RESET) {
            if (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == RESET) {
                SPI_Cmd(SPI1, DISABLE);
                while(1) { } // FIXME outro
            }
        }
#elif (SPI_MODE == SPI_SLAVE_MODE)
        while (Rxval < 18) { }

        for (uint8_t i = 0; i < 18; i++) {
            printf("Rxdata:%04x\n", RxData[i]);
        }

        while(1) { }
#endif
    }
}

void SPI1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void SPI1_IRQHandler(void) {

#if (SPI_MODE == SPI_HOST_MODE)
    if (SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_TXE) != RESET) {
        SPI_I2S_SendData(SPI1, TxData[Txval++]);
        if(Txval == 18) {
            SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_TXE, DISABLE);
        }
    }
#elif (SPI_MODE == SPI_SLAVE_MODE)
    RxData[Rxval++] = SPI_I2S_ReceiveData(SPI1);
#endif
}
