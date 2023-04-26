#include <ch32v00x/dma.h>
#include <ch32v00x/rcc.h>

/* DMA1 Channelx interrupt pending bit masks */
#define DMA1_Channel1_IT_Mask    ((uint32_t)(DMA_GIF1 | DMA_TCIF1 | DMA_HTIF1 | DMA_TEIF1))
#define DMA1_Channel2_IT_Mask    ((uint32_t)(DMA_GIF2 | DMA_TCIF2 | DMA_HTIF2 | DMA_TEIF2))
#define DMA1_Channel3_IT_Mask    ((uint32_t)(DMA_GIF3 | DMA_TCIF3 | DMA_HTIF3 | DMA_TEIF3))
#define DMA1_Channel4_IT_Mask    ((uint32_t)(DMA_GIF4 | DMA_TCIF4 | DMA_HTIF4 | DMA_TEIF4))
#define DMA1_Channel5_IT_Mask    ((uint32_t)(DMA_GIF5 | DMA_TCIF5 | DMA_HTIF5 | DMA_TEIF5))
#define DMA1_Channel6_IT_Mask    ((uint32_t)(DMA_GIF6 | DMA_TCIF6 | DMA_HTIF6 | DMA_TEIF6))
#define DMA1_Channel7_IT_Mask    ((uint32_t)(DMA_GIF7 | DMA_TCIF7 | DMA_HTIF7 | DMA_TEIF7))

/* DMA2 FLAG mask */
#define FLAG_Mask                ((uint32_t)0x10000000)

/* DMA registers Masks */
#define CFGR_CLEAR_Mask          ((uint32_t)0xFFFF800F)

void DMA_DeInit(DMA_Channel_TypeDef *DMAy_Channelx)
{
    DMAy_Channelx->CFGR &= (uint16_t)(~DMA_CFGR1_EN);
    DMAy_Channelx->CFGR = 0;
    DMAy_Channelx->CNTR = 0;
    DMAy_Channelx->PADDR = 0;
    DMAy_Channelx->MADDR = 0;
    if(DMAy_Channelx == DMA1_Channel1)
    {
        DMA1->INTFCR |= DMA1_Channel1_IT_Mask;
    }
    else if(DMAy_Channelx == DMA1_Channel2)
    {
        DMA1->INTFCR |= DMA1_Channel2_IT_Mask;
    }
    else if(DMAy_Channelx == DMA1_Channel3)
    {
        DMA1->INTFCR |= DMA1_Channel3_IT_Mask;
    }
    else if(DMAy_Channelx == DMA1_Channel4)
    {
        DMA1->INTFCR |= DMA1_Channel4_IT_Mask;
    }
    else if(DMAy_Channelx == DMA1_Channel5)
    {
        DMA1->INTFCR |= DMA1_Channel5_IT_Mask;
    }
    else if(DMAy_Channelx == DMA1_Channel6)
    {
        DMA1->INTFCR |= DMA1_Channel6_IT_Mask;
    }
    else if(DMAy_Channelx == DMA1_Channel7)
    {
        DMA1->INTFCR |= DMA1_Channel7_IT_Mask;
    }
}

void DMA_Init(DMA_Channel_TypeDef *DMAy_Channelx, DMA_InitTypeDef *DMA_InitStruct)
{
    uint32_t tmpreg = 0;

    tmpreg = DMAy_Channelx->CFGR;
    tmpreg &= CFGR_CLEAR_Mask;
    tmpreg |= DMA_InitStruct->DMA_DIR | DMA_InitStruct->DMA_Mode |
              DMA_InitStruct->DMA_PeripheralInc | DMA_InitStruct->DMA_MemoryInc |
              DMA_InitStruct->DMA_PeripheralDataSize | DMA_InitStruct->DMA_MemoryDataSize |
              DMA_InitStruct->DMA_Priority | DMA_InitStruct->DMA_M2M;

    DMAy_Channelx->CFGR = tmpreg;
    DMAy_Channelx->CNTR = DMA_InitStruct->DMA_BufferSize;
    DMAy_Channelx->PADDR = DMA_InitStruct->DMA_PeripheralBaseAddr;
    DMAy_Channelx->MADDR = DMA_InitStruct->DMA_MemoryBaseAddr;
}

void DMA_StructInit(DMA_InitTypeDef *DMA_InitStruct)
{
    DMA_InitStruct->DMA_PeripheralBaseAddr = 0;
    DMA_InitStruct->DMA_MemoryBaseAddr = 0;
    DMA_InitStruct->DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStruct->DMA_BufferSize = 0;
    DMA_InitStruct->DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStruct->DMA_MemoryInc = DMA_MemoryInc_Disable;
    DMA_InitStruct->DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStruct->DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStruct->DMA_Mode = DMA_Mode_Normal;
    DMA_InitStruct->DMA_Priority = DMA_Priority_Low;
    DMA_InitStruct->DMA_M2M = DMA_M2M_Disable;
}

void DMA_Cmd(DMA_Channel_TypeDef *DMAy_Channelx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        DMAy_Channelx->CFGR |= DMA_CFGR1_EN;
    }
    else
    {
        DMAy_Channelx->CFGR &= (uint16_t)(~DMA_CFGR1_EN);
    }
}

void DMA_ITConfig(DMA_Channel_TypeDef *DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        DMAy_Channelx->CFGR |= DMA_IT;
    }
    else
    {
        DMAy_Channelx->CFGR &= ~DMA_IT;
    }
}

void DMA_SetCurrDataCounter(DMA_Channel_TypeDef *DMAy_Channelx, uint16_t DataNumber)
{
    DMAy_Channelx->CNTR = DataNumber;
}

uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef *DMAy_Channelx)
{
    return ((uint16_t)(DMAy_Channelx->CNTR));
}

FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG)
{
    FlagStatus bitstatus = RESET;
    uint32_t   tmpreg = 0;

    tmpreg = DMA1->INTFR;

    if((tmpreg & DMAy_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

void DMA_ClearFlag(uint32_t DMAy_FLAG)
{

    DMA1->INTFCR = DMAy_FLAG;

}

ITStatus DMA_GetITStatus(uint32_t DMAy_IT)
{
    ITStatus bitstatus = RESET;
    uint32_t tmpreg = 0;

    tmpreg = DMA1->INTFR;

    if((tmpreg & DMAy_IT) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

void DMA_ClearITPendingBit(uint32_t DMAy_IT)
{
    DMA1->INTFCR = DMAy_IT;
}
