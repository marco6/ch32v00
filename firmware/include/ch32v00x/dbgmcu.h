#ifndef __CH32V00x_DBGMCU_H
#define __CH32V00x_DBGMCU_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ch32v00x/device.h>

/* CFGR0 Register */
#define DBGMCU_IWDG_STOP             ((uint32_t)0x00000001)
#define DBGMCU_WWDG_STOP             ((uint32_t)0x00000002)
#define DBGMCU_TIM1_STOP             ((uint32_t)0x00000010)
#define DBGMCU_TIM2_STOP             ((uint32_t)0x00000020)

/**
 * Returns the device revision identifier.
 *
 * @return  Revision identifier.
 */
uint32_t DBGMCU_GetREVID(void);

/**
 * Returns the device identifier.
 *
 * @return  Device identifier.
 */
uint32_t DBGMCU_GetDEVID(void);

/**
 * Return the DEBUGE Control Register
 *
 * @return  DEBUGE Control value
 */
uint32_t __get_DEBUG_CR(void);

/**
 * Set the DEBUGE Control Register
 *
 * @param value set DEBUGE Control value
 */
void __set_DEBUG_CR(uint32_t value);

/**
 * Configures the specified peripheral and low power mode behavior
 *        when the MCU under Debug mode.
 *
 * @param DBGMCU_Periph specifies the peripheral and low power mode.
 *    DBGMCU_IWDG_STOP - Debug IWDG stopped when Core is halted
 *    DBGMCU_WWDG_STOP - Debug WWDG stopped when Core is halted
 *    DBGMCU_TIM1_STOP - TIM1 counter stopped when Core is halted
 *    DBGMCU_TIM2_STOP - TIM2 counter stopped when Core is halted
 * @param NewState ENABLE or DISABLE.
 */
void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState);


#ifdef __cplusplus
}
#endif

#endif /* __CH32V00x_DBGMCU_H */
