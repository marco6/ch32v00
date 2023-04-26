#ifndef __CH32V00x_RCC_H
#define __CH32V00x_RCC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ch32v00x/device.h>

/* RCC_Exported_Types */
typedef struct RCC_ClocksTypeDef {
    uint32_t SYSCLK_Frequency; /* returns SYSCLK clock frequency expressed in Hz */
    uint32_t HCLK_Frequency;   /* returns HCLK clock frequency expressed in Hz */
    uint32_t PCLK1_Frequency;  /* returns PCLK1 clock frequency expressed in Hz */
    uint32_t PCLK2_Frequency;  /* returns PCLK2 clock frequency expressed in Hz */
    uint32_t ADCCLK_Frequency; /* returns ADCCLK clock frequency expressed in Hz */
} RCC_ClocksTypeDef;

/* HSE_configuration */
#define RCC_HSE_OFF                      ((uint32_t)0x00000000)
#define RCC_HSE_ON                       ((uint32_t)0x00010000)
#define RCC_HSE_Bypass                   ((uint32_t)0x00040000)

/* PLL_entry_clock_source */
#define RCC_PLLSource_HSI_MUL2           ((uint32_t)0x00000000)
#define RCC_PLLSource_HSE_MUL2           ((uint32_t)0x00030000)

/* System_clock_source */
#define RCC_SYSCLKSource_HSI             ((uint32_t)0x00000000)
#define RCC_SYSCLKSource_HSE             ((uint32_t)0x00000001)
#define RCC_SYSCLKSource_PLLCLK          ((uint32_t)0x00000002)

/* AHB_clock_source */
#define RCC_SYSCLK_Div1                  ((uint32_t)0x00000000)
#define RCC_SYSCLK_Div2                  ((uint32_t)0x00000010)
#define RCC_SYSCLK_Div3                  ((uint32_t)0x00000020)
#define RCC_SYSCLK_Div4                  ((uint32_t)0x00000030)
#define RCC_SYSCLK_Div5                  ((uint32_t)0x00000040)
#define RCC_SYSCLK_Div6                  ((uint32_t)0x00000050)
#define RCC_SYSCLK_Div7                  ((uint32_t)0x00000060)
#define RCC_SYSCLK_Div8                  ((uint32_t)0x00000070)
#define RCC_SYSCLK_Div16                 ((uint32_t)0x000000B0)
#define RCC_SYSCLK_Div32                 ((uint32_t)0x000000C0)
#define RCC_SYSCLK_Div64                 ((uint32_t)0x000000D0)
#define RCC_SYSCLK_Div128                ((uint32_t)0x000000E0)
#define RCC_SYSCLK_Div256                ((uint32_t)0x000000F0)

/* RCC_Interrupt_source */
#define RCC_IT_LSIRDY                    ((uint8_t)0x01)
#define RCC_IT_HSIRDY                    ((uint8_t)0x04)
#define RCC_IT_HSERDY                    ((uint8_t)0x08)
#define RCC_IT_PLLRDY                    ((uint8_t)0x10)
#define RCC_IT_CSS                       ((uint8_t)0x80)

/* ADC_clock_source */
#define RCC_PCLK2_Div2                   ((uint32_t)0x00000000)
#define RCC_PCLK2_Div4                   ((uint32_t)0x00004000)
#define RCC_PCLK2_Div6                   ((uint32_t)0x00008000)
#define RCC_PCLK2_Div8                   ((uint32_t)0x0000C000)
#define RCC_PCLK2_Div12                  ((uint32_t)0x0000A000)
#define RCC_PCLK2_Div16                  ((uint32_t)0x0000E000)
#define RCC_PCLK2_Div24                  ((uint32_t)0x0000A800)
#define RCC_PCLK2_Div32                  ((uint32_t)0x0000E800)
#define RCC_PCLK2_Div48                  ((uint32_t)0x0000B000)
#define RCC_PCLK2_Div64                  ((uint32_t)0x0000F000)
#define RCC_PCLK2_Div96                  ((uint32_t)0x0000B800)
#define RCC_PCLK2_Div128                 ((uint32_t)0x0000F800)

/* AHB_peripheral */
#define RCC_AHBPeriph_DMA1               ((uint32_t)0x00000001)
#define RCC_AHBPeriph_SRAM               ((uint32_t)0x00000004)

/* APB2_peripheral */
#define RCC_APB2Periph_AFIO              ((uint32_t)0x00000001)
#define RCC_APB2Periph_GPIOA             ((uint32_t)0x00000004)
#define RCC_APB2Periph_GPIOC             ((uint32_t)0x00000010)
#define RCC_APB2Periph_GPIOD             ((uint32_t)0x00000020)
#define RCC_APB2Periph_ADC1              ((uint32_t)0x00000200)
#define RCC_APB2Periph_TIM1              ((uint32_t)0x00000800)
#define RCC_APB2Periph_SPI1              ((uint32_t)0x00001000)
#define RCC_APB2Periph_USART1            ((uint32_t)0x00004000)

/* APB1_peripheral */
#define RCC_APB1Periph_TIM2              ((uint32_t)0x00000001)
#define RCC_APB1Periph_WWDG              ((uint32_t)0x00000800)
#define RCC_APB1Periph_I2C1              ((uint32_t)0x00200000)
#define RCC_APB1Periph_PWR               ((uint32_t)0x10000000)

/* Clock_source_to_output_on_MCO_pin */
#define RCC_MCO_NoClock                  ((uint8_t)0x00)
#define RCC_MCO_SYSCLK                   ((uint8_t)0x04)
#define RCC_MCO_HSI                      ((uint8_t)0x05)
#define RCC_MCO_HSE                      ((uint8_t)0x06)
#define RCC_MCO_PLLCLK                   ((uint8_t)0x07)

/* RCC_Flag */
#define RCC_FLAG_HSIRDY                  ((uint8_t)0x21)
#define RCC_FLAG_HSERDY                  ((uint8_t)0x31)
#define RCC_FLAG_PLLRDY                  ((uint8_t)0x39)
#define RCC_FLAG_LSIRDY                  ((uint8_t)0x61)
#define RCC_FLAG_PINRST                  ((uint8_t)0x7A)
#define RCC_FLAG_PORRST                  ((uint8_t)0x7B)
#define RCC_FLAG_SFTRST                  ((uint8_t)0x7C)
#define RCC_FLAG_IWDGRST                 ((uint8_t)0x7D)
#define RCC_FLAG_WWDGRST                 ((uint8_t)0x7E)
#define RCC_FLAG_LPWRRST                 ((uint8_t)0x7F)

/* SysTick_clock_source */
#define SysTick_CLKSource_HCLK_Div8      ((uint32_t)0xFFFFFFFB)
#define SysTick_CLKSource_HCLK           ((uint32_t)0x00000004)

extern uint32_t SystemCoreClock;          /* System Clock Frequency (Core Clock) */

/**
 * Resets the RCC clock configuration to the default reset state.
 */
void RCC_DeInit(void);

/**
 * Configures the External High Speed oscillator (HSE).
 *
 * Note:
 * HSE can not be stopped if it is used directly or through the PLL as system clock.
 *
 * @param RCC_HSE 
 *    RCC_HSE_OFF - HSE oscillator OFF.
 *    RCC_HSE_ON - HSE oscillator ON.
 *    RCC_HSE_Bypass - HSE oscillator bypassed with external clock.
 */
void RCC_HSEConfig(uint32_t RCC_HSE);

/**
 * Waits for HSE start-up.
 *
 * @return READY when HSE oscillator is stable and ready to use,
 * NoREADY when HSE oscillator not yet ready.
 */
ErrorStatus RCC_WaitForHSEStartUp(void);

/**
 * Adjusts the Internal High Speed oscillator (HSI) calibration value.
 *
 * @param HSICalibrationValue specifies the calibration trimming value.
 * This parameter must be a number between 0 and 0x1F.
 */
void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue);

/**
 * Enables or disables the Internal High Speed oscillator (HSI).
 *
 * @param NewState ENABLE or DISABLE.
 */
void RCC_HSICmd(FunctionalState NewState);

/**
 * Configures the PLL clock source and multiplication factor.
 *
 * @param RCC_PLLSource specifies the PLL entry clock source.
 *    RCC_PLLSource_HSI_MUL2 - HSI oscillator clock*2
 *    selected as PLL clock entry.
 *    RCC_PLLSource_HSE_MUL2 - HSE oscillator clock*2
 *    selected as PLL clock entry.
 */
void RCC_PLLConfig(uint32_t RCC_PLLSource);

/**
 * Enables or disables the PLL.
 *
 * Note:
 * The PLL can not be disabled if it is used as system clock.
 *
 * @param NewState ENABLE or DISABLE.
 */
void RCC_PLLCmd(FunctionalState NewState);

/**
 * Configures the system clock (SYSCLK).
 *
 * @param RCC_SYSCLKSource specifies the clock source used as system clock.
 *    RCC_SYSCLKSource_HSI - HSI selected as system clock.
 *    RCC_SYSCLKSource_HSE - HSE selected as system clock.
 *    RCC_SYSCLKSource_PLLCLK - PLL selected as system clock.
 */
void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource);

/**
 * Returns the clock source used as system clock.
 *
 * @return a value among:
 *    0x00 - HSI used as system clock.
 *    0x04 - HSE used as system clock.
 *    0x08 - PLL used as system clock.
 */
uint8_t RCC_GetSYSCLKSource(void);

/**
 * Configures the AHB clock (HCLK).
 *
 * @param RCC_SYSCLK defines the AHB clock divider. This clock is derived from
 * the system clock (SYSCLK).
 *    RCC_SYSCLK_Div1 - AHB clock = SYSCLK.
 *    RCC_SYSCLK_Div2 - AHB clock = SYSCLK/2.
 *    RCC_SYSCLK_Div3 - AHB clock = SYSCLK/3.
 *    RCC_SYSCLK_Div4 - AHB clock = SYSCLK/4.
 *    RCC_SYSCLK_Div5 - AHB clock = SYSCLK/5.
 *    RCC_SYSCLK_Div6 - AHB clock = SYSCLK/6.
 *    RCC_SYSCLK_Div7 - AHB clock = SYSCLK/7.
 *    RCC_SYSCLK_Div8 - AHB clock = SYSCLK/8.
 *    RCC_SYSCLK_Div16 - AHB clock = SYSCLK/16.
 *    RCC_SYSCLK_Div32 - AHB clock = SYSCLK/32.
 *    RCC_SYSCLK_Div64 - AHB clock = SYSCLK/64.
 *    RCC_SYSCLK_Div128 - AHB clock = SYSCLK/128.
 *    RCC_SYSCLK_Div256 - AHB clock = SYSCLK/256.
 */
void RCC_HCLKConfig(uint32_t RCC_SYSCLK);

/**
 * Enables or disables the specified RCC interrupts.
 *
 * @param RCC_IT specifies the RCC interrupt sources to be enabled or disabled.
 *    RCC_IT_LSIRDY - LSI ready interrupt.
 *    RCC_IT_HSIRDY - HSI ready interrupt.
 *    RCC_IT_HSERDY - HSE ready interrupt.
 *    RCC_IT_PLLRDY - PLL ready interrupt.
 * @param NewState ENABLE or DISABLE.
 */
void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState);

/**
 * Configures the ADC clock (ADCCLK).
 *
 * @param RCC_PCLK2 defines the ADC clock divider. This clock is derived from
 * the APB2 clock (PCLK2).
 *    RCC_PCLK2_Div2 - ADC clock = PCLK2/2.
 *    RCC_PCLK2_Div4 - ADC clock = PCLK2/4.
 *    RCC_PCLK2_Div6 - ADC clock = PCLK2/6.
 *    RCC_PCLK2_Div8 - ADC clock = PCLK2/8.
 *    RCC_PCLK2_Div12 - ADC clock = PCLK2/12.
 *    RCC_PCLK2_Div16 - ADC clock = PCLK2/16.
 *    RCC_PCLK2_Div24 - ADC clock = PCLK2/24.
 *    RCC_PCLK2_Div32 - ADC clock = PCLK2/32.
 *    RCC_PCLK2_Div48 - ADC clock = PCLK2/48.
 *    RCC_PCLK2_Div64 - ADC clock = PCLK2/64.
 *    RCC_PCLK2_Div96 - ADC clock = PCLK2/96.
 *    RCC_PCLK2_Div128 - ADC clock = PCLK2/128.
 */
void RCC_ADCCLKConfig(uint32_t RCC_PCLK2);

/**
 * Enables or disables the Internal Low Speed oscillator (LSI).
 *
 * Note:
 * LSI can not be disabled if the IWDG is running.
 *
 * @param NewState ENABLE or DISABLE.
 */
void RCC_LSICmd(FunctionalState NewState);

/**
 * The result of this function could be not correct when using
 * fractional value for HSE crystal.
 *
 * @param RCC_Clocks pointer to a RCC_ClocksTypeDef structure which will hold
 * the clocks frequencies.
 */
void RCC_GetClocksFreq(RCC_ClocksTypeDef *RCC_Clocks);

/**
 * Enables or disables the AHB peripheral clock.
 *
 * Note:
 * SRAM clock can be disabled only during sleep mode.
 *
 * @param RCC_AHBPeriph specifies the AHB peripheral to gates its clock.
 * Either RCC_AHBPeriph_DMA1, RCC_AHBPeriph_SRAM
 * @param NewState ENABLE or DISABLE.
 */
void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState);

/**
 * Enables or disables the High Speed APB (APB2) peripheral clock.
 *
 * @param RCC_APB2Periph specifies the APB2 peripheral to gates its clock.
 * Available values:
 *    RCC_APB2Periph_AFIO
 *    RCC_APB2Periph_GPIOA
 *    RCC_APB2Periph_GPIOC
 *    RCC_APB2Periph_GPIOD
 *    RCC_APB2Periph_ADC1
 *    RCC_APB2Periph_TIM1
 *    RCC_APB2Periph_SPI1
 *    RCC_APB2Periph_USART1
 * @param NewState ENABLE or DISABLE
 */
void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);

/**
 * Enables or disables the Low Speed APB (APB1) peripheral clock.
 *
 * @param RCC_APB1Periph specifies the APB1 peripheral to gates its clock.
 * Available values:
 *    RCC_APB1Periph_TIM2
 *    RCC_APB1Periph_WWDG
 *    RCC_APB1Periph_I2C1
 *    RCC_APB1Periph_PWR
 * @param NewState ENABLE or DISABLE.
 */
void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);

/**
 * Forces or releases High Speed APB (APB2) peripheral reset.
 *
 * @param RCC_APB2Periph specifies the APB2 peripheral to reset.
 * Available values:
 *    RCC_APB2Periph_AFIO
 *    RCC_APB2Periph_GPIOA
 *    RCC_APB2Periph_GPIOC
 *    RCC_APB2Periph_GPIOD
 *    RCC_APB2Periph_ADC1
 *    RCC_APB2Periph_TIM1
 *    RCC_APB2Periph_SPI1
 *    RCC_APB2Periph_USART1
 * @param NewState ENABLE or DISABLE
 */
void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState);

/**
 * Forces or releases Low Speed APB (APB1) peripheral reset.
 *
 * @param RCC_APB1Periph specifies the APB1 peripheral to reset.
 * Available values:
 *    RCC_APB1Periph_TIM2
 *    RCC_APB1Periph_WWDG
 *    RCC_APB1Periph_I2C1
 *    RCC_APB1Periph_PWR
 * @param NewState ENABLE or DISABLE.
 */
void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState);

/**
 * Enables or disables the Clock Security System.
 *
 * @param NewState ENABLE or DISABLE.
 */
void RCC_ClockSecuritySystemCmd(FunctionalState NewState);

/**
 * Selects the clock source to output on MCO pin.
 *
 * @param RCC_MCO specifies the clock source to output.
 *    RCC_MCO_NoClock - No clock selected.
 *    RCC_MCO_SYSCLK - System clock selected.
 *    RCC_MCO_HSI - HSI oscillator clock selected.
 *    RCC_MCO_HSE - HSE oscillator clock selected.
 *    RCC_MCO_PLLCLK - PLL clock selected.
 */
void RCC_MCOConfig(uint8_t RCC_MCO);

/**
 * Checks whether the specified RCC flag is set or not.
 *
 * @param RCC_FLAG specifies the flag to check.
 *    RCC_FLAG_HSIRDY - HSI oscillator clock ready.
 *    RCC_FLAG_HSERDY - HSE oscillator clock ready.
 *    RCC_FLAG_PLLRDY - PLL clock ready.
 *    RCC_FLAG_LSIRDY - LSI oscillator clock ready.
 *    RCC_FLAG_PINRST - Pin reset.
 *    RCC_FLAG_PORRST - POR/PDR reset.
 *    RCC_FLAG_SFTRST - Software reset.
 *    RCC_FLAG_IWDGRST - Independent Watchdog reset.
 *    RCC_FLAG_WWDGRST - Window Watchdog reset.
 *    RCC_FLAG_LPWRRST - Low Power reset.
 *
 * @return FlagStatus - SET or RESET.
 */
FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG);

/**
 * Clears the RCC reset flags.
 *
 * Note:   
 * The reset flags are: RCC_FLAG_PINRST, RCC_FLAG_PORRST, RCC_FLAG_SFTRST,
 * RCC_FLAG_IWDGRST, RCC_FLAG_WWDGRST, RCC_FLAG_LPWRRST
 */
void RCC_ClearFlag(void);

/**
 * Checks whether the specified RCC interrupt has occurred or not.
 *
 * @param RCC_IT specifies the RCC interrupt source to check.
 *    RCC_IT_LSIRDY - LSI ready interrupt.
 *    RCC_IT_HSIRDY - HSI ready interrupt.
 *    RCC_IT_HSERDY - HSE ready interrupt.
 *    RCC_IT_PLLRDY - PLL ready interrupt.
 *    RCC_IT_CSS - Clock Security System interrupt.
 *
 * @return SET or RESET.
 */
ITStatus RCC_GetITStatus(uint8_t RCC_IT);

/**
 * Clears the RCC's interrupt pending bits.
 *
 * @param RCC_IT specifies the interrupt pending bit to clear. 
 * Available values are:
 *  - RCC_IT_LSIRDY: LSI ready interrupt.
 *  - RCC_IT_HSIRDY: HSI ready interrupt.
 *  - RCC_IT_HSERDY: HSE ready interrupt.
 *  - RCC_IT_PLLRDY: PLL ready interrupt.
 *  - RCC_IT_CSS: Clock Security System interrupt.
 */
void RCC_ClearITPendingBit(uint8_t RCC_IT);

/**
 * Wait synchronously for n microseconds.
 *
 * @param n microseconds.
 */
void Delay_Us(uint32_t n);

/**
 * Wait synchronously for n milliseconds.
 *
 * @param n milliseconds.
 */
void Delay_Ms(uint32_t n);

#ifdef __cplusplus
}
#endif

#endif /* __CH32V00x_RCC_H */
