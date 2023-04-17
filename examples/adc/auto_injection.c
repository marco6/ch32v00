/*
 * Automatic injection mode routine:
 * ADC channel 2 (PC4) - regular group channel, channel 3 (PD2) - injection group channel
 */

#include <ch32v00x/adc.h>
#include <ch32v00x/debug.h>
#include <ch32v00x/gpio.h>
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

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    ADC_DeInit(ADC1);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_241Cycles);
    ADC_InjectedChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_241Cycles);
    ADC_Calibration_Vol(ADC1, ADC_CALVOL_50PERCENT);
    ADC_AutoInjectedConvCmd(ADC1, ENABLE);
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
    uint16_t adc_val;
    uint16_t adc_jval;

    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%"PRIu32"\n", SystemCoreClock);

    ADC_Function_Init();

    while(1) {
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);
        while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)) { }
        while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_JEOC)) { }

        adc_val = ADC_GetConversionValue(ADC1);
        adc_jval = ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1);
 
        Delay_Ms(500);
        printf("val:%04d\n", adc_val);
        printf("jval:%04d\n", adc_jval);
        Delay_Ms(2);
    }
}
