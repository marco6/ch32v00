/**
 * USART Print debugging routine:
 *  USART1_Tx(PD5).
 *
 * This example demonstrates the use of USART1(PD5) as a print debug port output.
 */

#include <ch32v00x/debug.h>
#include <ch32v00x/misc.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);

    printf("SystemClk:%"PRIu32"\n", SystemCoreClock);

    printf("This is printf example\n");

    while(1) { } // FIXME outro
}
