/**
 * Slave mode routine:
 *  TIM1_CH1(PD2)
 *
 * This example demonstrates that when the TIM_CH1(PD2) pin detects a rising edge,
 * TIM1 works differently in different slave modes:
 *  - RESET: TIM1->CNT reset and recount
 *  - GATED: PA8 pin input low level, TIM1->CNT counts normally, otherwise stop counting.
 *  - TRIGGER: TIM1->CNT continues counting.
 */

#include <ch32v00x/gpio.h>
#include <ch32v00x/rcc.h>
#include <ch32v00x/tim.h>
#include <ch32v00x/usart.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#define RESET      1
#define GATED      2
#define TRIGGER    3

#ifndef MODE
# error No MODE defined. Please define one among RESET, GATED, TRIGGER.
#elif !((MODE == RESET) || (MODE == GATED) || (MODE == TRIGGER))
# error MODE is not among the known values (RESET, GATED, TRIGGER).
#endif

/**
 * Initializes TIM1 external trigger synchronization.
 *
 * @param arr the period value.
 * @param psc the prescaler value.
 */
void TIM1_Synchro_ExtTrigger_Init(uint16_t arr, uint16_t psc) {
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };
    TIM_ICInitTypeDef TIM_ICInitStructure = { 0 };
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = { 0 };

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_TIM1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOD, GPIO_Pin_2);

    TIM_TimeBaseInitStructure.TIM_Period = arr;
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter =  0x00;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x00;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM1, &TIM_ICInitStructure);

    TIM_SelectInputTrigger(TIM1, TIM_TS_TI1FP1);

#if (MODE == RESET)
    TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset);
#elif (MODE == GATED)
    TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Gated);
#elif (MODE == TRIGGER)
    TIM_SelectMasterSlaveMode(TIM1, TIM_SlaveMode_Trigger);
#endif

    TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);

#if (MODE != TRIGGER)
    TIM_Cmd(TIM1, ENABLE);
#endif
}

int main(void) {
    USART_Printf_Init(115200);
    printf("SystemClk:%"PRIu32"\n", SystemCoreClock);

    TIM1_Synchro_ExtTrigger_Init(0xFFFF, 48000-1);

    while (1) {
        printf("cnt:%d\n", TIM1->CNT);
    }
}
