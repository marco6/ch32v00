#include <ch32v00x/iwdg.h>

/* CTLR register bit mask */
#define CTLR_KEY_Reload    ((uint16_t)0xAAAA)
#define CTLR_KEY_Enable    ((uint16_t)0xCCCC)

void IWDG_WriteAccessCmd(uint16_t IWDG_WriteAccess)
{
    IWDG->CTLR = IWDG_WriteAccess;
}

void IWDG_SetPrescaler(uint8_t IWDG_Prescaler)
{
    IWDG->PSCR = IWDG_Prescaler;
}

void IWDG_SetReload(uint16_t Reload)
{
    IWDG->RLDR = Reload;
}

void IWDG_ReloadCounter(void)
{
    IWDG->CTLR = CTLR_KEY_Reload;
}

void IWDG_Enable(void)
{
    IWDG->CTLR = CTLR_KEY_Enable;
}

FlagStatus IWDG_GetFlagStatus(uint16_t IWDG_FLAG)
{
    FlagStatus bitstatus = RESET;

    if((IWDG->STATR & IWDG_FLAG) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }

    return bitstatus;
}



