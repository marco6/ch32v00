/**
 * APP go to IAP routine:
 * Demonstrates how to jump from userland to IAP.
 *
 * Note: The IAP program is solidified in the chip,
 * you can refer to this routine to jump to the IAP to upgrade.
*/

#include <ch32v00x/flash.h>
#include <ch32v00x/nvic.h>
#include <ch32v00x/rcc.h>
#include <ch32v00x/usart.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

/**
 * Go to IAP
 */
void GoToIAP(void) {
    RCC_ClearFlag();
    SystemReset_StartMode(Start_Mode_BOOT);
    NVIC_SystemReset();
}

int main(void) {
    USART_Printf_Init(115200);
    printf("SystemClk:%"PRIu32"\n", SystemCoreClock);

    printf("Go to IAP...\n");
    Delay_Ms(10);

    GoToIAP();

    while(1) { }
}
