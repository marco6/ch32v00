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



