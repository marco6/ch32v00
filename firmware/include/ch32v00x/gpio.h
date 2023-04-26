#ifndef __CH32V00x_GPIO_H
#define __CH32V00x_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ch32v00x/device.h>

/* Output Maximum frequency selection */
typedef enum GPIOSpeed_TypeDef {
    GPIO_Speed_10MHz = 1,
    GPIO_Speed_2MHz,
    GPIO_Speed_50MHz
} GPIOSpeed_TypeDef;

/* Configuration Mode enumeration */
typedef enum GPIOMode_TypeDef {
    GPIO_Mode_AIN = 0x0,
    GPIO_Mode_IN_FLOATING = 0x04,
    GPIO_Mode_IPD = 0x28,
    GPIO_Mode_IPU = 0x48,
    GPIO_Mode_Out_OD = 0x14,
    GPIO_Mode_Out_PP = 0x10,
    GPIO_Mode_AF_OD = 0x1C,
    GPIO_Mode_AF_PP = 0x18
} GPIOMode_TypeDef;

/* GPIO Init structure definition */
typedef struct GPIO_InitTypeDef {
    /**
     * Specifies the GPIO pins to be configured.
     * This parameter can be any value of @ref GPIO_pins_define
     */
    uint16_t GPIO_Pin;

    /**
     * Specifies the speed for the selected pins.
     * This parameter can be a value of @ref GPIOSpeed_TypeDef
     */
    GPIOSpeed_TypeDef GPIO_Speed;

    /**
     * Specifies the operating mode for the selected pins.
     * This parameter can be a value of @ref GPIOMode_TypeDef
     */
    GPIOMode_TypeDef GPIO_Mode;
} GPIO_InitTypeDef;

/* Bit_SET and Bit_RESET enumeration */
typedef enum BitAction {
    Bit_RESET = 0,
    Bit_SET
} BitAction;

/* GPIO_pins_define */
#define GPIO_Pin_0                     ((uint16_t)0x0001) /* Pin 0 selected */
#define GPIO_Pin_1                     ((uint16_t)0x0002) /* Pin 1 selected */
#define GPIO_Pin_2                     ((uint16_t)0x0004) /* Pin 2 selected */
#define GPIO_Pin_3                     ((uint16_t)0x0008) /* Pin 3 selected */
#define GPIO_Pin_4                     ((uint16_t)0x0010) /* Pin 4 selected */
#define GPIO_Pin_5                     ((uint16_t)0x0020) /* Pin 5 selected */
#define GPIO_Pin_6                     ((uint16_t)0x0040) /* Pin 6 selected */
#define GPIO_Pin_7                     ((uint16_t)0x0080) /* Pin 7 selected */
#define GPIO_Pin_All                   ((uint16_t)0xFFFF) /* All pins selected */

/* GPIO_Remap_define */
#define GPIO_Remap_SPI1                ((uint32_t)0x00000001) /* SPI1 Alternate Function mapping */
#define GPIO_PartialRemap_I2C1         ((uint32_t)0x10000002) /* I2C1 Partial Alternate Function mapping */
#define GPIO_FullRemap_I2C1            ((uint32_t)0x10400002) /* I2C1 Full Alternate Function mapping */
#define GPIO_PartialRemap1_USART1      ((uint32_t)0x80000004) /* USART1 Partial1 Alternate Function mapping */
#define GPIO_PartialRemap2_USART1      ((uint32_t)0x80200000) /* USART1 Partial2 Alternate Function mapping */
#define GPIO_FullRemap_USART1          ((uint32_t)0x80200004) /* USART1 Full Alternate Function mapping */
#define GPIO_PartialRemap1_TIM1        ((uint32_t)0x00160040) /* TIM1 Partial1 Alternate Function mapping */
#define GPIO_PartialRemap2_TIM1        ((uint32_t)0x00160080) /* TIM1 Partial2 Alternate Function mapping */
#define GPIO_FullRemap_TIM1            ((uint32_t)0x001600C0) /* TIM1 Full Alternate Function mapping */
#define GPIO_PartialRemap1_TIM2        ((uint32_t)0x00180100) /* TIM2 Partial1 Alternate Function mapping */
#define GPIO_PartialRemap2_TIM2        ((uint32_t)0x00180200) /* TIM2 Partial2 Alternate Function mapping */
#define GPIO_FullRemap_TIM2            ((uint32_t)0x00180300) /* TIM2 Full Alternate Function mapping */
#define GPIO_Remap_PA1_2               ((uint32_t)0x00008000) /* PA1 and PA2 Alternate Function mapping */
#define GPIO_Remap_ADC1_ETRGINJ        ((uint32_t)0x00200002) /* ADC1 External Trigger Injected Conversion remapping */
#define GPIO_Remap_ADC1_ETRGREG        ((uint32_t)0x00200004) /* ADC1 External Trigger Regular Conversion remapping */
#define GPIO_Remap_LSI_CAL             ((uint32_t)0x00200080) /* LSI calibration Alternate Function mapping */
#define GPIO_Remap_SDI_Disable         ((uint32_t)0x00300400) /* SDI Disabled */

/* GPIO_Port_Sources */
#define GPIO_PortSourceGPIOA           ((uint8_t)0x00)
#define GPIO_PortSourceGPIOC           ((uint8_t)0x02)
#define GPIO_PortSourceGPIOD           ((uint8_t)0x03)

/* GPIO_Pin_sources */
#define GPIO_PinSource0                ((uint8_t)0x00)
#define GPIO_PinSource1                ((uint8_t)0x01)
#define GPIO_PinSource2                ((uint8_t)0x02)
#define GPIO_PinSource3                ((uint8_t)0x03)
#define GPIO_PinSource4                ((uint8_t)0x04)
#define GPIO_PinSource5                ((uint8_t)0x05)
#define GPIO_PinSource6                ((uint8_t)0x06)
#define GPIO_PinSource7                ((uint8_t)0x07)

/**
 * Deinitializes the GPIOx peripheral registers to their default
 * reset values.
 *
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 */
void GPIO_DeInit(GPIO_TypeDef *GPIOx);

/**
 * Deinitializes the Alternate Functions (remap, event control
 * and EXTI configuration) registers to their default reset values.
 */
void GPIO_AFIODeInit(void);

/**
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @param GPIO_InitStruct pointer to a GPIO_InitTypeDef structure that
 * contains the configuration information for the specified GPIO peripheral.
 */
void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct);

/**
 * Fills each GPIO_InitStruct member with its default
 *
 * @param GPIO_InitStruct pointer to a GPIO_InitTypeDef structure
 * which will be initialized.
 */
void GPIO_StructInit(GPIO_InitTypeDef *GPIO_InitStruct);

/**
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @param GPIO_Pin specifies the port bit to read.
 * This parameter can be GPIO_Pin_x where x can be (0..15).
 *
 * @return The input port pin value.
 */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/**
 * Reads the specified GPIO input data port.
 *
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 *
 * @return The input port pin value.
 */
uint16_t GPIO_ReadInputData(GPIO_TypeDef *GPIOx);

/**
 * Reads the specified output data port bit.
 *
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @param GPIO_Pin specifies the port bit to read.
 * This parameter can be GPIO_Pin_x where x can be (0..15).
 *
 * @return GPIO output pin value 
 */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/**
 * Reads the specified GPIO output data port.
 *
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 *
 * @return  GPIO output port pin value.
 */
uint16_t GPIO_ReadOutputData(GPIO_TypeDef *GPIOx);

/**
 * Sets the selected data port bits.
 *
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @param GPIO_Pin specifies the port bits to be written.
 * This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
 */
void GPIO_SetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/**
 * Clears the selected data port bits.
 *
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @param GPIO_Pin specifies the port bits to be written.
 * This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
 */
void GPIO_ResetBits(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/**
 * Sets or clears the selected data port bit.
 *
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @param GPIO_Pin specifies the port bit to be written.
 * This parameter can be one of GPIO_Pin_x where x can be (0..15).
 * @param BitVal specifies the value to be written to the selected bit.
 *    Bit_SetL - to clear the port pin.
 *    Bit_SetH - to set the port pin.
 */
void GPIO_WriteBit(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, BitAction BitVal);

/**
 * Writes data to the specified GPIO data port.
 *
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @param PortVal specifies the value to be written to the port output data register.
 */
void GPIO_Write(GPIO_TypeDef *GPIOx, uint16_t PortVal);

/**
 * Locks GPIO Pins configuration registers.
 *
 * @param GPIOx where x can be (A..G) to select the GPIO peripheral.
 * @param GPIO_Pin specifies the port bit to be written.
 * This parameter can be any combination of GPIO_Pin_x where x can be (0..15).
 */
void GPIO_PinLockConfig(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

/**
 * Changes the mapping of the specified pin.
 *
 * @param GPIO_Remap selects the pin to remap.
 *    GPIO_Remap_SPI1 - SPI1 Alternate Function mapping
 *    GPIO_PartialRemap_I2C1 - I2C1 Partial Alternate Function mapping
 *    GPIO_PartialRemap_I2C1 - I2C1 Full Alternate Function mapping
 *    GPIO_PartialRemap1_USART1 - USART1 Partial1 Alternate Function mapping
 *    GPIO_PartialRemap2_USART1 - USART1 Partial2 Alternate Function mapping
 *    GPIO_FullRemap_USART1 - USART1 Full Alternate Function mapping
 *    GPIO_PartialRemap1_TIM1 - TIM1 Partial1 Alternate Function mapping
 *    GPIO_PartialRemap2_TIM1 - TIM1 Partial2 Alternate Function mapping
 *    GPIO_FullRemap_TIM1 - TIM1 Full Alternate Function mapping
 *    GPIO_PartialRemap1_TIM2 - TIM2 Partial1 Alternate Function mapping
 *    GPIO_PartialRemap2_TIM2 - TIM2 Partial2 Alternate Function mapping
 *    GPIO_FullRemap_TIM2 - TIM2 Full Alternate Function mapping
 *    GPIO_Remap_PA12 - PA12 Alternate Function mapping
 *    GPIO_Remap_ADC1_ETRGINJ - ADC1 External Trigger Injected Conversion remapping
 *    GPIO_Remap_ADC1_ETRGREG - ADC1 External Trigger Regular Conversion remapping
 *    GPIO_Remap_LSI_CAL - LSI calibration Alternate Function mapping
 *    GPIO_Remap_SDI_Disable - SDI Disabled
 * @param NewState ENABLE or DISABLE.
 */
void GPIO_PinRemapConfig(uint32_t GPIO_Remap, FunctionalState NewState);

/**
 * Selects the GPIO pin used as EXTI Line.
 *
 * @param GPIO_PortSource selects the GPIO port to be used as source for EXTI lines.
 * This parameter can be GPIO_PortSourceGPIOx where x can be (A..G).
 * @param GPIO_PinSource specifies the EXTI line to be configured.
 * This parameter can be GPIO_PinSourcex where x can be (0..7).
 */
void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);

// FIXME these was declared, but there seems to be no implementation...
// void GPIO_EventOutputCmd(FunctionalState NewState);
// void     GPIO_EventOutputConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource);

#ifdef __cplusplus
}
#endif

#endif /* __CH32V00x_GPIO_H */
