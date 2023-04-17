/*
 * ADC DMA sampling routine:
 * ADC channel 2 (PC4), the rule group channel obtains ADC conversion data for 10 consecutive
 * times through DMA.
 */

#include <ch32v00x/adc.h>
#include <ch32v00x/debug.h>
#include <ch32v00x/dma.h>
#include <ch32v00x/gpio.h>
#include <ch32v00x/rcc.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>


/* Global Variable */
uint16_t TxBuf[10];

/**
 * Initializes ADC collection.
 */
void ADC_Function_Init(void) {
    ADC_InitTypeDef  ADC_InitStructure = {0};
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    ADC_DeInit(ADC1);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_Calibration_Vol(ADC1, ADC_CALVOL_50PERCENT);
    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);

    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
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

    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)) { }

    return ADC_GetConversionValue(ADC1);
}

/**
 * Initializes the DMAy Channelx configuration.
 *
 * @param channel DMA channel among the DMA_CHx macros where x can be 
 * 1 to 7.
 * @param ppadr Peripheral base address.
 * @param memadr Memory base address.
 * @param bufsize DMA channel buffer size.
 */
void DMA_Tx_Init(DMA_Channel_TypeDef *channel, u32 ppadr, u32 memadr, uint16_t bufsize) {
    DMA_InitTypeDef DMA_InitStructure = {0};

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_DeInit(channel);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ppadr;
    DMA_InitStructure.DMA_MemoryBaseAddr = memadr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = bufsize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(channel, &DMA_InitStructure);
}

int main(void) {
    uint16_t i;

    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%"PRIu32"\n", SystemCoreClock);

    ADC_Function_Init();

    DMA_Tx_Init(DMA1_Channel1, (uint32_t)&ADC1->RDATAR, (uint32_t)TxBuf, 10);
    DMA_Cmd(DMA1_Channel1, ENABLE);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_241Cycles);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    Delay_Ms(50);
    ADC_SoftwareStartConvCmd(ADC1, DISABLE);

    for (i = 0; i < 10; i++) {
        printf("%04"PRIu16"\n", TxBuf[i]);
        Delay_Ms(10);
    }

    while(1) { } // FIXME this should be in the outro from the library.
}
