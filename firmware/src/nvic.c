#include <ch32v00x/nvic.h>

// FIXME I really don't like this interface. Also, this could be inline
static __IO uint32_t NVIC_Priority_Group = 0;
void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup) {
    NVIC_Priority_Group = NVIC_PriorityGroup;
}

void NVIC_Init(NVIC_InitTypeDef *NVIC_InitStruct) {
    uint8_t tmppre = 0;

    switch (NVIC_Priority_Group) {
    case NVIC_PriorityGroup_0:
        NVIC_SetPriority(NVIC_InitStruct->NVIC_IRQChannel, NVIC_InitStruct->NVIC_IRQChannelSubPriority << 4);
        break;
    case NVIC_PriorityGroup_1:
        if(NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority == 1) {
            NVIC_SetPriority(NVIC_InitStruct->NVIC_IRQChannel, (1 << 7) | (NVIC_InitStruct->NVIC_IRQChannelSubPriority << 4));
        } else {
            NVIC_SetPriority(NVIC_InitStruct->NVIC_IRQChannel, (0 << 7) | (NVIC_InitStruct->NVIC_IRQChannelSubPriority << 4));
        }
        break;
    case NVIC_PriorityGroup_2:
        if(NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority <= 1) {
            tmppre = NVIC_InitStruct->NVIC_IRQChannelSubPriority + (4 * NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority);
            NVIC_SetPriority(NVIC_InitStruct->NVIC_IRQChannel, (0 << 7) | (tmppre << 4));
        } else {
            tmppre = NVIC_InitStruct->NVIC_IRQChannelSubPriority + (4 * (NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority - 2));
            NVIC_SetPriority(NVIC_InitStruct->NVIC_IRQChannel, (1 << 7) | (tmppre << 4));
        }
        break;
    case NVIC_PriorityGroup_3:
        if(NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority <= 3) {
            tmppre = NVIC_InitStruct->NVIC_IRQChannelSubPriority + (2 * NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority);
            NVIC_SetPriority(NVIC_InitStruct->NVIC_IRQChannel, (0 << 7) | (tmppre << 4));
        } else {
            tmppre = NVIC_InitStruct->NVIC_IRQChannelSubPriority + (2 * (NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority - 4));
            NVIC_SetPriority(NVIC_InitStruct->NVIC_IRQChannel, (1 << 7) | (tmppre << 4));
        }
        break;
    case NVIC_PriorityGroup_4:
        NVIC_SetPriority(NVIC_InitStruct->NVIC_IRQChannel, NVIC_InitStruct->NVIC_IRQChannelPreemptionPriority << 4);
        break;
    }

    if (NVIC_InitStruct->NVIC_IRQChannelCmd != DISABLE) {
        NVIC_EnableIRQ(NVIC_InitStruct->NVIC_IRQChannel);
    } else {
        NVIC_DisableIRQ(NVIC_InitStruct->NVIC_IRQChannel);
    }
}
