#include <ch32v00x/rcc.h>
#include <ch32v00x/tim.h>

/* TIM registers bit mask */
#define SMCFGR_ETR_Mask    ((uint16_t)0x00FF)
#define CHCTLR_Offset      ((uint16_t)0x0018)
#define CCER_CCE_Set       ((uint16_t)0x0001)
#define CCER_CCNE_Set      ((uint16_t)0x0004)

/**
 * Configure the TI1 as Input.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param IM_ICPolarity The Input Polarity.
 * Available values:
 *    TIM_ICPolarity_Rising.
 *    TIM_ICPolarity_Falling.
 * @param TIM_ICSelection specifies the input to be used.
 * Available values:
 *    TIM_ICSelection_DirectTI - TIM Input 1 is selected to be
 *    connected to IC1.
 *    TIM_ICSelection_IndirectTI - TIM Input 1 is selected to be
 *    connected to IC2.
 *    TIM_ICSelection_TRC - TIM Input 1 is selected to be connected
 *    to TRC.
 * @param TIM_ICFilter Specifies the Input Capture Filter.
 * This parameter must be a value between 0x00 and 0x0F.
 */
static void TI1_Config(TIM_TypeDef *TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection, uint16_t TIM_ICFilter);

/**
 * Configure the TI2 as Input.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param IM_ICPolarity The Input Polarity.
 * Available values:
 *    TIM_ICPolarity_Rising.
 *    TIM_ICPolarity_Falling.
 * @param TIM_ICSelection specifies the input to be used.
 * Available values:
 *    TIM_ICSelection_DirectTI - TIM Input 2 is selected to be
 *    connected to IC1.
 *    TIM_ICSelection_IndirectTI - TIM Input 2 is selected to be
 *    connected to IC2.
 *    TIM_ICSelection_TRC - TIM Input 2 is selected to be connected
 *    to TRC.
 * @param TIM_ICFilter Specifies the Input Capture Filter.
 * This parameter must be a value between 0x00 and 0x0F.
 */
static void TI2_Config(TIM_TypeDef *TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection, uint16_t TIM_ICFilter);

/**
 * Configure the TI3 as Input.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param IM_ICPolarity The Input Polarity.
 * Available values:
 *    TIM_ICPolarity_Rising.
 *    TIM_ICPolarity_Falling.
 * @param TIM_ICSelection specifies the input to be used.
 * Available values:
 *    TIM_ICSelection_DirectTI - TIM Input 3 is selected to be
 *    connected to IC1.
 *    TIM_ICSelection_IndirectTI - TIM Input 3 is selected to be
 *    connected to IC2.
 *    TIM_ICSelection_TRC - TIM Input 3 is selected to be connected
 *    to TRC.
 * @param TIM_ICFilter Specifies the Input Capture Filter.
 * This parameter must be a value between 0x00 and 0x0F.
 */
static void TI3_Config(TIM_TypeDef *TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection, uint16_t TIM_ICFilter);

/**
 * Configure the TI4 as Input.
 *
 * @param TIMx where x can be 1 to 2 select the TIM peripheral.
 * @param IM_ICPolarity The Input Polarity.
 * Available values:
 *    TIM_ICPolarity_Rising.
 *    TIM_ICPolarity_Falling.
 * @param TIM_ICSelection specifies the input to be used.
 * Available values:
 *    TIM_ICSelection_DirectTI - TIM Input 4 is selected to be
 *    connected to IC1.
 *    TIM_ICSelection_IndirectTI - TIM Input 4 is selected to be
 *    connected to IC2.
 *    TIM_ICSelection_TRC - TIM Input 4 is selected to be connected
 *    to TRC.
 * @param TIM_ICFilter Specifies the Input Capture Filter.
 * This parameter must be a value between 0x00 and 0x0F.
 */
static void TI4_Config(TIM_TypeDef *TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection, uint16_t TIM_ICFilter);

void TIM_DeInit(TIM_TypeDef *TIMx)
{
    if(TIMx == TIM1)
    {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_TIM1, DISABLE);
    }
    else if(TIMx == TIM2)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_TIM2, DISABLE);
    }
}

void TIM_TimeBaseInit(TIM_TypeDef *TIMx, TIM_TimeBaseInitTypeDef *TIM_TimeBaseInitStruct)
{
    uint16_t tmpcr1 = 0;

    tmpcr1 = TIMx->CTLR1;

    if((TIMx == TIM1) || (TIMx == TIM2))
    {
        tmpcr1 &= (uint16_t)(~((uint16_t)(TIM_DIR | TIM_CMS)));
        tmpcr1 |= (uint32_t)TIM_TimeBaseInitStruct->TIM_CounterMode;
    }

    tmpcr1 &= (uint16_t)(~((uint16_t)TIM_CTLR1_CKD));
    tmpcr1 |= (uint32_t)TIM_TimeBaseInitStruct->TIM_ClockDivision;

    TIMx->CTLR1 = tmpcr1;
    TIMx->ATRLR = TIM_TimeBaseInitStruct->TIM_Period;
    TIMx->PSC = TIM_TimeBaseInitStruct->TIM_Prescaler;

    if(TIMx == TIM1)
    {
        TIMx->RPTCR = TIM_TimeBaseInitStruct->TIM_RepetitionCounter;
    }

    TIMx->SWEVGR = TIM_PSCReloadMode_Immediate;
}

void TIM_OC1Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct)
{
    uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

    TIMx->CCER &= (uint16_t)(~(uint16_t)TIM_CC1E);
    tmpccer = TIMx->CCER;
    tmpcr2 = TIMx->CTLR2;
    tmpccmrx = TIMx->CHCTLR1;
    tmpccmrx &= (uint16_t)(~((uint16_t)TIM_OC1M));
    tmpccmrx &= (uint16_t)(~((uint16_t)TIM_CC1S));
    tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;
    tmpccer &= (uint16_t)(~((uint16_t)TIM_CC1P));
    tmpccer |= TIM_OCInitStruct->TIM_OCPolarity;
    tmpccer |= TIM_OCInitStruct->TIM_OutputState;

    if(TIMx == TIM1)
    {
        tmpccer &= (uint16_t)(~((uint16_t)TIM_CC1NP));
        tmpccer |= TIM_OCInitStruct->TIM_OCNPolarity;

        tmpccer &= (uint16_t)(~((uint16_t)TIM_CC1NE));
        tmpccer |= TIM_OCInitStruct->TIM_OutputNState;

        tmpcr2 &= (uint16_t)(~((uint16_t)TIM_OIS1));
        tmpcr2 &= (uint16_t)(~((uint16_t)TIM_OIS1N));

        tmpcr2 |= TIM_OCInitStruct->TIM_OCIdleState;
        tmpcr2 |= TIM_OCInitStruct->TIM_OCNIdleState;
    }

    TIMx->CTLR2 = tmpcr2;
    TIMx->CHCTLR1 = tmpccmrx;
    TIMx->CH1CVR = TIM_OCInitStruct->TIM_Pulse;
    TIMx->CCER = tmpccer;
}

void TIM_OC2Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct)
{
    uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

    TIMx->CCER &= (uint16_t)(~((uint16_t)TIM_CC2E));
    tmpccer = TIMx->CCER;
    tmpcr2 = TIMx->CTLR2;
    tmpccmrx = TIMx->CHCTLR1;
    tmpccmrx &= (uint16_t)(~((uint16_t)TIM_OC2M));
    tmpccmrx &= (uint16_t)(~((uint16_t)TIM_CC2S));
    tmpccmrx |= (uint16_t)(TIM_OCInitStruct->TIM_OCMode << 8);
    tmpccer &= (uint16_t)(~((uint16_t)TIM_CC2P));
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCPolarity << 4);
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputState << 4);

    if(TIMx == TIM1)
    {
        tmpccer &= (uint16_t)(~((uint16_t)TIM_CC2NP));
        tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCNPolarity << 4);
        tmpccer &= (uint16_t)(~((uint16_t)TIM_CC2NE));
        tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputNState << 4);

        tmpcr2 &= (uint16_t)(~((uint16_t)TIM_OIS2));
        tmpcr2 &= (uint16_t)(~((uint16_t)TIM_OIS2N));
        tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << 2);
        tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCNIdleState << 2);
    }

    TIMx->CTLR2 = tmpcr2;
    TIMx->CHCTLR1 = tmpccmrx;
    TIMx->CH2CVR = TIM_OCInitStruct->TIM_Pulse;
    TIMx->CCER = tmpccer;
}

void TIM_OC3Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct)
{
    uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

    TIMx->CCER &= (uint16_t)(~((uint16_t)TIM_CC3E));
    tmpccer = TIMx->CCER;
    tmpcr2 = TIMx->CTLR2;
    tmpccmrx = TIMx->CHCTLR2;
    tmpccmrx &= (uint16_t)(~((uint16_t)TIM_OC3M));
    tmpccmrx &= (uint16_t)(~((uint16_t)TIM_CC3S));
    tmpccmrx |= TIM_OCInitStruct->TIM_OCMode;
    tmpccer &= (uint16_t)(~((uint16_t)TIM_CC3P));
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCPolarity << 8);
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputState << 8);

    if(TIMx == TIM1)
    {
        tmpccer &= (uint16_t)(~((uint16_t)TIM_CC3NP));
        tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCNPolarity << 8);
        tmpccer &= (uint16_t)(~((uint16_t)TIM_CC3NE));
        tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputNState << 8);
        tmpcr2 &= (uint16_t)(~((uint16_t)TIM_OIS3));
        tmpcr2 &= (uint16_t)(~((uint16_t)TIM_OIS3N));
        tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << 4);
        tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCNIdleState << 4);
    }

    TIMx->CTLR2 = tmpcr2;
    TIMx->CHCTLR2 = tmpccmrx;
    TIMx->CH3CVR = TIM_OCInitStruct->TIM_Pulse;
    TIMx->CCER = tmpccer;
}

void TIM_OC4Init(TIM_TypeDef *TIMx, TIM_OCInitTypeDef *TIM_OCInitStruct)
{
    uint16_t tmpccmrx = 0, tmpccer = 0, tmpcr2 = 0;

    TIMx->CCER &= (uint16_t)(~((uint16_t)TIM_CC4E));
    tmpccer = TIMx->CCER;
    tmpcr2 = TIMx->CTLR2;
    tmpccmrx = TIMx->CHCTLR2;
    tmpccmrx &= (uint16_t)(~((uint16_t)TIM_OC4M));
    tmpccmrx &= (uint16_t)(~((uint16_t)TIM_CC4S));
    tmpccmrx |= (uint16_t)(TIM_OCInitStruct->TIM_OCMode << 8);
    tmpccer &= (uint16_t)(~((uint16_t)TIM_CC4P));
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OCPolarity << 12);
    tmpccer |= (uint16_t)(TIM_OCInitStruct->TIM_OutputState << 12);

    if(TIMx == TIM1)
    {
        tmpcr2 &= (uint16_t)(~((uint16_t)TIM_OIS4));
        tmpcr2 |= (uint16_t)(TIM_OCInitStruct->TIM_OCIdleState << 6);
    }

    TIMx->CTLR2 = tmpcr2;
    TIMx->CHCTLR2 = tmpccmrx;
    TIMx->CH4CVR = TIM_OCInitStruct->TIM_Pulse;
    TIMx->CCER = tmpccer;
}

void TIM_ICInit(TIM_TypeDef *TIMx, TIM_ICInitTypeDef *TIM_ICInitStruct)
{
    if(TIM_ICInitStruct->TIM_Channel == TIM_Channel_1)
    {
        TI1_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
                   TIM_ICInitStruct->TIM_ICSelection,
                   TIM_ICInitStruct->TIM_ICFilter);
        TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    }
    else if(TIM_ICInitStruct->TIM_Channel == TIM_Channel_2)
    {
        TI2_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
                   TIM_ICInitStruct->TIM_ICSelection,
                   TIM_ICInitStruct->TIM_ICFilter);
        TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    }
    else if(TIM_ICInitStruct->TIM_Channel == TIM_Channel_3)
    {
        TI3_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
                   TIM_ICInitStruct->TIM_ICSelection,
                   TIM_ICInitStruct->TIM_ICFilter);
        TIM_SetIC3Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    }
    else
    {
        TI4_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity,
                   TIM_ICInitStruct->TIM_ICSelection,
                   TIM_ICInitStruct->TIM_ICFilter);
        TIM_SetIC4Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    }
}

void TIM_PWMIConfig(TIM_TypeDef *TIMx, TIM_ICInitTypeDef *TIM_ICInitStruct)
{
    uint16_t icoppositepolarity = TIM_ICPolarity_Rising;
    uint16_t icoppositeselection = TIM_ICSelection_DirectTI;

    if(TIM_ICInitStruct->TIM_ICPolarity == TIM_ICPolarity_Rising)
    {
        icoppositepolarity = TIM_ICPolarity_Falling;
    }
    else
    {
        icoppositepolarity = TIM_ICPolarity_Rising;
    }

    if(TIM_ICInitStruct->TIM_ICSelection == TIM_ICSelection_DirectTI)
    {
        icoppositeselection = TIM_ICSelection_IndirectTI;
    }
    else
    {
        icoppositeselection = TIM_ICSelection_DirectTI;
    }

    if(TIM_ICInitStruct->TIM_Channel == TIM_Channel_1)
    {
        TI1_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity, TIM_ICInitStruct->TIM_ICSelection,
                   TIM_ICInitStruct->TIM_ICFilter);
        TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
        TI2_Config(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->TIM_ICFilter);
        TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    }
    else
    {
        TI2_Config(TIMx, TIM_ICInitStruct->TIM_ICPolarity, TIM_ICInitStruct->TIM_ICSelection,
                   TIM_ICInitStruct->TIM_ICFilter);
        TIM_SetIC2Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
        TI1_Config(TIMx, icoppositepolarity, icoppositeselection, TIM_ICInitStruct->TIM_ICFilter);
        TIM_SetIC1Prescaler(TIMx, TIM_ICInitStruct->TIM_ICPrescaler);
    }
}

void TIM_BDTRConfig(TIM_TypeDef *TIMx, TIM_BDTRInitTypeDef *TIM_BDTRInitStruct)
{
    TIMx->BDTR = (uint32_t)TIM_BDTRInitStruct->TIM_OSSRState | TIM_BDTRInitStruct->TIM_OSSIState |
                 TIM_BDTRInitStruct->TIM_LOCKLevel | TIM_BDTRInitStruct->TIM_DeadTime |
                 TIM_BDTRInitStruct->TIM_Break | TIM_BDTRInitStruct->TIM_BreakPolarity |
                 TIM_BDTRInitStruct->TIM_AutomaticOutput;
}

void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef *TIM_TimeBaseInitStruct)
{
    TIM_TimeBaseInitStruct->TIM_Period = 0xFFFF;
    TIM_TimeBaseInitStruct->TIM_Prescaler = 0x0000;
    TIM_TimeBaseInitStruct->TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct->TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct->TIM_RepetitionCounter = 0x0000;
}

void TIM_OCStructInit(TIM_OCInitTypeDef *TIM_OCInitStruct)
{
    TIM_OCInitStruct->TIM_OCMode = TIM_OCMode_Timing;
    TIM_OCInitStruct->TIM_OutputState = TIM_OutputState_Disable;
    TIM_OCInitStruct->TIM_OutputNState = TIM_OutputNState_Disable;
    TIM_OCInitStruct->TIM_Pulse = 0x0000;
    TIM_OCInitStruct->TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OCInitStruct->TIM_OCNPolarity = TIM_OCPolarity_High;
    TIM_OCInitStruct->TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OCInitStruct->TIM_OCNIdleState = TIM_OCNIdleState_Reset;
}

void TIM_ICStructInit(TIM_ICInitTypeDef *TIM_ICInitStruct)
{
    TIM_ICInitStruct->TIM_Channel = TIM_Channel_1;
    TIM_ICInitStruct->TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStruct->TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStruct->TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStruct->TIM_ICFilter = 0x00;
}

void TIM_BDTRStructInit(TIM_BDTRInitTypeDef *TIM_BDTRInitStruct)
{
    TIM_BDTRInitStruct->TIM_OSSRState = TIM_OSSRState_Disable;
    TIM_BDTRInitStruct->TIM_OSSIState = TIM_OSSIState_Disable;
    TIM_BDTRInitStruct->TIM_LOCKLevel = TIM_LOCKLevel_OFF;
    TIM_BDTRInitStruct->TIM_DeadTime = 0x00;
    TIM_BDTRInitStruct->TIM_Break = TIM_Break_Disable;
    TIM_BDTRInitStruct->TIM_BreakPolarity = TIM_BreakPolarity_Low;
    TIM_BDTRInitStruct->TIM_AutomaticOutput = TIM_AutomaticOutput_Disable;
}

void TIM_Cmd(TIM_TypeDef *TIMx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        TIMx->CTLR1 |= TIM_CEN;
    }
    else
    {
        TIMx->CTLR1 &= (uint16_t)(~((uint16_t)TIM_CEN));
    }
}

void TIM_CtrlPWMOutputs(TIM_TypeDef *TIMx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        TIMx->BDTR |= TIM_MOE;
    }
    else
    {
        TIMx->BDTR &= (uint16_t)(~((uint16_t)TIM_MOE));
    }
}

void TIM_ITConfig(TIM_TypeDef *TIMx, uint16_t TIM_IT, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        TIMx->DMAINTENR |= TIM_IT;
    }
    else
    {
        TIMx->DMAINTENR &= (uint16_t)~TIM_IT;
    }
}

void TIM_GenerateEvent(TIM_TypeDef *TIMx, uint16_t TIM_EventSource)
{
    TIMx->SWEVGR = TIM_EventSource;
}

void TIM_DMAConfig(TIM_TypeDef *TIMx, uint16_t TIM_DMABase, uint16_t TIM_DMABurstLength)
{
    TIMx->DMACFGR = TIM_DMABase | TIM_DMABurstLength;
}

void TIM_DMACmd(TIM_TypeDef *TIMx, uint16_t TIM_DMASource, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        TIMx->DMAINTENR |= TIM_DMASource;
    }
    else
    {
        TIMx->DMAINTENR &= (uint16_t)~TIM_DMASource;
    }
}

void TIM_InternalClockConfig(TIM_TypeDef *TIMx)
{
    TIMx->SMCFGR &= (uint16_t)(~((uint16_t)TIM_SMS));
}

void TIM_ITRxExternalClockConfig(TIM_TypeDef *TIMx, uint16_t TIM_InputTriggerSource)
{
    TIM_SelectInputTrigger(TIMx, TIM_InputTriggerSource);
    TIMx->SMCFGR |= TIM_SlaveMode_External1;
}

void TIM_TIxExternalClockConfig(TIM_TypeDef *TIMx, uint16_t TIM_TIxExternalCLKSource,
                                uint16_t TIM_ICPolarity, uint16_t ICFilter)
{
    if(TIM_TIxExternalCLKSource == TIM_TIxExternalCLK1Source_TI2)
    {
        TI2_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
    }
    else
    {
        TI1_Config(TIMx, TIM_ICPolarity, TIM_ICSelection_DirectTI, ICFilter);
    }

    TIM_SelectInputTrigger(TIMx, TIM_TIxExternalCLKSource);
    TIMx->SMCFGR |= TIM_SlaveMode_External1;
}

void TIM_ETRClockMode1Config(TIM_TypeDef *TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                             uint16_t ExtTRGFilter)
{
    uint16_t tmpsmcr = 0;

    TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);
    tmpsmcr = TIMx->SMCFGR;
    tmpsmcr &= (uint16_t)(~((uint16_t)TIM_SMS));
    tmpsmcr |= TIM_SlaveMode_External1;
    tmpsmcr &= (uint16_t)(~((uint16_t)TIM_TS));
    tmpsmcr |= TIM_TS_ETRF;
    TIMx->SMCFGR = tmpsmcr;
}

void TIM_ETRClockMode2Config(TIM_TypeDef *TIMx, uint16_t TIM_ExtTRGPrescaler,
                             uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter)
{
    TIM_ETRConfig(TIMx, TIM_ExtTRGPrescaler, TIM_ExtTRGPolarity, ExtTRGFilter);
    TIMx->SMCFGR |= TIM_ECE;
}

void TIM_ETRConfig(TIM_TypeDef *TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,
                   uint16_t ExtTRGFilter)
{
    uint16_t tmpsmcr = 0;

    tmpsmcr = TIMx->SMCFGR;
    tmpsmcr &= SMCFGR_ETR_Mask;
    tmpsmcr |= (uint16_t)(TIM_ExtTRGPrescaler | (uint16_t)(TIM_ExtTRGPolarity | (uint16_t)(ExtTRGFilter << (uint16_t)8)));
    TIMx->SMCFGR = tmpsmcr;
}

void TIM_PrescalerConfig(TIM_TypeDef *TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode)
{
    TIMx->PSC = Prescaler;
    TIMx->SWEVGR = TIM_PSCReloadMode;
}

void TIM_CounterModeConfig(TIM_TypeDef *TIMx, uint16_t TIM_CounterMode)
{
    uint16_t tmpcr1 = 0;

    tmpcr1 = TIMx->CTLR1;
    tmpcr1 &= (uint16_t)(~((uint16_t)(TIM_DIR | TIM_CMS)));
    tmpcr1 |= TIM_CounterMode;
    TIMx->CTLR1 = tmpcr1;
}

void TIM_SelectInputTrigger(TIM_TypeDef *TIMx, uint16_t TIM_InputTriggerSource)
{
    uint16_t tmpsmcr = 0;

    tmpsmcr = TIMx->SMCFGR;
    tmpsmcr &= (uint16_t)(~((uint16_t)TIM_TS));
    tmpsmcr |= TIM_InputTriggerSource;
    TIMx->SMCFGR = tmpsmcr;
}

void TIM_EncoderInterfaceConfig(TIM_TypeDef *TIMx, uint16_t TIM_EncoderMode,
                                uint16_t TIM_IC1Polarity, uint16_t TIM_IC2Polarity)
{
    uint16_t tmpsmcr = 0;
    uint16_t tmpccmr1 = 0;
    uint16_t tmpccer = 0;

    tmpsmcr = TIMx->SMCFGR;
    tmpccmr1 = TIMx->CHCTLR1;
    tmpccer = TIMx->CCER;
    tmpsmcr &= (uint16_t)(~((uint16_t)TIM_SMS));
    tmpsmcr |= TIM_EncoderMode;
    tmpccmr1 &= (uint16_t)(((uint16_t) ~((uint16_t)TIM_CC1S)) & (uint16_t)(~((uint16_t)TIM_CC2S)));
    tmpccmr1 |= TIM_CC1S_0 | TIM_CC2S_0;
    tmpccer &= (uint16_t)(((uint16_t) ~((uint16_t)TIM_CC1P)) & ((uint16_t) ~((uint16_t)TIM_CC2P)));
    tmpccer |= (uint16_t)(TIM_IC1Polarity | (uint16_t)(TIM_IC2Polarity << (uint16_t)4));
    TIMx->SMCFGR = tmpsmcr;
    TIMx->CHCTLR1 = tmpccmr1;
    TIMx->CCER = tmpccer;
}

void TIM_ForcedOC1Config(TIM_TypeDef *TIMx, uint16_t TIM_ForcedAction)
{
    uint16_t tmpccmr1 = 0;

    tmpccmr1 = TIMx->CHCTLR1;
    tmpccmr1 &= (uint16_t) ~((uint16_t)TIM_OC1M);
    tmpccmr1 |= TIM_ForcedAction;
    TIMx->CHCTLR1 = tmpccmr1;
}

void TIM_ForcedOC2Config(TIM_TypeDef *TIMx, uint16_t TIM_ForcedAction)
{
    uint16_t tmpccmr1 = 0;

    tmpccmr1 = TIMx->CHCTLR1;
    tmpccmr1 &= (uint16_t) ~((uint16_t)TIM_OC2M);
    tmpccmr1 |= (uint16_t)(TIM_ForcedAction << 8);
    TIMx->CHCTLR1 = tmpccmr1;
}

void TIM_ForcedOC3Config(TIM_TypeDef *TIMx, uint16_t TIM_ForcedAction)
{
    uint16_t tmpccmr2 = 0;

    tmpccmr2 = TIMx->CHCTLR2;
    tmpccmr2 &= (uint16_t) ~((uint16_t)TIM_OC3M);
    tmpccmr2 |= TIM_ForcedAction;
    TIMx->CHCTLR2 = tmpccmr2;
}

void TIM_ForcedOC4Config(TIM_TypeDef *TIMx, uint16_t TIM_ForcedAction)
{
    uint16_t tmpccmr2 = 0;

    tmpccmr2 = TIMx->CHCTLR2;
    tmpccmr2 &= (uint16_t) ~((uint16_t)TIM_OC4M);
    tmpccmr2 |= (uint16_t)(TIM_ForcedAction << 8);
    TIMx->CHCTLR2 = tmpccmr2;
}

void TIM_ARRPreloadConfig(TIM_TypeDef *TIMx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        TIMx->CTLR1 |= TIM_ARPE;
    }
    else
    {
        TIMx->CTLR1 &= (uint16_t) ~((uint16_t)TIM_ARPE);
    }
}

void TIM_SelectCOM(TIM_TypeDef *TIMx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        TIMx->CTLR2 |= TIM_CCUS;
    }
    else
    {
        TIMx->CTLR2 &= (uint16_t) ~((uint16_t)TIM_CCUS);
    }
}

void TIM_SelectCCDMA(TIM_TypeDef *TIMx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        TIMx->CTLR2 |= TIM_CCDS;
    }
    else
    {
        TIMx->CTLR2 &= (uint16_t) ~((uint16_t)TIM_CCDS);
    }
}

void TIM_CCPreloadControl(TIM_TypeDef *TIMx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        TIMx->CTLR2 |= TIM_CCPC;
    }
    else
    {
        TIMx->CTLR2 &= (uint16_t) ~((uint16_t)TIM_CCPC);
    }
}

void TIM_OC1PreloadConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPreload)
{
    uint16_t tmpccmr1 = 0;

    tmpccmr1 = TIMx->CHCTLR1;
    tmpccmr1 &= (uint16_t) ~((uint16_t)TIM_OC1PE);
    tmpccmr1 |= TIM_OCPreload;
    TIMx->CHCTLR1 = tmpccmr1;
}

void TIM_OC2PreloadConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPreload)
{
    uint16_t tmpccmr1 = 0;

    tmpccmr1 = TIMx->CHCTLR1;
    tmpccmr1 &= (uint16_t) ~((uint16_t)TIM_OC2PE);
    tmpccmr1 |= (uint16_t)(TIM_OCPreload << 8);
    TIMx->CHCTLR1 = tmpccmr1;
}

void TIM_OC3PreloadConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPreload)
{
    uint16_t tmpccmr2 = 0;

    tmpccmr2 = TIMx->CHCTLR2;
    tmpccmr2 &= (uint16_t) ~((uint16_t)TIM_OC3PE);
    tmpccmr2 |= TIM_OCPreload;
    TIMx->CHCTLR2 = tmpccmr2;
}

void TIM_OC4PreloadConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPreload)
{
    uint16_t tmpccmr2 = 0;

    tmpccmr2 = TIMx->CHCTLR2;
    tmpccmr2 &= (uint16_t) ~((uint16_t)TIM_OC4PE);
    tmpccmr2 |= (uint16_t)(TIM_OCPreload << 8);
    TIMx->CHCTLR2 = tmpccmr2;
}

void TIM_OC1FastConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCFast)
{
    uint16_t tmpccmr1 = 0;

    tmpccmr1 = TIMx->CHCTLR1;
    tmpccmr1 &= (uint16_t) ~((uint16_t)TIM_OC1FE);
    tmpccmr1 |= TIM_OCFast;
    TIMx->CHCTLR1 = tmpccmr1;
}

void TIM_OC2FastConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCFast)
{
    uint16_t tmpccmr1 = 0;

    tmpccmr1 = TIMx->CHCTLR1;
    tmpccmr1 &= (uint16_t) ~((uint16_t)TIM_OC2FE);
    tmpccmr1 |= (uint16_t)(TIM_OCFast << 8);
    TIMx->CHCTLR1 = tmpccmr1;
}

void TIM_OC3FastConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCFast)
{
    uint16_t tmpccmr2 = 0;

    tmpccmr2 = TIMx->CHCTLR2;
    tmpccmr2 &= (uint16_t) ~((uint16_t)TIM_OC3FE);
    tmpccmr2 |= TIM_OCFast;
    TIMx->CHCTLR2 = tmpccmr2;
}

void TIM_OC4FastConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCFast)
{
    uint16_t tmpccmr2 = 0;

    tmpccmr2 = TIMx->CHCTLR2;
    tmpccmr2 &= (uint16_t) ~((uint16_t)TIM_OC4FE);
    tmpccmr2 |= (uint16_t)(TIM_OCFast << 8);
    TIMx->CHCTLR2 = tmpccmr2;
}

void TIM_ClearOC1Ref(TIM_TypeDef *TIMx, uint16_t TIM_OCClear)
{
    uint16_t tmpccmr1 = 0;

    tmpccmr1 = TIMx->CHCTLR1;
    tmpccmr1 &= (uint16_t) ~((uint16_t)TIM_OC1CE);
    tmpccmr1 |= TIM_OCClear;
    TIMx->CHCTLR1 = tmpccmr1;
}

void TIM_ClearOC2Ref(TIM_TypeDef *TIMx, uint16_t TIM_OCClear)
{
    uint16_t tmpccmr1 = 0;

    tmpccmr1 = TIMx->CHCTLR1;
    tmpccmr1 &= (uint16_t) ~((uint16_t)TIM_OC2CE);
    tmpccmr1 |= (uint16_t)(TIM_OCClear << 8);
    TIMx->CHCTLR1 = tmpccmr1;
}

void TIM_ClearOC3Ref(TIM_TypeDef *TIMx, uint16_t TIM_OCClear)
{
    uint16_t tmpccmr2 = 0;

    tmpccmr2 = TIMx->CHCTLR2;
    tmpccmr2 &= (uint16_t) ~((uint16_t)TIM_OC3CE);
    tmpccmr2 |= TIM_OCClear;
    TIMx->CHCTLR2 = tmpccmr2;
}

void TIM_ClearOC4Ref(TIM_TypeDef *TIMx, uint16_t TIM_OCClear)
{
    uint16_t tmpccmr2 = 0;

    tmpccmr2 = TIMx->CHCTLR2;
    tmpccmr2 &= (uint16_t) ~((uint16_t)TIM_OC4CE);
    tmpccmr2 |= (uint16_t)(TIM_OCClear << 8);
    TIMx->CHCTLR2 = tmpccmr2;
}

void TIM_OC1PolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPolarity)
{
    uint16_t tmpccer = 0;

    tmpccer = TIMx->CCER;
    tmpccer &= (uint16_t) ~((uint16_t)TIM_CC1P);
    tmpccer |= TIM_OCPolarity;
    TIMx->CCER = tmpccer;
}

void TIM_OC1NPolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCNPolarity)
{
    uint16_t tmpccer = 0;

    tmpccer = TIMx->CCER;
    tmpccer &= (uint16_t) ~((uint16_t)TIM_CC1NP);
    tmpccer |= TIM_OCNPolarity;
    TIMx->CCER = tmpccer;
}

void TIM_OC2PolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPolarity)
{
    uint16_t tmpccer = 0;

    tmpccer = TIMx->CCER;
    tmpccer &= (uint16_t) ~((uint16_t)TIM_CC2P);
    tmpccer |= (uint16_t)(TIM_OCPolarity << 4);
    TIMx->CCER = tmpccer;
}

void TIM_OC2NPolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCNPolarity)
{
    uint16_t tmpccer = 0;

    tmpccer = TIMx->CCER;
    tmpccer &= (uint16_t) ~((uint16_t)TIM_CC2NP);
    tmpccer |= (uint16_t)(TIM_OCNPolarity << 4);
    TIMx->CCER = tmpccer;
}

void TIM_OC3PolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPolarity)
{
    uint16_t tmpccer = 0;

    tmpccer = TIMx->CCER;
    tmpccer &= (uint16_t) ~((uint16_t)TIM_CC3P);
    tmpccer |= (uint16_t)(TIM_OCPolarity << 8);
    TIMx->CCER = tmpccer;
}

void TIM_OC3NPolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCNPolarity)
{
    uint16_t tmpccer = 0;

    tmpccer = TIMx->CCER;
    tmpccer &= (uint16_t) ~((uint16_t)TIM_CC3NP);
    tmpccer |= (uint16_t)(TIM_OCNPolarity << 8);
    TIMx->CCER = tmpccer;
}

void TIM_OC4PolarityConfig(TIM_TypeDef *TIMx, uint16_t TIM_OCPolarity)
{
    uint16_t tmpccer = 0;

    tmpccer = TIMx->CCER;
    tmpccer &= (uint16_t) ~((uint16_t)TIM_CC4P);
    tmpccer |= (uint16_t)(TIM_OCPolarity << 12);
    TIMx->CCER = tmpccer;
}

void TIM_CCxCmd(TIM_TypeDef *TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx)
{
    uint16_t tmp = 0;

    tmp = CCER_CCE_Set << TIM_Channel;
    TIMx->CCER &= (uint16_t)~tmp;
    TIMx->CCER |= (uint16_t)(TIM_CCx << TIM_Channel);
}

void TIM_CCxNCmd(TIM_TypeDef *TIMx, uint16_t TIM_Channel, uint16_t TIM_CCxN)
{
    uint16_t tmp = 0;

    tmp = CCER_CCNE_Set << TIM_Channel;
    TIMx->CCER &= (uint16_t)~tmp;
    TIMx->CCER |= (uint16_t)(TIM_CCxN << TIM_Channel);
}

void TIM_SelectOCxM(TIM_TypeDef *TIMx, uint16_t TIM_Channel, uint16_t TIM_OCMode)
{
    uint32_t tmp = 0;
    uint16_t tmp1 = 0;

    tmp = (uint32_t)TIMx;
    tmp += CHCTLR_Offset;
    tmp1 = CCER_CCE_Set << (uint16_t)TIM_Channel;
    TIMx->CCER &= (uint16_t)~tmp1;

    if((TIM_Channel == TIM_Channel_1) || (TIM_Channel == TIM_Channel_3))
    {
        tmp += (TIM_Channel >> 1);
        *(__IO uint32_t *)tmp &= (uint32_t) ~((uint32_t)TIM_OC1M);
        *(__IO uint32_t *)tmp |= TIM_OCMode;
    }
    else
    {
        tmp += (uint16_t)(TIM_Channel - (uint16_t)4) >> (uint16_t)1;
        *(__IO uint32_t *)tmp &= (uint32_t) ~((uint32_t)TIM_OC2M);
        *(__IO uint32_t *)tmp |= (uint16_t)(TIM_OCMode << 8);
    }
}

void TIM_UpdateDisableConfig(TIM_TypeDef *TIMx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        TIMx->CTLR1 |= TIM_UDIS;
    }
    else
    {
        TIMx->CTLR1 &= (uint16_t) ~((uint16_t)TIM_UDIS);
    }
}

void TIM_UpdateRequestConfig(TIM_TypeDef *TIMx, uint16_t TIM_UpdateSource)
{
    if(TIM_UpdateSource != TIM_UpdateSource_Global)
    {
        TIMx->CTLR1 |= TIM_URS;
    }
    else
    {
        TIMx->CTLR1 &= (uint16_t) ~((uint16_t)TIM_URS);
    }
}

void TIM_SelectHallSensor(TIM_TypeDef *TIMx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        TIMx->CTLR2 |= TIM_TI1S;
    }
    else
    {
        TIMx->CTLR2 &= (uint16_t) ~((uint16_t)TIM_TI1S);
    }
}

void TIM_SelectOnePulseMode(TIM_TypeDef *TIMx, uint16_t TIM_OPMode)
{
    TIMx->CTLR1 &= (uint16_t) ~((uint16_t)TIM_OPM);
    TIMx->CTLR1 |= TIM_OPMode;
}

void TIM_SelectOutputTrigger(TIM_TypeDef *TIMx, uint16_t TIM_TRGOSource)
{
    TIMx->CTLR2 &= (uint16_t) ~((uint16_t)TIM_MMS);
    TIMx->CTLR2 |= TIM_TRGOSource;
}

void TIM_SelectSlaveMode(TIM_TypeDef *TIMx, uint16_t TIM_SlaveMode)
{
    TIMx->SMCFGR &= (uint16_t) ~((uint16_t)TIM_SMS);
    TIMx->SMCFGR |= TIM_SlaveMode;
}

void TIM_SelectMasterSlaveMode(TIM_TypeDef *TIMx, uint16_t TIM_MasterSlaveMode)
{
    TIMx->SMCFGR &= (uint16_t) ~((uint16_t)TIM_MSM);
    TIMx->SMCFGR |= TIM_MasterSlaveMode;
}

void TIM_SetCounter(TIM_TypeDef *TIMx, uint16_t Counter)
{
    TIMx->CNT = Counter;
}

void TIM_SetAutoreload(TIM_TypeDef *TIMx, uint16_t Autoreload)
{
    TIMx->ATRLR = Autoreload;
}

void TIM_SetCompare1(TIM_TypeDef *TIMx, uint16_t Compare1)
{
    TIMx->CH1CVR = Compare1;
}

void TIM_SetCompare2(TIM_TypeDef *TIMx, uint16_t Compare2)
{
    TIMx->CH2CVR = Compare2;
}

void TIM_SetCompare3(TIM_TypeDef *TIMx, uint16_t Compare3)
{
    TIMx->CH3CVR = Compare3;
}

void TIM_SetCompare4(TIM_TypeDef *TIMx, uint16_t Compare4)
{
    TIMx->CH4CVR = Compare4;
}

void TIM_SetIC1Prescaler(TIM_TypeDef *TIMx, uint16_t TIM_ICPSC)
{
    TIMx->CHCTLR1 &= (uint16_t) ~((uint16_t)TIM_IC1PSC);
    TIMx->CHCTLR1 |= TIM_ICPSC;
}

void TIM_SetIC2Prescaler(TIM_TypeDef *TIMx, uint16_t TIM_ICPSC)
{
    TIMx->CHCTLR1 &= (uint16_t) ~((uint16_t)TIM_IC2PSC);
    TIMx->CHCTLR1 |= (uint16_t)(TIM_ICPSC << 8);
}

void TIM_SetIC3Prescaler(TIM_TypeDef *TIMx, uint16_t TIM_ICPSC)
{
    TIMx->CHCTLR2 &= (uint16_t) ~((uint16_t)TIM_IC3PSC);
    TIMx->CHCTLR2 |= TIM_ICPSC;
}

void TIM_SetIC4Prescaler(TIM_TypeDef *TIMx, uint16_t TIM_ICPSC)
{
    TIMx->CHCTLR2 &= (uint16_t) ~((uint16_t)TIM_IC4PSC);
    TIMx->CHCTLR2 |= (uint16_t)(TIM_ICPSC << 8);
}

void TIM_SetClockDivision(TIM_TypeDef *TIMx, uint16_t TIM_CKD)
{
    TIMx->CTLR1 &= (uint16_t) ~((uint16_t)TIM_CTLR1_CKD);
    TIMx->CTLR1 |= TIM_CKD;
}

uint16_t TIM_GetCapture1(TIM_TypeDef *TIMx)
{
    return TIMx->CH1CVR;
}

uint16_t TIM_GetCapture2(TIM_TypeDef *TIMx)
{
    return TIMx->CH2CVR;
}

uint16_t TIM_GetCapture3(TIM_TypeDef *TIMx)
{
    return TIMx->CH3CVR;
}

uint16_t TIM_GetCapture4(TIM_TypeDef *TIMx)
{
    return TIMx->CH4CVR;
}

uint16_t TIM_GetCounter(TIM_TypeDef *TIMx)
{
    return TIMx->CNT;
}

uint16_t TIM_GetPrescaler(TIM_TypeDef *TIMx)
{
    return TIMx->PSC;
}

FlagStatus TIM_GetFlagStatus(TIM_TypeDef *TIMx, uint16_t TIM_FLAG)
{
    ITStatus bitstatus = RESET;

    if((TIMx->INTFR & TIM_FLAG) != (uint16_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

void TIM_ClearFlag(TIM_TypeDef *TIMx, uint16_t TIM_FLAG)
{
    TIMx->INTFR = (uint16_t)~TIM_FLAG;
}

ITStatus TIM_GetITStatus(TIM_TypeDef *TIMx, uint16_t TIM_IT)
{
    ITStatus bitstatus = RESET;
    uint16_t itstatus = 0x0, itenable = 0x0;

    itstatus = TIMx->INTFR & TIM_IT;

    itenable = TIMx->DMAINTENR & TIM_IT;
    if((itstatus != (uint16_t)RESET) && (itenable != (uint16_t)RESET))
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

void TIM_ClearITPendingBit(TIM_TypeDef *TIMx, uint16_t TIM_IT)
{
    TIMx->INTFR = (uint16_t)~TIM_IT;
}

static void TI1_Config(TIM_TypeDef *TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection, uint16_t TIM_ICFilter)
{
    uint16_t tmpccmr1 = 0, tmpccer = 0;

    TIMx->CCER &= (uint16_t) ~((uint16_t)TIM_CC1E);
    tmpccmr1 = TIMx->CHCTLR1;
    tmpccer = TIMx->CCER;
    tmpccmr1 &= (uint16_t)(((uint16_t) ~((uint16_t)TIM_CC1S)) & ((uint16_t) ~((uint16_t)TIM_IC1F)));

    TIMx->CHCTLR1 |= (uint16_t)(TIM_ICSelection);
    tmpccmr1 |= (uint16_t)(TIM_ICSelection | (uint16_t)(TIM_ICFilter << (uint16_t)4));

    if((TIMx == TIM1) || (TIMx == TIM2))
    {
        tmpccer &= (uint16_t) ~((uint16_t)(TIM_CC1P));
        tmpccer |= (uint16_t)(TIM_ICPolarity | (uint16_t)TIM_CC1E);
    }
    else
    {
        tmpccer &= (uint16_t) ~((uint16_t)(TIM_CC1P | TIM_CC1NP));
        tmpccer |= (uint16_t)(TIM_ICPolarity | (uint16_t)TIM_CC1E);
    }

    TIMx->CHCTLR1 = tmpccmr1;
    TIMx->CCER = tmpccer;
}

static void TI2_Config(TIM_TypeDef *TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection, uint16_t TIM_ICFilter)
{
    uint16_t tmpccmr1 = 0, tmpccer = 0, tmp = 0;

    TIMx->CCER &= (uint16_t) ~((uint16_t)TIM_CC2E);
    tmpccmr1 = TIMx->CHCTLR1;
    tmpccer = TIMx->CCER;
    tmp = (uint16_t)(TIM_ICPolarity << 4);
    tmpccmr1 &= (uint16_t)(((uint16_t) ~((uint16_t)TIM_CC2S)) & ((uint16_t) ~((uint16_t)TIM_IC2F)));

    TIMx->CHCTLR1 |= (uint16_t)(TIM_ICSelection << 8);
    tmpccmr1 |= (uint16_t)(TIM_ICSelection << 8) | (uint16_t)(TIM_ICFilter << 12);

    if((TIMx == TIM1) || (TIMx == TIM2))
    {
        tmpccer &= (uint16_t) ~((uint16_t)(TIM_CC2P));
        tmpccer |= (uint16_t)(tmp | (uint16_t)TIM_CC2E);
    }
    else
    {
        tmpccer &= (uint16_t) ~((uint16_t)(TIM_CC2P | TIM_CC2NP));
        tmpccer |= (uint16_t)(TIM_ICPolarity | (uint16_t)TIM_CC2E);
    }

    TIMx->CHCTLR1 = tmpccmr1;
    TIMx->CCER = tmpccer;
}

static void TI3_Config(TIM_TypeDef *TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection, uint16_t TIM_ICFilter)
{
    uint16_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;

    TIMx->CCER &= (uint16_t) ~((uint16_t)TIM_CC3E);
    tmpccmr2 = TIMx->CHCTLR2;
    tmpccer = TIMx->CCER;
    tmp = (uint16_t)(TIM_ICPolarity << 8);
    tmpccmr2 &= (uint16_t)(((uint16_t) ~((uint16_t)TIM_CC3S)) & ((uint16_t) ~((uint16_t)TIM_IC3F)));

    TIMx->CHCTLR2 |= (uint16_t)(TIM_ICSelection);
    tmpccmr2 |= (uint16_t)(TIM_ICSelection | (uint16_t)(TIM_ICFilter << (uint16_t)4));

    if((TIMx == TIM1) || (TIMx == TIM2))
    {
        tmpccer &= (uint16_t) ~((uint16_t)(TIM_CC3P));
        tmpccer |= (uint16_t)(tmp | (uint16_t)TIM_CC3E);
    }
    else
    {
        tmpccer &= (uint16_t) ~((uint16_t)(TIM_CC3P | TIM_CC3NP));
        tmpccer |= (uint16_t)(TIM_ICPolarity | (uint16_t)TIM_CC3E);
    }

    TIMx->CHCTLR2 = tmpccmr2;
    TIMx->CCER = tmpccer;
}

static void TI4_Config(TIM_TypeDef *TIMx, uint16_t TIM_ICPolarity, uint16_t TIM_ICSelection, uint16_t TIM_ICFilter)
{
    uint16_t tmpccmr2 = 0, tmpccer = 0, tmp = 0;

    TIMx->CCER &= (uint16_t) ~((uint16_t)TIM_CC4E);
    tmpccmr2 = TIMx->CHCTLR2;
    tmpccer = TIMx->CCER;
    tmp = (uint16_t)(TIM_ICPolarity << 12);
    tmpccmr2 &= (uint16_t)((uint16_t)(~(uint16_t)TIM_CC4S) & ((uint16_t) ~((uint16_t)TIM_IC4F)));

    TIMx->CHCTLR2 |= (uint16_t)(TIM_ICSelection << 8);
    tmpccmr2 |= (uint16_t)(TIM_ICSelection << 8) | (uint16_t)(TIM_ICFilter << 12);

    if((TIMx == TIM1) || (TIMx == TIM2))
    {
        tmpccer &= (uint16_t) ~((uint16_t)(TIM_CC4P));
        tmpccer |= (uint16_t)(tmp | (uint16_t)TIM_CC4E);
    }
    else
    {
        tmpccer &= (uint16_t) ~((uint16_t)(TIM_CC3P | TIM_CC4NP));
        tmpccer |= (uint16_t)(TIM_ICPolarity | (uint16_t)TIM_CC4E);
    }

    TIMx->CHCTLR2 = tmpccmr2;
    TIMx->CCER = tmpccer;
}
