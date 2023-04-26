#ifndef __CH32V00x_SPI_H
#define __CH32V00x_SPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ch32v00x/device.h>

/* SPI Init structure definition */
typedef struct SPI_InitTypeDef {
    /**
     * Specifies the SPI unidirectional or bidirectional data mode.
     * This parameter can be a value of @ref SPI_data_direction
     */
    uint16_t SPI_Direction;

    /**
     * Specifies the SPI operating mode.
     * This parameter can be a value of @ref SPI_mode
     */
    uint16_t SPI_Mode;

    /**
     * Specifies the SPI data size.
     * This parameter can be a value of @ref SPI_data_size
     */
    uint16_t SPI_DataSize;

    /**
     * Specifies the serial clock steady state.
     * This parameter can be a value of @ref SPI_Clock_Polarity
     */
    uint16_t SPI_CPOL;

    /**
     * Specifies the clock active edge for the bit capture.
     * This parameter can be a value of @ref SPI_Clock_Phase
     */
    uint16_t SPI_CPHA;

    /**
     * Specifies whether the NSS signal is managed by
     * hardware (NSS pin) or by software using the SSI bit.
     * This parameter can be a value of @ref SPI_Slave_Select_management
     */
    uint16_t SPI_NSS;

    /**
     * Specifies the Baud Rate prescaler value which will be
     * used to configure the transmit and receive SCK clock.
     * This parameter can be a value of @ref SPI_BaudRate_Prescaler.
     *
     * @note The communication clock is derived from the master
     * clock. The slave clock does not need to be set.
     */
    uint16_t SPI_BaudRatePrescaler;
    
    /**
     * Specifies whether data transfers start from MSB bit.
     */
    uint16_t SPI_FirstBit;
    
    /**
     * Specifies the polynomial used for the CRC calculation.
     */
    uint16_t SPI_CRCPolynomial;
} SPI_InitTypeDef;

/* SPI_data_direction */
#define SPI_Direction_2Lines_FullDuplex    ((uint16_t)0x0000)
#define SPI_Direction_2Lines_RxOnly        ((uint16_t)0x0400)
#define SPI_Direction_1Line_Rx             ((uint16_t)0x8000)
#define SPI_Direction_1Line_Tx             ((uint16_t)0xC000)

/* SPI_mode */
#define SPI_Mode_Master                    ((uint16_t)0x0104)
#define SPI_Mode_Slave                     ((uint16_t)0x0000)

/* SPI_data_size */
#define SPI_DataSize_16b                   ((uint16_t)0x0800)
#define SPI_DataSize_8b                    ((uint16_t)0x0000)

/* SPI_Clock_Polarity */
#define SPI_CPOL_Low                       ((uint16_t)0x0000)
#define SPI_CPOL_High                      ((uint16_t)0x0002)

/* SPI_Clock_Phase */
#define SPI_CPHA_1Edge                     ((uint16_t)0x0000)
#define SPI_CPHA_2Edge                     ((uint16_t)0x0001)

/* SPI_Slave_Select_management */
#define SPI_NSS_Soft                       ((uint16_t)0x0200)
#define SPI_NSS_Hard                       ((uint16_t)0x0000)

/* SPI_BaudRate_Prescaler */
#define SPI_BaudRatePrescaler_2            ((uint16_t)0x0000)
#define SPI_BaudRatePrescaler_4            ((uint16_t)0x0008)
#define SPI_BaudRatePrescaler_8            ((uint16_t)0x0010)
#define SPI_BaudRatePrescaler_16           ((uint16_t)0x0018)
#define SPI_BaudRatePrescaler_32           ((uint16_t)0x0020)
#define SPI_BaudRatePrescaler_64           ((uint16_t)0x0028)
#define SPI_BaudRatePrescaler_128          ((uint16_t)0x0030)
#define SPI_BaudRatePrescaler_256          ((uint16_t)0x0038)

/* SPI_MSB transmission */
#define SPI_FirstBit_MSB                   ((uint16_t)0x0000)

/* SPI_I2S_DMA_transfer_requests */
#define SPI_I2S_DMAReq_Tx                  ((uint16_t)0x0002)
#define SPI_I2S_DMAReq_Rx                  ((uint16_t)0x0001)

/* SPI_NSS_internal_software_management */
#define SPI_NSSInternalSoft_Set            ((uint16_t)0x0100)
#define SPI_NSSInternalSoft_Reset          ((uint16_t)0xFEFF)

/* SPI_CRC_Transmit_Receive */
#define SPI_CRC_Tx                         ((uint8_t)0x00)
#define SPI_CRC_Rx                         ((uint8_t)0x01)

/* SPI_direction_transmit_receive */
#define SPI_Direction_Rx                   ((uint16_t)0xBFFF)
#define SPI_Direction_Tx                   ((uint16_t)0x4000)

/* SPI_I2S_interrupts_definition */
#define SPI_I2S_IT_TXE                     ((uint8_t)0x71)
#define SPI_I2S_IT_RXNE                    ((uint8_t)0x60)
#define SPI_I2S_IT_ERR                     ((uint8_t)0x50)
#define SPI_I2S_IT_OVR                     ((uint8_t)0x56)
#define SPI_IT_MODF                        ((uint8_t)0x55)
#define SPI_IT_CRCERR                      ((uint8_t)0x54)
#define I2S_IT_UDR                         ((uint8_t)0x53)

/* SPI_I2S_flags_definition */
#define SPI_I2S_FLAG_RXNE                  ((uint16_t)0x0001)
#define SPI_I2S_FLAG_TXE                   ((uint16_t)0x0002)
#define I2S_FLAG_CHSIDE                    ((uint16_t)0x0004)
#define I2S_FLAG_UDR                       ((uint16_t)0x0008)
#define SPI_FLAG_CRCERR                    ((uint16_t)0x0010)
#define SPI_FLAG_MODF                      ((uint16_t)0x0020)
#define SPI_I2S_FLAG_OVR                   ((uint16_t)0x0040)
#define SPI_I2S_FLAG_BSY                   ((uint16_t)0x0080)

/**
 * Deinitializes the SPIx peripheral registers to their default
 * reset values.
 *
 * @param SPIx where x can be 1 to select the SPI peripheral.
 */
void SPI_I2S_DeInit(SPI_TypeDef *SPIx);

/**
 * Initializes the SPIx peripheral according to the specified
 * parameters in the SPI_InitStruct.
 *
 * @param SPIx where x can be 1 to select the SPI peripheral.
 * @param SPI_InitStruct pointer to a SPI_InitTypeDef structure that
 * contains the configuration information for the specified SPI peripheral.
 */
void SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct);

/**
 * Fills each SPI_InitStruct member with its default value.
 *
 * @param SPI_InitStruct pointer to a SPI_InitTypeDef structure which
 * will be initialized.
 */
void SPI_StructInit(SPI_InitTypeDef *SPI_InitStruct);

/**
 * Enables or disables the specified SPI peripheral.
 *
 * @param SPIx where x can be 1 to select the SPI peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void SPI_Cmd(SPI_TypeDef *SPIx, FunctionalState NewState);

/**
 * Enables or disables the specified SPI interrupts.
 *
 * @param SPIx where x can be
 *    - 1 in SPI mode.
 * @param SPI_I2S_IT specifies the SPI interrupt source to be
 * enabled or disabled.
 *    SPI_I2S_IT_TXE - Tx buffer empty interrupt mask.
 *    SPI_I2S_IT_RXNE - Rx buffer not empty interrupt mask.
 *    SPI_I2S_IT_ERR - Error interrupt mask.
 * @param NewState ENABLE or DISABLE.
 */
void SPI_I2S_ITConfig(SPI_TypeDef *SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState);

/**
 * Enables or disables the SPIx DMA interface.
 *
 * @param SPIx where x can be
 *            - 1 in SPI mode.
 * @param SPI_I2S_DMAReq specifies the SPI DMA transfer request to
 * be enabled or disabled.
 *    SPI_I2S_DMAReq_Tx - Tx buffer DMA transfer request.
 *    SPI_I2S_DMAReq_Rx - Rx buffer DMA transfer request.
 * @param NewState ENABLE or DISABLE.
 */
void SPI_I2S_DMACmd(SPI_TypeDef *SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState);

/**
 * Transmits a Data through the SPIx peripheral.
 *
 * @param SPIx where x can be
 *    - 1 in SPI mode.
 * @param Data Data to be transmitted.
 */
void SPI_I2S_SendData(SPI_TypeDef *SPIx, uint16_t Data);

/**
 * Returns the most recent received data by the SPIx peripheral.
 *
 * @param SPIx where x can be
 *    - 1 in SPI mode.
 * @param Data Data to be transmitted.
 *
 * @return The value of the received data.
 */
uint16_t SPI_I2S_ReceiveData(SPI_TypeDef *SPIx);

/**
 * Configures internally by software the NSS pin for the selected SPI.
 *
 * @param SPIx where x can be 1 to select the SPI peripheral.
 * @param SPI_NSSInternalSoft
 *    SPI_NSSInternalSoft_Set - Set NSS pin internally.
 *    SPI_NSSInternalSoft_Reset - Reset NSS pin internally.
 */
void SPI_NSSInternalSoftwareConfig(SPI_TypeDef *SPIx, uint16_t SPI_NSSInternalSoft);

/**
 * Enables or disables the SS output for the selected SPI.
 *
 * @param SPIx where x can be 1 to select the SPI peripheral.
 * @param NewState new state of the SPIx SS output.
 */
void SPI_SSOutputCmd(SPI_TypeDef *SPIx, FunctionalState NewState);

/**
 * Configures the data size for the selected SPI.
 *
 * @param SPIx where x can be 1 to select the SPI peripheral.
 * @param SPI_DataSize specifies the SPI data size.
 *    SPI_DataSize_16b - Set data frame format to 16bit.
 *    SPI_DataSize_8b - Set data frame format to 8bit.
 */
void SPI_DataSizeConfig(SPI_TypeDef *SPIx, uint16_t SPI_DataSize);

/**
 * Transmit the SPIx CRC value.
 *
 * @param SPIx where x can be 1 to select the SPI peripheral.
 */
void SPI_TransmitCRC(SPI_TypeDef *SPIx);

/**
 * Enables or disables the CRC value calculation of the transferred bytes.
 *
 * @param SPIx where x can be 1 to select the SPI peripheral.
 * @param NewState new state of the SPIx CRC value calculation.
 */
void SPI_CalculateCRC(SPI_TypeDef *SPIx, FunctionalState NewState);

/**
 * Returns the transmit or the receive CRC register value for the specified SPI.
 *
 * @param SPIx where x can be 1 to select the SPI peripheral.
 * @param SPI_CRC specifies the CRC register to be read.
 *    SPI_CRC_Tx - Selects Tx CRC register.
 *    SPI_CRC_Rx - Selects Rx CRC register.
 *
 * @return The selected CRC register value.
 */
uint16_t SPI_GetCRC(SPI_TypeDef *SPIx, uint8_t SPI_CRC);

/**
 * Returns the CRC Polynomial register value for the specified SPI.
 *
 * @param SPIx where x can be 1 to select the SPI peripheral.
 *
 * @return The CRC Polynomial register value.
 */
uint16_t SPI_GetCRCPolynomial(SPI_TypeDef *SPIx);

/**
 * Selects the data transfer direction in bi-directional mode
 * for the specified SPI.
 *
 * @param SPIx where x can be 1 to select the SPI peripheral.
 * @param SPI_Direction - specifies the data transfer direction in
 * bi-directional mode.
 * Available values:
 *    SPI_Direction_Tx - Selects Tx transmission direction.
 *    SPI_Direction_Rx - Selects Rx receive direction.
 */
void SPI_BiDirectionalLineConfig(SPI_TypeDef *SPIx, uint16_t SPI_Direction);

/**
 * Checks whether the specified SPI flag is set or not.
 *
 * @param SPIx where x can be:
 *    - 1 in SPI mode.
 * @param SPI_I2S_FLAG - specifies the SPI/I2S flag to check.
 *    SPI_I2S_FLAG_TXE - Transmit buffer empty flag.
 *    SPI_I2S_FLAG_RXNE - Receive buffer not empty flag.
 *    SPI_I2S_FLAG_BSY - Busy flag.
 *    SPI_I2S_FLAG_OVR - Overrun flag.
 *    SPI_FLAG_MODF - Mode Fault flag.
 *    SPI_FLAG_CRCERR - CRC Error flag.
 *    I2S_FLAG_UDR - Underrun Error flag.
 *    I2S_FLAG_CHSIDE - Channel Side flag.
 *
 * @return SET or RESET.
 */
FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef *SPIx, uint16_t SPI_I2S_FLAG);

/**
 * Clears the SPIx CRC Error (CRCERR) flag.
 *
 * Note:
 * - OVR (OverRun error) flag is cleared by software sequence: a read 
 *   operation to SPI_DATAR register (SPI_I2S_ReceiveData()) followed by a read 
 *   operation to SPI_STATR register (SPI_I2S_GetFlagStatus()).
 * - UDR (UnderRun error) flag is cleared by a read operation to 
 *   SPI_STATR register (SPI_I2S_GetFlagStatus()).
 * - MODF (Mode Fault) flag is cleared by software sequence: a read/write 
 *   operation to SPI_STATR register (SPI_I2S_GetFlagStatus()) followed by a 
 *
 * @param SPIx where x can be:
 *    - 1 in SPI mode.
 * @param SPI_I2S_FLAG - specifies the SPI flag to clear.
 * Available values:
 *    SPI_FLAG_CRCERR - CRC Error flag.
 */
void SPI_I2S_ClearFlag(SPI_TypeDef *SPIx, uint16_t SPI_I2S_FLAG);

/**
 * Checks whether the specified SPI interrupt has occurred or not.
 *
 * @param SPIx where x can be
 *    - 1 in SPI mode.
 * @param SPI_I2S_IT - specifies the SPI interrupt source to check..
 *    SPI_I2S_IT_TXE - Transmit buffer empty interrupt.
 *    SPI_I2S_IT_RXNE - Receive buffer not empty interrupt.
 *    SPI_I2S_IT_OVR - Overrun interrupt.
 *    SPI_IT_MODF - Mode Fault interrupt.
 *    SPI_IT_CRCERR - CRC Error interrupt.
 *    I2S_IT_UDR - Underrun Error interrupt.
 *
 * @return SET or RESET.
 */
ITStatus SPI_I2S_GetITStatus(SPI_TypeDef *SPIx, uint8_t SPI_I2S_IT);

/**
 * Clears the SPIx CRC Error (CRCERR) interrupt pending bit.
 *
 * Note:
 * - OVR (OverRun Error) interrupt pending bit is cleared by software 
 *   sequence: a read operation to SPI_DATAR register (SPI_I2S_ReceiveData()) 
 *   followed by a read operation to SPI_STATR register (SPI_I2S_GetITStatus()).
 * - UDR (UnderRun Error) interrupt pending bit is cleared by a read 
 *   operation to SPI_STATR register (SPI_I2S_GetITStatus()).
 * - MODF (Mode Fault) interrupt pending bit is cleared by software sequence:
 *   a read/write operation to SPI_STATR register (SPI_I2S_GetITStatus()) 
 *   followed by a write operation to SPI_CTLR1 register (SPI_Cmd() to enable 
 *   the SPI).  
 *
 * @param SPIx where x can be
 *    - 1 in SPI mode.
 * @param SPI_I2S_IT - specifies the SPI interrupt pending bit to clear.
 *    SPI_IT_CRCERR - CRC Error interrupt.
 */
void SPI_I2S_ClearITPendingBit(SPI_TypeDef *SPIx, uint8_t SPI_I2S_IT);


#ifdef __cplusplus
}
#endif

#endif /*__CH32V00x_SPI_H */
