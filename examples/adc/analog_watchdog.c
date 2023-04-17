/*
 * Analog watchdog routine:
 * ADC channel 2 (PC4), detect that the ADC conversion data on the rule group channel is
 * outside 500 - 900 and trigger the simulation Watchdog interrupt.
*/

#include <ch32v00x/adc.h>
#include <ch32v00x/debug.h>
#include <ch32v00x/gpio.h>
#include <ch32v00x/misc.h>
#include <ch32v00x/rcc.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

/**
 * Initializes ADC collection.
 */
void ADC_Function_Init(void) {
    ADC_InitTypeDef  ADC_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    ADC_DeInit(ADC1);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_241Cycles);

    /* Higher Threshold:900, Lower Threshold:500 */
    ADC_AnalogWatchdogThresholdsConfig(ADC1, 900, 500);
    ADC_AnalogWatchdogSingleChannelConfig(ADC1, ADC_Channel_2);
    ADC_AnalogWatchdogCmd(ADC1, ADC_AnalogWatchdog_SingleRegEnable);

    NVIC_InitStructure.NVIC_IRQChannel = ADC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    ADC_Calibration_Vol(ADC1, ADC_CALVOL_50PERCENT);
    ADC_ITConfig(ADC1, ADC_IT_AWD, ENABLE);
    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1)) { }
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1)) { }
}

/**
 * Returns ADCx conversion result data.
 *
 * @param ch ADC channel among ADC_Channel_x macros where x between
 * 0 and 9.
 */
uint16_t Get_ADC_Val(uint8_t ch) {
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)) { }

    return ADC_GetConversionValue(ADC1);
}

int main(void) {
    uint16_t ADC_val;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%"PRIu32"\n", SystemCoreClock);

    ADC_Function_Init();

    while(1) {
        ADC_val = Get_ADC_Val(ADC_Channel_2);
        Delay_Ms(500);
        printf("%04d\n", ADC_val);
        Delay_Ms(2);
    }
}


void ADC1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

/**
 * This function handles analog wathdog exception.
 */
void ADC1_IRQHandler(void) {
    if(ADC_GetITStatus( ADC1, ADC_IT_AWD)){
        printf( "Enter AnalogWatchdog Interrupt\n" );
    }

    ADC_ClearITPendingBit( ADC1, ADC_IT_AWD);
}
