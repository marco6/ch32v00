/********************************** (C) COPYRIGHT *******************************
 * File Name          : system_ch32v00x.h
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/08/08
 * Description        : CH32V00x Device Peripheral Access Layer System Header File.
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * SPDX-License-Identifier: Apache-2.0
 *******************************************************************************/
#ifndef __SYSTEM_CH32V00x_H
#define __SYSTEM_CH32V00x_H

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif 

extern uint32_t SystemCoreClock;          /* System Clock Frequency (Core Clock) */

/* System_Exported_Functions */  
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif /*__CH32V00x_SYSTEM_H */



