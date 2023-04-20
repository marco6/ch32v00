#include <ch32v00x/gpio.h>
#include <ch32v00x/rcc.h>
#include <ch32v00x/usart.h>

/* USART_Private_Defines */
#define CTLR1_UE_Set              ((uint16_t)0x2000) /* USART Enable Mask */
#define CTLR1_UE_Reset            ((uint16_t)0xDFFF) /* USART Disable Mask */

#define CTLR1_WAKE_Mask           ((uint16_t)0xF7FF) /* USART WakeUp Method Mask */

#define CTLR1_RWU_Set             ((uint16_t)0x0002) /* USART mute mode Enable Mask */
#define CTLR1_RWU_Reset           ((uint16_t)0xFFFD) /* USART mute mode Enable Mask */
#define CTLR1_SBK_Set             ((uint16_t)0x0001) /* USART Break Character send Mask */
#define CTLR1_CLEAR_Mask          ((uint16_t)0xE9F3) /* USART CR1 Mask */
#define CTLR2_Address_Mask        ((uint16_t)0xFFF0) /* USART address Mask */

#define CTLR2_LINEN_Set           ((uint16_t)0x4000) /* USART LIN Enable Mask */
#define CTLR2_LINEN_Reset         ((uint16_t)0xBFFF) /* USART LIN Disable Mask */

#define CTLR2_LBDL_Mask           ((uint16_t)0xFFDF) /* USART LIN Break detection Mask */
#define CTLR2_STOP_CLEAR_Mask     ((uint16_t)0xCFFF) /* USART CR2 STOP Bits Mask */
#define CTLR2_CLOCK_CLEAR_Mask    ((uint16_t)0xF0FF) /* USART CR2 Clock Mask */

#define CTLR3_SCEN_Set            ((uint16_t)0x0020) /* USART SC Enable Mask */
#define CTLR3_SCEN_Reset          ((uint16_t)0xFFDF) /* USART SC Disable Mask */

#define CTLR3_NACK_Set            ((uint16_t)0x0010) /* USART SC NACK Enable Mask */
#define CTLR3_NACK_Reset          ((uint16_t)0xFFEF) /* USART SC NACK Disable Mask */

#define CTLR3_HDSEL_Set           ((uint16_t)0x0008) /* USART Half-Duplex Enable Mask */
#define CTLR3_HDSEL_Reset         ((uint16_t)0xFFF7) /* USART Half-Duplex Disable Mask */

#define CTLR3_IRLP_Mask           ((uint16_t)0xFFFB) /* USART IrDA LowPower mode Mask */
#define CTLR3_CLEAR_Mask          ((uint16_t)0xFCFF) /* USART CR3 Mask */

#define CTLR3_IREN_Set            ((uint16_t)0x0002) /* USART IrDA Enable Mask */
#define CTLR3_IREN_Reset          ((uint16_t)0xFFFD) /* USART IrDA Disable Mask */
#define GPR_LSB_Mask              ((uint16_t)0x00FF) /* Guard Time Register LSB Mask */
#define GPR_MSB_Mask              ((uint16_t)0xFF00) /* Guard Time Register MSB Mask */
#define IT_Mask                   ((uint16_t)0x001F) /* USART Interrupt Mask */

/* USART OverSampling-8 Mask */
#define CTLR1_OVER8_Set           ((uint16_t)0x8000) /* USART OVER8 mode Enable Mask */
#define CTLR1_OVER8_Reset         ((uint16_t)0x7FFF) /* USART OVER8 mode Disable Mask */

/* USART One Bit Sampling Mask */
#define CTLR3_ONEBITE_Set         ((uint16_t)0x0800) /* USART ONEBITE mode Enable Mask */
#define CTLR3_ONEBITE_Reset       ((uint16_t)0xF7FF) /* USART ONEBITE mode Disable Mask */

void USART_DeInit(USART_TypeDef *USARTx) {
    if (USARTx == USART1) {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_USART1, DISABLE);
    }
}

void USART_Init(USART_TypeDef *USARTx, USART_InitTypeDef *USART_InitStruct) {
    uint32_t          tmpreg = 0x00, apbclock = 0x00;
    uint32_t          integerdivider = 0x00;
    uint32_t          fractionaldivider = 0x00;
    uint32_t          usartxbase = 0;
    RCC_ClocksTypeDef RCC_ClocksStatus;

    if (USART_InitStruct->USART_HardwareFlowControl != USART_HardwareFlowControl_None)
    { /* FIXME: ..? What's this about? */ }

    usartxbase = (uint32_t)USARTx;
    tmpreg = USARTx->CTLR2;
    tmpreg &= CTLR2_STOP_CLEAR_Mask;
    tmpreg |= (uint32_t)USART_InitStruct->USART_StopBits;

    USARTx->CTLR2 = (uint16_t)tmpreg;
    tmpreg = USARTx->CTLR1;
    tmpreg &= CTLR1_CLEAR_Mask;
    tmpreg |= (uint32_t)USART_InitStruct->USART_WordLength | USART_InitStruct->USART_Parity |
              USART_InitStruct->USART_Mode;
    USARTx->CTLR1 = (uint16_t)tmpreg;

    tmpreg = USARTx->CTLR3;
    tmpreg &= CTLR3_CLEAR_Mask;
    tmpreg |= USART_InitStruct->USART_HardwareFlowControl;
    USARTx->CTLR3 = (uint16_t)tmpreg;

    RCC_GetClocksFreq(&RCC_ClocksStatus);

    if (usartxbase == USART1_BASE) {
        apbclock = RCC_ClocksStatus.PCLK2_Frequency;
    } else {
        apbclock = RCC_ClocksStatus.PCLK1_Frequency;
    }

    if ((USARTx->CTLR1 & CTLR1_OVER8_Set) != 0) {
        integerdivider = ((25 * apbclock) / (2 * (USART_InitStruct->USART_BaudRate)));
    } else {
        integerdivider = ((25 * apbclock) / (4 * (USART_InitStruct->USART_BaudRate)));
    }
    tmpreg = (integerdivider / 100) << 4;

    fractionaldivider = integerdivider - (100 * (tmpreg >> 4));

    if ((USARTx->CTLR1 & CTLR1_OVER8_Set) != 0) {
        tmpreg |= ((((fractionaldivider * 8) + 50) / 100)) & ((uint8_t)0x07);
    } else {
        tmpreg |= ((((fractionaldivider * 16) + 50) / 100)) & ((uint8_t)0x0F);
    }

    USARTx->BRR = (uint16_t)tmpreg;
}

void USART_StructInit(USART_InitTypeDef *USART_InitStruct) {
    USART_InitStruct->USART_BaudRate = 9600;
    USART_InitStruct->USART_WordLength = USART_WordLength_8b;
    USART_InitStruct->USART_StopBits = USART_StopBits_1;
    USART_InitStruct->USART_Parity = USART_Parity_No;
    USART_InitStruct->USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStruct->USART_HardwareFlowControl = USART_HardwareFlowControl_None;
}

void USART_ClockInit(USART_TypeDef *USARTx, USART_ClockInitTypeDef *USART_ClockInitStruct) {
    uint32_t tmpreg = 0x00;

    tmpreg = USARTx->CTLR2;
    tmpreg &= CTLR2_CLOCK_CLEAR_Mask;
    tmpreg |= (uint32_t)USART_ClockInitStruct->USART_Clock | USART_ClockInitStruct->USART_CPOL |
              USART_ClockInitStruct->USART_CPHA | USART_ClockInitStruct->USART_LastBit;
    USARTx->CTLR2 = (uint16_t)tmpreg;
}

void USART_ClockStructInit(USART_ClockInitTypeDef *USART_ClockInitStruct) {
    USART_ClockInitStruct->USART_Clock = USART_Clock_Disable;
    USART_ClockInitStruct->USART_CPOL = USART_CPOL_Low;
    USART_ClockInitStruct->USART_CPHA = USART_CPHA_1Edge;
    USART_ClockInitStruct->USART_LastBit = USART_LastBit_Disable;
}

void USART_Cmd(USART_TypeDef *USARTx, FunctionalState NewState) {
    if (NewState != DISABLE) {
        USARTx->CTLR1 |= CTLR1_UE_Set;
    } else {
        USARTx->CTLR1 &= CTLR1_UE_Reset;
    }
}

void USART_ITConfig(USART_TypeDef *USARTx, uint16_t USART_IT, FunctionalState NewState) {
    uint32_t usartreg = 0x00, itpos = 0x00, itmask = 0x00;
    uint32_t usartxbase = 0x00;


    usartxbase = (uint32_t)USARTx;
    usartreg = (((uint8_t)USART_IT) >> 0x05);
    itpos = USART_IT & IT_Mask;
    itmask = (((uint32_t)0x01) << itpos);

    if (usartreg == 0x01) {
        usartxbase += 0x0C;
    } else if (usartreg == 0x02) {
        usartxbase += 0x10;
    } else {
        usartxbase += 0x14;
    }

    if (NewState != DISABLE) {
        *(__IO uint32_t *)usartxbase |= itmask;
    } else {
        *(__IO uint32_t *)usartxbase &= ~itmask;
    }
}

void USART_DMACmd(USART_TypeDef *USARTx, uint16_t USART_DMAReq, FunctionalState NewState) {
    if (NewState != DISABLE) {
        USARTx->CTLR3 |= USART_DMAReq;
    } else {
        USARTx->CTLR3 &= (uint16_t)~USART_DMAReq;
    }
}

void USART_SetAddress(USART_TypeDef *USARTx, uint8_t USART_Address) {
    USARTx->CTLR2 &= CTLR2_Address_Mask;
    USARTx->CTLR2 |= USART_Address;
}

void USART_WakeUpConfig(USART_TypeDef *USARTx, uint16_t USART_WakeUp) {
    USARTx->CTLR1 &= CTLR1_WAKE_Mask;
    USARTx->CTLR1 |= USART_WakeUp;
}

void USART_ReceiverWakeUpCmd(USART_TypeDef *USARTx, FunctionalState NewState) {
    if (NewState != DISABLE) {
        USARTx->CTLR1 |= CTLR1_RWU_Set;
    } else {
        USARTx->CTLR1 &= CTLR1_RWU_Reset;
    }
}

void USART_LINBreakDetectLengthConfig(USART_TypeDef *USARTx, uint16_t USART_LINBreakDetectLength) {
    USARTx->CTLR2 &= CTLR2_LBDL_Mask;
    USARTx->CTLR2 |= USART_LINBreakDetectLength;
}

void USART_LINCmd(USART_TypeDef *USARTx, FunctionalState NewState) {
    if (NewState != DISABLE) {
        USARTx->CTLR2 |= CTLR2_LINEN_Set;
    } else {
        USARTx->CTLR2 &= CTLR2_LINEN_Reset;
    }
}

void USART_SendData(USART_TypeDef *USARTx, uint16_t Data) {
    USARTx->DATAR = (Data & (uint16_t)0x01FF);
}

uint16_t USART_ReceiveData(USART_TypeDef *USARTx) {
    return (uint16_t)(USARTx->DATAR & (uint16_t)0x01FF);
}

void USART_SendBreak(USART_TypeDef *USARTx) {
    USARTx->CTLR1 |= CTLR1_SBK_Set;
}

void USART_SetGuardTime(USART_TypeDef *USARTx, uint8_t USART_GuardTime) {
    USARTx->GPR &= GPR_LSB_Mask;
    USARTx->GPR |= (uint16_t)((uint16_t)USART_GuardTime << 0x08);
}

void USART_SetPrescaler(USART_TypeDef *USARTx, uint8_t USART_Prescaler) {
    USARTx->GPR &= GPR_MSB_Mask;
    USARTx->GPR |= USART_Prescaler;
}

void USART_SmartCardCmd(USART_TypeDef *USARTx, FunctionalState NewState) {
    if (NewState != DISABLE) {
        USARTx->CTLR3 |= CTLR3_SCEN_Set;
    } else {
        USARTx->CTLR3 &= CTLR3_SCEN_Reset;
    }
}

void USART_SmartCardNACKCmd(USART_TypeDef *USARTx, FunctionalState NewState) {
    if (NewState != DISABLE) {
        USARTx->CTLR3 |= CTLR3_NACK_Set;
    } else {
        USARTx->CTLR3 &= CTLR3_NACK_Reset;
    }
}

void USART_HalfDuplexCmd(USART_TypeDef *USARTx, FunctionalState NewState) {
    if (NewState != DISABLE) {
        USARTx->CTLR3 |= CTLR3_HDSEL_Set;
    } else {
        USARTx->CTLR3 &= CTLR3_HDSEL_Reset;
    }
}

void USART_OverSampling8Cmd(USART_TypeDef *USARTx, FunctionalState NewState) {
    if (NewState != DISABLE) {
        USARTx->CTLR1 |= CTLR1_OVER8_Set;
    } else {
        USARTx->CTLR1 &= CTLR1_OVER8_Reset;
    }
}

void USART_OneBitMethodCmd(USART_TypeDef *USARTx, FunctionalState NewState) {
    if (NewState != DISABLE) {
        USARTx->CTLR3 |= CTLR3_ONEBITE_Set;
    } else {
        USARTx->CTLR3 &= CTLR3_ONEBITE_Reset;
    }
}

void USART_IrDAConfig(USART_TypeDef *USARTx, uint16_t USART_IrDAMode) {
    USARTx->CTLR3 &= CTLR3_IRLP_Mask;
    USARTx->CTLR3 |= USART_IrDAMode;
}

void USART_IrDACmd(USART_TypeDef *USARTx, FunctionalState NewState) {
    if (NewState != DISABLE) {
        USARTx->CTLR3 |= CTLR3_IREN_Set;
    } else {
        USARTx->CTLR3 &= CTLR3_IREN_Reset;
    }
}

FlagStatus USART_GetFlagStatus(USART_TypeDef *USARTx, uint16_t USART_FLAG) {
    if ((USARTx->STATR & USART_FLAG) != (uint16_t)RESET) {
        return SET;
    } else {
        return RESET;
    }
}

void USART_ClearFlag(USART_TypeDef *USARTx, uint16_t USART_FLAG) {
    USARTx->STATR = (uint16_t)~USART_FLAG;
}

ITStatus USART_GetITStatus(USART_TypeDef *USARTx, uint16_t USART_IT) {
    uint32_t bitpos = 0x00, itmask = 0x00, usartreg = 0x00;
    ITStatus bitstatus = RESET;

    usartreg = (((uint8_t)USART_IT) >> 0x05);
    itmask = USART_IT & IT_Mask;
    itmask = (uint32_t)0x01 << itmask;

    if (usartreg == 0x01) {
        itmask &= USARTx->CTLR1;
    } else if (usartreg == 0x02) {
        itmask &= USARTx->CTLR2;
    } else {
        itmask &= USARTx->CTLR3;
    }

    bitpos = USART_IT >> 0x08;
    bitpos = (uint32_t)0x01 << bitpos;
    bitpos &= USARTx->STATR;

    if ((itmask != (uint16_t)RESET) && (bitpos != (uint16_t)RESET)) {
        bitstatus = SET;
    } else {
        bitstatus = RESET;
    }

    return bitstatus;
}

void USART_ClearITPendingBit(USART_TypeDef *USARTx, uint16_t USART_IT) {
    uint16_t bitpos = 0x00, itmask = 0x00;

    bitpos = USART_IT >> 0x08;
    itmask = ((uint16_t)0x01 << (uint16_t)bitpos);
    USARTx->STATR = (uint16_t)~itmask;
}

void USART_Printf_Init(uint32_t baudrate) {
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = baudrate;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
}