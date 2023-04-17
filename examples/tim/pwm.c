/**
 * PWM output routine:
 *  TIM1_CH1(PD2)
 *
 * This example demonstrates that the TIM_CH1(PD2) pin outputs PWM in PWM mode 1
 * and PWM mode 2.
 */

#include <ch32v00x/debug.h>
#include <ch32v00x/gpio.h>
#include <ch32v00x/rcc.h>
#include <ch32v00x/tim.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#ifndef PWM_MODE
# warning No PWM_MODE defined. Defaulting to 1. Available values: 1, 2
#elif !((PWM_MODE == 1) || (PWM_MODE == 2))
# error PWM_MODE must be either 1 or 2.
#endif

/**
 * Initializes TIM1 output compare.
 *
 * @param arr the period value.
 * @param psc the prescaler value.
 * @param ccp the pulse value.
 */
void TIM1_PWMOut_Init(uint16_t arr, uint16_t psc, uint16_t ccp) {
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

#if (PWM_MODE == 1)
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
#elif (PWM_MODE == 2)
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
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

    TIM1_PWMOut_Init(100, 48000-1, 50);

    while (1) { } // FIXME outro
}
