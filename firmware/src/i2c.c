#include <ch32v00x/i2c.h>
#include <ch32v00x/rcc.h>

/* I2C SPE mask */
#define CTLR1_PE_Set             ((uint16_t)0x0001)
#define CTLR1_PE_Reset           ((uint16_t)0xFFFE)

/* I2C START mask */
#define CTLR1_START_Set          ((uint16_t)0x0100)
#define CTLR1_START_Reset        ((uint16_t)0xFEFF)

/* I2C STOP mask */
#define CTLR1_STOP_Set           ((uint16_t)0x0200)
#define CTLR1_STOP_Reset         ((uint16_t)0xFDFF)

/* I2C ACK mask */
#define CTLR1_ACK_Set            ((uint16_t)0x0400)
#define CTLR1_ACK_Reset          ((uint16_t)0xFBFF)

/* I2C ENGC mask */
#define CTLR1_ENGC_Set           ((uint16_t)0x0040)
#define CTLR1_ENGC_Reset         ((uint16_t)0xFFBF)

/* I2C SWRST mask */
#define CTLR1_SWRST_Set          ((uint16_t)0x8000)
#define CTLR1_SWRST_Reset        ((uint16_t)0x7FFF)

/* I2C PEC mask */
#define CTLR1_PEC_Set            ((uint16_t)0x1000)
#define CTLR1_PEC_Reset          ((uint16_t)0xEFFF)

/* I2C ENPEC mask */
#define CTLR1_ENPEC_Set          ((uint16_t)0x0020)
#define CTLR1_ENPEC_Reset        ((uint16_t)0xFFDF)

/* I2C ENARP mask */
#define CTLR1_ENARP_Set          ((uint16_t)0x0010)
#define CTLR1_ENARP_Reset        ((uint16_t)0xFFEF)

/* I2C NOSTRETCH mask */
#define CTLR1_NOSTRETCH_Set      ((uint16_t)0x0080)
#define CTLR1_NOSTRETCH_Reset    ((uint16_t)0xFF7F)

/* I2C registers Masks */
#define CTLR1_CLEAR_Mask         ((uint16_t)0xFBF5)

/* I2C DMAEN mask */
#define CTLR2_DMAEN_Set          ((uint16_t)0x0800)
#define CTLR2_DMAEN_Reset        ((uint16_t)0xF7FF)

/* I2C LAST mask */
#define CTLR2_LAST_Set           ((uint16_t)0x1000)
#define CTLR2_LAST_Reset         ((uint16_t)0xEFFF)

/* I2C FREQ mask */
#define CTLR2_FREQ_Reset         ((uint16_t)0xFFC0)

/* I2C ADD0 mask */
#define OADDR1_ADD0_Set          ((uint16_t)0x0001)
#define OADDR1_ADD0_Reset        ((uint16_t)0xFFFE)

/* I2C ENDUAL mask */
#define OADDR2_ENDUAL_Set        ((uint16_t)0x0001)
#define OADDR2_ENDUAL_Reset      ((uint16_t)0xFFFE)

/* I2C ADD2 mask */
#define OADDR2_ADD2_Reset        ((uint16_t)0xFF01)

/* I2C F/S mask */
#define CKCFGR_FS_Set            ((uint16_t)0x8000)

/* I2C CCR mask */
#define CKCFGR_CCR_Set           ((uint16_t)0x0FFF)

/* I2C FLAG mask */
#define FLAG_Mask                ((uint32_t)0x00FFFFFF)

/* I2C Interrupt Enable mask */
#define ITEN_Mask                ((uint32_t)0x07000000)

void I2C_DeInit(I2C_TypeDef *I2Cx)
{
    if(I2Cx == I2C1)
    {
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, ENABLE);
        RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1, DISABLE);
    }
}

void I2C_Init(I2C_TypeDef *I2Cx, I2C_InitTypeDef *I2C_InitStruct)
{
    uint16_t tmpreg = 0, freqrange = 0;
    uint16_t result = 0x04;
    uint32_t pclk1 = 8000000;

    RCC_ClocksTypeDef rcc_clocks;

    tmpreg = I2Cx->CTLR2;
    tmpreg &= CTLR2_FREQ_Reset;
    RCC_GetClocksFreq(&rcc_clocks);
    pclk1 = rcc_clocks.PCLK1_Frequency;
    freqrange = (uint16_t)(pclk1 / 1000000);
    tmpreg |= freqrange;
    I2Cx->CTLR2 = tmpreg;

    I2Cx->CTLR1 &= CTLR1_PE_Reset;
    tmpreg = 0;

    if(I2C_InitStruct->I2C_ClockSpeed <= 100000)
    {
        result = (uint16_t)(pclk1 / (I2C_InitStruct->I2C_ClockSpeed << 1));

        if(result < 0x04)
        {
            result = 0x04;
        }

        tmpreg |= result;
    }
    else
    {
        if(I2C_InitStruct->I2C_DutyCycle == I2C_DutyCycle_2)
        {
            result = (uint16_t)(pclk1 / (I2C_InitStruct->I2C_ClockSpeed * 3));
        }
        else
        {
            result = (uint16_t)(pclk1 / (I2C_InitStruct->I2C_ClockSpeed * 25));
            result |= I2C_DutyCycle_16_9;
        }

        if((result & CKCFGR_CCR_Set) == 0)
        {
            result |= (uint16_t)0x0001;
        }

        tmpreg |= (uint16_t)(result | CKCFGR_FS_Set);
    }

    I2Cx->CKCFGR = tmpreg;
    I2Cx->CTLR1 |= CTLR1_PE_Set;

    tmpreg = I2Cx->CTLR1;
    tmpreg &= CTLR1_CLEAR_Mask;
    tmpreg |= (uint16_t)((uint32_t)I2C_InitStruct->I2C_Mode | I2C_InitStruct->I2C_Ack);
    I2Cx->CTLR1 = tmpreg;

    I2Cx->OADDR1 = (I2C_InitStruct->I2C_AcknowledgedAddress | I2C_InitStruct->I2C_OwnAddress1);
}

void I2C_StructInit(I2C_InitTypeDef *I2C_InitStruct)
{
    I2C_InitStruct->I2C_ClockSpeed = 5000;
    I2C_InitStruct->I2C_Mode = I2C_Mode_I2C;
    I2C_InitStruct->I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStruct->I2C_OwnAddress1 = 0;
    I2C_InitStruct->I2C_Ack = I2C_Ack_Disable;
    I2C_InitStruct->I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
}

void I2C_Cmd(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        I2Cx->CTLR1 |= CTLR1_PE_Set;
    }
    else
    {
        I2Cx->CTLR1 &= CTLR1_PE_Reset;
    }
}

void I2C_DMACmd(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        I2Cx->CTLR2 |= CTLR2_DMAEN_Set;
    }
    else
    {
        I2Cx->CTLR2 &= CTLR2_DMAEN_Reset;
    }
}

void I2C_DMALastTransferCmd(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        I2Cx->CTLR2 |= CTLR2_LAST_Set;
    }
    else
    {
        I2Cx->CTLR2 &= CTLR2_LAST_Reset;
    }
}

void I2C_GenerateSTART(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        I2Cx->CTLR1 |= CTLR1_START_Set;
    }
    else
    {
        I2Cx->CTLR1 &= CTLR1_START_Reset;
    }
}

void I2C_GenerateSTOP(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        I2Cx->CTLR1 |= CTLR1_STOP_Set;
    }
    else
    {
        I2Cx->CTLR1 &= CTLR1_STOP_Reset;
    }
}

void I2C_AcknowledgeConfig(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        I2Cx->CTLR1 |= CTLR1_ACK_Set;
    }
    else
    {
        I2Cx->CTLR1 &= CTLR1_ACK_Reset;
    }
}

void I2C_OwnAddress2Config(I2C_TypeDef *I2Cx, uint8_t Address)
{
    uint16_t tmpreg = 0;

    tmpreg = I2Cx->OADDR2;
    tmpreg &= OADDR2_ADD2_Reset;
    tmpreg |= (uint16_t)((uint16_t)Address & (uint16_t)0x00FE);
    I2Cx->OADDR2 = tmpreg;
}

void I2C_DualAddressCmd(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        I2Cx->OADDR2 |= OADDR2_ENDUAL_Set;
    }
    else
    {
        I2Cx->OADDR2 &= OADDR2_ENDUAL_Reset;
    }
}

void I2C_GeneralCallCmd(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        I2Cx->CTLR1 |= CTLR1_ENGC_Set;
    }
    else
    {
        I2Cx->CTLR1 &= CTLR1_ENGC_Reset;
    }
}

void I2C_ITConfig(I2C_TypeDef *I2Cx, uint16_t I2C_IT, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        I2Cx->CTLR2 |= I2C_IT;
    }
    else
    {
        I2Cx->CTLR2 &= (uint16_t)~I2C_IT;
    }
}

void I2C_SendData(I2C_TypeDef *I2Cx, uint8_t Data)
{
    I2Cx->DATAR = Data;
}

uint8_t I2C_ReceiveData(I2C_TypeDef *I2Cx)
{
    return (uint8_t)I2Cx->DATAR;
}

void I2C_Send7bitAddress(I2C_TypeDef *I2Cx, uint8_t Address, uint8_t I2C_Direction)
{
    if(I2C_Direction != I2C_Direction_Transmitter)
    {
        Address |= OADDR1_ADD0_Set;
    }
    else
    {
        Address &= OADDR1_ADD0_Reset;
    }

    I2Cx->DATAR = Address;
}

uint16_t I2C_ReadRegister(I2C_TypeDef *I2Cx, uint8_t I2C_Register)
{
    __IO uint32_t tmp = 0;

    tmp = (uint32_t)I2Cx;
    tmp += I2C_Register;

    return (*(__IO uint16_t *)tmp);
}

void I2C_SoftwareResetCmd(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        I2Cx->CTLR1 |= CTLR1_SWRST_Set;
    }
    else
    {
        I2Cx->CTLR1 &= CTLR1_SWRST_Reset;
    }
}

void I2C_NACKPositionConfig(I2C_TypeDef *I2Cx, uint16_t I2C_NACKPosition)
{
    if(I2C_NACKPosition == I2C_NACKPosition_Next)
    {
        I2Cx->CTLR1 |= I2C_NACKPosition_Next;
    }
    else
    {
        I2Cx->CTLR1 &= I2C_NACKPosition_Current;
    }
}

void I2C_TransmitPEC(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        I2Cx->CTLR1 |= CTLR1_PEC_Set;
    }
    else
    {
        I2Cx->CTLR1 &= CTLR1_PEC_Reset;
    }
}

void I2C_PECPositionConfig(I2C_TypeDef *I2Cx, uint16_t I2C_PECPosition)
{
    if(I2C_PECPosition == I2C_PECPosition_Next)
    {
        I2Cx->CTLR1 |= I2C_PECPosition_Next;
    }
    else
    {
        I2Cx->CTLR1 &= I2C_PECPosition_Current;
    }
}

void I2C_CalculatePEC(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        I2Cx->CTLR1 |= CTLR1_ENPEC_Set;
    }
    else
    {
        I2Cx->CTLR1 &= CTLR1_ENPEC_Reset;
    }
}

uint8_t I2C_GetPEC(I2C_TypeDef *I2Cx)
{
    return ((I2Cx->STAR2) >> 8);
}

void I2C_ARPCmd(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        I2Cx->CTLR1 |= CTLR1_ENARP_Set;
    }
    else
    {
        I2Cx->CTLR1 &= CTLR1_ENARP_Reset;
    }
}

void I2C_StretchClockCmd(I2C_TypeDef *I2Cx, FunctionalState NewState)
{
    if(NewState == DISABLE)
    {
        I2Cx->CTLR1 |= CTLR1_NOSTRETCH_Set;
    }
    else
    {
        I2Cx->CTLR1 &= CTLR1_NOSTRETCH_Reset;
    }
}

void I2C_FastModeDutyCycleConfig(I2C_TypeDef *I2Cx, uint16_t I2C_DutyCycle)
{
    if(I2C_DutyCycle != I2C_DutyCycle_16_9)
    {
        I2Cx->CKCFGR &= I2C_DutyCycle_2;
    }
    else
    {
        I2Cx->CKCFGR |= I2C_DutyCycle_16_9;
    }
}

ErrorStatus I2C_CheckEvent(I2C_TypeDef *I2Cx, uint32_t I2C_EVENT)
{
    uint32_t    lastevent = 0;
    uint32_t    flag1 = 0, flag2 = 0;
    ErrorStatus status = NoREADY;

    flag1 = I2Cx->STAR1;
    flag2 = I2Cx->STAR2;
    flag2 = flag2 << 16;

    lastevent = (flag1 | flag2) & FLAG_Mask;

    if((lastevent & I2C_EVENT) == I2C_EVENT)
    {
        status = READY;
    }
    else
    {
        status = NoREADY;
    }

    return status;
}

uint32_t I2C_GetLastEvent(I2C_TypeDef *I2Cx)
{
    uint32_t lastevent = 0;
    uint32_t flag1 = 0, flag2 = 0;

    flag1 = I2Cx->STAR1;
    flag2 = I2Cx->STAR2;
    flag2 = flag2 << 16;
    lastevent = (flag1 | flag2) & FLAG_Mask;

    return lastevent;
}

FlagStatus I2C_GetFlagStatus(I2C_TypeDef *I2Cx, uint32_t I2C_FLAG)
{
    FlagStatus    bitstatus = RESET;
    __IO uint32_t i2creg = 0, i2cxbase = 0;

    i2cxbase = (uint32_t)I2Cx;
    i2creg = I2C_FLAG >> 28;
    I2C_FLAG &= FLAG_Mask;

    if(i2creg != 0)
    {
        i2cxbase += 0x14;
    }
    else
    {
        I2C_FLAG = (uint32_t)(I2C_FLAG >> 16);
        i2cxbase += 0x18;
    }

    if(((*(__IO uint32_t *)i2cxbase) & I2C_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

void I2C_ClearFlag(I2C_TypeDef *I2Cx, uint32_t I2C_FLAG)
{
    uint32_t flagpos = 0;

    flagpos = I2C_FLAG & FLAG_Mask;
    I2Cx->STAR1 = (uint16_t)~flagpos;
}

ITStatus I2C_GetITStatus(I2C_TypeDef *I2Cx, uint32_t I2C_IT)
{
    ITStatus bitstatus = RESET;
    uint32_t enablestatus = 0;

    enablestatus = (uint32_t)(((I2C_IT & ITEN_Mask) >> 16) & (I2Cx->CTLR2));
    I2C_IT &= FLAG_Mask;

    if(((I2Cx->STAR1 & I2C_IT) != (uint32_t)RESET) && enablestatus)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

void I2C_ClearITPendingBit(I2C_TypeDef *I2Cx, uint32_t I2C_IT)
{
    uint32_t flagpos = 0;

    flagpos = I2C_IT & FLAG_Mask;
    I2Cx->STAR1 = (uint16_t)~flagpos;
}







