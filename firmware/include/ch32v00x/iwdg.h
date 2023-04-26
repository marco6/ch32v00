#ifndef __CH32V00x_IWDG_H
#define __CH32V00x_IWDG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ch32v00x/device.h>

/* IWDG_WriteAccess */
#define IWDG_WriteAccess_Enable     ((uint16_t)0x5555)
#define IWDG_WriteAccess_Disable    ((uint16_t)0x0000)

/* IWDG_prescaler */
#define IWDG_Prescaler_4            ((uint8_t)0x00)
#define IWDG_Prescaler_8            ((uint8_t)0x01)
#define IWDG_Prescaler_16           ((uint8_t)0x02)
#define IWDG_Prescaler_32           ((uint8_t)0x03)
#define IWDG_Prescaler_64           ((uint8_t)0x04)
#define IWDG_Prescaler_128          ((uint8_t)0x05)
#define IWDG_Prescaler_256          ((uint8_t)0x06)

/* IWDG_Flag */
#define IWDG_FLAG_PVU               ((uint16_t)0x0001)
#define IWDG_FLAG_RVU               ((uint16_t)0x0002)

/**
 * Enables or disables write access to IWDG_PSCR and IWDG_RLDR registers.
 *
 * @param WDG_WriteAccess new state of write access to IWDG_PSCR and
 * IWDG_RLDR registers.
 *    IWDG_WriteAccess_Enable - Enable write access to IWDG_PSCR and
 *    IWDG_RLDR registers.
 *    IWDG_WriteAccess_Disable - Disable write access to IWDG_PSCR
 *    and IWDG_RLDR registers.
 */
void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess);

/**
 * Sets IWDG Prescaler value.
 *
 * @param IWDG_Prescaler specifies the IWDG Prescaler value.
 *    IWDG_Prescaler_4 - IWDG prescaler set to 4.
 *    IWDG_Prescaler_8 - IWDG prescaler set to 8.
 *    IWDG_Prescaler_16 - IWDG prescaler set to 16.
 *    IWDG_Prescaler_32 - IWDG prescaler set to 32.
 *    IWDG_Prescaler_64 - IWDG prescaler set to 64.
 *    IWDG_Prescaler_128 - IWDG prescaler set to 128.
 *    IWDG_Prescaler_256 - IWDG prescaler set to 256.
 */
void IWDG_SetPrescaler(uint8_t IWDG_Prescaler);

/**
 * Sets IWDG Reload value.
 *
 * @param Reload specifies the IWDG Reload value.
 * This parameter must be a number between 0 and 0x0FFF.
 */
void IWDG_SetReload(uint16_t Reload);

/**
 * Reloads IWDG counter with value defined in the reload register.
 */
void IWDG_ReloadCounter(void);

/**
 * Enables IWDG (write access to IWDG_PSCR and IWDG_RLDR registers disabled).
 */
void IWDG_Enable(void);

/**
 * Checks whether the specified IWDG flag is set or not.
 *
 * @param IWDG_FLAG specifies the flag to check.
 *    IWDG_FLAG_PVU - Prescaler Value Update on going.
 *    IWDG_FLAG_RVU - Reload Value Update on going.
 */
FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG);


#ifdef __cplusplus
}
#endif

#endif /* __CH32V00x_IWDG_H */
