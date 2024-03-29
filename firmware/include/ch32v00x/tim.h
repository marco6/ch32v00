#ifndef __CH32V00x_TIM_H
#define __CH32V00x_TIM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ch32v00x/device.h>

/* TIM Time Base Init structure definition */
typedef struct TIM_TimeBaseInitTypeDef {
    /**
     * Specifies the prescaler value used to divide the TIM clock.
     * This parameter can be a number between 0x0000 and 0xFFFF
     */
    uint16_t TIM_Prescaler;

    /**
     * Specifies the counter mode.
     * This parameter can be a value of @ref TIM_Counter_Mode
     */
    uint16_t TIM_CounterMode;
    
    /**
     * Specifies the period value to be loaded into the active
     * Auto-Reload Register at the next update event.
     * This parameter must be a number between 0x0000 and 0xFFFF.
     */
    uint16_t TIM_Period;
    
    /**
     * Specifies the clock division.
     * This parameter can be a value of @ref TIM_Clock_Division_CKD
     */
    uint16_t TIM_ClockDivision;

    /**
     * Specifies the repetition counter value. Each time the RCR downcounter
     * reaches zero, an update event is generated and counting restarts
     * from the RCR value (N).
     * This means in PWM mode that (N+1) corresponds to:
     *  - the number of PWM periods in edge-aligned mode
     *  - the number of half PWM period in center-aligned mode
     * This parameter must be a number between 0x00 and 0xFF.
     * @note This parameter is valid only for TIM1 and TIM8.
     */
    uint8_t TIM_RepetitionCounter;
} TIM_TimeBaseInitTypeDef;

/* TIM Output Compare Init structure definition */
typedef struct TIM_OCInitTypeDef {
/**
 * Specifies the TIM mode.
 * This parameter can be a value of @ref TIM_Output_Compare_and_PWM_modes
 */
uint16_t TIM_OCMode;

/**
 * Specifies the TIM Output Compare state.
 * This parameter can be a value of @ref TIM_Output_Compare_state
 */
uint16_t TIM_OutputState;

/**
 * Specifies the TIM complementary Output Compare state.
 * This parameter can be a value of @ref TIM_Output_Compare_N_state
 * @note This parameter is valid only for TIM1 and TIM8.
 */
uint16_t TIM_OutputNState;

/**
 * Specifies the pulse value to be loaded into the Capture Compare Register.
 * This parameter can be a number between 0x0000 and 0xFFFF
 */
uint16_t TIM_Pulse;

/**
 * Specifies the output polarity.
 * This parameter can be a value of @ref TIM_Output_Compare_Polarity
 */
uint16_t TIM_OCPolarity;
/**
 * Specifies the complementary output polarity.
 * This parameter can be a value of @ref TIM_Output_Compare_N_Polarity
 * @note This parameter is valid only for TIM1 and TIM8.
 */
uint16_t TIM_OCNPolarity;
/**
 * Specifies the TIM Output Compare pin state during Idle state.
 * This parameter can be a value of @ref TIM_Output_Compare_Idle_State
 * @note This parameter is valid only for TIM1 and TIM8.
 */
uint16_t TIM_OCIdleState;

/**
 * Specifies the TIM Output Compare pin state during Idle state.
 * This parameter can be a value of @ref TIM_Output_Compare_N_Idle_State
 * @note This parameter is valid only for TIM1 and TIM8.
 */
uint16_t TIM_OCNIdleState;
} TIM_OCInitTypeDef;

/* TIM Input Capture Init structure definition */
typedef struct TIM_ICInitTypeDef {
    /**
    * Specifies the TIM channel.
    * This parameter can be a value of @ref TIM_Channel
    */
    uint16_t TIM_Channel;

    /**
    * Specifies the active edge of the input signal.
    * This parameter can be a value of @ref TIM_Input_Capture_Polarity
    */
    uint16_t TIM_ICPolarity;

    /**
    * Specifies the input.
    * This parameter can be a value of @ref TIM_Input_Capture_Selection
    */
    uint16_t TIM_ICSelection;

    /**
    * Specifies the Input Capture Prescaler.
    * This parameter can be a value of @ref TIM_Input_Capture_Prescaler
    */
    uint16_t TIM_ICPrescaler;

    /**
    * Specifies the input capture filter.
    * This parameter can be a number between 0x0 and 0xF
    */
    uint16_t TIM_ICFilter;
} TIM_ICInitTypeDef;

/* BDTR structure definition */
typedef struct TIM_BDTRInitTypeDef {
    /**
    * Specifies the Off-State selection used in Run mode.
    * This parameter can be a value of @ref OSSR_Off_State_Selection_for_Run_mode_state 
    */
    uint16_t TIM_OSSRState;

    /**
    * Specifies the Off-State used in Idle state.
    * This parameter can be a value of @ref OSSI_Off_State_Selection_for_Idle_mode_state 
    */
    uint16_t TIM_OSSIState;

    /**
    * Specifies the LOCK level parameters.
    * This parameter can be a value of @ref Lock_level 
    */
    uint16_t TIM_LOCKLevel;

    /**
    * Specifies the delay time between the switching-off and the
    * switching-on of the outputs.
    * This parameter can be a number between 0x00 and 0xFF  
    */
    uint16_t TIM_DeadTime;

    /**
    * Specifies whether the TIM Break input is enabled or not.
    * This parameter can be a value of @ref Break_Input_enable_disable 
    */
    uint16_t TIM_Break;

    /**
    * Specifies the TIM Break Input pin polarity.
    * This parameter can be a value of @ref Break_Polarity 
    */
    uint16_t TIM_BreakPolarity;

    /**
    * Specifies whether the TIM Automatic Output feature is enabled or not.
    * This parameter can be a value of @ref TIM_AOE_Bit_Set_Reset 
    */
    uint16_t TIM_AutomaticOutput;
} TIM_BDTRInitTypeDef;

/* TIM_Output_Compare_and_PWM_modes */
#define TIM_OCMode_Timing                  ((uint16_t)0x0000)
#define TIM_OCMode_Active                  ((uint16_t)0x0010)
#define TIM_OCMode_Inactive                ((uint16_t)0x0020)
#define TIM_OCMode_Toggle                  ((uint16_t)0x0030)
#define TIM_OCMode_PWM1                    ((uint16_t)0x0060)
#define TIM_OCMode_PWM2                    ((uint16_t)0x0070)

/* TIM_One_Pulse_Mode */
#define TIM_OPMode_Single                  ((uint16_t)0x0008)
#define TIM_OPMode_Repetitive              ((uint16_t)0x0000)

/* TIM_Channel */
#define TIM_Channel_1                      ((uint16_t)0x0000)
#define TIM_Channel_2                      ((uint16_t)0x0004)
#define TIM_Channel_3                      ((uint16_t)0x0008)
#define TIM_Channel_4                      ((uint16_t)0x000C)

/* TIM_Clock_Division_CKD */
#define TIM_CKD_DIV1                       ((uint16_t)0x0000)
#define TIM_CKD_DIV2                       ((uint16_t)0x0100)
#define TIM_CKD_DIV4                       ((uint16_t)0x0200)

/* TIM_Counter_Mode */
#define TIM_CounterMode_Up                 ((uint16_t)0x0000)
#define TIM_CounterMode_Down               ((uint16_t)0x0010)
#define TIM_CounterMode_CenterAligned1     ((uint16_t)0x0020)
#define TIM_CounterMode_CenterAligned2     ((uint16_t)0x0040)
#define TIM_CounterMode_CenterAligned3     ((uint16_t)0x0060)

/* TIM_Output_Compare_Polarity */
#define TIM_OCPolarity_High                ((uint16_t)0x0000)
#define TIM_OCPolarity_Low                 ((uint16_t)0x0002)

/* TIM_Output_Compare_N_Polarity */
#define TIM_OCNPolarity_High               ((uint16_t)0x0000)
#define TIM_OCNPolarity_Low                ((uint16_t)0x0008)

/* TIM_Output_Compare_state */
#define TIM_OutputState_Disable            ((uint16_t)0x0000)
#define TIM_OutputState_Enable             ((uint16_t)0x0001)

/* TIM_Output_Compare_N_state */
#define TIM_OutputNState_Disable           ((uint16_t)0x0000)
#define TIM_OutputNState_Enable            ((uint16_t)0x0004)

/* TIM_Capture_Compare_state */
#define TIM_CCx_Enable                     ((uint16_t)0x0001)
#define TIM_CCx_Disable                    ((uint16_t)0x0000)

/* TIM_Capture_Compare_N_state */
#define TIM_CCxN_Enable                    ((uint16_t)0x0004)
#define TIM_CCxN_Disable                   ((uint16_t)0x0000)

/* Break_Input_enable_disable */
#define TIM_Break_Enable                   ((uint16_t)0x1000)
#define TIM_Break_Disable                  ((uint16_t)0x0000)

/* Break_Polarity */
#define TIM_BreakPolarity_Low              ((uint16_t)0x0000)
#define TIM_BreakPolarity_High             ((uint16_t)0x2000)

/* TIM_AOE_Bit_Set_Reset */
#define TIM_AutomaticOutput_Enable         ((uint16_t)0x4000)
#define TIM_AutomaticOutput_Disable        ((uint16_t)0x0000)

/* Lock_level */
#define TIM_LOCKLevel_OFF                  ((uint16_t)0x0000)
#define TIM_LOCKLevel_1                    ((uint16_t)0x0100)
#define TIM_LOCKLevel_2                    ((uint16_t)0x0200)
#define TIM_LOCKLevel_3                    ((uint16_t)0x0300)

/* OSSI_Off_State_Selection_for_Idle_mode_state */
#define TIM_OSSIState_Enable               ((uint16_t)0x0400)
#define TIM_OSSIState_Disable              ((uint16_t)0x0000)

/* OSSR_Off_State_Selection_for_Run_mode_state */
#define TIM_OSSRState_Enable               ((uint16_t)0x0800)
#define TIM_OSSRState_Disable              ((uint16_t)0x0000)

/* TIM_Output_Compare_Idle_State */
#define TIM_OCIdleState_Set                ((uint16_t)0x0100)
#define TIM_OCIdleState_Reset              ((uint16_t)0x0000)

/* TIM_Output_Compare_N_Idle_State */
#define TIM_OCNIdleState_Set               ((uint16_t)0x0200)
#define TIM_OCNIdleState_Reset             ((uint16_t)0x0000)

/* TIM_Input_Capture_Polarity */
#define TIM_ICPolarity_Rising              ((uint16_t)0x0000)
#define TIM_ICPolarity_Falling             ((uint16_t)0x0002)
#define TIM_ICPolarity_BothEdge            ((uint16_t)0x000A)

/* TIM_Input_Capture_Selection */
#define TIM_ICSelection_DirectTI           ((uint16_t)0x0001) /* TIM Input 1, 2, 3 or 4 is selected to be \
                                                                 connected to IC1, IC2, IC3 or IC4, respectively */
#define TIM_ICSelection_IndirectTI         ((uint16_t)0x0002) /* TIM Input 1, 2, 3 or 4 is selected to be \
                                                                 connected to IC2, IC1, IC4 or IC3, respectively. */
#define TIM_ICSelection_TRC                ((uint16_t)0x0003) /* TIM Input 1, 2, 3 or 4 is selected to be connected to TRC. */

/* TIM_Input_Capture_Prescaler */
#define TIM_ICPSC_DIV1                     ((uint16_t)0x0000) /* Capture performed each time an edge is detected on the capture input. */
#define TIM_ICPSC_DIV2                     ((uint16_t)0x0004) /* Capture performed once every 2 events. */
#define TIM_ICPSC_DIV4                     ((uint16_t)0x0008) /* Capture performed once every 4 events. */
#define TIM_ICPSC_DIV8                     ((uint16_t)0x000C) /* Capture performed once every 8 events. */

/* TIM_interrupt_sources */
#define TIM_IT_Update                      ((uint16_t)0x0001)
#define TIM_IT_CC1                         ((uint16_t)0x0002)
#define TIM_IT_CC2                         ((uint16_t)0x0004)
#define TIM_IT_CC3                         ((uint16_t)0x0008)
#define TIM_IT_CC4                         ((uint16_t)0x0010)
#define TIM_IT_COM                         ((uint16_t)0x0020)
#define TIM_IT_Trigger                     ((uint16_t)0x0040)
#define TIM_IT_Break                       ((uint16_t)0x0080)

/* TIM_DMA_Base_address */
#define TIM_DMABase_CR1                    ((uint16_t)0x0000)
#define TIM_DMABase_CR2                    ((uint16_t)0x0001)
#define TIM_DMABase_SMCR                   ((uint16_t)0x0002)
#define TIM_DMABase_DIER                   ((uint16_t)0x0003)
#define TIM_DMABase_SR                     ((uint16_t)0x0004)
#define TIM_DMABase_EGR                    ((uint16_t)0x0005)
#define TIM_DMABase_CCMR1                  ((uint16_t)0x0006)
#define TIM_DMABase_CCMR2                  ((uint16_t)0x0007)
#define TIM_DMABase_CCER                   ((uint16_t)0x0008)
#define TIM_DMABase_CNT                    ((uint16_t)0x0009)
#define TIM_DMABase_PSC                    ((uint16_t)0x000A)
#define TIM_DMABase_ARR                    ((uint16_t)0x000B)
#define TIM_DMABase_RCR                    ((uint16_t)0x000C)
#define TIM_DMABase_CCR1                   ((uint16_t)0x000D)
#define TIM_DMABase_CCR2                   ((uint16_t)0x000E)
#define TIM_DMABase_CCR3                   ((uint16_t)0x000F)
#define TIM_DMABase_CCR4                   ((uint16_t)0x0010)
#define TIM_DMABase_BDTR                   ((uint16_t)0x0011)
#define TIM_DMABase_DCR                    ((uint16_t)0x0012)

/* TIM_DMA_Burst_Length */
#define TIM_DMABurstLength_1Transfer       ((uint16_t)0x0000)
#define TIM_DMABurstLength_2Transfers      ((uint16_t)0x0100)
#define TIM_DMABurstLength_3Transfers      ((uint16_t)0x0200)
#define TIM_DMABurstLength_4Transfers      ((uint16_t)0x0300)
#define TIM_DMABurstLength_5Transfers      ((uint16_t)0x0400)
#define TIM_DMABurstLength_6Transfers      ((uint16_t)0x0500)
#define TIM_DMABurstLength_7Transfers      ((uint16_t)0x0600)
#define TIM_DMABurstLength_8Transfers      ((uint16_t)0x0700)
#define TIM_DMABurstLength_9Transfers      ((uint16_t)0x0800)
#define TIM_DMABurstLength_10Transfers     ((uint16_t)0x0900)
#define TIM_DMABurstLength_11Transfers     ((uint16_t)0x0A00)
#define TIM_DMABurstLength_12Transfers     ((uint16_t)0x0B00)
#define TIM_DMABurstLength_13Transfers     ((uint16_t)0x0C00)
#define TIM_DMABurstLength_14Transfers     ((uint16_t)0x0D00)
#define TIM_DMABurstLength_15Transfers     ((uint16_t)0x0E00)
#define TIM_DMABurstLength_16Transfers     ((uint16_t)0x0F00)
#define TIM_DMABurstLength_17Transfers     ((uint16_t)0x1000)
#define TIM_DMABurstLength_18Transfers     ((uint16_t)0x1100)

/* TIM_DMA_sources */
#define TIM_DMA_Update                     ((uint16_t)0x0100)
#define TIM_DMA_CC1                        ((uint16_t)0x0200)
#define TIM_DMA_CC2                        ((uint16_t)0x0400)
#define TIM_DMA_CC3                        ((uint16_t)0x0800)
#define TIM_DMA_CC4                        ((uint16_t)0x1000)
#define TIM_DMA_COM                        ((uint16_t)0x2000)
#define TIM_DMA_Trigger                    ((uint16_t)0x4000)

/* TIM_External_Trigger_Prescaler */
#define TIM_ExtTRGPSC_OFF                  ((uint16_t)0x0000)
#define TIM_ExtTRGPSC_DIV2                 ((uint16_t)0x1000)
#define TIM_ExtTRGPSC_DIV4                 ((uint16_t)0x2000)
#define TIM_ExtTRGPSC_DIV8                 ((uint16_t)0x3000)

/* TIM_Internal_Trigger_Selection */
#define TIM_TS_ITR0                        ((uint16_t)0x0000)
#define TIM_TS_ITR1                        ((uint16_t)0x0010)
#define TIM_TS_ITR2                        ((uint16_t)0x0020)
#define TIM_TS_ITR3                        ((uint16_t)0x0030)
#define TIM_TS_TI1F_ED                     ((uint16_t)0x0040)
#define TIM_TS_TI1FP1                      ((uint16_t)0x0050)
#define TIM_TS_TI2FP2                      ((uint16_t)0x0060)
#define TIM_TS_ETRF                        ((uint16_t)0x0070)

/* TIM_TIx_External_Clock_Source */
#define TIM_TIxExternalCLK1Source_TI1      ((uint16_t)0x0050)
#define TIM_TIxExternalCLK1Source_TI2      ((uint16_t)0x0060)
#define TIM_TIxExternalCLK1Source_TI1ED    ((uint16_t)0x0040)

/* TIM_External_Trigger_Polarity */
#define TIM_ExtTRGPolarity_Inverted        ((uint16_t)0x8000)
#define TIM_ExtTRGPolarity_NonInverted     ((uint16_t)0x0000)

/* TIM_Prescaler_Reload_Mode */
#define TIM_PSCReloadMode_Update           ((uint16_t)0x0000)
#define TIM_PSCReloadMode_Immediate        ((uint16_t)0x0001)

/* TIM_Forced_Action */
#define TIM_ForcedAction_Active            ((uint16_t)0x0050)
#define TIM_ForcedAction_InActive          ((uint16_t)0x0040)

/* TIM_Encoder_Mode */
#define TIM_EncoderMode_TI1                ((uint16_t)0x0001)
#define TIM_EncoderMode_TI2                ((uint16_t)0x0002)
#define TIM_EncoderMode_TI12               ((uint16_t)0x0003)

/* TIM_Event_Source */
#define TIM_EventSource_Update             ((uint16_t)0x0001)
#define TIM_EventSource_CC1                ((uint16_t)0x0002)
#define TIM_EventSource_CC2                ((uint16_t)0x0004)
#define TIM_EventSource_CC3                ((uint16_t)0x0008)
#define TIM_EventSource_CC4                ((uint16_t)0x0010)
#define TIM_EventSource_COM                ((uint16_t)0x0020)
#define TIM_EventSource_Trigger            ((uint16_t)0x0040)
#define TIM_EventSource_Break              ((uint16_t)0x0080)

/* TIM_Update_Source */
#define TIM_UpdateSource_Global            ((uint16_t)0x0000) /* Source of update is the counter overflow/underflow \
                                                                 or the setting of UG bit, or an update generation  \
                                                                 through the slave mode controller. */
#define TIM_UpdateSource_Regular           ((uint16_t)0x0001) /* Source of update is counter overflow/underflow. */

/* TIM_Output_Compare_Preload_State */
#define TIM_OCPreload_Enable               ((uint16_t)0x0008)
#define TIM_OCPreload_Disable              ((uint16_t)0x0000)

/* TIM_Output_Compare_Fast_State */
#define TIM_OCFast_Enable                  ((uint16_t)0x0004)
#define TIM_OCFast_Disable                 ((uint16_t)0x0000)

/* TIM_Output_Compare_Clear_State */
#define TIM_OCClear_Enable                 ((uint16_t)0x0080)
#define TIM_OCClear_Disable                ((uint16_t)0x0000)

/* TIM_Trigger_Output_Source */
#define TIM_TRGOSource_Reset               ((uint16_t)0x0000)
#define TIM_TRGOSource_Enable              ((uint16_t)0x0010)
#define TIM_TRGOSource_Update              ((uint16_t)0x0020)
#define TIM_TRGOSource_OC1                 ((uint16_t)0x0030)
#define TIM_TRGOSource_OC1Ref              ((uint16_t)0x0040)
#define TIM_TRGOSource_OC2Ref              ((uint16_t)0x0050)
#define TIM_TRGOSource_OC3Ref              ((uint16_t)0x0060)
#define TIM_TRGOSource_OC4Ref              ((uint16_t)0x0070)

/* TIM_Slave_Mode */
#define TIM_SlaveMode_Reset                ((uint16_t)0x0004)
#define TIM_SlaveMode_Gated                ((uint16_t)0x0005)
#define TIM_SlaveMode_Trigger              ((uint16_t)0x0006)
#define TIM_SlaveMode_External1            ((uint16_t)0x0007)

/* TIM_Master_Slave_Mode */
#define TIM_MasterSlaveMode_Enable         ((uint16_t)0x0080)
#define TIM_MasterSlaveMode_Disable        ((uint16_t)0x0000)

/* TIM_Flags */
#define TIM_FLAG_Update                    ((uint16_t)0x0001)
#define TIM_FLAG_CC1                       ((uint16_t)0x0002)
#define TIM_FLAG_CC2                       ((uint16_t)0x0004)
#define TIM_FLAG_CC3                       ((uint16_t)0x0008)
#define TIM_FLAG_CC4                       ((uint16_t)0x0010)
#define TIM_FLAG_COM                       ((uint16_t)0x0020)
#define TIM_FLAG_Trigger                   ((uint16_t)0x0040)
#define TIM_FLAG_Break                     ((uint16_t)0x0080)
#define TIM_FLAG_CC1OF                     ((uint16_t)0x0200)
#define TIM_FLAG_CC2OF                     ((uint16_t)0x0400)
#define TIM_FLAG_CC3OF                     ((uint16_t)0x0800)
#define TIM_FLAG_CC4OF                     ((uint16_t)0x1000)

/* TIM_Legacy */
#define TIM_DMABurstLength_1Byte           TIM_DMABurstLength_1Transfer
#define TIM_DMABurstLength_2Bytes          TIM_DMABurstLength_2Transfers
#define TIM_DMABurstLength_3Bytes          TIM_DMABurstLength_3Transfers
#define TIM_DMABurstLength_4Bytes          TIM_DMABurstLength_4Transfers
#define TIM_DMABurstLength_5Bytes          TIM_DMABurstLength_5Transfers
#define TIM_DMABurstLength_6Bytes          TIM_DMABurstLength_6Transfers
#define TIM_DMABurstLength_7Bytes          TIM_DMABurstLength_7Transfers
#define TIM_DMABurstLength_8Bytes          TIM_DMABurstLength_8Transfers
#define TIM_DMABurstLength_9Bytes          TIM_DMABurstLength_9Transfers
#define TIM_DMABurstLength_10Bytes         TIM_DMABurstLength_10Transfers
#define TIM_DMABurstLength_11Bytes         TIM_DMABurstLength_11Transfers
#define TIM_DMABurstLength_12Bytes         TIM_DMABurstLength_12Transfers
#define TIM_DMABurstLength_13Bytes         TIM_DMABurstLength_13Transfers
#define TIM_DMABurstLength_14Bytes         TIM_DMABurstLength_14Transfers
#define TIM_DMABurstLength_15Bytes         TIM_DMABurstLength_15Transfers
#define TIM_DMABurstLength_16Bytes         TIM_DMABurstLength_16Transfers
#define TIM_DMABurstLength_17Bytes         TIM_DMABurstLength_17Transfers
#define TIM_DMABurstLength_18Bytes         TIM_DMABurstLength_18Transfers

/**
 * Deinitializes the TIMx peripheral registers to their default
 *    reset values.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 */
void TIM_DeInit(TIM_TypeDef *TIMx);

/**
 * Initializes the TIMx Time Base Unit peripheral according to
 * the specified parameters in the TIM_TimeBaseInitStruct.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_TimeBaseInitStruct pointer to a TIM_TimeBaseInitTypeDef
 * structure.
 */
void TIM_TimeBaseInit(TIM_TypeDef *TIMx, TIM_TimeBaseInitTypeDef *TIM_TimeBaseInitStruct);

/**
 * Initializes the TIMx Channel1 according to the specified
 * parameters in the TIM_OCInitStruct.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_OCInitStruct pointer to a TIM_OCInitTypeDef structure.
 */
void TIM_OC1Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct);

/**
 * Initializes the TIMx Channel2 according to the specified
 * parameters in the TIM_OCInitStruct.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_OCInitStruct pointer to a TIM_OCInitTypeDef structure.
 */
void TIM_OC2Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct);

/**
 * Initializes the TIMx Channel3 according to the specified
 * parameters in the TIM_OCInitStruct.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_OCInitStruct pointer to a TIM_OCInitTypeDef structure.
 */
void TIM_OC3Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct);

/**
 * Initializes the TIMx Channel4 according to the specified
 * parameters in the TIM_OCInitStruct.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_OCInitStruct pointer to a TIM_OCInitTypeDef structure.
 */
void TIM_OC4Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct);

/**
 * IInitializes the TIM peripheral according to the specified
 * parameters in the TIM_ICInitStruct.
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_ICInitStruct pointer to a TIM_ICInitTypeDef structure.
 */
void TIM_ICInit(TIM_TypeDef *TIMx, TIM_ICInitTypeDef *TIM_ICInitStruct);

/**
 * Configures the TIM peripheral according to the specified
 * parameters in the TIM_ICInitStruct to measure an external
 * PWM signal.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_ICInitStruct pointer to a TIM_ICInitTypeDef structure.
 */
void TIM_PWMIConfig(TIM_TypeDef *TIMx, TIM_ICInitTypeDef *TIM_ICInitStruct);

/**
 * Configures the: Break feature, dead time, Lock level, the OSSI,
 *      the OSSR State and the AOE(automatic output enable).
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_BDTRInitStruct pointer to a TIM_BDTRInitTypeDef structure.
 */
void TIM_BDTRConfig(TIM_TypeDef *TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct);

/**
 * Fills each TIM_TimeBaseInitStruct member with its default value.
 *
 * @param TIM_TimeBaseInitStruct pointer to a TIM_TimeBaseInitTypeDef structure.
 */
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef *TIM_TimeBaseInitStruct);

/**
 * Fills each TIM_OCInitStruct member with its default value.
 *
 * @param TIM_OCInitStruct pointer to a TIM_OCInitTypeDef structure.
 */
void TIM_OCStructInit(TIM_OCInitTypeDef *TIM_OCInitStruct);

/**
 * Fills each TIM_ICInitStruct member with its default value.
 *
 * @param TIM_ICInitStruct pointer to a TIM_ICInitTypeDef structure.
 */
void TIM_ICStructInit(TIM_ICInitTypeDef *TIM_ICInitStruct);

/**
 * Fills each TIM_BDTRInitStruct member with its default value.
 *
 * @param TIM_BDTRInitStruct pointer to a TIM_BDTRInitTypeDef structure.
 */
void TIM_BDTRStructInit(TIM_BDTRInitTypeDef *TIM_BDTRInitStruct);

/**
 * Enables or disables the specified TIM peripheral.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void TIM_Cmd(TIM_TypeDef *TIMx, FunctionalState NewState);

/**
 * Enables or disables the TIM peripheral Main Outputs.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void TIM_CtrlPWMOutputs(TIM_TypeDef *TIMx, FunctionalState NewState);

/**
 * Enables or disables the specified TIM interrupts.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_IT specifies the TIM interrupts sources to be enabled or disabled.
 *    TIM_IT_Update - TIM update Interrupt source.
 *    TIM_IT_CC1 - TIM Capture Compare 1 Interrupt source.
 *    TIM_IT_CC2 - TIM Capture Compare 2 Interrupt source
 *    TIM_IT_CC3 - TIM Capture Compare 3 Interrupt source.
 *    TIM_IT_CC4 - TIM Capture Compare 4 Interrupt source.
 *    TIM_IT_COM - TIM Commutation Interrupt source.
 *    TIM_IT_Trigger - TIM Trigger Interrupt source.
 *    TIM_IT_Break - TIM Break Interrupt source.
 * @param NewState ENABLE or DISABLE.
 */
void TIM_ITConfig(TIM_TypeDef *TIMx, uint16_t TIM_IT, FunctionalState NewState);

/**
 * Configures the TIMx event to be generate by software.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_IT specifies the TIM interrupts sources to be enabled or disabled.
 *    TIM_IT_Update - TIM update Interrupt source.
 *    TIM_IT_CC1 - TIM Capture Compare 1 Interrupt source.
 *    TIM_IT_CC2 - TIM Capture Compare 2 Interrupt source
 *    TIM_IT_CC3 - TIM Capture Compare 3 Interrupt source.
 *    TIM_IT_CC4 - TIM Capture Compare 4 Interrupt source.
 *    TIM_IT_COM - TIM Commutation Interrupt source.
 *    TIM_IT_Trigger - TIM Trigger Interrupt source.
 *    TIM_IT_Break - TIM Break Interrupt source.
 * @param NewState ENABLE or DISABLE.
 */
void TIM_GenerateEvent(TIM_TypeDef *TIMx, uint16_t TIM_EventSource);

/**
 * Configures the TIMx's DMA interface.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 *    TIM_DMABase: DMA Base address.
 *    TIM_DMABase_CR.
 *    TIM_DMABase_CR2.
 *    TIM_DMABase_SMCR.
 *    TIM_DMABase_DIER.
 *    TIM1_DMABase_SR.
 *    TIM_DMABase_EGR.
 *    TIM_DMABase_CCMR1.
 *    TIM_DMABase_CCMR2.
 *    TIM_DMABase_CCER.
 *    TIM_DMABase_CNT.
 *    TIM_DMABase_PSC.
 *    TIM_DMABase_CCR1.
 *    TIM_DMABase_CCR2.
 *    TIM_DMABase_CCR3.
 *    TIM_DMABase_CCR4.
 *    TIM_DMABase_BDTR.
 *    TIM_DMABase_DCR.
 * @param TIM_DMABurstLength DMA Burst length.
 *    TIM_DMABurstLength_1Transfer.
 *    TIM_DMABurstLength_18Transfers.
 */
void TIM_DMAConfig(TIM_TypeDef *TIMx, uint16_t TIM_DMABase, uint16_t TIM_DMABurstLength);

/**
 * Enables or disables the TIMx's DMA Requests.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_DMASource specifies the DMA Request sources.
 *    TIM_DMA_Update - TIM update Interrupt source.
 *    TIM_DMA_CC1 - TIM Capture Compare 1 DMA source.
 *    TIM_DMA_CC2 - TIM Capture Compare 2 DMA source.
 *    TIM_DMA_CC3 - TIM Capture Compare 3 DMA source.
 *    TIM_DMA_CC4 - TIM Capture Compare 4 DMA source.
 *    TIM_DMA_COM - TIM Commutation DMA source.
 *    TIM_DMA_Trigger - TIM Trigger DMA source.
 * @param NewState ENABLE or DISABLE.
 */
void TIM_DMACmd(TIM_TypeDef *TIMx, uint16_t TIM_DMASource, FunctionalState NewState);

/**
 * Configures the TIMx internal Clock.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 */
void TIM_InternalClockConfig(TIM_TypeDef *TIMx);

/**
 * Configures the TIMx Internal Trigger as External Clock.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 *    TIM_InputTriggerSource: Trigger source.
 *    TIM_TS_ITR0 - Internal Trigger 0.
 *    TIM_TS_ITR1 - Internal Trigger 1.
 *    TIM_TS_ITR2 - Internal Trigger 2.
 *    TIM_TS_ITR3 - Internal Trigger 3.
 */
void TIM_ITRxExternalClockConfig(TIM_TypeDef *TIMx, uint16_t TIM_InputTriggerSource);

/**
 * Configures the TIMx Trigger as External Clock.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_TIxExternalCLKSource Trigger source.
 *    TIM_TIxExternalCLK1Source_TI1ED - TI1 Edge Detector.
 *    TIM_TIxExternalCLK1Source_TI1 - Filtered Timer Input 1.
 *    TIM_TIxExternalCLK1Source_TI2 - Filtered Timer Input 2.
 * @param TIM_ICPolarity specifies the TIx Polarity.
 *    TIM_ICPolarity_Rising.
 *    TIM_ICPolarity_Falling.
 *    TIM_DMA_COM - TIM Commutation DMA source.
 *    TIM_DMA_Trigger - TIM Trigger DMA source.
 * @param ICFilter specifies the filter value.
 * This parameter must be a value between 0x0 and 0xF.
 */
void TIM_TIxExternalClockConfig(TIM_TypeDef *TIMx, uint16_t TIM_TIxExternalCLKSource, uint16_t TIM_ICPolarity, uint16_t ICFilter);

/**
 * Configures the External clock Mode1.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_ExtTRGPrescaler The external Trigger Prescaler.
 *    TIM_ExtTRGPSC_OFF - ETRP Prescaler OFF.
 *    TIM_ExtTRGPSC_DIV2 - ETRP frequency divided by 2.
 *    TIM_ExtTRGPSC_DIV4 - ETRP frequency divided by 4.
 *    TIM_ExtTRGPSC_DIV8 - ETRP frequency divided by 8.
 * @param TIM_ExtTRGPolarity The external Trigger Polarity.
 *    TIM_ExtTRGPolarity_Inverted - active low or falling edge active.
 *    TIM_ExtTRGPolarity_NonInverted - active high or rising edge active.
 * @param ExtTRGFilter External Trigger Filter.
 * This parameter must be a value between 0x0 and 0xF.
 */
void TIM_ETRClockMode1Config(TIM_TypeDef *TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter);

/**
 * Configures the External clock Mode2.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_ExtTRGPrescaler The external Trigger Prescaler.
 *    TIM_ExtTRGPSC_OFF - ETRP Prescaler OFF.
 *    TIM_ExtTRGPSC_DIV2 - ETRP frequency divided by 2.
 *    TIM_ExtTRGPSC_DIV4 - ETRP frequency divided by 4.
 *    TIM_ExtTRGPSC_DIV8 - ETRP frequency divided by 8.
 * @param TIM_ExtTRGPolarity The external Trigger Polarity.
 *    TIM_ExtTRGPolarity_Inverted - active low or falling edge active.
 *    TIM_ExtTRGPolarity_NonInverted - active high or rising edge active.
 * @param ExtTRGFilter External Trigger Filter.
 * This parameter must be a value between 0x0 and 0xF.
 */
void TIM_ETRClockMode2Config(TIM_TypeDef *TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter);

/**
 * Configures the TIMx External Trigger (ETR).
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_ExtTRGPrescaler The external Trigger Prescaler.
 *    TIM_ExtTRGPSC_OFF - ETRP Prescaler OFF.
 *    TIM_ExtTRGPSC_DIV2 - ETRP frequency divided by 2.
 *    TIM_ExtTRGPSC_DIV4 - ETRP frequency divided by 4.
 *    TIM_ExtTRGPSC_DIV8 - ETRP frequency divided by 8.
 * @param TIM_ExtTRGPolarity The external Trigger Polarity.
 *    TIM_ExtTRGPolarity_Inverted - active low or falling edge active.
 *    TIM_ExtTRGPolarity_NonInverted - active high or rising edge active.
 * @param ExtTRGFilter External Trigger Filter.
 * This parameter must be a value between 0x0 and 0xF.
 */
void TIM_ETRConfig(TIM_TypeDef *TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter);

/**
 * Configures the TIMx Prescaler.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param Prescaler specifies the Prescaler Register value.
 * @param TIM_PSCReloadMode specifies the TIM Prescaler Reload mode.
 *    TIM_PSCReloadMode - specifies the TIM Prescaler Reload mode.
 *    TIM_PSCReloadMode_Update - The Prescaler is loaded at the update event.
 *    TIM_PSCReloadMode_Immediate - The Prescaler is loaded immediately.
 */
void TIM_PrescalerConfig(TIM_TypeDef *TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode);

/**
 * Specifies the TIMx Counter Mode to be used.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_CounterMode specifies the Counter Mode to be used.
 *    TIM_CounterMode_Up - TIM Up Counting Mode.
 *    TIM_CounterMode_Down - TIM Down Counting Mode.
 *    TIM_CounterMode_CenterAligned1 - TIM Center Aligned Mode1.
 *    TIM_CounterMode_CenterAligned2 - TIM Center Aligned Mode2.
 *    TIM_CounterMode_CenterAligned3 - TIM Center Aligned Mode3.
 */
void TIM_CounterModeConfig(TIM_TypeDef *TIMx, uint16_t TIM_CounterMode);

/**
 * Selects the Input Trigger source.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_InputTriggerSource The Input Trigger source.
 *    TIM_TS_ITR0 - Internal Trigger 0.
 *    TIM_TS_ITR1 - Internal Trigger 1.
 *    TIM_TS_ITR2 - Internal Trigger 2.
 *    TIM_TS_ITR3 - Internal Trigger 3.
 *    TIM_TS_TI1F_ED - TI1 Edge Detector.
 *    TIM_TS_TI1FP1 - Filtered Timer Input 1.
 *    TIM_TS_TI2FP2 - Filtered Timer Input 2.
 *    TIM_TS_ETRF - External Trigger input.
 */
void TIM_SelectInputTrigger(TIM_TypeDef *TIMx, uint16_t TIM_InputTriggerSource);

/**
 * Configures the TIMx Encoder Interface.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_EncoderMode specifies the TIMx Encoder Mode.
 *    TIM_EncoderMode_TI1 - Counter counts on TI1FP1 edge depending
 *    on TI2FP2 level.
 *    TIM_EncoderMode_TI2 - Counter counts on TI2FP2 edge depending
 *    on TI1FP1 level.
 *    TIM_EncoderMode_TI12 - Counter counts on both TI1FP1 and
 *    TI2FP2 edges depending.
 * @param TIM_IC1Polarity specifies the IC1 Polarity.
 *    TIM_ICPolarity_Falling - IC Falling edge.
 *    TTIM_ICPolarity_Rising - IC Rising edge.
 * @param TIM_IC2Polarity specifies the IC2 Polarity.
 *    TIM_ICPolarity_Falling - IC Falling edge.
 *    TIM_ICPolarity_Rising - IC Rising edge.
 */
void TIM_EncoderInterfaceConfig(TIM_TypeDef *TIMx, uint16_t TIM_EncoderMode, uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity);

/**
 * Forces the TIMx output 1 waveform to active or inactive level.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_ForcedAction specifies the forced Action to be set to the
 * output waveform.
 *    TIM_ForcedAction_Active - Force active level on OC1REF.
 *    TIM_ForcedAction_InActive - Force inactive level on OC1REF.
 */
void TIM_ForcedOC1Config(TIM_TypeDef *TIMx, uint16_t TIM_ForcedAction);

/**
 * Forces the TIMx output 2 waveform to active or inactive level.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_ForcedAction specifies the forced Action to be set to the
 * output waveform.
 *    TIM_ForcedAction_Active - Force active level on OC2REF.
 *    TIM_ForcedAction_InActive - Force inactive level on OC2REF.
 */
void TIM_ForcedOC2Config(TIM_TypeDef *TIMx, uint16_t TIM_ForcedAction);

/**
 * Forces the TIMx output 3 waveform to active or inactive level.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_ForcedAction specifies the forced Action to be set to the
 * output waveform.
 *    TIM_ForcedAction_Active - Force active level on OC3REF.
 *    TIM_ForcedAction_InActive - Force inactive level on OC3REF.
 */
void TIM_ForcedOC3Config(TIM_TypeDef *TIMx, uint16_t TIM_ForcedAction);

/**
 * Forces the TIMx output 4 waveform to active or inactive level.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_ForcedAction specifies the forced Action to be set to the
 * output waveform.
 *    TIM_ForcedAction_Active - Force active level on OC4REF.
 *    TIM_ForcedAction_InActive - Force inactive level on OC4REF.
 */
void TIM_ForcedOC4Config(TIM_TypeDef *TIMx, uint16_t TIM_ForcedAction);

/**
 * Enables or disables TIMx peripheral Preload register on ARR.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void TIM_ARRPreloadConfig(TIM_TypeDef *TIMx, FunctionalState NewState);

/**
 * Selects the TIM peripheral Commutation event.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void TIM_SelectCOM(TIM_TypeDef *TIMx, FunctionalState NewState);

/**
 * Selects the TIMx peripheral Capture Compare DMA source.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void TIM_SelectCCDMA(TIM_TypeDef *TIMx, FunctionalState NewState);

/**
 * DSets or Resets the TIM peripheral Capture Compare Preload Control bit.
 * reset values (Affects also the I2Ss).
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void TIM_CCPreloadControl(TIM_TypeDef *TIMx, FunctionalState NewState);

/**
 * Enables or disables the TIMx peripheral Preload register on CCR1.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_OCPreload new state of the TIMx peripheral Preload register.
 *    TIM_OCPreload_Enable.
 *    TIM_OCPreload_Disable.
 */
void TIM_OC1PreloadConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPreload);

/**
 * Enables or disables the TIMx peripheral Preload register on CCR2.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_OCPreload new state of the TIMx peripheral Preload register.
 *    TIM_OCPreload_Enable.
 *    TIM_OCPreload_Disable.
 */
void TIM_OC2PreloadConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPreload);

/**
 * Enables or disables the TIMx peripheral Preload register on CCR3.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_OCPreload new state of the TIMx peripheral Preload register.
 *    TIM_OCPreload_Enable.
 *    TIM_OCPreload_Disable.
 */
void TIM_OC3PreloadConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPreload);

/**
 * Enables or disables the TIMx peripheral Preload register on CCR4.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_OCPreload new state of the TIMx peripheral Preload register.
 *    TIM_OCPreload_Enable.
 *    TIM_OCPreload_Disable.
 */
void TIM_OC4PreloadConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPreload);

/**
 * Configures the TIMx Output Compare 1 Fast feature.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_OCFast new state of the Output Compare Fast Enable Bit.
 *    TIM_OCFast_Enable - TIM output compare fast enable.
 *    TIM_OCFast_Disable - TIM output compare fast disable.
 */
void TIM_OC1FastConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCFast);

/**
 * Configures the TIMx Output Compare 2 Fast feature.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_OCFast new state of the Output Compare Fast Enable Bit.
 *    TIM_OCFast_Enable - TIM output compare fast enable.
 *    TIM_OCFast_Disable - TIM output compare fast disable.
 */
void TIM_OC2FastConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCFast);

/**
 * Configures the TIMx Output Compare 3 Fast feature.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_OCFast new state of the Output Compare Fast Enable Bit.
 *    TIM_OCFast_Enable - TIM output compare fast enable.
 *    TIM_OCFast_Disable - TIM output compare fast disable.
 */
void TIM_OC3FastConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCFast);

/**
 * Configures the TIMx Output Compare 4 Fast feature.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_OCFast new state of the Output Compare Fast Enable Bit.
 *    TIM_OCFast_Enable - TIM output compare fast enable.
 *    TIM_OCFast_Disable - TIM output compare fast disable.
 */
void TIM_OC4FastConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCFast);

/**
 * Clears or safeguards the OCREF1 signal on an external event.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_OCClear new state of the Output Compare Clear Enable Bit.
 *    TIM_OCClear_Enable - TIM Output clear enable.
 *    TIM_OCClear_Disable - TIM Output clear disable.
 */
void TIM_ClearOC1Ref(TIM_TypeDef *TIMx, uint16_t TIM_OCClear);

/**
 * Clears or safeguards the OCREF2 signal on an external event.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_OCClear new state of the Output Compare Clear Enable Bit.
 *    TIM_OCClear_Enable - TIM Output clear enable.
 *    TIM_OCClear_Disable - TIM Output clear disable.
 */
void TIM_ClearOC2Ref(TIM_TypeDef *TIMx, uint16_t TIM_OCClear);

/**
 * Clears or safeguards the OCREF3 signal on an external event.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_OCClear new state of the Output Compare Clear Enable Bit.
 *    TIM_OCClear_Enable - TIM Output clear enable.
 *    TIM_OCClear_Disable - TIM Output clear disable.
 */
void TIM_ClearOC3Ref(TIM_TypeDef *TIMx, uint16_t TIM_OCClear);

/**
 * Clears or safeguards the OCREF4 signal on an external event.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_OCClear new state of the Output Compare Clear Enable Bit.
 *    TIM_OCClear_Enable - TIM Output clear enable.
 *    TIM_OCClear_Disable - TIM Output clear disable.
 */
void TIM_ClearOC4Ref(TIM_TypeDef *TIMx, uint16_t TIM_OCClear);

/**
 * Configures the TIMx channel 1 polarity.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_OCPolarity specifies the OC1 Polarity.
 *    TIM_OCPolarity_High - Output Compare active high.
 *    TIM_OCPolarity_Low - Output Compare active low.
 */
void TIM_OC1PolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPolarity);

/**
 * Configures the TIMx channel 1 polarity.
 *
 * @param TIMx where x can be 1 to select the TIM peripheral.
 * @param TIM_OCNPolarity specifies the OC1N Polarity.
 *    TIM_OCNPolarity_High - Output Compare active high.
 *    TIM_OCNPolarity_Low - Output Compare active low.
 */
void TIM_OC1NPolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCNPolarity);

/**
 * Configures the TIMx channel 2 polarity.
 *
 * @param TIMx where x can be 1 to 2 to select the TIM peripheral.
 * @param TIM_OCPolarity specifies the OC2 Polarity.
 *    TIM_OCPolarity_High - Output Compare active high.
 *    TIM_OCPolarity_Low - Output Compare active low.
 */
void TIM_OC2PolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPolarity);

/**
 * Configures the TIMx channel 2 polarity.
 *
 * @param TIMx where x can be 1 to select the TIM peripheral.
 * @param TIM_OCNPolarity specifies the OC1N Polarity.
 *    TIM_OCNPolarity_High - Output Compare active high.
 *    TIM_OCNPolarity_Low - Output Compare active low.
 */
void TIM_OC2NPolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCNPolarity);

/**
 * Configures the TIMx Channel 3 polarity.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param TIM_OCPolarit specifies the OC3 Polarity.
 *    TIM_OCPolarity_High - Output Compare active high.
 *    TIM_OCPolarity_Low - Output Compare active low.
 */
void TIM_OC3PolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPolarity);

/**
 * Configures the TIMx Channel 3N polarity.
 *
 * @param TIMx where x can be 1 to select the TIM peripheral.
 * @param TIM_OCNPolarity specifies the OC2N Polarity.
 *    TIM_OCNPolarity_High - Output Compare active high.
 *    TIM_OCNPolarity_Low - Output Compare active low.
 */
void TIM_OC3NPolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCNPolarity);

/**
 * Configures the TIMx Channel 2 polarity.
 *
 * @param TIMx where x can be 1 to 4 select the TIM peripheral.
 * @param TIM_OCPolarit specifies the OC3 Polarity.
 *    TIM_OCPolarity_High - Output Compare active high.
 *    TIM_OCPolarity_Low - Output Compare active low.
 */
void TIM_OC4PolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPolarity);

/**
 * Enables or disables the TIM Capture Compare Channel x.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param TIM_Channel specifies the TIM Channel.
 *    TIM_Channel_1 - TIM Channel 1.
 *    TIM_Channel_2 - TIM Channel 2.
 *    TIM_Channel_3 - TIM Channel 3.
 *    TIM_Channel_4 - TIM Channel 4.
 * @param TIM_CCx specifies the TIM Channel CCxE bit new state.
 *    TIM_CCx_Enable.
 *    TIM_CCx_Disable.
 */
void TIM_CCxCmd(TIM_TypeDef *TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx);

/**
 * Enables or disables the TIM Capture Compare Channel xN.
 *
 * @param TIMx where x can be 1 select the TIM peripheral.
 * @param TIM_Channel specifies the TIM Channel.
 *    TIM_Channel_1 - TIM Channel 1.
 *    TIM_Channel_2 - TIM Channel 2.
 *    TIM_Channel_3 - TIM Channel 3.
 * @param TIM_CCxN specifies the TIM Channel CCxNE bit new state.
 *    TIM_CCxN_Enable.
 *    TIM_CCxN_Disable.
 */
void TIM_CCxNCmd(TIM_TypeDef *TIMx, uint16_t TIM_Channel, uint16_t TIM_CCxN);

/**
 * Selects the TIM Output Compare Mode.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param TIM_Channel specifies the TIM Channel.
 *    TIM_Channel_1 - TIM Channel 1.
 *    TIM_Channel_2 - TIM Channel 2.
 *    TIM_Channel_3 - TIM Channel 3.
 *    TIM_Channel_4 - TIM Channel 4.
 * @param TIM_OCMode specifies the TIM Output Compare Mode.
 *    TIM_OCMode_Timing.
 *    TIM_OCMode_Active.
 *    TIM_OCMode_Toggle.
 *    TIM_OCMode_PWM1.
 *    TIM_OCMode_PWM2.
 *    TIM_ForcedAction_Active.
 *    TIM_ForcedAction_InActive.
 */
void TIM_SelectOCxM(TIM_TypeDef *TIMx, uint16_t TIM_Channel, uint16_t TIM_OCMode);

/**
 * Enables or Disables the TIMx Update event.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void TIM_UpdateDisableConfig(TIM_TypeDef *TIMx, FunctionalState NewState);

/**
 * Configures the TIMx Update Request Interrupt source.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param TIM_UpdateSource specifies the Update source.
 *    TIM_UpdateSource_Regular.
 *    TIM_UpdateSource_Global.
 */
void TIM_UpdateRequestConfig(TIM_TypeDef *TIMx, uint16_t TIM_UpdateSource);

/**
 * Enables or disables the TIMx's Hall sensor interface.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param NewState ENABLE or DISABLE.
 */
void TIM_SelectHallSensor(TIM_TypeDef *TIMx, FunctionalState NewState);

/**
 * Selects the TIMx's One Pulse Mode.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param TIM_OPMode specifies the OPM Mode to be used.
 *    TIM_OPMode_Single.
 *    TIM_OPMode_Repetitive.
 */
void TIM_SelectOnePulseMode(TIM_TypeDef *TIMx, uint16_t TIM_OPMode);

/**
 * Selects the TIMx Trigger Output Mode.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param TIM_TRGOSource specifies the Trigger Output source.
 *    TIM_TRGOSource_Reset -  The UG bit in the TIM_EGR register is
 *    used as the trigger output (TRGO).
 *    TIM_TRGOSource_Enable - The Counter Enable CEN is used as the
 *    trigger output (TRGO).
 *    TIM_TRGOSource_Update - The update event is selected as the
 *    trigger output (TRGO).
 *    TIM_TRGOSource_OC1 - The trigger output sends a positive pulse
 *    when the CC1IF flag is to be set, as soon as a capture or compare match occurs (TRGO).
 *    TIM_TRGOSource_OC1Ref - OC1REF signal is used as the trigger output (TRGO).
 *    TIM_TRGOSource_OC2Ref - OC2REF signal is used as the trigger output (TRGO).
 *    TIM_TRGOSource_OC3Ref - OC3REF signal is used as the trigger output (TRGO).
 *    TIM_TRGOSource_OC4Ref - OC4REF signal is used as the trigger output (TRGO).
 */
void TIM_SelectOutputTrigger(TIM_TypeDef *TIMx, uint16_t TIM_TRGOSource);

/**
 * Selects the TIMx Slave Mode.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param TIM_SlaveMode specifies the Timer Slave Mode.
 *    TIM_SlaveMode_Reset - Rising edge of the selected trigger
 *    signal (TRGI) re-initializes.
 *    TIM_SlaveMode_Gated - The counter clock is enabled when the
 *    trigger signal (TRGI) is high.
 *    TIM_SlaveMode_Trigger - The counter starts at a rising edge
 *    of the trigger TRGI.
 *    TIM_SlaveMode_External1 - Rising edges of the selected trigger
 *    TRGI) clock the counter.
 */
void TIM_SelectSlaveMode(TIM_TypeDef *TIMx, uint16_t TIM_SlaveMode);

/**
 * Sets or Resets the TIMx Master/Slave Mode.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param TIM_MasterSlaveMode specifies the Timer Master Slave Mode.
 *    TIM_MasterSlaveMode_Enable - synchronization between the current
 *    timer and its slaves (through TRGO).
 *    TIM_MasterSlaveMode_Disable - No action.
 */
void TIM_SelectMasterSlaveMode(TIM_TypeDef *TIMx, uint16_t TIM_MasterSlaveMode);

/**
 * Sets the TIMx Counter Register value.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param Counter specifies the Counter register new value.
 */
void TIM_SetCounter(TIM_TypeDef *TIMx, uint16_t Counter);

/**
 * Sets the TIMx Autoreload Register value.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param Autoreload specifies the Autoreload register new value.
 */
void TIM_SetAutoreload(TIM_TypeDef *TIMx, uint16_t Autoreload);

/**
 * Sets the TIMx Capture Compare1 Register value.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param Compare1 specifies the Capture Compare1 register new value.
 */
void TIM_SetCompare1(TIM_TypeDef *TIMx, uint16_t Compare1);

/**
 * Sets the TIMx Capture Compare2 Register value.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param Compare1 specifies the Capture Compare1 register new value.
 */
void TIM_SetCompare2(TIM_TypeDef *TIMx, uint16_t Compare2);

/**
 * Sets the TIMx Capture Compare3 Register value.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param Compare1 specifies the Capture Compare1 register new value.
 */
void TIM_SetCompare3(TIM_TypeDef *TIMx, uint16_t Compare3);

/**
 * Sets the TIMx Capture Compare4 Register value.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param Compare1 specifies the Capture Compare1 register new value.
 */
void TIM_SetCompare4(TIM_TypeDef *TIMx, uint16_t Compare4);

/**
 * Sets the TIMx Input Capture 1 prescaler.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param TIM_ICPSC specifies the Input Capture1 prescaler new value.
 *    TIM_ICPSC_DIV1 - no prescaler.
 *    TIM_ICPSC_DIV2 - capture is done once every 2 events.
 *    TIM_ICPSC_DIV4 - capture is done once every 4 events.
 *    TIM_ICPSC_DIV8 - capture is done once every 8 events.
 */
void TIM_SetIC1Prescaler(TIM_TypeDef *TIMx, uint16_t TIM_ICPSC);

/**
 * Sets the TIMx Input Capture 2 prescaler.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param TIM_ICPSC specifies the Input Capture1 prescaler new value.
 *    TIM_ICPSC_DIV1 - no prescaler.
 *    TIM_ICPSC_DIV2 - capture is done once every 2 events.
 *    TIM_ICPSC_DIV4 - capture is done once every 4 events.
 *    TIM_ICPSC_DIV8 - capture is done once every 8 events.
 */
void TIM_SetIC2Prescaler(TIM_TypeDef *TIMx, uint16_t TIM_ICPSC);

/**
 * Sets the TIMx Input Capture 3 prescaler.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param TIM_ICPSC specifies the Input Capture1 prescaler new value.
 *    TIM_ICPSC_DIV1 - no prescaler.
 *    TIM_ICPSC_DIV2 - capture is done once every 2 events.
 *    TIM_ICPSC_DIV4 - capture is done once every 4 events.
 *    TIM_ICPSC_DIV8 - capture is done once every 8 events.
 */
void TIM_SetIC3Prescaler(TIM_TypeDef *TIMx, uint16_t TIM_ICPSC);

/**
 * Sets the TIMx Input Capture 4 prescaler.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param TIM_ICPSC specifies the Input Capture1 prescaler new value.
 *    TIM_ICPSC_DIV1 - no prescaler.
 *    TIM_ICPSC_DIV2 - capture is done once every 2 events.
 *    TIM_ICPSC_DIV4 - capture is done once every 4 events.
 *    TIM_ICPSC_DIV8 - capture is done once every 8 events.
 */
void TIM_SetIC4Prescaler(TIM_TypeDef *TIMx, uint16_t TIM_ICPSC);

/**
 * Sets the TIMx Clock Division value.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param TIM_CKD specifies the clock division value.
 *    TIM_CKD_DIV1 - TDTS = Tck_tim.
 *    TIM_CKD_DIV2 - TDTS = 2*Tck_tim.
 *    TIM_CKD_DIV4 - TDTS = 4*Tck_tim.
 */
void TIM_SetClockDivision(TIM_TypeDef *TIMx, uint16_t TIM_CKD);

/**
 * Gets the TIMx Input Capture 1 value.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 *
 * @return Capture Compare 1 Register value.
 */
uint16_t TIM_GetCapture1(TIM_TypeDef *TIMx);

/**
 * Gets the TIMx Input Capture 2 value.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 *
 * @return Capture Compare 2 Register value.
 */
uint16_t TIM_GetCapture2(TIM_TypeDef *TIMx);

/**
 * Gets the TIMx Input Capture 3 value.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 *
 * @return Capture Compare 2 Register value.
 */
uint16_t TIM_GetCapture3(TIM_TypeDef *TIMx);

/**
 * Gets the TIMx Input Capture 4 value.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 *
 * @return Capture Compare 4 Register value.
 */
uint16_t TIM_GetCapture4(TIM_TypeDef *TIMx);

/**
 * Gets the TIMx Counter value.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 *
 * @return Counter Register value.
 */
uint16_t TIM_GetCounter(TIM_TypeDef *TIMx);

/**
 * Gets the TIMx Prescaler value.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 *
 * @return Prescaler Register value.
 */
uint16_t TIM_GetPrescaler(TIM_TypeDef *TIMx);

/**
 * Checks whether the specified TIM flag is set or not.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param TIM_FLAG specifies the flag to check.
 *    TIM_FLAG_Update - TIM update Flag.
 *    TIM_FLAG_CC1 - TIM Capture Compare 1 Flag.
 *    TIM_FLAG_CC2 - TIM Capture Compare 2 Flag.
 *    TIM_FLAG_CC3 - TIM Capture Compare 3 Flag.
 *    TIM_FLAG_CC4 - TIM Capture Compare 4 Flag.
 *    TIM_FLAG_COM - TIM Commutation Flag.
 *    TIM_FLAG_Trigger - TIM Trigger Flag.
 *    TIM_FLAG_Break - TIM Break Flag.
 *    TIM_FLAG_CC1OF - TIM Capture Compare 1 overcapture Flag.
 *    TIM_FLAG_CC2OF - TIM Capture Compare 2 overcapture Flag.
 *    TIM_FLAG_CC3OF - TIM Capture Compare 3 overcapture Flag.
 *    TIM_FLAG_CC4OF - TIM Capture Compare 4 overcapture Flag.
 *
 * @return SET or RESET.
 */
FlagStatus TIM_GetFlagStatus(TIM_TypeDef *TIMx, uint16_t TIM_FLAG);

/**
 * Clears the TIMx's pending flags.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param TIM_FLAG specifies the flag to check.
 *    TIM_FLAG_Update - TIM update Flag.
 *    TIM_FLAG_CC1 - TIM Capture Compare 1 Flag.
 *    TIM_FLAG_CC2 - TIM Capture Compare 2 Flag.
 *    TIM_FLAG_CC3 - TIM Capture Compare 3 Flag.
 *    TIM_FLAG_CC4 - TIM Capture Compare 4 Flag.
 *    TIM_FLAG_COM - TIM Commutation Flag.
 *    TIM_FLAG_Trigger - TIM Trigger Flag.
 *    TIM_FLAG_Break - TIM Break Flag.
 *    TIM_FLAG_CC1OF - TIM Capture Compare 1 overcapture Flag.
 *    TIM_FLAG_CC2OF - TIM Capture Compare 2 overcapture Flag.
 *    TIM_FLAG_CC3OF - TIM Capture Compare 3 overcapture Flag.
 *    TIM_FLAG_CC4OF - TIM Capture Compare 4 overcapture Flag.
 */
void TIM_ClearFlag(TIM_TypeDef *TIMx, uint16_t TIM_FLAG);

/**
 * Checks whether the TIM interrupt has occurred or not.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param TIM_IT specifies the TIM interrupt source to check.
 *    TIM_IT_Update - TIM update Interrupt source.
 *    TIM_IT_CC1 - TIM Capture Compare 1 Interrupt source.
 *    TIM_IT_CC2 - TIM Capture Compare 2 Interrupt source.
 *    TIM_IT_CC3 - TIM Capture Compare 3 Interrupt source.
 *    TIM_IT_CC4 - TIM Capture Compare 4 Interrupt source.
 *    TIM_IT_COM - TIM Commutation Interrupt source.
 *    TIM_IT_Trigger - TIM Trigger Interrupt source.
 *    TIM_IT_Break - TIM Break Interrupt source.
 *
 * @return none
 */
ITStatus TIM_GetITStatus(TIM_TypeDef *TIMx, uint16_t TIM_IT);

/**
 * Clears the TIMx's interrupt pending bits.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param TIM_IT specifies the TIM interrupt source to check.
 *    TIM_IT_Update - TIM update Interrupt source.
 *    TIM_IT_CC1 - TIM Capture Compare 1 Interrupt source.
 *    TIM_IT_CC2 - TIM Capture Compare 2 Interrupt source.
 *    TIM_IT_CC3 - TIM Capture Compare 3 Interrupt source.
 *    TIM_IT_CC4 - TIM Capture Compare 4 Interrupt source.
 *    TIM_IT_COM - TIM Commutation Interrupt source.
 *    TIM_IT_Trigger - TIM Trigger Interrupt source.
 *    TIM_IT_Break - TIM Break Interrupt source.
 */
void TTIM_IM_ClearITPendingBit(TIM_TypeDef *TIMx, uint16_t TIM_IT);

#ifdef __cplusplus
}
#endif

#endif /*__CH32V00x_TIM_H */
