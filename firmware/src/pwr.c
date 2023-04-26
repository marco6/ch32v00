#include <ch32v00x/pwr.h>
#include <ch32v00x/rcc.h>

/* PWR registers bit mask */
/* CTLR register bit mask */
#define CTLR_DS_MASK     ((uint32_t)0xFFFFFFFD)
#define CTLR_PLS_MASK    ((uint32_t)0xFFFFFF1F)
#define AWUPSC_MASK      ((uint32_t)0xFFFFFFF0)
#define AWUWR_MASK       ((uint32_t)0xFFFFFFC0)

void PWR_DeInit(void)
{
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, DISABLE);
}

void PWR_PVDCmd(FunctionalState NewState)
{
    if(NewState)
    {
        PWR->CTLR |= (1 << 4);
    }
    else
    {
        PWR->CTLR &= ~(1 << 4);
    }
}

void PWR_PVDLevelConfig(uint32_t PWR_PVDLevel)
{
    uint32_t tmpreg = 0;
    tmpreg = PWR->CTLR;
    tmpreg &= CTLR_PLS_MASK;
    tmpreg |= PWR_PVDLevel;
    PWR->CTLR = tmpreg;
}

void PWR_AutoWakeUpCmd(FunctionalState NewState)
{
    if(NewState)
    {
        PWR->AWUCSR |= (1 << 1);
    }
    else
    {
        PWR->AWUCSR &= ~(1 << 1);
    }
}

void PWR_AWU_SetPrescaler(uint32_t AWU_Prescaler)
{
    uint32_t tmpreg = 0;
    tmpreg = PWR->AWUPSC & AWUPSC_MASK;
    tmpreg |= AWU_Prescaler;
    PWR->AWUPSC = tmpreg;
}

void PWR_AWU_SetWindowValue(uint8_t WindowValue)
{
    __IO uint32_t tmpreg = 0;

    tmpreg = PWR->AWUWR & AWUWR_MASK;

    tmpreg |= WindowValue;

    PWR->AWUWR  = tmpreg;
}

void PWR_EnterSTANDBYMode(uint8_t PWR_STANDBYEntry)
{
    PWR->CTLR &= CTLR_DS_MASK;
    PWR->CTLR |= PWR_CTLR_PDDS;

    NVIC->SCTLR |= (1 << 2);

    if(PWR_STANDBYEntry == PWR_STANDBYEntry_WFI)
    {
        __WFI();
    }
    else
    {
        __WFE();
    }

    NVIC->SCTLR &= ~(1 << 2);
}

FlagStatus PWR_GetFlagStatus(uint32_t PWR_FLAG)
{
    FlagStatus bitstatus = RESET;

    if((PWR->CSR & PWR_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}
