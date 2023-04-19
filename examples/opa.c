/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/08/08
 * Description        : Main program body.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

/*
 *@Note
 OPA1 is used as a voltage follower output, the external voltage
 is output to OPA1, and the ADC samples OPA1
 OPA1_CHP1--PD7
 OPA1_CHN1--PD0
 OPA1_OUT--PD4

 In this example, PD0 and PD4 are short-circuited, and the external voltage is input from PD7.
 If the negative feedback is connected to a resistor, it can also form an operational amplifier.
 Note: When using PD7, the reset function of this pin needs to be turned off.
*/

#include <ch32v00x/adc.h>
#include <ch32v00x/gpio.h>
#include <ch32v00x/nvic.h>
#include <ch32v00x/opa.h>
#include <ch32v00x/rcc.h>
#include <ch32v00x/usart.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

/**
 * Initializes OPA collection.
 */
void OPA1_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    OPA_InitTypeDef  OPA_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    OPA_InitStructure.PSEL = CHP1;
    OPA_InitStructure.NSEL = CHN1;
    OPA_Init(&OPA_InitStructure);
    OPA_Cmd(ENABLE);
}

/**
 * Initializes ADC Channel7 collection.
 */
void ADC_Channel7_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    ADC_InitTypeDef ADC_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_Calibration_Vol(ADC1, ADC_CALVOL_50PERCENT);
    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1)) { }

    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1)) { }
}

/**
 * Returns ADCx conversion result data.
 *
 * @param ch ADC channel among ADC_Channel_x macros where x between
 * 0 and 9.
 */
uint16_t Get_ADC_Val(uint8_t ch) {
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_241Cycles);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);

    while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)) { }

    return ADC_GetConversionValue(ADC1);
}

/**
 * Returns ADCx conversion result average data.
 *
 * @param ch ADC channel among ADC_Channel_x macros where x between
 * 0 and 9.
 */
uint16_t Get_ADC_Average(uint8_t ch, uint8_t times) {
    uint32_t temp_val = 0;

    for (uint8_t t = 0; t < times; t++){
        temp_val += Get_ADC_Val(ch);
        Delay_Ms(5);
    }

    return (int16_t)(temp_val / times);
}

int main(void) {
    uint16_t ADC_val;

    USART_Printf_Init(115200);
    printf("SystemClk:%"PRIu32"\n", SystemCoreClock);
    printf("OPA Test\n");
    
    OPA1_Init();
    ADC_Channel7_Init();

    while (1) {
        for (uint8_t i = 0; i < 6; i++) {
            ADC_val = Get_ADC_Average(ADC_Channel_7, 10);
            printf("OPA_OUT:%04d\n", ADC_val);
            Delay_Ms(500);
        }
    }
}
