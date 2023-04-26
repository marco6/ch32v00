#ifndef __CH32V00x_WWDG_H
#define __CH32V00x_WWDG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ch32v00x/device.h>

/* WWDG_Prescaler */
#define WWDG_Prescaler_1    ((uint32_t)0x00000000)
#define WWDG_Prescaler_2    ((uint32_t)0x00000080)
#define WWDG_Prescaler_4    ((uint32_t)0x00000100)
#define WWDG_Prescaler_8    ((uint32_t)0x00000180)

/**
 * Deinitializes the WWDG peripheral registers to their default reset values
 */
void WWDG_DeInit(void);

/**
 * Sets the WWDG Prescaler
 *
 * @param WWDG_Prescaler specifies the WWDG Prescaler
 *    WWDG_Prescaler_1 - WWDG counter clock = (PCLK1/4096)/1
 *    WWDG_Prescaler_2 - WWDG counter clock = (PCLK1/4096)/2
 *    WWDG_Prescaler_4 - WWDG counter clock = (PCLK1/4096)/4
 *    WWDG_Prescaler_8 - WWDG counter clock = (PCLK1/4096)/8
 */
void WWDG_SetPrescaler(uint32_t WWDG_Prescaler);

/**
 * Sets the WWDG window value
 *
 * @param WindowValue specifies the window value to be compared to the
 * downcounter,which must be lower than 0x80
 */
void WWDG_SetWindowValue(uint8_t WindowValue);

/**
 * Enables the WWDG Early Wakeup interrupt(EWI)
 */
void WWDG_EnableIT(void);

/**
 * Sets the WWDG counter value
 *
 * @param Counter specifies the watchdog counter value,which must be a
 * number between 0x40 and 0x7F
 */
void WWDG_SetCounter(uint8_t Counter);

/**
 * Enables WWDG and load the counter value
 *
 * @param Counter specifies the watchdog counter value,which must be a
 * number between 0x40 and 0x7F
 */
void WWDG_Enable(uint8_t Counter);

/**
 * Checks whether the Early Wakeup interrupt flag is set or not
 *
 * @return The new state of the Early Wakeup interrupt flag (SET or RESET)
 */
FlagStatus WWDG_GetFlagStatus(void);

/**
 * Clears Early Wakeup interrupt flag
 */
void WWDG_ClearFlag(void);

#ifdef __cplusplus
}
#endif

#endif /* __CH32V00x_WWDG_H */
