/**
 * Timer synchronization mode:
 *  TIM1_CH1(PD2)
 *
 * This example demonstrates 4 timer synchronization modes.
 */

#include <ch32v00x/gpio.h>
#include <ch32v00x/rcc.h>
#include <ch32v00x/tim.h>
#include <ch32v00x/usart.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#ifndef MODE
# warning You can select a TIM mode betweeen 1-4. Defaulting to 1.
# define MODE 1
#elif !(1 <= MODE && MODE <= 4)
# error MODE can be between 1 and 4.
#endif

#define __TIM_SynchroMode(N) TIM_TimSynchroMode##N##_Init
#define _TIM_SynchroMode(N)  __TIM_SynchroMode(N)
#define TIM_SynchroMode _TIM_SynchroMode(MODE)

/**
 * Using TIM2 as prescaler for TIM1.
 */
void TIM_TimSynchroMode1_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_CounterModeConfig(TIM1, TIM_CounterMode_Up);
    TIM_CounterModeConfig(TIM2, TIM_CounterMode_Up);
    TIM_SetAutoreload(TIM1, 0x3E8);
    TIM_PrescalerConfig(TIM1, 48000 - 1, TIM_PSCReloadMode_Immediate);
    TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update);
    TIM_ITRxExternalClockConfig(TIM2, TIM_TS_ITR0);
    TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_External1);

    TIM_Cmd(TIM1, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}

/**
 * Using TIM2 to use TIM1.
 */
void TIM_TimSynchroMode2_Init(void) {
    TIM_OCInitTypeDef TIM_OCInitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_CounterModeConfig(TIM1, TIM_CounterMode_Up);
    TIM_CounterModeConfig(TIM2, TIM_CounterMode_Up);
    TIM_SetAutoreload(TIM1, 0x3E8);
    TIM_PrescalerConfig(TIM1, 48000 - 1, TIM_PSCReloadMode_Immediate);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0x64;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);

    TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_OC1Ref);
    TIM_SelectInputTrigger(TIM2, TIM_TS_ITR0);
    TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Gated);

    TIM_Cmd(TIM2, ENABLE);
    TIM_Cmd(TIM1, ENABLE);
}

/**
 * Using TIM2 to start TIM1.
 */
void TIM_TimSynchroMode3_Init(void) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_CounterModeConfig(TIM1, TIM_CounterMode_Up);
    TIM_CounterModeConfig(TIM2, TIM_CounterMode_Up);
    TIM_SetAutoreload(TIM1, 0xFFFF);
    TIM_PrescalerConfig(TIM1, 48000 - 1, TIM_PSCReloadMode_Immediate);
    TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update);
    TIM_SelectInputTrigger(TIM2, TIM_TS_ITR0);
    TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Trigger);
    TIM_Cmd(TIM1, ENABLE);
}

/**
 * Starting TIM1 and TIM2 synchronously in response to an external trigger.
 */
void TIM_TimSynchroMode4_Init(void) {
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    TIM_ICInitTypeDef TIM_ICInitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOD, GPIO_Pin_2);

    TIM_CounterModeConfig(TIM1, TIM_CounterMode_Up);
    TIM_CounterModeConfig(TIM2, TIM_CounterMode_Up);
    TIM_SetAutoreload(TIM1, 0xFFF);
    TIM_PrescalerConfig(TIM1, 48000 - 1, TIM_PSCReloadMode_Immediate);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICFilter = 0x00;
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM1, &TIM_ICInitStructure);

    TIM_SelectInputTrigger(TIM1, TIM_TS_TI1FP1);
    TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Trigger);
    TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);
    TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Enable);
    TIM_SelectInputTrigger(TIM2, TIM_TS_ITR0);
    TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Trigger);
}

int main(void) {
    USART_Printf_Init(115200);
    printf("SystemClk:%"PRIu32"\n", SystemCoreClock);

    /* Timer synchronization Mode Selection */
    TIM_SynchroMode();

    while (1) {
        printf("TIM1 cnt:%d\n", TIM1->CNT);
        printf("TIM2 cnt:%d\n", TIM2->CNT);
    }
}
