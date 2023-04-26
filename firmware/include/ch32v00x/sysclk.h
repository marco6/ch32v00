#ifndef __SYSTEM_CH32V00x_H
#define __SYSTEM_CH32V00x_H

#include <stdint.h>

#ifdef __cplusplus
 extern "C" {
#endif 

/**
 * Update SystemCoreClock variable according to Clock Register Values.
 */
void SystemCoreClockUpdate(void);

/**
 * Overrides the startup logic to setup the clock to HSI.
 * This can be used only once as it will override the 
 * default (weak) symbol for setting up the clock.
 *
 * When no definition for the clock is used, it will default 
 * to 48MHZ.
 *
 * @param Freq frequency of the default system clock. Available
 * values are 8MHz, 24MHz and 48MHz.
 */
#define HSISysClock(Freq)           \
void InitSysClock(void) {           \
    InitSysClockTo_##Freq##_HSI();  \
}                                   \

#define HSENoCheck()

/**
 * Overrides the startup logic to setup the clock to HSE.
 * This can be used only once as it will override the 
 * default (weak) symbol for setting up the clock. This
 * definition accepts an OnFailed function to call if the
 * HSE setup fails.
 *
 * When no sys clock is defined, through either HSISysClock, 
 * or HSESysClock, the system will default to 24MHZ HSI.
 *
 * @param Freq frequency of the default system clock. Available
 * values are 8MHz, 24MHz and 48MHz.
 * @param OnFailed routine to call if HSE setup fails. If no
 * error checking is required, it is possible to pass HSENoCheck.
 */
#define HSESysClock(Freq, OnFailed)         \
void InitSysClock(void) {                   \
    if (InitSysClockTo_##Freq##_HSE()) {    \
        OnFailed();                         \
    }                                       \
}                                           \

/**
 * Sets HSE as System clock source and configure HCLK, PCLK2 and PCLK1 prescalers.
 *
 * This method should never be used outside of InitSysClock routine. 
 * @see HSISysClock and HSESysClock
 */
void InitSysClockTo_8MHz_HSI(void);

/**
 * Sets System clock frequency to 24MHz and configure HCLK, PCLK2 and PCLK1 prescalers.
 *
 * This method should never be used outside of InitSysClock routine. 
 * @see HSISysClock and HSESysClock
 */
void InitSysClockTo_24MHz_HSI(void);

/**
 * Sets System clock frequency to 48MHz and configure HCLK, PCLK2 and PCLK1 prescalers.
 */
void InitSysClockTo_48MHz_HSI(void);

/**
 * Sets System clock frequency to 56MHz and configure HCLK, PCLK2 and PCLK1 prescalers.
 * 
 * This method should never be used outside of InitSysClock routine. 
 * @see HSISysClock and HSESysClock
 *
 * @return 0 if succeeded, 1 on failure
 */
int InitSysClockTo_8MHz_HSE(void);

/**
 * Sets System clock frequency to 72MHz and configure HCLK, PCLK2 and PCLK1 prescalers.
 * 
 * This method should never be used outside of InitSysClock routine. 
 * @see HSISysClock and HSESysClock
 *
 * @return 0 if succeeded, 1 on failure
 */
int InitSysClockTo_24MHz_HSE(void);

/**
 * Sets System clock frequency to 72MHz and configure HCLK, PCLK2 and PCLK1 prescalers.
 * 
 * This method should never be used outside of InitSysClock routine. 
 * @see HSISysClock and HSESysClock
 *
 * @return 0 if succeeded, 1 on failure
 */
int InitSysClockTo_48MHz_HSE(void);


#ifdef __cplusplus
}
#endif

#endif /*__CH32V00x_SYSTEM_H */



