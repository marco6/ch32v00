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

void       PWR_DeInit(void);
void       PWR_PVDCmd(FunctionalState NewState);
void       PWR_PVDLevelConfig(uint32_t PWR_PVDLevel);
void       PWR_AutoWakeUpCmd(FunctionalState NewState);
void       PWR_AWU_SetPrescaler(uint32_t AWU_Prescaler);
void       PWR_AWU_SetWindowValue(uint8_t WindowValue);
void       PWR_EnterSTANDBYMode(uint8_t PWR_STANDBYEntry);
FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG);

#ifdef __cplusplus
}
#endif

#endif /* __CH32V00x_PWR_H */
