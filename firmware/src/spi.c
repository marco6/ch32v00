#include <ch32v00x/rcc.h>
#include <ch32v00x/spi.h>

/* SPI SPE mask */
#define CTLR1_SPE_Set         ((uint16_t)0x0040)
#define CTLR1_SPE_Reset       ((uint16_t)0xFFBF)

/* SPI CRCNext mask */
#define CTLR1_CRCNext_Set     ((uint16_t)0x1000)

/* SPI CRCEN mask */
#define CTLR1_CRCEN_Set       ((uint16_t)0x2000)
#define CTLR1_CRCEN_Reset     ((uint16_t)0xDFFF)

/* SPI SSOE mask */
#define CTLR2_SSOE_Set        ((uint16_t)0x0004)
#define CTLR2_SSOE_Reset      ((uint16_t)0xFFFB)

/* SPI registers Masks */
#define CTLR1_CLEAR_Mask      ((uint16_t)0x3040)
#define I2SCFGR_CLEAR_Mask    ((uint16_t)0xF040)


void SPI_I2S_DeInit(SPI_TypeDef *SPIx)
{
    if(SPIx == SPI1)
    {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE);
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, DISABLE);
    }
}

void SPI_Init(SPI_TypeDef *SPIx, SPI_InitTypeDef *SPI_InitStruct)
{
    uint16_t tmpreg = 0;

    tmpreg = SPIx->CTLR1;
    tmpreg &= CTLR1_CLEAR_Mask;
    tmpreg |= (uint16_t)((uint32_t)SPI_InitStruct->SPI_Direction | SPI_InitStruct->SPI_Mode |
                         SPI_InitStruct->SPI_DataSize | SPI_InitStruct->SPI_CPOL |
                         SPI_InitStruct->SPI_CPHA | SPI_InitStruct->SPI_NSS |
                         SPI_InitStruct->SPI_BaudRatePrescaler | SPI_InitStruct->SPI_FirstBit);

    SPIx->CTLR1 = tmpreg;
    SPIx->CRCR = SPI_InitStruct->SPI_CRCPolynomial;
}

void SPI_StructInit(SPI_InitTypeDef *SPI_InitStruct)
{
    SPI_InitStruct->SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStruct->SPI_Mode = SPI_Mode_Slave;
    SPI_InitStruct->SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct->SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStruct->SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStruct->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
    SPI_InitStruct->SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStruct->SPI_CRCPolynomial = 7;
}

void SPI_Cmd(SPI_TypeDef *SPIx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        SPIx->CTLR1 |= CTLR1_SPE_Set;
    }
    else
    {
        SPIx->CTLR1 &= CTLR1_SPE_Reset;
    }
}

void SPI_I2S_ITConfig(SPI_TypeDef *SPIx, uint8_t SPI_I2S_IT, FunctionalState NewState)
{
    uint16_t itpos = 0, itmask = 0;

    itpos = SPI_I2S_IT >> 4;
    itmask = (uint16_t)1 << (uint16_t)itpos;

    if(NewState != DISABLE)
    {
        SPIx->CTLR2 |= itmask;
    }
    else
    {
        SPIx->CTLR2 &= (uint16_t)~itmask;
    }
}

void SPI_I2S_DMACmd(SPI_TypeDef *SPIx, uint16_t SPI_I2S_DMAReq, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        SPIx->CTLR2 |= SPI_I2S_DMAReq;
    }
    else
    {
        SPIx->CTLR2 &= (uint16_t)~SPI_I2S_DMAReq;
    }
}

void SPI_I2S_SendData(SPI_TypeDef *SPIx, uint16_t Data)
{
    SPIx->DATAR = Data;
}

uint16_t SPI_I2S_ReceiveData(SPI_TypeDef *SPIx)
{
    return SPIx->DATAR;
}

void SPI_NSSInternalSoftwareConfig(SPI_TypeDef *SPIx, uint16_t SPI_NSSInternalSoft)
{
    if(SPI_NSSInternalSoft != SPI_NSSInternalSoft_Reset)
    {
        SPIx->CTLR1 |= SPI_NSSInternalSoft_Set;
    }
    else
    {
        SPIx->CTLR1 &= SPI_NSSInternalSoft_Reset;
    }
}

void SPI_SSOutputCmd(SPI_TypeDef *SPIx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        SPIx->CTLR2 |= CTLR2_SSOE_Set;
    }
    else
    {
        SPIx->CTLR2 &= CTLR2_SSOE_Reset;
    }
}

void SPI_DataSizeConfig(SPI_TypeDef *SPIx, uint16_t SPI_DataSize)
{
    SPIx->CTLR1 &= (uint16_t)~SPI_DataSize_16b;
    SPIx->CTLR1 |= SPI_DataSize;
}

void SPI_TransmitCRC(SPI_TypeDef *SPIx)
{
    SPIx->CTLR1 |= CTLR1_CRCNext_Set;
}

void SPI_CalculateCRC(SPI_TypeDef *SPIx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        SPIx->CTLR1 |= CTLR1_CRCEN_Set;
    }
    else
    {
        SPIx->CTLR1 &= CTLR1_CRCEN_Reset;
    }
}

uint16_t SPI_GetCRC(SPI_TypeDef *SPIx, uint8_t SPI_CRC)
{
    uint16_t crcreg = 0;

    if(SPI_CRC != SPI_CRC_Rx)
    {
        crcreg = SPIx->TCRCR;
    }
    else
    {
        crcreg = SPIx->RCRCR;
    }

    return crcreg;
}

uint16_t SPI_GetCRCPolynomial(SPI_TypeDef *SPIx)
{
    return SPIx->CRCR;
}

void SPI_BiDirectionalLineConfig(SPI_TypeDef *SPIx, uint16_t SPI_Direction)
{
    if(SPI_Direction == SPI_Direction_Tx)
    {
        SPIx->CTLR1 |= SPI_Direction_Tx;
    }
    else
    {
        SPIx->CTLR1 &= SPI_Direction_Rx;
    }
}

FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef *SPIx, uint16_t SPI_I2S_FLAG)
{
    FlagStatus bitstatus = RESET;

    if((SPIx->STATR & SPI_I2S_FLAG) != (uint16_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

void SPI_I2S_ClearFlag(SPI_TypeDef *SPIx, uint16_t SPI_I2S_FLAG)
{
    SPIx->STATR = (uint16_t)~SPI_I2S_FLAG;
}

ITStatus SPI_I2S_GetITStatus(SPI_TypeDef *SPIx, uint8_t SPI_I2S_IT)
{
    ITStatus bitstatus = RESET;
    uint16_t itpos = 0, itmask = 0, enablestatus = 0;

    itpos = 0x01 << (SPI_I2S_IT & 0x0F);
    itmask = SPI_I2S_IT >> 4;
    itmask = 0x01 << itmask;
    enablestatus = (SPIx->CTLR2 & itmask);

    if(((SPIx->STATR & itpos) != (uint16_t)RESET) && enablestatus)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

void SPI_I2S_ClearITPendingBit(SPI_TypeDef *SPIx, uint8_t SPI_I2S_IT)
{
    uint16_t itpos = 0;

    itpos = 0x01 << (SPI_I2S_IT & 0x0F);
    SPIx->STATR = (uint16_t)~itpos;
}






