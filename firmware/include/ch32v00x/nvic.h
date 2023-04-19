#ifndef __NVIC_RISCV_H__
#define __NVIC_RISCV_H__

#include <ch32v00x/core.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Interrupt Number Definition, according to the selected device
 */
typedef enum IRQn
{
    /******  RISC-V Processor Exceptions Numbers *******************************************************/
    NonMaskableInt_IRQn = 2, /* 2 Non Maskable Interrupt                             */
    EXC_IRQn = 3,            /* 3 Exception Interrupt                                */
    SysTicK_IRQn = 12,       /* 12 System timer Interrupt                            */
    Software_IRQn = 14,      /* 14 software Interrupt                                */

    /******  RISC-V specific Interrupt Numbers *********************************************************/
    WWDG_IRQn = 16,          /* Window WatchDog Interrupt                            */
    PVD_IRQn = 17,           /* PVD through EXTI Line detection Interrupt            */
    FLASH_IRQn = 18,         /* FLASH global Interrupt                               */
    RCC_IRQn = 19,           /* RCC global Interrupt                                 */
    EXTI7_0_IRQn = 20,       /* External Line[7:0] Interrupts                        */
    AWU_IRQn = 21,           /* AWU global Interrupt                                 */
    DMA1_Channel1_IRQn = 22, /* DMA1 Channel 1 global Interrupt                      */
    DMA1_Channel2_IRQn = 23, /* DMA1 Channel 2 global Interrupt                      */
    DMA1_Channel3_IRQn = 24, /* DMA1 Channel 3 global Interrupt                      */
    DMA1_Channel4_IRQn = 25, /* DMA1 Channel 4 global Interrupt                      */
    DMA1_Channel5_IRQn = 26, /* DMA1 Channel 5 global Interrupt                      */
    DMA1_Channel6_IRQn = 27, /* DMA1 Channel 6 global Interrupt                      */
    DMA1_Channel7_IRQn = 28, /* DMA1 Channel 7 global Interrupt                      */
    ADC_IRQn = 29,           /* ADC global Interrupt                                 */
    I2C1_EV_IRQn = 30,       /* I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn = 31,       /* I2C1 Error Interrupt                                 */
    USART1_IRQn = 32,        /* USART1 global Interrupt                              */
    SPI1_IRQn = 33,          /* SPI1 global Interrupt                                */
    TIM1_BRK_IRQn = 34,      /* TIM1 Break Interrupt                                 */
    TIM1_UP_IRQn = 35,       /* TIM1 Update Interrupt                                */
    TIM1_TRG_COM_IRQn = 36,  /* TIM1 Trigger and Commutation Interrupt               */
    TIM1_CC_IRQn = 37,       /* TIM1 Capture Compare Interrupt                       */
    TIM2_IRQn = 38,          /* TIM2 global Interrupt                                */
} IRQn_Type;

typedef struct {
  uint8_t NVIC_IRQChannel;
  uint8_t NVIC_IRQChannelPreemptionPriority;
  uint8_t NVIC_IRQChannelSubPriority;
  FunctionalState NVIC_IRQChannelCmd;
} NVIC_InitTypeDef;

#define NVIC_PriorityGroup_0           ((uint32_t)0x00)
#define NVIC_PriorityGroup_1           ((uint32_t)0x01)
#define NVIC_PriorityGroup_2           ((uint32_t)0x02)
#define NVIC_PriorityGroup_3           ((uint32_t)0x03)
#define NVIC_PriorityGroup_4           ((uint32_t)0x04)

/**
 * Configures the priority grouping - pre-emption priority and subpriority.
 *
 * @param NVIC_PriorityGroup specifies the priority grouping bits length.
 * NVIC_PriorityGroup_0 - 0 bits for pre-emption priority
 *                        4 bits for subpriority
 * NVIC_PriorityGroup_1 - 1 bits for pre-emption priority
 *                        3 bits for subpriority
 * NVIC_PriorityGroup_2 - 2 bits for pre-emption priority
 *                        2 bits for subpriority
 * NVIC_PriorityGroup_3 - 3 bits for pre-emption priority
 *                        1 bits for subpriority
 * NVIC_PriorityGroup_4 - 4 bits for pre-emption priority
 *                        0 bits for subpriority
 */
void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);

/**
 * Initializes the NVIC peripheral according to the specified parameters in
 * the NVIC_InitStruct.
 *
 * @param NVIC_InitStruct pointer to a NVIC_InitTypeDef structure that contains
 * the configuration information for the specified NVIC peripheral.
 */
void NVIC_Init(NVIC_InitTypeDef* NVIC_InitStruct);

/**
 * Disable Interrupt
 *
 * @param IRQn Interrupt Numbers
 */
RV_STATIC_INLINE void NVIC_EnableIRQ(IRQn_Type IRQn) {
    NVIC->IENR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

/**
 * Disable Interrupt
 *
 * @param IRQn Interrupt Numbers
 */
RV_STATIC_INLINE void NVIC_DisableIRQ(IRQn_Type IRQn) {
    NVIC->IRER[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

/**
 * Get Interrupt Enable State
 *
 * @param IRQn Interrupt Numbers
 *
 * @return either 1 (Interrupt Pending Enable) or 0 (Interrupt Pending Disable)
 */
RV_STATIC_INLINE uint32_t NVIC_GetStatusIRQ(IRQn_Type IRQn) {
    return ((uint32_t)((NVIC->ISR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));
}

/**
 * Get Interrupt Pending State
 *
 * @param IRQn Interrupt Numbers
 *
 * @return either 1 (Interrupt Pending Enable) or 0 (Interrupt Pending Disable)
 */
RV_STATIC_INLINE uint32_t NVIC_GetPendingIRQ(IRQn_Type IRQn) {
    return ((uint32_t)((NVIC->IPR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));
}

/**
 * Set Interrupt Pending
 *
 * @param IRQn Interrupt Numbers
 */
RV_STATIC_INLINE void NVIC_SetPendingIRQ(IRQn_Type IRQn) {
    NVIC->IPSR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

/**
 * Clear Interrupt Pending
 *
 * @param IRQn Interrupt Numbers
 */
RV_STATIC_INLINE void NVIC_ClearPendingIRQ(IRQn_Type IRQn) {
    NVIC->IPRR[((uint32_t)(IRQn) >> 5)] = (1 << ((uint32_t)(IRQn) & 0x1F));
}

/**
 * Get Interrupt Active State
 *
 * @param IRQn Interrupt Numbers
 *
 * @return either 1 (Interrupt Active) or 0 (Interrupt No Active)
 */
RV_STATIC_INLINE uint32_t NVIC_GetActive(IRQn_Type IRQn) {
    return((uint32_t)((NVIC->IACTR[(uint32_t)(IRQn) >> 5] & (1 << ((uint32_t)(IRQn) & 0x1F)))?1:0));
}

/**
 * Set Interrupt Priority
 *
 * @param IRQn Interrupt Numbers
 * @param priority bit7 - pre-emption priority
 *                 bit6 - subpriority
 *                 bit[5-0] - reserved
 */
RV_STATIC_INLINE void NVIC_SetPriority(IRQn_Type IRQn, uint8_t priority) {
    NVIC->IPRIOR[(uint32_t)(IRQn)] = priority;
}

/**
 * Set VTF Interrupt
 *
 * @param addr VTF interrupt service function base address.
 * @param IRQn Interrupt Numbers
 * @param num VTF Interrupt Numbers
 * @param NewState DISABLE or ENABLE
 */
RV_STATIC_INLINE void SetVTFIRQ(uint32_t addr, IRQn_Type IRQn, uint8_t num, FunctionalState NewState) {
    if (num > 1) { return; }

    if (NewState != DISABLE) {
        NVIC->VTFIDR[num] = IRQn;
        NVIC->VTFADDR[num] = ((addr&0xFFFFFFFE)|0x1);
    } else {
        NVIC->VTFIDR[num] = IRQn;
        NVIC->VTFADDR[num] = ((addr&0xFFFFFFFE)&(~0x1));
    }
}

/**
 * Initiate a system reset request
 */
RV_STATIC_INLINE void NVIC_SystemReset(void) {
    NVIC->CFGR = NVIC_KEY3|(1<<7);
}


#ifdef __cplusplus
}
#endif

#endif