#ifndef __CH32V00x_USART_H
#define __CH32V00x_USART_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ch32v00x/device.h>

/* USART Init Structure definition */
typedef struct
{
    uint32_t USART_BaudRate; /* This member configures the USART communication baud rate.
                                The baud rate is computed using the following formula:
                                 - IntegerDivider = ((PCLKx) / (16 * (USART_InitStruct->USART_BaudRate)))
                                 - FractionalDivider = ((IntegerDivider - ((u32) IntegerDivider)) * 16) + 0.5 */

    uint16_t USART_WordLength; /* Specifies the number of data bits transmitted or received in a frame.
                                  This parameter can be a value of @ref USART_Word_Length */

    uint16_t USART_StopBits; /* Specifies the number of stop bits transmitted.
                                This parameter can be a value of @ref USART_Stop_Bits */

    uint16_t USART_Parity; /* Specifies the parity mode.
                              This parameter can be a value of @ref USART_Parity
                              @note When parity is enabled, the computed parity is inserted
                                    at the MSB position of the transmitted data (9th bit when
                                    the word length is set to 9 data bits; 8th bit when the
                                    word length is set to 8 data bits). */

    uint16_t USART_Mode; /* Specifies wether the Receive or Transmit mode is enabled or disabled.
                            This parameter can be a value of @ref USART_Mode */

    uint16_t USART_HardwareFlowControl; /* Specifies wether the hardware flow control mode is enabled
                                           or disabled.
                                           This parameter can be a value of @ref USART_Hardware_Flow_Control */
} USART_InitTypeDef;

/* USART Clock Init Structure definition */
typedef struct
{
    uint16_t USART_Clock; /* Specifies whether the USART clock is enabled or disabled.
                             This parameter can be a value of @ref USART_Clock */

    uint16_t USART_CPOL; /* Specifies the steady state value of the serial clock.
                            This parameter can be a value of @ref USART_Clock_Polarity */

    uint16_t USART_CPHA; /* Specifies the clock transition on which the bit capture is made.
                            This parameter can be a value of @ref USART_Clock_Phase */

    uint16_t USART_LastBit; /* Specifies whether the clock pulse corresponding to the last transmitted
                               data bit (MSB) has to be output on the SCLK pin in synchronous mode.
                               This parameter can be a value of @ref USART_Last_Bit */
} USART_ClockInitTypeDef;

/* USART_Word_Length */
#define USART_WordLength_8b                  ((uint16_t)0x0000)
#define USART_WordLength_9b                  ((uint16_t)0x1000)

/* USART_Stop_Bits */
#define USART_StopBits_1                     ((uint16_t)0x0000)
#define USART_StopBits_0_5                   ((uint16_t)0x1000)
#define USART_StopBits_2                     ((uint16_t)0x2000)
#define USART_StopBits_1_5                   ((uint16_t)0x3000)

/* USART_Parity */
#define USART_Parity_No                      ((uint16_t)0x0000)
#define USART_Parity_Even                    ((uint16_t)0x0400)
#define USART_Parity_Odd                     ((uint16_t)0x0600)

/* USART_Mode */
#define USART_Mode_Rx                        ((uint16_t)0x0004)
#define USART_Mode_Tx                        ((uint16_t)0x0008)

/* USART_Hardware_Flow_Control */
#define USART_HardwareFlowControl_None       ((uint16_t)0x0000)
#define USART_HardwareFlowControl_RTS        ((uint16_t)0x0100)
#define USART_HardwareFlowControl_CTS        ((uint16_t)0x0200)
#define USART_HardwareFlowControl_RTS_CTS    ((uint16_t)0x0300)

/* USART_Clock */
#define USART_Clock_Disable                  ((uint16_t)0x0000)
#define USART_Clock_Enable                   ((uint16_t)0x0800)

/* USART_Clock_Polarity */
#define USART_CPOL_Low                       ((uint16_t)0x0000)
#define USART_CPOL_High                      ((uint16_t)0x0400)

/* USART_Clock_Phase */
#define USART_CPHA_1Edge                     ((uint16_t)0x0000)
#define USART_CPHA_2Edge                     ((uint16_t)0x0200)

/* USART_Last_Bit */
#define USART_LastBit_Disable                ((uint16_t)0x0000)
#define USART_LastBit_Enable                 ((uint16_t)0x0100)

/* USART_Interrupt_definition */
#define USART_IT_PE                          ((uint16_t)0x0028)
#define USART_IT_TXE                         ((uint16_t)0x0727)
#define USART_IT_TC                          ((uint16_t)0x0626)
#define USART_IT_RXNE                        ((uint16_t)0x0525)
#define USART_IT_ORE_RX                      ((uint16_t)0x0325)
#define USART_IT_IDLE                        ((uint16_t)0x0424)
#define USART_IT_LBD                         ((uint16_t)0x0846)
#define USART_IT_CTS                         ((uint16_t)0x096A)
#define USART_IT_ERR                         ((uint16_t)0x0060)
#define USART_IT_ORE_ER                      ((uint16_t)0x0360)
#define USART_IT_NE                          ((uint16_t)0x0260)
#define USART_IT_FE                          ((uint16_t)0x0160)

#define USART_IT_ORE                         USART_IT_ORE_ER

/* USART_DMA_Requests */
#define USART_DMAReq_Tx                      ((uint16_t)0x0080)
#define USART_DMAReq_Rx                      ((uint16_t)0x0040)

/* USART_WakeUp_methods */
#define USART_WakeUp_IdleLine                ((uint16_t)0x0000)
#define USART_WakeUp_AddressMark             ((uint16_t)0x0800)

/* USART_LIN_Break_Detection_Length */
#define USART_LINBreakDetectLength_10b       ((uint16_t)0x0000)
#define USART_LINBreakDetectLength_11b       ((uint16_t)0x0020)

/* USART_IrDA_Low_Power */
#define USART_IrDAMode_LowPower              ((uint16_t)0x0004)
#define USART_IrDAMode_Normal                ((uint16_t)0x0000)

/* USART_Flags */
#define USART_FLAG_CTS                       ((uint16_t)0x0200)
#define USART_FLAG_LBD                       ((uint16_t)0x0100)
#define USART_FLAG_TXE                       ((uint16_t)0x0080)
#define USART_FLAG_TC                        ((uint16_t)0x0040)
#define USART_FLAG_RXNE                      ((uint16_t)0x0020)
#define USART_FLAG_IDLE                      ((uint16_t)0x0010)
#define USART_FLAG_ORE                       ((uint16_t)0x0008)
#define USART_FLAG_NE                        ((uint16_t)0x0004)
#define USART_FLAG_FE                        ((uint16_t)0x0002)
#define USART_FLAG_PE                        ((uint16_t)0x0001)

/**
 * Initializes the USARTx peripheral.
 *
 * @param baudrate USART communication baud rate.
 */
void USART_Printf_Init(uint32_t baudrate); // FIXME this should probably go away 

/**
 * Deinitializes the USARTx peripheral registers to their default
 * reset values.
 *
 * @param USARTx where x can be 1 to select the UART peripheral.
 */
void USART_DeInit(USART_TypeDef *USARTx);

/**
 * Initializes the USARTx peripheral according to the specified
 * parameters in the USART_InitStruct.
 *
 * @param USARTx where x can be 1 to select the UART peripheral.
 * @param USART_InitStruct pointer to a USART_InitTypeDef structure
 * that contains the configuration information for the specified
 * USART peripheral.
 */
void USART_Init(USART_TypeDef *USARTx, USART_InitTypeDef *USART_InitStruct);

/**
 * Fills each USART_InitStruct member with its default value.
 *
 * @param USART_InitStruct: pointer to a USART_InitTypeDef structure
 * which will be initialized.
 */
void USART_StructInit(USART_InitTypeDef *USART_InitStruct);

/**
 * Initializes the USARTx peripheral Clock according to the
 * specified parameters in the USART_ClockInitStruct .
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 * @param USART_ClockInitStruct pointer to a USART_ClockInitTypeDef
 * structure that contains the configuration information for the specified
 * USART peripheral.
 */
void USART_ClockInit(USART_TypeDef *USARTx, USART_ClockInitTypeDef *USART_ClockInitStruct);

/**
 * Fills each USART_ClockStructInit member with its default value.
 *
 * @param USART_ClockInitStruct: pointer to a USART_ClockInitTypeDef
 * structure which will be initialized.
 */
void USART_ClockStructInit(USART_ClockInitTypeDef *USART_ClockInitStruct);

/**
 * Enables or disables the specified USART peripheral.
 * Reset values (affects also the I2Ss).
 *
 * @param  USARTx where x can be 1 to select the USART peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void USART_Cmd(USART_TypeDef *USARTx, FunctionalState NewState);

/**
 * Enables or disables the specified USART interrupts.
 * Reset values (affects also the I2Ss).
 *
 * @param USARTx where x can be to select the USART peripheral.
 * @param USART_IT specifies the USART interrupt sources to be enabled or disabled.
 * Available values:
 *    USART_IT_LBD - LIN Break detection interrupt.
 *    USART_IT_TXE - Transmit Data Register empty interrupt.
 *    USART_IT_TC - Transmission complete interrupt.
 *    USART_IT_RXNE - Receive Data register not empty interrupt.
 *    USART_IT_IDLE - Idle line detection interrupt.
 *    USART_IT_PE - Parity Error interrupt.
 *    USART_IT_ERR - Error interrupt.
 * @param NewState - ENABLE or DISABLE.
 */
void USART_ITConfig(USART_TypeDef *USARTx, uint16_t USART_IT, FunctionalState NewState);

/**
 * Enables or disables the USART DMA interface.
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 * @param USART_DMAReq specifies the DMA request.
 * Available values:
 *    USART_DMAReq_Tx - USART DMA transmit request.
 *    USART_DMAReq_Rx - USART DMA receive request.
 * @param NewState ENABLE or DISABLE.
 */
void USART_DMACmd(USART_TypeDef *USARTx, uint16_t USART_DMAReq, FunctionalState NewState);

/**
 * Sets the address of the USART node.
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 * @param USART_Address indicates the address of the USART node.
 */
void USART_SetAddress(USART_TypeDef *USARTx, uint8_t USART_Address);

/**
 * Selects the USART WakeUp method.
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 * @param USART_WakeUp specifies the USART wakeup method.
 * Available values:
 *    USART_WakeUp_IdleLine - WakeUp by an idle line detection.
 *    USART_WakeUp_AddressMark - WakeUp by an address mark.
 */
void USART_WakeUpConfig(USART_TypeDef *USARTx, uint16_t USART_WakeUp);

/**
 * Determines if the USART is in mute mode or not.
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void USART_ReceiverWakeUpCmd(USART_TypeDef *USARTx, FunctionalState NewState);

/**
 * Sets the USART LIN Break detection length.
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 * @param USART_LINBreakDetectLength specifies the LIN break detection length.
 * Available values:
 *    USART_LINBreakDetectLength_10b - 10-bit break detection.
 *    USART_LINBreakDetectLength_11b - 11-bit break detection.
 */
void       USART_LINBreakDetectLengthConfig(USART_TypeDef *USARTx, uint16_t USART_LINBreakDetectLength);

/**
 * Enables or disables the USART LIN mode.
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void USART_LINCmd(USART_TypeDef *USARTx, FunctionalState NewState);

/**
 * Transmits single data through the USARTx peripheral.
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 * @param Data the data to transmit.
 */
void USART_SendData(USART_TypeDef *USARTx, uint16_t Data);

/**
 * Returns the most recent received data by the USARTx peripheral.
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 *
 * @return  The received data.
 */
uint16_t USART_ReceiveData(USART_TypeDef *USARTx);

/**
 * Transmits break characters.
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 */
void USART_SendBreak(USART_TypeDef *USARTx);

/**
 * Sets the specified USART guard time.
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 * @param USART_GuardTime specifies the guard time.
 */
void USART_SetGuardTime(USART_TypeDef *USARTx, uint8_t USART_GuardTime);

/**
 * Sets the system clock prescaler.
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 * @param USART_Prescaler specifies the prescaler clock.
 */
void USART_SetPrescaler(USART_TypeDef *USARTx, uint8_t USART_Prescaler);

/**
 * Enables or disables the USART Smart Card mode.
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void USART_SmartCardCmd(USART_TypeDef *USARTx, FunctionalState NewState);

/**
 * Enables or disables NACK transmission.
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void USART_SmartCardNACKCmd(USART_TypeDef *USARTx, FunctionalState NewState);

/**
 * Enables or disables the USART Half Duplex communication.
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void USART_HalfDuplexCmd(USART_TypeDef *USARTx, FunctionalState NewState);

/**
 * Enables or disables the USART's 8x oversampling mode.
 *
 * Note:
 * This function has to be called before calling USART_Init()
 * function in order to have correct baudrate Divider value. 
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void USART_OverSampling8Cmd(USART_TypeDef *USARTx, FunctionalState NewState);

/**
 * Enables or disables the USART's one bit sampling method.
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void USART_OneBitMethodCmd(USART_TypeDef *USARTx, FunctionalState NewState);

/**
 * Configures the USART's IrDA interface.
 *
 * @param USARTx - where x can be 1 to select the USART peripheral.
 * @param USART_IrDAMode - specifies the IrDA mode.
 * Available values:
 *    USART_IrDAMode_LowPower.
 *    USART_IrDAMode_Normal.
 */
void USART_IrDAConfig(USART_TypeDef *USARTx, uint16_t USART_IrDAMode);

/**
 * Enables or disables the USART's IrDA interface.
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void USART_IrDACmd(USART_TypeDef *USARTx, FunctionalState NewState);

/**
 * Checks whether the specified USART flag is set or not.
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 * @param USART_FLAG specifies the flag to check.
 * Available values:
 *    USART_FLAG_LBD - LIN Break detection flag.
 *    USART_FLAG_TXE - Transmit data register empty flag.
 *    USART_FLAG_TC - Transmission Complete flag.
 *    USART_FLAG_RXNE - Receive data register not empty flag.
 *    USART_FLAG_IDLE - Idle Line detection flag.
 *    USART_FLAG_ORE - OverRun Error flag.
 *    USART_FLAG_NE - Noise Error flag.
 *    USART_FLAG_FE - Framing Error flag.
 *    USART_FLAG_PE - Parity Error flag.
 *
 * @return bitstatus: SET or RESET
 */
FlagStatus USART_GetFlagStatus(USART_TypeDef *USARTx, uint16_t USART_FLAG);

/**
 * Clears the USARTx's pending flags.
 *
 * Note:
 *  - PE (Parity error), FE (Framing error), NE (Noise error), ORE (OverRun 
 *    error) and IDLE (Idle line detected) flags are cleared by software 
 *    sequence: a read operation to USART_STATR register (USART_GetFlagStatus()) 
 *    followed by a read operation to USART_DATAR register (USART_ReceiveData()).
 *  - RXNE flag can be also cleared by a read to the USART_DATAR register 
 *    (USART_ReceiveData()).
 *  - TC flag can be also cleared by software sequence: a read operation to 
 *    USART_STATR register (USART_GetFlagStatus()) followed by a write operation
 *    to USART_DATAR register (USART_SendData()).
 *  - TXE flag is cleared only by a write to the USART_DATAR register 
 *    (USART_SendData()).
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 * @param USART_FLAG specifies the flag to clear.
 * Available values:
 *    USART_FLAG_LBD - LIN Break detection flag.
 *    USART_FLAG_TC - Transmission Complete flag.
 *    USART_FLAG_RXNE - Receive data register not empty flag.
 */
void USART_ClearFlag(USART_TypeDef *USARTx, uint16_t USART_FLAG);

/**
 * Checks whether the specified USART interrupt has occurred or not.
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 * @param USART_IT specifies the USART interrupt source to check.
 * Available values:
 *    USART_IT_LBD - LIN Break detection interrupt.
 *    USART_IT_TXE - Tansmit Data Register empty interrupt.
 *    USART_IT_TC - Transmission complete interrupt.
 *    USART_IT_RXNE - Receive Data register not empty interrupt.
 *    USART_IT_IDLE - Idle line detection interrupt.
 *    USART_IT_ORE_RX - OverRun Error interrupt if the RXNEIE bit is set.
 *    USART_IT_ORE_ER - OverRun Error interrupt if the EIE bit is set.
 *    USART_IT_NE - Noise Error interrupt.
 *    USART_IT_FE - Framing Error interrupt.
 *    USART_IT_PE - Parity Error interrupt.
 *
 * @return  bitstatus: SET or RESET.
 */
ITStatus USART_GetITStatus(USART_TypeDef *USARTx, uint16_t USART_IT);

/**
 * Clears the USARTx's interrupt pending bits.
 *
 * Note:
 *  - PE (Parity error), FE (Framing error), NE (Noise error), ORE (OverRun 
 *    error) and IDLE (Idle line detected) pending bits are cleared by 
 *    software sequence: a read operation to USART_STATR register 
 *    (USART_GetITStatus()) followed by a read operation to USART_DATAR register 
 *    (USART_ReceiveData()).
 *  - RXNE pending bit can be also cleared by a read to the USART_DATAR register 
 *    (USART_ReceiveData()).
 *  - TC pending bit can be also cleared by software sequence: a read 
 *    operation to USART_STATR register (USART_GetITStatus()) followed by a write 
 *    operation to USART_DATAR register (USART_SendData()).
 *  - TXE pending bit is cleared only by a write to the USART_DATAR register 
 *    (USART_SendData()).
 *
 * @param USARTx where x can be 1 to select the USART peripheral.
 * @param USART_IT specifies the interrupt pending bit to clear. 
 * Available values:
 *   USART_IT_LBD - LIN Break detection interrupt.
 *   USART_IT_TC - Transmission complete interrupt.
 *   USART_IT_RXNE - Receive Data register not empty interrupt.
 */
void USART_ClearITPendingBit(USART_TypeDef *USARTx, uint16_t USART_IT);

#ifdef __cplusplus
}
#endif

#endif /* __CH32V00x_USART_H */
