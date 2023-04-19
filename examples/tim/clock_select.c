/**
 * Clock source selection routine:
 * This example demonstrates two external clock source modes of TIM1.
 *
 * External clock source mode 1: PD2 is used as clock input pin,
 * External clock source mode 2: PC5 is used as clock input pin.
 */

#include <ch32v00x/rcc.h>
#include <ch32v00x/tim.h>
#include <ch32v00x/usart.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#ifndef CLK_MODE
# warning CLK_MODE not defined, defaulting to 1. Avaliable values: 1, 2.
# define CLK_MODE 1
#elif !((CLK_MODE == 1) || (CLK_MODE == 2))
# error CLK_MODE must be among 1 and 2.
#endif

#define __TIM1_ETRClockMode_Init(N) TIM1_ETRClockMode##N##_Init
#define _TIM1_ETRClockMode_Init(N) __TIM1_ETRClockMode_Init(N)
#define TIM1_ETRClockMode_Init _TIM1_ETRClockMode_Init(CLK_MODE)

/**
 * Configures the External clock Mode1.
 */
void TIM1_ETRClockMode1_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOD, ENABLE);

    TIM_CounterModeConfig(TIM1, TIM_CounterMode_Up);
    TIM_SetAutoreload(TIM1, 0x3EB);
    TIM_ETRClockMode1Config(TIM1, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_Inverted, 0x0);
    /* GPIOD2 Input as TIM Clock Source */
    TIM_TIxExternalClockConfig(TIM1, TIM_TIxExternalCLK1Source_TI1, TIM_ICPolarity_Rising, 0x00);
    TIM_Cmd(TIM1, ENABLE);
}

/**
 * Configures the External clock Mode2.
 */
void TIM1_ETRClockMode2_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOC, ENABLE);

    TIM_CounterModeConfig(TIM1, TIM_CounterMode_Up);
    TIM_SetAutoreload(TIM1, 0x3EB);
    /* GPIOC5 Input as TIM Clock Source */
    TIM_ETRClockMode2Config(TIM1, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_Inverted, 0x0);
    TIM_SelectInputTrigger(TIM1, TIM_TS_ETRF);
    TIM_Cmd(TIM1, ENABLE);
}

int main(void) {
    USART_Printf_Init(115200);
    printf("SystemClk:%"PRIu32"\n", SystemCoreClock);

    TIM1_ETRClockMode_Init();

    while (1) {
        if (TIM_GetFlagStatus(TIM1, TIM_FLAG_CC1) != RESET) {
            TIM_ClearFlag(TIM1, TIM_FLAG_CC1);
        }

        if (TIM_GetFlagStatus(TIM1, TIM_FLAG_Update) != RESET) {
            printf("Count Update\n");

            TIM_ClearFlag(TIM1, TIM_FLAG_Update);
        }
    }
}
