#ifndef __CH32V00x_ADC_H
#define __CH32V00x_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ch32v00x/device.h>

/**
 * ADC Init structure definition 
 */
typedef struct ADC_InitTypeDef {
    /** 
     * Configures the ADC to operate in independent or
     * dual mode.
     * This parameter can be a value of @ref ADC_mode.
     */
    uint32_t ADC_Mode;
    
    /**
     * Specifies whether the conversion is performed in
     * Scan (multichannels) or Single (one channel) mode.
     * This parameter can be set to ENABLE or DISABLE.
     */
    FunctionalState ADC_ScanConvMode;

    /**
     * Specifies whether the conversion is performed in
     * Continuous or Single mode.
     * This parameter can be set to ENABLE or DISABLE.
     */
    FunctionalState ADC_ContinuousConvMode;

    /**
     * Defines the external trigger used to start the analog
     * to digital conversion of regular channels. 
     * This parameter can be a value of 
     * @ref ADC_external_trigger_sources_for_regular_channels_conversion 
     */
    uint32_t ADC_ExternalTrigConv;
    
    /**
     * Specifies whether the ADC data alignment is left or right.
     * This parameter can be a value of @ref ADC_data_align.
     */
    uint32_t ADC_DataAlign;
    
    /**
     * Specifies the number of ADC channels that will be converted
     * using the sequencer for regular channel group.
     * This parameter must range from 1 to 16.
     */
    uint8_t ADC_NbrOfChannel; 
} ADC_InitTypeDef;

/* ADC_mode */
#define ADC_Mode_Independent                           ((uint32_t)0x00000000)

/* ADC_external_trigger_sources_for_regular_channels_conversion */
#define ADC_ExternalTrigConv_T1_TRGO                   ((uint32_t)0x00000000)
#define ADC_ExternalTrigConv_T1_CC1                    ((uint32_t)0x00020000)
#define ADC_ExternalTrigConv_T1_CC2                    ((uint32_t)0x00040000)
#define ADC_ExternalTrigConv_T2_TRGO                   ((uint32_t)0x00060000)
#define ADC_ExternalTrigConv_T2_CC1                    ((uint32_t)0x00080000)
#define ADC_ExternalTrigConv_T2_CC2                    ((uint32_t)0x000A0000)
#define ADC_ExternalTrigConv_Ext_PD3_PC2               ((uint32_t)0x000C0000)
#define ADC_ExternalTrigConv_None                      ((uint32_t)0x000E0000)

/* ADC_data_align */
#define ADC_DataAlign_Right                            ((uint32_t)0x00000000)
#define ADC_DataAlign_Left                             ((uint32_t)0x00000800)

/* ADC_channels */
#define ADC_Channel_0                                  ((uint8_t)0x00)
#define ADC_Channel_1                                  ((uint8_t)0x01)
#define ADC_Channel_2                                  ((uint8_t)0x02)
#define ADC_Channel_3                                  ((uint8_t)0x03)
#define ADC_Channel_4                                  ((uint8_t)0x04)
#define ADC_Channel_5                                  ((uint8_t)0x05)
#define ADC_Channel_6                                  ((uint8_t)0x06)
#define ADC_Channel_7                                  ((uint8_t)0x07)
#define ADC_Channel_8                                  ((uint8_t)0x08)
#define ADC_Channel_9                                  ((uint8_t)0x09)

#define ADC_Channel_Vrefint                            ((uint8_t)ADC_Channel_8)
#define ADC_Channel_Vcalint                            ((uint8_t)ADC_Channel_9)

/* ADC_sampling_time */
#define ADC_SampleTime_3Cycles                         ((uint8_t)0x00)
#define ADC_SampleTime_9Cycles                         ((uint8_t)0x01)
#define ADC_SampleTime_15Cycles                        ((uint8_t)0x02)
#define ADC_SampleTime_30Cycles                        ((uint8_t)0x03)
#define ADC_SampleTime_43Cycles                        ((uint8_t)0x04)
#define ADC_SampleTime_57Cycles                        ((uint8_t)0x05)
#define ADC_SampleTime_73Cycles                        ((uint8_t)0x06)
#define ADC_SampleTime_241Cycles                       ((uint8_t)0x07)

/* ADC_external_trigger_sources_for_injected_channels_conversion */
#define ADC_ExternalTrigInjecConv_T1_CC3               ((uint32_t)0x00000000)
#define ADC_ExternalTrigInjecConv_T1_CC4               ((uint32_t)0x00001000)
#define ADC_ExternalTrigInjecConv_T2_CC3               ((uint32_t)0x00002000)
#define ADC_ExternalTrigInjecConv_T2_CC4               ((uint32_t)0x00003000)
#define ADC_ExternalTrigInjecConv_Ext_PD1_PA2          ((uint32_t)0x00006000)
#define ADC_ExternalTrigInjecConv_None                 ((uint32_t)0x00007000)

/* ADC_injected_channel_selection */
#define ADC_InjectedChannel_1                          ((uint8_t)0x14)
#define ADC_InjectedChannel_2                          ((uint8_t)0x18)
#define ADC_InjectedChannel_3                          ((uint8_t)0x1C)
#define ADC_InjectedChannel_4                          ((uint8_t)0x20)

/* ADC_analog_watchdog_selection */
#define ADC_AnalogWatchdog_SingleRegEnable             ((uint32_t)0x00800200)
#define ADC_AnalogWatchdog_SingleInjecEnable           ((uint32_t)0x00400200)
#define ADC_AnalogWatchdog_SingleRegOrInjecEnable      ((uint32_t)0x00C00200)
#define ADC_AnalogWatchdog_AllRegEnable                ((uint32_t)0x00800000)
#define ADC_AnalogWatchdog_AllInjecEnable              ((uint32_t)0x00400000)
#define ADC_AnalogWatchdog_AllRegAllInjecEnable        ((uint32_t)0x00C00000)
#define ADC_AnalogWatchdog_None                        ((uint32_t)0x00000000)

/* ADC_interrupts_definition */
#define ADC_IT_EOC                                     ((uint16_t)0x0220)
#define ADC_IT_AWD                                     ((uint16_t)0x0140)
#define ADC_IT_JEOC                                    ((uint16_t)0x0480)

/* ADC_flags_definition */
#define ADC_FLAG_AWD                                   ((uint8_t)0x01)
#define ADC_FLAG_EOC                                   ((uint8_t)0x02)
#define ADC_FLAG_JEOC                                  ((uint8_t)0x04)
#define ADC_FLAG_JSTRT                                 ((uint8_t)0x08)
#define ADC_FLAG_STRT                                  ((uint8_t)0x10)

/* ADC_calibration_voltage_definition */
#define ADC_CALVOL_50PERCENT                           ((uint32_t)0x02000000)
#define ADC_CALVOL_75PERCENT                           ((uint32_t)0x04000000)

/* ADC_external_trigger_sources_delay_channels_definition */
#define ADC_ExternalTrigRegul_DLY                      ((uint32_t)0x00000000)
#define ADC_ExternalTrigInjec_DLY                      ((uint32_t)0x00020000)

/**
 * Deinitializes the ADCx peripheral registers to their default
 * reset values.
 *
 * @param ADCx  where x can be 1 to select the ADC peripheral.
 *
 */
void ADC_DeInit(ADC_TypeDef *ADCx);

/**
 * Initializes the ADCx peripheral according to the specified
 * parameters in the ADC_InitStruct.
 *
 * @param ADCx where x can be 1  to select the ADC peripheral.
 * @param ADC_InitStruct pointer to an ADC_InitTypeDef structure that
 * contains the configuration information for the specified ADC
 * peripheral.
 *
 */
void ADC_Init(ADC_TypeDef *ADCx, ADC_InitTypeDef *ADC_InitStruct);

/**
 * Fills each ADC_InitStruct member with its default value.
 *
 * @param ADC_InitStruct pointer to an ADC_InitTypeDef structure that
 * contains the configuration information for the specified ADC
 * peripheral.
 *
 */
void ADC_StructInit(ADC_InitTypeDef *ADC_InitStruct);

/**
 * Enables or disables the specified ADC peripheral.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param NewState ENABLE or DISABLE.
 *
 */
void ADC_Cmd(ADC_TypeDef *ADCx, FunctionalState NewState);

/**
 * Enables or disables the specified ADC DMA request.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param NewState ENABLE or DISABLE.
 *
 */
void ADC_DMACmd(ADC_TypeDef *ADCx, FunctionalState NewState);

/**
 * Enables or disables the specified ADC interrupts.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param ADC_IT specifies the ADC interrupt sources to be enabled or disabled.
 *    ADC_IT_EOC - End of conversion interrupt mask.
 *    ADC_IT_AWD - Analog watchdog interrupt mask.
 *    ADC_IT_JEOC - End of injected conversion interrupt mask.
 * @param NewState ENABLE or DISABLE.
 *
 */
void ADC_ITConfig(ADC_TypeDef *ADCx, uint16_t ADC_IT, FunctionalState NewState);

/**
 * Resets the selected ADC calibration registers.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 *
 */
void ADC_ResetCalibration(ADC_TypeDef *ADCx);

/**
 * Gets the selected ADC reset calibration registers status.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 *
 * @return  FlagStatus: SET or RESET.
 */
FlagStatus ADC_GetResetCalibrationStatus(ADC_TypeDef *ADCx);

/**
 * Starts the selected ADC calibration process.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 *
 */
void ADC_StartCalibration(ADC_TypeDef *ADCx);

/**
 * Gets the selected ADC calibration status.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 *
 * @return  FlagStatus: SET or RESET.
 */
FlagStatus ADC_GetCalibrationStatus(ADC_TypeDef *ADCx);

/**
 * Enables or disables the selected ADC software start conversion.
 *
 * @param ADCx where x can be 1 or 2 to select the ADC peripheral.
 * @param NewState ENABLE or DISABLE.
 *
 */
void ADC_SoftwareStartConvCmd(ADC_TypeDef *ADCx, FunctionalState NewState);

/**
 * Gets the selected ADC Software start conversion Status.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 *
 * @return  FlagStatus - SET or RESET.
 */
FlagStatus ADC_GetSoftwareStartConvStatus(ADC_TypeDef *ADCx);

/**
 * Configures the discontinuous mode for the selected ADC regular
 * group channel.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param Number specifies the discontinuous mode regular channel
 * count value(1-8).
 *
 */
void ADC_DiscModeChannelCountConfig(ADC_TypeDef *ADCx, uint8_t Number);

/**
 * Enables or disables the discontinuous mode on regular group
 * channel for the specified ADC.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param NewState ENABLE or DISABLE.
 *
 */
void ADC_DiscModeCmd(ADC_TypeDef *ADCx, FunctionalState NewState);

/**
 * Configures for the selected ADC regular channel its corresponding
 * rank in the sequencer and its sample time.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param ADC_Channel the ADC channel to configure.
 *    ADC_Channel_0 - ADC Channel0 selected.
 *    ADC_Channel_1 - ADC Channel1 selected.
 *    ADC_Channel_2 - ADC Channel2 selected.
 *    ADC_Channel_3 - ADC Channel3 selected.
 *    ADC_Channel_4 - ADC Channel4 selected.
 *    ADC_Channel_5 - ADC Channel5 selected.
 *    ADC_Channel_6 - ADC Channel6 selected.
 *    ADC_Channel_7 - ADC Channel7 selected.
 *    ADC_Channel_Vrefint - ADC Channel8 selected.
 *    ADC_Channel_Vcalint - ADC Channel9 selected.
 * @param Rank The rank in the regular group sequencer.
 * This parameter must be between 1 to 16.
 * @param ADC_SampleTime The sample time value to be set for the selected channel.
 *    ADC_SampleTime_3Cycles - Sample time equal to 3 cycles.
 *    ADC_SampleTime_9Cycles - Sample time equal to 9 cycles.
 *    ADC_SampleTime_15Cycles - Sample time equal to 15 cycles.
 *    ADC_SampleTime_30Cycles - Sample time equal to 30 cycles.
 *    ADC_SampleTime_43Cycles - Sample time equal to 43 cycles.
 *    ADC_SampleTime_57Cycles - Sample time equal to 57 cycles.
 *    ADC_SampleTime_73Cycles - Sample time equal to 73 cycles.
 *    ADC_SampleTime_241Cycles - Sample time equal to 241 cycles.
 *
 */
void ADC_RegularChannelConfig(ADC_TypeDef *ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);

/**
 * Enables or disables the ADCx conversion through external trigger.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param NewState ENABLE or DISABLE.
 *
 */
void ADC_ExternalTrigConvCmd(ADC_TypeDef *ADCx, FunctionalState NewState);

/**
 * Returns the last ADCx conversion result data for regular channel.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 *
 * @return  ADCx->RDATAR - The Data conversion value.
 */
uint16_t ADC_GetConversionValue(ADC_TypeDef *ADCx);

/**
 * Enables or disables the selected ADC automatic injected group
 * conversion after regular one.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param NewState ENABLE or DISABLE.
 *
 */
void ADC_AutoInjectedConvCmd(ADC_TypeDef *ADCx, FunctionalState NewState);

/**
 * Enables or disables the discontinuous mode for injected group
 * channel for the specified ADC.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param NewState ENABLE or DISABLE.
 *
 */
void ADC_InjectedDiscModeCmd(ADC_TypeDef *ADCx, FunctionalState NewState);

/**
 * Configures the ADCx external trigger for injected channels conversion.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param ADC_ExternalTrigInjecConv specifies the ADC trigger to start
 * injected conversion.
 *    ADC_ExternalTrigInjecConv_T1_CC3 - Timer1 capture compare3 selected.
 *    ADC_ExternalTrigInjecConv_T1_CC4 - Timer1 capture compare4 selected.
 *    ADC_ExternalTrigInjecConv_T2_CC3 - Timer2 capture compare3 selected.
 *    ADC_ExternalTrigInjecConv_T2_CC4 - Timer2 capture compare4 selected.
 *    ADC_ExternalTrigInjecConv_Ext_PD1_PA2 - PD1 or PA2 selected.
 * line 15 event selected.
 * ADC_ExternalTrigInjecConv_None: Injected conversion started
 * by software and not by external trigger.
 *
 */
void ADC_ExternalTrigInjectedConvConfig(ADC_TypeDef *ADCx, uint32_t ADC_ExternalTrigInjecConv);

/**
 * Enables or disables the ADCx injected channels conversion through
 * external trigger.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param NewState ENABLE or DISABLE.
 *
 */
void ADC_ExternalTrigInjectedConvCmd(ADC_TypeDef *ADCx, FunctionalState NewState);

/**
 * Enables or disables the selected ADC start of the injected
 * channels conversion.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param NewState ENABLE or DISABLE.
 *
 */
void ADC_SoftwareStartInjectedConvCmd(ADC_TypeDef *ADCx, FunctionalState NewState);

/**
 * Gets the selected ADC Software start injected conversion Status.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 *
 * @return  FlagStatus: SET or RESET.
 */
FlagStatus ADC_GetSoftwareStartInjectedConvCmdStatus(ADC_TypeDef *ADCx);

/**
 * Configures for the selected ADC injected channel its corresponding
 * rank in the sequencer and its sample time.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param ADC_Channel the ADC channel to configure.
 *    ADC_Channel_0 - ADC Channel0 selected.
 *    ADC_Channel_1 - ADC Channel1 selected.
 *    ADC_Channel_2 - ADC Channel2 selected.
 *    ADC_Channel_3 - ADC Channel3 selected.
 *    ADC_Channel_4 - ADC Channel4 selected.
 *    ADC_Channel_5 - ADC Channel5 selected.
 *    ADC_Channel_6 - ADC Channel6 selected.
 *    ADC_Channel_7 - ADC Channel7 selected.
 *    ADC_Channel_Vrefint - ADC Channel8 selected.
 *    ADC_Channel_Vcalint - ADC Channel9 selected.
 * @param Rank The rank in the regular group sequencer.
 * This parameter must be between 1 to 16.
 * @param ADC_SampleTime The sample time value to be set for the selected channel.
 *    ADC_SampleTime_3Cycles - Sample time equal to 3 cycles.
 *    ADC_SampleTime_9Cycles - Sample time equal to 9 cycles.
 *    ADC_SampleTime_15Cycles - Sample time equal to 15 cycles.
 *    ADC_SampleTime_30Cycles - Sample time equal to 30 cycles.
 *    ADC_SampleTime_43Cycles - Sample time equal to 43 cycles.
 *    ADC_SampleTime_57Cycles - Sample time equal to 57 cycles.
 *    ADC_SampleTime_73Cycles - Sample time equal to 73 cycles.
 *    ADC_SampleTime_241Cycles - Sample time equal to 241 cycles.
 *
 */
void ADC_InjectedChannelConfig(ADC_TypeDef *ADCx, uint8_t ADC_Channel, uint8_t Rank, uint8_t ADC_SampleTime);

/**
 * Configures the sequencer length for injected channels.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param Length The sequencer length.
 * This parameter must be a number between 1 to 4.
 *
 */
void ADC_InjectedSequencerLengthConfig(ADC_TypeDef *ADCx, uint8_t Length);

/**
 * Set the injected channels conversion value offset.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * ADC_InjectedChannel: the ADC injected channel to set its offset.
 *    ADC_InjectedChannel_1 - Injected Channel1 selected.
 *    ADC_InjectedChannel_2 - Injected Channel2 selected.
 *    ADC_InjectedChannel_3 - Injected Channel3 selected.
 *    ADC_InjectedChannel_4 - Injected Channel4 selected.
 * @param Offset the offset value for the selected ADC injected channel.
 * This parameter must be a 12bit value.
 *
 */
void ADC_SetInjectedOffset(ADC_TypeDef *ADCx, uint8_t ADC_InjectedChannel, uint16_t Offset);

/**
 * Returns the ADC injected channel conversion result.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param ADC_InjectedChannel the ADC injected channel to set its offset.
 *    ADC_InjectedChannel_1 - Injected Channel1 selected.
 *    ADC_InjectedChannel_2 - Injected Channel2 selected.
 *    ADC_InjectedChannel_3 - Injected Channel3 selected.
 *    ADC_InjectedChannel_4 - Injected Channel4 selected.
 *
 * @return  tmp - The Data conversion value.
 */
uint16_t ADC_GetInjectedConversionValue(ADC_TypeDef *ADCx, uint8_t ADC_InjectedChannel);

/**
 * Enables or disables the analog watchdog on single/all regular
 * or injected channels.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param ADC_AnalogWatchdog the ADC analog watchdog configuration.
 *    ADC_AnalogWatchdog_SingleRegEnable - Analog watchdog on a
 *    single regular channel.
 *    ADC_AnalogWatchdog_SingleInjecEnable - Analog watchdog on a
 *    single injected channel.
 *    ADC_AnalogWatchdog_SingleRegOrInjecEnable - Analog watchdog
 *    on a single regular or injected channel.
 *    ADC_AnalogWatchdog_AllRegEnable - Analog watchdog on  all
 *    regular channel.
 *    ADC_AnalogWatchdog_AllInjecEnable - Analog watchdog on  all
 *    injected channel.
 *    ADC_AnalogWatchdog_AllRegAllInjecEnable - Analog watchdog on
 *    all regular and injected channels.
 *    ADC_AnalogWatchdog_None - No channel guarded by the analog
 *    watchdog.
 *
 */
void ADC_AnalogWatchdogCmd(ADC_TypeDef *ADCx, uint32_t ADC_AnalogWatchdog);

/**
 * Configures the high and low thresholds of the analog watchdog.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param HighThreshold the ADC analog watchdog High threshold value.
 * This parameter must be a 10bit value.
 * @param LowThreshold the ADC analog watchdog Low threshold value.
 * This parameter must be a 10bit value.
 *
 */
void ADC_AnalogWatchdogThresholdsConfig(ADC_TypeDef *ADCx, uint16_t HighThreshold, uint16_t LowThreshold);

/**
 * Configures the analog watchdog guarded single channel.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param ADC_Channel the ADC channel to configure.
 *    ADC_Channel_0 - ADC Channel0 selected.
 *    ADC_Channel_1 - ADC Channel1 selected.
 *    ADC_Channel_2 - ADC Channel2 selected.
 *    ADC_Channel_3 - ADC Channel3 selected.
 *    ADC_Channel_4 - ADC Channel4 selected.
 *    ADC_Channel_5 - ADC Channel5 selected.
 *    ADC_Channel_6 - ADC Channel6 selected.
 *    ADC_Channel_7 - ADC Channel7 selected.
 *    ADC_Channel_Vrefint - ADC Channel8 selected.
 *    ADC_Channel_Vcalint - ADC Channel9 selected.
 *
 */
void ADC_AnalogWatchdogSingleChannelConfig(ADC_TypeDef *ADCx, uint8_t ADC_Channel);

/**
 * Checks whether the specified ADC flag is set or not.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param ADC_FLAG specifies the flag to check.
 *    ADC_FLAG_AWD - Analog watchdog flag.
 *    ADC_FLAG_EOC - End of conversion flag.
 *    ADC_FLAG_JEOC - End of injected group conversion flag.
 *    ADC_FLAG_JSTRT - Start of injected group conversion flag.
 *    ADC_FLAG_STRT - Start of regular group conversion flag.
 *
 * @return  FlagStatus: SET or RESET.
 */
FlagStatus ADC_GetFlagStatus(ADC_TypeDef *ADCx, uint8_t ADC_FLAG);

/**
 * Clears the ADCx's pending flags.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param ADC_FLAG specifies the flag to clear.
 *    ADC_FLAG_AWD - Analog watchdog flag.
 *    ADC_FLAG_EOC - End of conversion flag.
 *    ADC_FLAG_JEOC - End of injected group conversion flag.
 *    ADC_FLAG_JSTRT - Start of injected group conversion flag.
 *    ADC_FLAG_STRT - Start of regular group conversion flag.
 *
 */
void ADC_ClearFlag(ADC_TypeDef *ADCx, uint8_t ADC_FLAG);

/**
 * Checks whether the specified ADC interrupt has occurred or not.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param ADC_IT specifies the ADC interrupt source to check.
 *    ADC_IT_EOC - End of conversion interrupt mask.
 *    ADC_IT_AWD - Analog watchdog interrupt mask.
 *    ADC_IT_JEOC - End of injected conversion interrupt mask.
 *
 * @return  ITStatus: SET or RESET.
 */
ITStatus ADC_GetITStatus(ADC_TypeDef *ADCx, uint16_t ADC_IT);

/**
 * Clears the ADCx's interrupt pending bits.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param ADC_IT specifies the ADC interrupt pending bit to clear.
 *    ADC_IT_EOC - End of conversion interrupt mask.
 *    ADC_IT_AWD - Analog watchdog interrupt mask.
 *    ADC_IT_JEOC - End of injected conversion interrupt mask.
 *
 */
void ADC_ClearITPendingBit(ADC_TypeDef *ADCx, uint16_t ADC_IT);

/**
 * ADC calibration voltage.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param ADC_CALVOL ADC calibration voltage.
 *    ADC_CALVOL_50PERCENT - 50% VDD.
 *    ADC_CALVOL_75PERCENT - 75% VDD.
 *
 */
void ADC_Calibration_Vol(ADC_TypeDef *ADCx, uint32_t ADC_CALVOL);

/**
 * ADC external trigger sources delay channels and time.
 *
 * @param ADCx where x can be 1 to select the ADC peripheral.
 * @param channel ADC external trigger sources delay channels.
 *    ADC_ExternalTrigRegul_DLY - External trigger sources regular.
 *    ADC_ExternalTrigInjec_DLY - External trigger sources injected.
 * @param DelayTim ADC external trigger sources delay time
 * This parameter must range from 0 to 0x1FF.
 *
 */
void ADC_ExternalTrig_DLY(ADC_TypeDef *ADCx, uint32_t channel, uint16_t DelayTim);

#ifdef __cplusplus
}
#endif

#endif /*__CH32V00x_ADC_H */
