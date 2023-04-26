#ifndef __CH32V00x_PWR_H
#define __CH32V00x_PWR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ch32v00x/device.h>

/* PVD_detection_level  */
#define PWR_PVDLevel_2V9          ((uint32_t)0x00000000)
#define PWR_PVDLevel_3V1          ((uint32_t)0x00000020)
#define PWR_PVDLevel_3V3          ((uint32_t)0x00000040)
#define PWR_PVDLevel_3V5          ((uint32_t)0x00000060)
#define PWR_PVDLevel_3V7          ((uint32_t)0x00000080)
#define PWR_PVDLevel_3V9          ((uint32_t)0x000000A0)
#define PWR_PVDLevel_4V1          ((uint32_t)0x000000C0)
#define PWR_PVDLevel_4V4          ((uint32_t)0x000000E0)

/* PWR_AWU_Prescaler */
#define PWR_AWU_Prescaler_1       ((uint32_t)0x00000000)
#define PWR_AWU_Prescaler_2       ((uint32_t)0x00000002)
#define PWR_AWU_Prescaler_4       ((uint32_t)0x00000003)
#define PWR_AWU_Prescaler_8       ((uint32_t)0x00000004)
#define PWR_AWU_Prescaler_16      ((uint32_t)0x00000005)
#define PWR_AWU_Prescaler_32      ((uint32_t)0x00000006)
#define PWR_AWU_Prescaler_64      ((uint32_t)0x00000007)
#define PWR_AWU_Prescaler_128     ((uint32_t)0x00000008)
#define PWR_AWU_Prescaler_256     ((uint32_t)0x00000009)
#define PWR_AWU_Prescaler_512     ((uint32_t)0x0000000A)
#define PWR_AWU_Prescaler_1024    ((uint32_t)0x0000000B)
#define PWR_AWU_Prescaler_2048    ((uint32_t)0x0000000C)
#define PWR_AWU_Prescaler_4096    ((uint32_t)0x0000000D)
#define PWR_AWU_Prescaler_10240   ((uint32_t)0x0000000E)
#define PWR_AWU_Prescaler_61440   ((uint32_t)0x0000000F)

/* STOP_mode_entry */
#define PWR_STANDBYEntry_WFI      ((uint8_t)0x01)
#define PWR_STANDBYEntry_WFE      ((uint8_t)0x02)

/* PWR_Flag */
#define PWR_FLAG_PVDO             ((uint32_t)0x00000004)

/**
 * Deinitializes the PWR peripheral registers to their default
 * reset values.
 */
void PWR_DeInit(void);

/**
 * Enables or disables the Power Voltage Detector(PVD).
 *
 * @param NewState new state of the PVD(ENABLE or DISABLE).
 */
void PWR_PVDCmd(FunctionalState NewState);

/**
 * Configures the voltage threshold detected by the Power Voltage
 * Detector(PVD).
 *
 * @param PWR_PVDLevel specifies the PVD detection level
 *    PWR_PVDLevel_2V2 - PVD detection level set to 2.2V
 *    PWR_PVDLevel_2V3 - PVD detection level set to 2.3V
 *    PWR_PVDLevel_2V4 - PVD detection level set to 2.4V
 *    PWR_PVDLevel_2V5 - PVD detection level set to 2.5V
 *    PWR_PVDLevel_2V6 - PVD detection level set to 2.6V
 *    PWR_PVDLevel_2V7 - PVD detection level set to 2.7V
 *    PWR_PVDLevel_2V8 - PVD detection level set to 2.8V
 *    PWR_PVDLevel_2V9 - PVD detection level set to 2.9V
 */
void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel);

/**
 * Enables or disables the Auto WakeUp functionality.
 *
 * @param NewState new state of the Auto WakeUp functionality
 * (ENABLE or DISABLE).
 */
void PWR_AutoWakeUpCmd(FunctionalState NewState);

/**
 * Sets the Auto Wake up Prescaler
 *
 * @param AWU_Prescaler specifies the Auto Wake up Prescaler
 *    PWR_AWU_Prescaler_1 - AWU counter clock = LSI/1
 *    PWR_AWU_Prescaler_2 - AWU counter clock = LSI/2
 *    PWR_AWU_Prescaler_4 - AWU counter clock = LSI/4
 *    PWR_AWU_Prescaler_8 - AWU counter clock = LSI/8
 *    PWR_AWU_Prescaler_16 - AWU counter clock = LSI/16
 *    PWR_AWU_Prescaler_32 - AWU counter clock = LSI/32
 *    PWR_AWU_Prescaler_64 - AWU counter clock = LSI/64
 *    PWR_AWU_Prescaler_128 - AWU counter clock = LSI/128
 *    PWR_AWU_Prescaler_256 - AWU counter clock = LSI/256
 *    PWR_AWU_Prescaler_512 - AWU counter clock = LSI/512
 *    PWR_AWU_Prescaler_1024 - AWU counter clock = LSI/1024
 *    PWR_AWU_Prescaler_2048 - AWU counter clock = LSI/2048
 *    PWR_AWU_Prescaler_4096 - AWU counter clock = LSI/4096
 *    PWR_AWU_Prescaler_10240 - AWU counter clock = LSI/10240
 *    PWR_AWU_Prescaler_61440 - AWU counter clock = LSI/61440
 */
void PWR_AWU_SetPrescaler(uint32_t AWU_Prescaler);

/**
 * Sets the WWDG window value
 *
 * @param WindowValue specifies the window value to be compared to the
 * downcounter,which must be lower than 0x3F
 */
void PWR_AWU_SetWindowValue(uint8_t WindowValue);

/**
 * Enters STANDBY mode.
 *
 * @param PWR_STANDBYEntry specifies if STANDBY mode in entered with WFI or WFE instruction.
 *    PWR_STANDBYEntry_WFI - enter STANDBY mode with WFI instruction
 *    PWR_STANDBYEntry_WFE - enter STANDBY mode with WFE instruction
 */
void PWR_EnterSTANDBYMode(uint8_t PWR_STANDBYEntry);

/**
 * Checks whether the specified PWR flag is set or not.
 *
 * @param PWR_FLAG specifies the flag to check.
 *    PWR_FLAG_PVDO - PVD Output
 *
 * @return  The new state of PWR_FLAG (SET or RESET).
 */
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);


#ifdef __cplusplus
}
#endif

#endif /* __CH32V00x_PWR_H */
