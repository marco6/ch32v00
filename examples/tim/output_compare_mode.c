/**
 * Output comparison mode routine:
 *  TIM1_CH1(PD2)
 * This example demonstrates the output waveform of the TIM_CH1(PD2) 
 * pin in 4 output comparison modes.
 * Output compare modes include Timing, Active, Inactive, Toggle.
 */

#include <ch32v00x/debug.h>
#include <ch32v00x/gpio.h>
#include <ch32v00x/rcc.h>
#include <ch32v00x/tim.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#define Timing   1
#define Active   2
#define Inactive 3
#define Toggle   4

#ifndef CMP_MODE
# warning CMP_MODE not defined, defaulting to Timing. Avaliable values: Timing, Active, Inactive and Toggle.
# define CMP_MODE Timing
#elif !((CMP_MODE == Timing) || (CMP_MODE == Active) || (CMP_MODE == Inactive) || (CMP_MODE == Toggle))
# error CMP_MODE must be among Timing, Active, Inactive and Toggle.
#endif

/**
 * Initializes TIM1 output compare.
 *
 * @param arr the period value.
 * @param psc the prescaler value.
 * @param ccp the pulse value.
 */
void TIM1_OutCompare_Init(uint16_t arr, uint16_t psc, uint16_t ccp) {
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
    TIM_OCInitTypeDef TIM_OCInitStructure = { 0 };
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_TIM1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

#if (CMP_MODE == Timing)
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
#elif (CMP_MODE == Active)
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Active;
#elif (CMP_MODE == Inactive)
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Inactive;
#elif (CMP_MODE == Toggle)
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Toggle;
#endif

    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = ccp;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);

    TIM_CtrlPWMOutputs(TIM1, ENABLE );
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Disable);
    TIM_ARRPreloadConfig(TIM1, ENABLE);
    TIM_Cmd(TIM1, ENABLE);
}

int main(void) {
    USART_Printf_Init(115200);
    printf("SystemClk:%"PRIu32"\n", SystemCoreClock);

    TIM1_OutCompare_Init(100, 48000-1, 50);

    while(1) { } // FIXME: outro
}
