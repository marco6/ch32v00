#include <ch32v00x/rcc.h>
#include <ch32v00x/wwdg.h>

/* CTLR register bit mask */
#define CTLR_WDGA_Set      ((uint32_t)0x00000080)

/* CFGR register bit mask */
#define CFGR_WDGTB_Mask    ((uint32_t)0xFFFFFE7F)
#define CFGR_W_Mask        ((uint32_t)0xFFFFFF80)
#define BIT_Mask           ((uint8_t)0x7F)

void WWDG_DeInit(void)
{
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, ENABLE);
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_WWDG, DISABLE);
}

void WWDG_SetPrescaler(uint32_t WWDG_Prescaler)
{
    uint32_t tmpreg = 0;
    tmpreg = WWDG->CFGR & CFGR_WDGTB_Mask;
    tmpreg |= WWDG_Prescaler;
    WWDG->CFGR = tmpreg;
}

void WWDG_SetWindowValue(uint8_t WindowValue)
{
    __IO uint32_t tmpreg = 0;

    tmpreg = WWDG->CFGR & CFGR_W_Mask;

    tmpreg |= WindowValue & (uint32_t)BIT_Mask;

    WWDG->CFGR = tmpreg;
}

void WWDG_EnableIT(void)
{
    WWDG->CFGR |= (1 << 9);
}

void WWDG_SetCounter(uint8_t Counter)
{
    WWDG->CTLR = Counter & BIT_Mask;
}

void WWDG_Enable(uint8_t Counter)
{
    WWDG->CTLR = CTLR_WDGA_Set | Counter;
}

FlagStatus WWDG_GetFlagStatus(void)
{
    return (FlagStatus)(WWDG->STATR);
}

void WWDG_ClearFlag(void)
{
    WWDG->STATR = (uint32_t)RESET;
}
