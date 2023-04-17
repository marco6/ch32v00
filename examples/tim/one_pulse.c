/**
 * Single pulse output routine:
 *  TIM2_CH1(PD4), TIM2_CH2(PD3)
 * This routine demonstrates that in single-pulse mode, the 
 * TIM2_CH2(PD3) pin detects a rising edge, then TIM2_CH1(PD4) 
 * outputs positive pulse.
 */

#include <ch32v00x/debug.h>
#include <ch32v00x/gpio.h>
#include <ch32v00x/rcc.h>
#include <ch32v00x/tim.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

/**
 * Initializes TIM1 one pulse.
 *
 * @param arr the period value.
 * @param psc the prescaler value.
 * @param ccp the pulse value.
 */
void One_Pulse_Init(uint16_t arr, uint16_t psc, uint16_t ccp) {
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
    TIM_OCInitTypeDef TIM_OCInitStructure = { 0 };
    TIM_ICInitTypeDef TIM_ICInitStructure = { 0 };
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = ccp;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);

    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x00;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;

    TIM_ICInit(TIM2, &TIM_ICInitStructure);
    TIM_SelectOnePulseMode(TIM2,TIM_OPMode_Single);
    TIM_SelectInputTrigger(TIM2, TIM_TS_TI2FP2);
    TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Trigger);
}

int main(void) {
    USART_Printf_Init(115200);
    printf("SystemClk:%"PRIu32"\n", SystemCoreClock);

    One_Pulse_Init(200, 48000-1, 100);

    while (1) { } // FIXME outro
}
