#ifndef __CH32V00x_I2C_H
#define __CH32V00x_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ch32v00x/device.h>

/**
 * I2C Init structure definition
 */
typedef struct I2C_InitTypeDef {
    /**
     * Specifies the clock frequency.
     * This parameter must be set to a value lower than 400kHz
     */
    uint32_t I2C_ClockSpeed;

    /**
     * Specifies the I2C mode.
     * This parameter can be a value of @ref I2C_mode
     */
    uint16_t I2C_Mode;

    /**
     * Specifies the I2C fast mode duty cycle.
     * This parameter can be a value of @ref I2C_duty_cycle_in_fast_mode
     */
    uint16_t I2C_DutyCycle;

    /**
     * Specifies the first device own address.
     * This parameter can be a 7-bit or 10-bit address.
     */
    uint16_t I2C_OwnAddress1;

    /**
     * Enables or disables the acknowledgement.
     * This parameter can be a value of @ref I2C_acknowledgement
     */
    uint16_t I2C_Ack;

    /**
     * Specifies if 7-bit or 10-bit address is acknowledged.
     * This parameter can be a value of @ref I2C_acknowledged_address
     */
    uint16_t I2C_AcknowledgedAddress;
} I2C_InitTypeDef;

/* I2C_mode */
#define I2C_Mode_I2C                                         ((uint16_t)0x0000)

/* I2C_duty_cycle_in_fast_mode */
#define I2C_DutyCycle_16_9                                   ((uint16_t)0x4000) /* I2C fast mode Tlow/Thigh = 16/9 */
#define I2C_DutyCycle_2                                      ((uint16_t)0xBFFF) /* I2C fast mode Tlow/Thigh = 2 */

/* I2C_acknowledgement */
#define I2C_Ack_Enable                                       ((uint16_t)0x0400)
#define I2C_Ack_Disable                                      ((uint16_t)0x0000)

/* I2C_transfer_direction */
#define I2C_Direction_Transmitter                            ((uint8_t)0x00)
#define I2C_Direction_Receiver                               ((uint8_t)0x01)

/* I2C_acknowledged_address */
#define I2C_AcknowledgedAddress_7bit                         ((uint16_t)0x4000)
#define I2C_AcknowledgedAddress_10bit                        ((uint16_t)0xC000)

/* I2C_registers */
#define I2C_Register_CTLR1                                   ((uint8_t)0x00)
#define I2C_Register_CTLR2                                   ((uint8_t)0x04)
#define I2C_Register_OADDR1                                  ((uint8_t)0x08)
#define I2C_Register_OADDR2                                  ((uint8_t)0x0C)
#define I2C_Register_DATAR                                   ((uint8_t)0x10)
#define I2C_Register_STAR1                                   ((uint8_t)0x14)
#define I2C_Register_STAR2                                   ((uint8_t)0x18)
#define I2C_Register_CKCFGR                                  ((uint8_t)0x1C)

/* I2C_PEC_position */
#define I2C_PECPosition_Next                                 ((uint16_t)0x0800)
#define I2C_PECPosition_Current                              ((uint16_t)0xF7FF)

/* I2C_NACK_position */
#define I2C_NACKPosition_Next                                ((uint16_t)0x0800)
#define I2C_NACKPosition_Current                             ((uint16_t)0xF7FF)

/* I2C_interrupts_definition */
#define I2C_IT_BUF                                           ((uint16_t)0x0400)
#define I2C_IT_EVT                                           ((uint16_t)0x0200)
#define I2C_IT_ERR                                           ((uint16_t)0x0100)

/* I2C_interrupts_definition */
#define I2C_IT_PECERR                                        ((uint32_t)0x01001000)
#define I2C_IT_OVR                                           ((uint32_t)0x01000800)
#define I2C_IT_AF                                            ((uint32_t)0x01000400)
#define I2C_IT_ARLO                                          ((uint32_t)0x01000200)
#define I2C_IT_BERR                                          ((uint32_t)0x01000100)
#define I2C_IT_TXE                                           ((uint32_t)0x06000080)
#define I2C_IT_RXNE                                          ((uint32_t)0x06000040)
#define I2C_IT_STOPF                                         ((uint32_t)0x02000010)
#define I2C_IT_ADD10                                         ((uint32_t)0x02000008)
#define I2C_IT_BTF                                           ((uint32_t)0x02000004)
#define I2C_IT_ADDR                                          ((uint32_t)0x02000002)
#define I2C_IT_SB                                            ((uint32_t)0x02000001)

/* SR2 register flags  */
#define I2C_FLAG_DUALF                                       ((uint32_t)0x00800000)
#define I2C_FLAG_GENCALL                                     ((uint32_t)0x00100000)
#define I2C_FLAG_TRA                                         ((uint32_t)0x00040000)
#define I2C_FLAG_BUSY                                        ((uint32_t)0x00020000)
#define I2C_FLAG_MSL                                         ((uint32_t)0x00010000)

/* SR1 register flags */
#define I2C_FLAG_PECERR                                      ((uint32_t)0x10001000)
#define I2C_FLAG_OVR                                         ((uint32_t)0x10000800)
#define I2C_FLAG_AF                                          ((uint32_t)0x10000400)
#define I2C_FLAG_ARLO                                        ((uint32_t)0x10000200)
#define I2C_FLAG_BERR                                        ((uint32_t)0x10000100)
#define I2C_FLAG_TXE                                         ((uint32_t)0x10000080)
#define I2C_FLAG_RXNE                                        ((uint32_t)0x10000040)
#define I2C_FLAG_STOPF                                       ((uint32_t)0x10000010)
#define I2C_FLAG_ADD10                                       ((uint32_t)0x10000008)
#define I2C_FLAG_BTF                                         ((uint32_t)0x10000004)
#define I2C_FLAG_ADDR                                        ((uint32_t)0x10000002)
#define I2C_FLAG_SB                                          ((uint32_t)0x10000001)

/****************I2C Master Events (Events grouped in order of communication)********************/

/** 
 * @brief  Start communicate
 * 
 * After master use I2C_GenerateSTART() function sending the START condition,the master 
 * has to wait for event 5(the Start condition has been correctly 
 * released on the I2C bus ).
 * 
 */
/* EVT5 */
#define  I2C_EVENT_MASTER_MODE_SELECT                      ((uint32_t)0x00030001)  /* BUSY, MSL and SB flag */

/**
 * @brief  Address Acknowledge
 * 
 * When start condition correctly released on the bus(check EVT5), the 
 * master use I2C_Send7bitAddress() function sends the address of the slave(s) with which it will communicate 
 * it also determines master as transmitter or Receiver. Then the master has to wait that a slave acknowledges 
 * his address. If an acknowledge is sent on the bus, one of the following events will be set:
 * 
 *
 * 
 *  1) In case of Master Receiver (7-bit addressing): the I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED 
 *     event is set.
 *  
 *  2) In case of Master Transmitter (7-bit addressing): the I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED 
 *     is set
 *  
 *  3) In case of 10-Bit addressing mode, the master (after generating the START 
 *  and checking on EVT5) use I2C_SendData() function send the header of 10-bit addressing mode.  
 *  Then master wait EVT9. EVT9 means that the 10-bit addressing header has been correctly sent 
 *  on the bus. Then master should use the function I2C_Send7bitAddress() to send the second part 
 *  of the 10-bit address (LSB) . Then master should wait for event 6. 
 *
 *     
 */

/* EVT6 */
#define  I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED        ((uint32_t)0x00070082)  /* BUSY, MSL, ADDR, TXE and TRA flags */
#define  I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED           ((uint32_t)0x00030002)  /* BUSY, MSL and ADDR flags */
/*EVT9 */
#define  I2C_EVENT_MASTER_MODE_ADDRESS10                   ((uint32_t)0x00030008)  /* BUSY, MSL and ADD10 flags */

/** 
 * @brief Communication events
 * 
 * If START condition has generated and slave address 
 * been acknowledged. then the master has to check one of the following events for 
 * communication procedures:
 *  
 * 1) Master Receiver mode: The master has to wait on the event EVT7 then use  
 *   I2C_ReceiveData() function to read the data received from the slave .
 * 
 * 2) Master Transmitter mode: The master use I2C_SendData() function to send data  
 *     then to wait on event EVT8 or EVT8_2.
 *    These two events are similar: 
 *     - EVT8 means that the data has been written in the data register and is 
 *       being shifted out.
 *     - EVT8_2 means that the data has been physically shifted out and output 
 *       on the bus.
 *     In most cases, using EVT8 is sufficient for the application.
 *     Using EVT8_2  will leads to a slower communication  speed but will more reliable .
 *     EVT8_2 is also more suitable than EVT8 for testing on the last data transmission 
 *    
 *     
 *  Note:
 *  In case the  user software does not guarantee that this event EVT7 is managed before 
 *  the current byte end of transfer, then user may check on I2C_EVENT_MASTER_BYTE_RECEIVED 
 *  and I2C_FLAG_BTF flag at the same time .But in this case the communication may be slower.
 *
 * 
 */

/* Master Receive mode */ 
/* EVT7 */
#define  I2C_EVENT_MASTER_BYTE_RECEIVED                    ((uint32_t)0x00030040)  /* BUSY, MSL and RXNE flags */

/* Master Transmitter mode*/
/* EVT8 */
#define I2C_EVENT_MASTER_BYTE_TRANSMITTING                 ((uint32_t)0x00070080) /* TRA, BUSY, MSL, TXE flags */
/* EVT8_2 */
#define  I2C_EVENT_MASTER_BYTE_TRANSMITTED                 ((uint32_t)0x00070084)  /* TRA, BUSY, MSL, TXE and BTF flags */

/******************I2C Slave Events (Events grouped in order of communication)******************/

/** 
 * @brief  Start Communicate events
 * 
 * Wait on one of these events at the start of the communication. It means that 
 * the I2C peripheral detected a start condition of master device generate on the bus.  
 * If the acknowledge feature is enabled through function I2C_AcknowledgeConfig()),The peripheral generates an ACK condition on the bus. 
 *
 * a) In normal case (only one address managed by the slave), when the address 
 *   sent by the master matches the own address of the peripheral (configured by 
 *   I2C_OwnAddress1 field) the I2C_EVENT_SLAVE_XXX_ADDRESS_MATCHED event is set 
 *   (where XXX could be TRANSMITTER or RECEIVER).
 *    
 * b) In case the address sent by the master matches the second address of the 
 *   peripheral (configured by the function I2C_OwnAddress2Config() and enabled 
 *   by the function I2C_DualAddressCmd()) the events I2C_EVENT_SLAVE_XXX_SECONDADDRESS_MATCHED 
 *   (where XXX could be TRANSMITTER or RECEIVER) are set.
 *   
 * c) In case the address sent by the master is General Call (address 0x00) and 
 *   if the General Call is enabled for the peripheral (using function I2C_GeneralCallCmd()) 
 *   the following event is set I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED.   
 */

/* EVT1 */   
/* a) Case of One Single Address managed by the slave */
#define  I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED          ((uint32_t)0x00020002) /* BUSY and ADDR flags */
#define  I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED       ((uint32_t)0x00060082) /* TRA, BUSY, TXE and ADDR flags */

/* b) Case of Dual address managed by the slave */
#define  I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED    ((uint32_t)0x00820000)  /* DUALF and BUSY flags */
#define  I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED ((uint32_t)0x00860080)  /* DUALF, TRA, BUSY and TXE flags */

/* c) Case of General Call enabled for the slave */
#define  I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED        ((uint32_t)0x00120000)  /* GENCALL and BUSY flags */

/** 
 * @brief  Communication events
 * 
 * Wait on one of these events when EVT1 has already been checked : 
 * 
 * - Slave Receiver mode:
 *     - EVT2--The device is expecting to receive a data byte . 
 *     - EVT4--The device is expecting the end of the communication: master 
 *       sends a stop condition and data transmission is stopped.
 *    
 * - Slave Transmitter mode:
 *    - EVT3--When a byte has been transmitted by the slave and the Master is expecting 
 *      the end of the byte transmission. The two events I2C_EVENT_SLAVE_BYTE_TRANSMITTED and
 *      I2C_EVENT_SLAVE_BYTE_TRANSMITTING are similar. If the user software doesn't guarantee 
 *      the EVT3 is managed before the current byte end of transfer The second one can optionally
 *      be used. 
 *    - EVT3_2--When the master sends a NACK  to tell slave device that data transmission 
 *      shall end . The slave device has to stop sending 
 *      data bytes and wait a Stop condition from bus.
 *      
 *  Note:
 *  If the  user software does not guarantee that the event 2 is 
 *  managed before the current byte end of transfer, User may check on I2C_EVENT_SLAVE_BYTE_RECEIVED 
 *  and I2C_FLAG_BTF flag at the same time .
 *  In this case the communication will be slower.
 */

/* Slave Receiver mode*/ 
/* EVT2 */
#define  I2C_EVENT_SLAVE_BYTE_RECEIVED                     ((uint32_t)0x00020040)  /* BUSY and RXNE flags */
/* EVT4  */
#define  I2C_EVENT_SLAVE_STOP_DETECTED                     ((uint32_t)0x00000010)  /* STOPF flag */

/* Slave Transmitter mode */
/* EVT3 */
#define  I2C_EVENT_SLAVE_BYTE_TRANSMITTED                  ((uint32_t)0x00060084)  /* TRA, BUSY, TXE and BTF flags */
#define  I2C_EVENT_SLAVE_BYTE_TRANSMITTING                 ((uint32_t)0x00060080)  /* TRA, BUSY and TXE flags */
/*EVT3_2 */
#define  I2C_EVENT_SLAVE_ACK_FAILURE                       ((uint32_t)0x00000400)  /* AF flag */


/**
 * Deinitializes the I2Cx peripheral registers to their default
 * reset values.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 */
void I2C_DeInit(I2C_TypeDef *I2Cx);

/**
 * Initializes the I2Cx peripheral according to the specified
 * parameters in the I2C_InitStruct.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param I2C_InitStruct pointer to a I2C_InitTypeDef structure that
 * contains the configuration information for the specified I2C peripheral.
 */
void I2C_Init(I2C_TypeDef *I2Cx, I2C_InitTypeDef *I2C_InitStruct);

/**
 * Fills each I2C_InitStruct member with its default value.
 *
 * @param I2C_InitStruct pointer to an I2C_InitTypeDef structure which
 * will be initialized.
 */
void I2C_StructInit(I2C_InitTypeDef *I2C_InitStruct);

/**
 * Enables or disables the specified I2C peripheral.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void I2C_Cmd(I2C_TypeDef *I2Cx, FunctionalState NewState);

/**
 * Enables or disables the specified I2C DMA requests.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void I2C_DMACmd(I2C_TypeDef *I2Cx, FunctionalState NewState);

/**
 * Specifies if the next DMA transfer will be the last one.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void I2C_DMALastTransferCmd(I2C_TypeDef *I2Cx, FunctionalState NewState);

/**
 * Generates I2Cx communication START condition.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void I2C_GenerateSTART(I2C_TypeDef *I2Cx, FunctionalState NewState);

/**
 * Generates I2Cx communication STOP condition.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void I2C_GenerateSTOP(I2C_TypeDef *I2Cx, FunctionalState NewState);

/**
 * Enables or disables the specified I2C acknowledge feature.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void I2C_AcknowledgeConfig(I2C_TypeDef *I2Cx, FunctionalState NewState);

/**
 * Configures the specified I2C own address2.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param Address specifies the 7bit I2C own address2.
 */
void I2C_OwnAddress2Config(I2C_TypeDef *I2Cx, uint8_t Address);

/**
 * Enables or disables the specified I2C dual addressing mode.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void I2C_DualAddressCmd(I2C_TypeDef *I2Cx, FunctionalState NewState);

/**
 * Enables or disables the specified I2C general call feature.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void I2C_GeneralCallCmd(I2C_TypeDef *I2Cx, FunctionalState NewState);

/**
 * Enables or disables the specified I2C interrupts.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param I2C_IT specifies the I2C interrupts sources to be enabled or disabled.
 *    I2C_IT_BUF - Buffer interrupt mask.
 *    I2C_IT_EVT - Event interrupt mask.
 *    I2C_IT_ERR - Error interrupt mask.
 * @param NewState ENABLE or DISABLE.
 */
void I2C_ITConfig(I2C_TypeDef *I2Cx, uint16_t I2C_IT, FunctionalState NewState);

/**
 * Sends a data byte through the I2Cx peripheral.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param Data Byte to be transmitted.
 */
void I2C_SendData(I2C_TypeDef *I2Cx, uint8_t Data);

/**
 * Returns the most recent received data by the I2Cx peripheral.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 *
 * @return The value of the received data.
 */
uint8_t I2C_ReceiveData(I2C_TypeDef *I2Cx);

/**
 * Transmits the address byte to select the slave device.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param Address specifies the slave address which will be transmitted.
 * @param I2C_Direction specifies whether the I2C device will be a
 * Transmitter (I2C_Direction_Transmitter) or a Receiver (I2C_Direction_Receiver)
 */
void I2C_Send7bitAddress(I2C_TypeDef *I2Cx, uint8_t Address, uint8_t I2C_Direction);

/**
 * Reads the specified I2C register and returns its value.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param I2C_Register specifies the register to read.
 *    I2C_Register_CTLR1
 *    I2C_Register_CTLR2
 *    I2C_Register_OADDR1
 *    I2C_Register_OADDR2
 *    I2C_Register_DATAR
 *    I2C_Register_STAR1
 *    I2C_Register_STAR2
 *    I2C_Register_CKCFGR
 */
uint16_t I2C_ReadRegister(I2C_TypeDef *I2Cx, uint8_t I2C_Register);

/**
 * Enables or disables the specified I2C software reset.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void I2C_SoftwareResetCmd(I2C_TypeDef *I2Cx, FunctionalState NewState);

/**
 * Selects the specified I2C NACK position in master receiver mode.
 *
 * Note:
 *    This function configures the same bit (POS) as I2C_PECPositionConfig() 
 *    but is intended to be used in I2C mode while I2C_PECPositionConfig() 
 *    is intended to used in SMBUS mode. 
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param I2C_NACKPosition specifies the NACK position.
 *    I2C_NACKPosition_Next - indicates that the next byte will be
 *    the last received byte.
 *    I2C_NACKPosition_Current - indicates that current byte is the
 *    last received byte.
 */
void I2C_NACKPositionConfig(I2C_TypeDef *I2Cx, uint16_t I2C_NACKPosition);

/**
 * Enables or disables the specified I2C PEC transfer.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void I2C_TransmitPEC(I2C_TypeDef *I2Cx, FunctionalState NewState);

/**
 * Selects the specified I2C PEC position.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param I2C_PECPosition specifies the PEC position.
 *    I2C_PECPosition_Next - indicates that the next byte is PEC.
 *    I2C_PECPosition_Current - indicates that current byte is PEC.
 */
void I2C_PECPositionConfig(I2C_TypeDef *I2Cx, uint16_t I2C_PECPosition);

/**
 * Enables or disables the PEC value calculation of the transferred bytes.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void I2C_CalculatePEC(I2C_TypeDef *I2Cx, FunctionalState NewState);

/**
 * Returns the PEC value for the specified I2C.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 *
 * @return The PEC value.
 */
uint8_t I2C_GetPEC(I2C_TypeDef *I2Cx);

/**
 * Enables or disables the specified I2C ARP.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void I2C_ARPCmd(I2C_TypeDef *I2Cx, FunctionalState NewState);

/**
 * Enables or disables the specified I2C Clock stretching.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void I2C_StretchClockCmd(I2C_TypeDef *I2Cx, FunctionalState NewState);

/**
 * Selects the specified I2C fast mode duty cycle.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param I2C_DutyCycle specifies the fast mode duty cycle.
 *    I2C_DutyCycle_2 - I2C fast mode Tlow/Thigh = 2.
 *    I2C_DutyCycle_16_9 - I2C fast mode Tlow/Thigh = 16/9.
 */
void I2C_FastModeDutyCycleConfig(I2C_TypeDef *I2Cx, uint16_t I2C_DutyCycle);

/**
 *
 *                         I2C State Monitoring Functions
 *                       
 ****************************************************************************************   
 * This I2C driver provides three different ways for I2C state monitoring
 *  profit the application requirements and constraints:
 *        
 *  
 * a) First way:
 *    Using I2C_CheckEvent() function:
 *    It compares the status registers (STARR1 and STAR2) content to a given event
 *    (can be the combination of more flags).
 *    If the current status registers includes the given flags  will return SUCCESS.
 *    and  if the current status registers miss flags will returns ERROR.
 *    - When to use:
 *      - This function is suitable for most applications as well as for startup 
 *      activity since the events are fully described in the product reference manual 
 *      (CH32V03RM).
 *      - It is also suitable for users who need to define their own events.
 *    - Limitations:
 *      - If an error occurs besides to the monitored error,
 *        the I2C_CheckEvent() function may return SUCCESS despite the communication
 *       in corrupted state.  it is suggeted to use error interrupts to monitor the error
 *        events and handle them in IRQ handler.
 *
 *        
 *        Note: 
 *        The following functions are recommended for error management: :
 *          - I2C_ITConfig() main function of configure and enable the error interrupts.
 *          - I2Cx_ER_IRQHandler() will be called when the error interrupt happen.
 *            Where x is the peripheral instance (I2C1, I2C2 ...)
 *          -  I2Cx_ER_IRQHandler() will call I2C_GetFlagStatus() or I2C_GetITStatus() functions
 *            to determine which error occurred.
 *          - I2C_ClearFlag() \ I2C_ClearITPendingBit() \ I2C_SoftwareResetCmd()
 *            \ I2C_GenerateStop() will be use to clear the error flag and source,
 *            and return to correct communication status.
 *            
 *
 *  b) Second way:
 *     Using the function to get a single word(uint32_t) composed of status register 1 and register 2. 
 *     (Status Register 2 value is shifted left by 16 bits and concatenated to Status Register 1).
 *     - When to use:
 *
 *       - This function is suitable for the same applications above but it 
 *         don't have the limitations of I2C_GetFlagStatus() function .
 *         The returned value could be compared to events already defined in the 
 *         library (CH32V00x_i2c.h) or to custom values defined by user.
 *       - This function can be used to monitor the status of multiple flags simultaneously.
 *       - Contrary to the I2C_CheckEvent () function, this function can choose the time to
 *         accept the event according to the user's needs (when all event flags are set and  
 *         no other flags are set, or only when the required flags are set) 
 *     
 *     - Limitations:
 *       - User may need to define his own events.
 *       - Same remark concerning the error management is applicable for this 
 *         function if user decides to check only regular communication flags (and 
 *         ignores error flags).
 *     
 *
 *  c) Third way:
 *     Using the function I2C_GetFlagStatus() get the status of 
 *     one single flag . 
 *     - When to use:
 *        - This function could be used for specific applications or in debug phase.
 *        - It is suitable when only one flag checking is needed . 
 *          
 *     - Limitations: 
 *        - Call this function to access the status register. Some flag bits may be cleared.           
 *       - Function may need to be called twice or more in order to monitor one single event. 
 */
            
/**
 * Checks whether the last I2Cx Event is equal to the one passed
 * as parameter.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param I2C_EVENT specifies the event to be checked.
 *    I2C_EVENT_SLAVE_TRANSMITTER_ADDRESS_MATCHED - EVT1.
 *    I2C_EVENT_SLAVE_RECEIVER_ADDRESS_MATCHED - EVT1.
 *    I2C_EVENT_SLAVE_TRANSMITTER_SECONDADDRESS_MATCHED - EVT1.
 *    I2C_EVENT_SLAVE_RECEIVER_SECONDADDRESS_MATCHED - EVT1.
 *    I2C_EVENT_SLAVE_GENERALCALLADDRESS_MATCHED - EVT1.
 *    I2C_EVENT_SLAVE_BYTE_RECEIVED - EVT2.
 *    (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_DUALF) - EVT2.
 *    (I2C_EVENT_SLAVE_BYTE_RECEIVED | I2C_FLAG_GENCALL) - EVT2.
 *    I2C_EVENT_SLAVE_BYTE_TRANSMITTED - EVT3.
 *    (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_DUALF) - EVT3.
 *    (I2C_EVENT_SLAVE_BYTE_TRANSMITTED | I2C_FLAG_GENCALL) - EVT3.
 *    I2C_EVENT_SLAVE_ACK_FAILURE - EVT3_2.
 *    I2C_EVENT_SLAVE_STOP_DETECTED - EVT4.
 *    I2C_EVENT_MASTER_MODE_SELECT - EVT5.
 *    I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED - EVT6.
 *    I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED - EVT6.
 *    I2C_EVENT_MASTER_BYTE_RECEIVED - EVT7.
 *    I2C_EVENT_MASTER_BYTE_TRANSMITTING - EVT8.
 *    I2C_EVENT_MASTER_BYTE_TRANSMITTED - EVT8_2.
 *    I2C_EVENT_MASTER_MODE_ADDRESS10 - EVT9.
 *
 * @return READY or NoREADY.
 */
ErrorStatus I2C_CheckEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT);

/**
 * Returns the last I2Cx Event.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 */
uint32_t I2C_GetLastEvent(I2C_TypeDef* I2Cx);

/**
 * Checks whether the last I2Cx Event is equal to the one passed
 * as parameter.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param I2C_FLAG specifies the flag to check.
 *    I2C_FLAG_DUALF - Dual flag (Slave mode).
 *    I2C_FLAG_GENCALL - General call header flag (Slave mode).
 *    I2C_FLAG_TRA - Transmitter/Receiver flag.
 *    I2C_FLAG_BUSY - Bus busy flag.
 *    I2C_FLAG_MSL - Master/Slave flag.
 *    I2C_FLAG_PECERR - PEC error in reception flag.
 *    I2C_FLAG_OVR - Overrun/Underrun flag (Slave mode).
 *    I2C_FLAG_AF - Acknowledge failure flag.
 *    I2C_FLAG_ARLO - Arbitration lost flag (Master mode).
 *    I2C_FLAG_BERR - Bus error flag.
 *    I2C_FLAG_TXE - Data register empty flag (Transmitter).
 *    I2C_FLAG_RXNE - Data register not empty (Receiver) flag.
 *    I2C_FLAG_STOPF - Stop detection flag (Slave mode).
 *    I2C_FLAG_ADD10 - 10-bit header sent flag (Master mode).
 *    I2C_FLAG_BTF - Byte transfer finished flag.
 *    I2C_FLAG_ADDR - Address sent flag (Master mode) "ADSL"
 *    Address matched flag (Slave mode)"ENDA".
 *    I2C_FLAG_SB - Start bit flag (Master mode).
 *
 * @return SET or RESET.
 */
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint32_t I2C_FLAG);


/**
 * Clears the I2Cx's pending flags.
 *
 * Note:
 *  - STOPF (STOP detection) is cleared by software sequence: a read operation 
 *    to I2C_STAR1 register (I2C_GetFlagStatus()) followed by a write operation 
 *    to I2C_CTLR1 register (I2C_Cmd() to re-enable the I2C peripheral).
 *  - ADD10 (10-bit header sent) is cleared by software sequence: a read 
 *    operation to I2C_SATR1 (I2C_GetFlagStatus()) followed by writing the 
 *    second byte of the address in DATAR register.
 *  - BTF (Byte Transfer Finished) is cleared by software sequence: a read 
 *    operation to I2C_SATR1 register (I2C_GetFlagStatus()) followed by a 
 *    read/write to I2C_DATAR register (I2C_SendData()).
 *  - ADDR (Address sent) is cleared by software sequence: a read operation to 
 *    I2C_SATR1 register (I2C_GetFlagStatus()) followed by a read operation to 
 *    I2C_SATR2 register ((void)(I2Cx->SR2)).
 *  - SB (Start Bit) is cleared software sequence: a read operation to I2C_STAR1
 *    register (I2C_GetFlagStatus()) followed by a write operation to I2C_DATAR
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param I2C_FLAG specifies the flag to clear.
 *    I2C_FLAG_SMBALERT - SMBus Alert flag.
 *    I2C_FLAG_TIMEOUT - Timeout or Tlow error flag.
 *    I2C_FLAG_PECERR - PEC error in reception flag.
 *    I2C_FLAG_OVR - Overrun/Underrun flag (Slave mode).
 *    I2C_FLAG_AF - Acknowledge failure flag.
 *    I2C_FLAG_ARLO - Arbitration lost flag (Master mode).
 *    I2C_FLAG_BERR - Bus error flag.
 */
void I2C_ClearFlag(I2C_TypeDef *I2Cx, uint32_t I2C_FLAG);

/**
 * Checks whether the specified I2C interrupt has occurred or not.
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param II2C_IT specifies the interrupt source to check.
 *    I2C_IT_PECERR - PEC error in reception flag.
 *    I2C_IT_OVR - Overrun/Underrun flag (Slave mode).
 *    I2C_IT_AF - Acknowledge failure flag.
 *    I2C_IT_ARLO - Arbitration lost flag (Master mode).
 *    I2C_IT_BERR - Bus error flag.
 *    I2C_IT_TXE - Data register empty flag (Transmitter).
 *    I2C_IT_RXNE - Data register not empty (Receiver) flag.
 *    I2C_IT_STOPF - Stop detection flag (Slave mode).
 *    I2C_IT_ADD10 - 10-bit header sent flag (Master mode).
 *    I2C_IT_BTF - Byte transfer finished flag.
 *    I2C_IT_ADDR - Address sent flag (Master mode) "ADSL"  Address matched
 *    flag (Slave mode)"ENDAD".
 *    I2C_IT_SB - Start bit flag (Master mode).
 */
ITStatus I2C_GetITStatus(I2C_TypeDef *I2Cx, uint32_t I2C_IT);

/**
 * Clears the I2Cx interrupt pending bits.
 *
 * Note:
 *  - STOPF (STOP detection) is cleared by software sequence: a read operation 
 *    to I2C_STAR1 register (I2C_GetITStatus()) followed by a write operation to 
 *    I2C_CTLR1 register (I2C_Cmd() to re-enable the I2C peripheral).
 *  - ADD10 (10-bit header sent) is cleared by software sequence: a read 
 *    operation to I2C_STAR1 (I2C_GetITStatus()) followed by writing the second 
 *    byte of the address in I2C_DATAR register.
 *  - BTF (Byte Transfer Finished) is cleared by software sequence: a read 
 *    operation to I2C_STAR1 register (I2C_GetITStatus()) followed by a 
 *    read/write to I2C_DATAR register (I2C_SendData()).
 *  - ADDR (Address sent) is cleared by software sequence: a read operation to 
 *    I2C_STAR1 register (I2C_GetITStatus()) followed by a read operation to 
 *    I2C_STAR2 register ((void)(I2Cx->SR2)).
 *  - SB (Start Bit) is cleared by software sequence: a read operation to 
 *    I2C_STAR1 register (I2C_GetITStatus()) followed by a write operation to 
 *    I2C_DATAR register (I2C_SendData()).
 *
 * @param I2Cx where x can be 1 to select the I2C peripheral.
 * @param I2C_IT specifies the interrupt pending bit to clear.
 *    I2C_IT_PECERR - PEC error in reception  interrupt.
 *    I2C_IT_OVR - Overrun/Underrun interrupt (Slave mode).
 *    I2C_IT_AF - Acknowledge failure interrupt.
 *    I2C_IT_ARLO - Arbitration lost interrupt (Master mode).
 *    I2C_IT_BERR - Bus error interrupt.
 */
void I2C_ClearITPendingBit(I2C_TypeDef *I2Cx, uint32_t I2C_IT);


#ifdef __cplusplus
}
#endif

#endif /*__CH32V00x_I2C_H */
