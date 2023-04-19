/*
 * Systick interrupt routine:
 */
#include <ch32v00x/adc.h>
#include <ch32v00x/gpio.h>
#include <ch32v00x/nvic.h>
#include <ch32v00x/rcc.h>
#include <ch32v00x/usart.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
    USART_Printf_Init(115200);
    printf("SystemClk:%"PRIu32"\n", SystemCoreClock);

    NVIC_EnableIRQ(SysTicK_IRQn);
    SysTick->SR &= ~(1 << 0);
    SysTick->CMP = SystemCoreClock-1;
    SysTick->CNT = 0;
    SysTick->CTLR = 0xF;

    while(1) { } // FIXME this should be part of the outro (like end obj or something)
}

void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void SysTick_Handler(void) {
    printf("Systick\n");
    SysTick->SR = 0;
}
