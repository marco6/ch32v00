#include <ch32v00x/sysclk.h>
#include <ch32v00x/rcc.h>

/* RCC registers bit address in the alias region */
#define RCC_OFFSET                 (RCC_BASE - PERIPH_BASE)

/* BDCTLR Register */
#define BDCTLR_OFFSET              (RCC_OFFSET + 0x20)

/* RCC registers bit mask */

/* CTLR register bit mask */
#define CTLR_HSEBYP_Reset          ((uint32_t)0xFFFBFFFF)
#define CTLR_HSEBYP_Set            ((uint32_t)0x00040000)
#define CTLR_HSEON_Reset           ((uint32_t)0xFFFEFFFF)
#define CTLR_HSEON_Set             ((uint32_t)0x00010000)
#define CTLR_HSITRIM_Mask          ((uint32_t)0xFFFFFF07)

#define CFGR0_PLL_Mask             ((uint32_t)0xFFC0FFFF)
#define CFGR0_PLLMull_Mask         ((uint32_t)0x003C0000)
#define CFGR0_PLLSRC_Mask          ((uint32_t)0x00010000)
#define CFGR0_PLLXTPRE_Mask        ((uint32_t)0x00020000)
#define CFGR0_SWS_Mask             ((uint32_t)0x0000000C)
#define CFGR0_SW_Mask              ((uint32_t)0xFFFFFFFC)
#define CFGR0_HPRE_Reset_Mask      ((uint32_t)0xFFFFFF0F)
#define CFGR0_HPRE_Set_Mask        ((uint32_t)0x000000F0)
#define CFGR0_PPRE1_Reset_Mask     ((uint32_t)0xFFFFF8FF)
#define CFGR0_PPRE1_Set_Mask       ((uint32_t)0x00000700)
#define CFGR0_PPRE2_Reset_Mask     ((uint32_t)0xFFFFC7FF)
#define CFGR0_PPRE2_Set_Mask       ((uint32_t)0x00003800)
#define CFGR0_ADCPRE_Reset_Mask    ((uint32_t)0xFFFF07FF)
#define CFGR0_ADCPRE_Set_Mask      ((uint32_t)0x0000F800)

/* RSTSCKR register bit mask */
#define RSTSCKR_RMVF_Set           ((uint32_t)0x01000000)

/* RCC Flag Mask */
#define FLAG_Mask                  ((uint8_t)0x1F)

/* INTR register byte 2 (Bits[15:8]) base address */
#define INTR_BYTE2_ADDRESS         ((uint32_t)0x40021009)

/* INTR register byte 3 (Bits[23:16]) base address */
#define INTR_BYTE3_ADDRESS         ((uint32_t)0x4002100A)

/* CFGR0 register byte 4 (Bits[31:24]) base address */
#define CFGR0_BYTE4_ADDRESS        ((uint32_t)0x40021007)

/* BDCTLR register base address */
#define BDCTLR_ADDRESS             (PERIPH_BASE + BDCTLR_OFFSET)

static __I uint8_t APBAHBPrescTable[16] = {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8};
static __I uint8_t ADCPrescTable[20] = {2, 4, 6, 8, 4, 8, 12, 16, 8, 16, 24, 32, 16, 32, 48, 64, 32, 64, 96, 128};

void RCC_DeInit(void)
{
    RCC->CTLR |= (uint32_t)0x00000001;
    RCC->CFGR0 &= (uint32_t)0xFCFF0000;
    RCC->CTLR &= (uint32_t)0xFEF6FFFF;
    RCC->CTLR &= (uint32_t)0xFFFBFFFF;
    RCC->CFGR0 &= (uint32_t)0xFFFEFFFF;
    RCC->INTR = 0x009F0000;
}

void RCC_HSEConfig(uint32_t RCC_HSE)
{
    RCC->CTLR &= CTLR_HSEON_Reset;
    RCC->CTLR &= CTLR_HSEBYP_Reset;

    switch(RCC_HSE)
    {
        case RCC_HSE_ON:
            RCC->CTLR |= CTLR_HSEON_Set;
            break;

        case RCC_HSE_Bypass:
            RCC->CTLR |= CTLR_HSEBYP_Set | CTLR_HSEON_Set;
            break;

        default:
            break;
    }
}

ErrorStatus RCC_WaitForHSEStartUp(void)
{
    __IO uint32_t StartUpCounter = 0;

    ErrorStatus status = NoREADY;
    FlagStatus  HSEStatus = RESET;

    do
    {
        HSEStatus = RCC_GetFlagStatus(RCC_FLAG_HSERDY);
        StartUpCounter++;
    } while((StartUpCounter != HSE_STARTUP_TIMEOUT) && (HSEStatus == RESET));

    if(RCC_GetFlagStatus(RCC_FLAG_HSERDY) != RESET)
    {
        status = READY;
    }
    else
    {
        status = NoREADY;
    }

    return (status);
}

void RCC_AdjustHSICalibrationValue(uint8_t HSICalibrationValue)
{
    uint32_t tmpreg = 0;

    tmpreg = RCC->CTLR;
    tmpreg &= CTLR_HSITRIM_Mask;
    tmpreg |= (uint32_t)HSICalibrationValue << 3;
    RCC->CTLR = tmpreg;
}

void RCC_HSICmd(FunctionalState NewState)
{
    if(NewState)
    {
        RCC->CTLR |= (1 << 0);
    }
    else
    {
        RCC->CTLR &= ~(1 << 0);
    }
}

void RCC_PLLConfig(uint32_t RCC_PLLSource)
{
    uint32_t tmpreg = 0;

    tmpreg = RCC->CFGR0;
    tmpreg &= CFGR0_PLL_Mask;
    tmpreg |= RCC_PLLSource;
    RCC->CFGR0 = tmpreg;
}

void RCC_PLLCmd(FunctionalState NewState)
{
    if(NewState)
    {
        RCC->CTLR |= (1 << 24);
    }
    else
    {
        RCC->CTLR &= ~(1 << 24);
    }
}

void RCC_SYSCLKConfig(uint32_t RCC_SYSCLKSource)
{
    uint32_t tmpreg = 0;

    tmpreg = RCC->CFGR0;
    tmpreg &= CFGR0_SW_Mask;
    tmpreg |= RCC_SYSCLKSource;
    RCC->CFGR0 = tmpreg;
}

uint8_t RCC_GetSYSCLKSource(void)
{
    return ((uint8_t)(RCC->CFGR0 & CFGR0_SWS_Mask));
}

void RCC_HCLKConfig(uint32_t RCC_SYSCLK)
{
    uint32_t tmpreg = 0;

    tmpreg = RCC->CFGR0;
    tmpreg &= CFGR0_HPRE_Reset_Mask;
    tmpreg |= RCC_SYSCLK;
    RCC->CFGR0 = tmpreg;
}

void RCC_ITConfig(uint8_t RCC_IT, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        *(__IO uint8_t *)INTR_BYTE2_ADDRESS |= RCC_IT;
    }
    else
    {
        *(__IO uint8_t *)INTR_BYTE2_ADDRESS &= (uint8_t)~RCC_IT;
    }
}

void RCC_ADCCLKConfig(uint32_t RCC_PCLK2)
{
    uint32_t tmpreg = 0;

    tmpreg = RCC->CFGR0;
    tmpreg &= CFGR0_ADCPRE_Reset_Mask;
    tmpreg |= RCC_PCLK2;
    RCC->CFGR0 = tmpreg;
}

void RCC_LSICmd(FunctionalState NewState)
{
    if(NewState)
    {
        RCC->RSTSCKR |= (1 << 0);
    }
    else
    {
        RCC->RSTSCKR &= ~(1 << 0);
    }
}

void RCC_GetClocksFreq(RCC_ClocksTypeDef *RCC_Clocks)
{
    uint32_t tmp = 0, pllsource = 0, presc = 0;

    tmp = RCC->CFGR0 & CFGR0_SWS_Mask;

    switch(tmp)
    {
        case 0x00:
            RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
            break;

        case 0x04:
            RCC_Clocks->SYSCLK_Frequency = HSE_VALUE;
            break;

        case 0x08:
            pllsource = RCC->CFGR0 & CFGR0_PLLSRC_Mask;

            if(pllsource == 0x00)
            {
                RCC_Clocks->SYSCLK_Frequency = HSI_VALUE * 2;
            }
            else
            {
                RCC_Clocks->SYSCLK_Frequency = HSE_VALUE * 2;
            }
            break;

        default:
            RCC_Clocks->SYSCLK_Frequency = HSI_VALUE;
            break;
    }

    tmp = RCC->CFGR0 & CFGR0_HPRE_Set_Mask;
    tmp = tmp >> 4;
    presc = APBAHBPrescTable[tmp];

    if(((RCC->CFGR0 & CFGR0_HPRE_Set_Mask) >> 4) < 8)
    {
        RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency / presc;
    }
    else
    {
        RCC_Clocks->HCLK_Frequency = RCC_Clocks->SYSCLK_Frequency >> presc;
    }

    RCC_Clocks->PCLK1_Frequency = RCC_Clocks->HCLK_Frequency;
    RCC_Clocks->PCLK2_Frequency = RCC_Clocks->HCLK_Frequency;
    tmp = RCC->CFGR0 & CFGR0_ADCPRE_Set_Mask;
    tmp = tmp >> 11;
    tmp = ((tmp & 0x18) >> 3) | ((tmp & 0x7) << 2);

    if((tmp & 0x13) >= 4)
    {
        tmp -= 12;
    }

    presc = ADCPrescTable[tmp];
    RCC_Clocks->ADCCLK_Frequency = RCC_Clocks->PCLK2_Frequency / presc;
}

void RCC_AHBPeriphClockCmd(uint32_t RCC_AHBPeriph, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        RCC->AHBPCENR |= RCC_AHBPeriph;
    }
    else
    {
        RCC->AHBPCENR &= ~RCC_AHBPeriph;
    }
}

void RCC_APB2PeriphClockCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        RCC->APB2PCENR |= RCC_APB2Periph;
    }
    else
    {
        RCC->APB2PCENR &= ~RCC_APB2Periph;
    }
}

void RCC_APB1PeriphClockCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        RCC->APB1PCENR |= RCC_APB1Periph;
    }
    else
    {
        RCC->APB1PCENR &= ~RCC_APB1Periph;
    }
}

void RCC_APB2PeriphResetCmd(uint32_t RCC_APB2Periph, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        RCC->APB2PRSTR |= RCC_APB2Periph;
    }
    else
    {
        RCC->APB2PRSTR &= ~RCC_APB2Periph;
    }
}

void RCC_APB1PeriphResetCmd(uint32_t RCC_APB1Periph, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        RCC->APB1PRSTR |= RCC_APB1Periph;
    }
    else
    {
        RCC->APB1PRSTR &= ~RCC_APB1Periph;
    }
}

void RCC_ClockSecuritySystemCmd(FunctionalState NewState)
{
    if(NewState)
    {
        RCC->CTLR |= (1 << 19);
    }
    else
    {
        RCC->CTLR &= ~(1 << 19);
    }
}

void RCC_MCOConfig(uint8_t RCC_MCO)
{
    *(__IO uint8_t *)CFGR0_BYTE4_ADDRESS = RCC_MCO;
}

FlagStatus RCC_GetFlagStatus(uint8_t RCC_FLAG)
{
    uint32_t tmp = 0;
    uint32_t statusreg = 0;

    FlagStatus bitstatus = RESET;
    tmp = RCC_FLAG >> 5;

    if(tmp == 1)
    {
        statusreg = RCC->CTLR;
    }
    else
    {
        statusreg = RCC->RSTSCKR;
    }

    tmp = RCC_FLAG & FLAG_Mask;

    if((statusreg & ((uint32_t)1 << tmp)) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

void RCC_ClearFlag(void)
{
    RCC->RSTSCKR |= RSTSCKR_RMVF_Set;
}

ITStatus RCC_GetITStatus(uint8_t RCC_IT) {
    ITStatus bitstatus = RESET;

    if((RCC->INTR & RCC_IT) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}

void RCC_ClearITPendingBit(uint8_t RCC_IT) {
    *(__IO uint8_t *)INTR_BYTE3_ADDRESS = RCC_IT;
}

typedef struct {
    uint16_t period_ms;
    uint8_t period_us;
} clock_info_t;

static clock_info_t SysclkInfo() {
    clock_info_t info;
    info.period_us = SystemCoreClock / 8000000;
    info.period_ms = (uint16_t)info.period_us * 1000;

    return info;
}

void Delay_Us(uint32_t n) {
    const clock_info_t info = SysclkInfo();
    uint32_t i;

    SysTick->SR &= ~(1 << 0);
    i = (uint32_t)n * info.period_us;

    SysTick->CMP = i;
    SysTick->CNT = 0;
    SysTick->CTLR |=(1 << 0);

    while((SysTick->SR & (1 << 0)) != (1 << 0)) { }
    SysTick->CTLR &= ~(1 << 0);
}

void Delay_Ms(uint32_t n) {
    const clock_info_t info = SysclkInfo();
    uint32_t i;

    SysTick->SR &= ~(1 << 0);
    i = (uint32_t)n * info.period_ms;

    SysTick->CMP = i;
    SysTick->CNT = 0;
    SysTick->CTLR |=(1 << 0);

    while((SysTick->SR & (1 << 0)) != (1 << 0)) { }
    SysTick->CTLR &= ~(1 << 0);
}

