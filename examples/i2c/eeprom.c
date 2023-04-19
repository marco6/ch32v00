/**
 * I2C interface routine to operate EEPROM peripheral:
 * I2C1_SCL(PC2)\I2C1_SDA(PC1).
 *
 * This example uses EEPROM for AT24Cxx series.
 *
 * Steps:
 *  - READ EEPROM:Start + 0xA0 + 8bit Data Address + Start + 0xA1 + Read Data + Stop.
 *  - WRITE EERPOM:Start + 0xA0 + 8bit Data Address + Write Data + Stop.
 */

#include <ch32v00x/gpio.h>
#include <ch32v00x/i2c.h>
#include <ch32v00x/rcc.h>
#include <ch32v00x/usart.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#if !defined(ADDRESS_LENGTH) || ((ADDRESS_LENGTH != 8) && (ADDRESS_LENGTH != 16))
# warning "EEPROM address length not defined. Defaulting to 8bit (e.g. -DADDRESS_LENGTH={8,16})"
# undef ADDRESS_LENGTH
# define ADDRESS_LENGTH 8
#endif

#define SIZE sizeof(TEXT_Buffer)

static const uint8_t TEXT_Buffer[] = { "CH32V00x I2C TEST" };

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
    I2C_InitTSturcture.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitTSturcture.I2C_OwnAddress1 = address;
    I2C_InitTSturcture.I2C_Ack = I2C_Ack_Enable;
    I2C_InitTSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(I2C1, &I2C_InitTSturcture);

    I2C_Cmd(I2C1, ENABLE);
    I2C_AcknowledgeConfig(I2C1, ENABLE);
}

/**
 * Initializes AT24xx EEPROM.
 */
void AT24CXX_Init(void) {
    IIC_Init(100000, 0xA0);
}

/**
 * Read one data from EEPROM.
 *
 * @param ReadAddr Read address.
 * @return byte read
 */
uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr) {
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) != RESET) { }

    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) { }

    I2C_Send7bitAddress(I2C1, 0XA0, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) { }

#if (ADDRESS_LENGTH == 8)

    I2C_SendData(I2C1, (u8)(ReadAddr&0x00FF));
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) { }

#elif (ADDRESS_LENGTH == 16)

    I2C_SendData(I2C1, (uint8_t)(ReadAddr>>8));
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) { }

    I2C_SendData(I2C1, (u8)(ReadAddr&0x00FF));
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) { }

#endif

    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) { }
    
    I2C_Send7bitAddress(I2C1, 0XA0, I2C_Direction_Receiver);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) { }
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_RXNE) == RESET) { }
    I2C_AcknowledgeConfig(I2C1, DISABLE);

    uint8_t result = I2C_ReceiveData(I2C1);
    I2C_GenerateSTOP(I2C1, ENABLE);

    return result;
}

/**
 * Write one data to EEPROM.
 *
 * @param WriteAddr - Write address.
 */
void AT24CXX_WriteOneByte(uint16_t WriteAddr, uint8_t DataToWrite) {
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY) != RESET) { }

    I2C_GenerateSTART(I2C1, ENABLE);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT)) { }
    
    I2C_Send7bitAddress(I2C1, 0XA0, I2C_Direction_Transmitter);
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) { }

#if (ADDRESS_LENGTH  == 8)

    I2C_SendData(I2C1, (uint8_t)(WriteAddr&0x00FF));
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) { }

#elif (ADDRESS_LENGTH  == 16)

    I2C_SendData(I2C1, (uint8_t)(WriteAddr>>8));
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) { }

    I2C_SendData(I2C1, (uint8_t)(WriteAddr&0x00FF));
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) { }

#endif

    if (I2C_GetFlagStatus(I2C1, I2C_FLAG_TXE) != RESET) {
        I2C_SendData(I2C1, DataToWrite);
    }

    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) { }
    I2C_GenerateSTOP(I2C1, ENABLE);
}

/**
 * Read multiple data from EEPROM.
 *
 * @param ReadAddr Read address. (AT24c02: 0~255)
 * @param pBuffer Read data.
 * @param NumToRead Data size.
 */
void AT24CXX_Read(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead) {
    while (NumToRead) {
        *pBuffer++ = AT24CXX_ReadOneByte(ReadAddr++);
        NumToRead--;
    }
}

/**
 * Write multiple data to EEPROM.
 *
 * @param WriteAddr Write address. (AT24c02: 0~255)
 * @param pBuffer Write data.
 * @param NumToWrite Data size.
 */
void AT24CXX_Write(uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite) {
    while (NumToWrite--) {
        AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
        WriteAddr++;
        pBuffer++;
        Delay_Ms(2);
    }
}

int main(void) {
    uint8_t data[SIZE];

    USART_Printf_Init(115200);
    printf("SystemClk:%"PRIu32"\n", SystemCoreClock);

    AT24CXX_Init();

    printf("Start Write 24Cxx....\n");
    AT24CXX_Write(100, (uint8_t*)TEXT_Buffer, SIZE);
    printf("24Cxx Write Sucess!\n");

    Delay_Ms(500);

    printf("Start Read 24Cxx....\n");
    AT24CXX_Read(100, data, SIZE);
    printf("The Data Readed Is: \n");

    printf("%s\n", data);

    while(1) { } // FIXME: outro
}
