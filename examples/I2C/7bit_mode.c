/*
 * 7-bit addressing mode, master/slave mode, transceiver routine:
 * I2C1_SCL(PC2)\I2C1_SDA(PC1).
 * This routine demonstrates that Master sends and Slave receives.
 *
 * Note: The two boards download the Master and Slave programs respectively,
 * and power on at the same time.
 *
 * Hardware connection:
 *  PC2 -- PC2
 *  PC1 -- PC1
 */

#include <ch32v00x/debug.h>
#include <ch32v00x/i2c.h>
#include <ch32v00x/gpio.h>
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

    I2C_Cmd(I2C1, ENABLE);

#if (I2C_MODE == I2C_HOST_MODE)
    I2C_AcknowledgeConfig(I2C1, ENABLE);
#endif
}

int main(void) {
    Delay_Init();
    USART_Printf_Init(460800);
    printf("SystemClk:%"PRIu32"\n",SystemCoreClock);

#if (I2C_MODE == I2C_HOST_MODE)
    printf("IIC Host mode\n");
    IIC_Init( 80000, TxAdderss);

	for (uint8_t j = 0; j < 5; j++) {
        while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) != RESET) { }

        I2C_GenerateSTART(I2C1, ENABLE);
        while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) { }

        I2C_Send7bitAddress(I2C1, 0x02, I2C_Direction_Transmitter);
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) { }
    
        for (uint8_t i = 0; i < 6; i++) {
            if (I2C_GetFlagStatus(I2C1, I2C_FLAG_TXE) !=  RESET) {
                Delay_Ms(100);
                I2C_SendData(I2C1, TxData[i]);
            }
        }

        while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) { }
        I2C_GenerateSTOP(I2C1, ENABLE);
        Delay_Ms(1000);
    }

#elif (I2C_MODE == I2C_SLAVE_MODE)

    printf("IIC Slave mode\n");
    IIC_Init(80000, RXAdderss);

	for (uint8_t p = 0; p < 5; p++) {
        while(!I2C_CheckEvent(I2C1, I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED)) { }

        uint8_t i = 0;
        while (i < 6) {
            if(I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE) != RESET) {
                RxData[p][i] = I2C_ReceiveData(I2C1);
                i++;
            }
        }

        I2C1->CTLR1 &= I2C1->CTLR1;
    }

	printf("RxData:\n");
	for (uint8_t p = 0; p < 5; p++) {
        for (uint8_t i = 0; i < 6; i++) {
           printf("%02x ", RxData[p][i]);
		}

        printf("\r\n ");
	}
#endif

    while(1) { } // FIXME: outro
}
