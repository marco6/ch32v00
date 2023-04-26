#include <ch32v00x/exti.h>

/* No interrupt selected */
#define EXTI_LINENONE    ((uint32_t)0x00000)

void EXTI_DeInit(void)
{
    EXTI->INTENR = 0x00000000;
    EXTI->EVENR = 0x00000000;
    EXTI->RTENR = 0x00000000;
    EXTI->FTENR = 0x00000000;
    EXTI->INTFR = 0x000FFFFF;
}

void EXTI_Init(EXTI_InitTypeDef *EXTI_InitStruct)
{
    uint32_t tmp = 0;

    tmp = (uint32_t)EXTI_BASE;
    if(EXTI_InitStruct->EXTI_LineCmd != DISABLE)
    {
        EXTI->INTENR &= ~EXTI_InitStruct->EXTI_Line;
        EXTI->EVENR &= ~EXTI_InitStruct->EXTI_Line;
        tmp += EXTI_InitStruct->EXTI_Mode;
        *(__IO uint32_t *)tmp |= EXTI_InitStruct->EXTI_Line;
        EXTI->RTENR &= ~EXTI_InitStruct->EXTI_Line;
        EXTI->FTENR &= ~EXTI_InitStruct->EXTI_Line;
        if(EXTI_InitStruct->EXTI_Trigger == EXTI_Trigger_Rising_Falling)
        {
            EXTI->RTENR |= EXTI_InitStruct->EXTI_Line;
            EXTI->FTENR |= EXTI_InitStruct->EXTI_Line;
        }
        else
        {
            tmp = (uint32_t)EXTI_BASE;
            tmp += EXTI_InitStruct->EXTI_Trigger;
            *(__IO uint32_t *)tmp |= EXTI_InitStruct->EXTI_Line;
        }
    }
    else
    {
        tmp += EXTI_InitStruct->EXTI_Mode;
        *(__IO uint32_t *)tmp &= ~EXTI_InitStruct->EXTI_Line;
    }
}

void EXTI_StructInit(EXTI_InitTypeDef *EXTI_InitStruct)
{
    EXTI_InitStruct->EXTI_Line = EXTI_LINENONE;
    EXTI_InitStruct->EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct->EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStruct->EXTI_LineCmd = DISABLE;
}

void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line)
{
    EXTI->SWIEVR |= EXTI_Line;
}

FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line)
{
    FlagStatus bitstatus = RESET;
    if((EXTI->INTFR & EXTI_Line) != (uint32_t)RESET)
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

void EXTI_ClearFlag(uint32_t EXTI_Line)
{
    EXTI->INTFR = EXTI_Line;
}

ITStatus EXTI_GetITStatus(uint32_t EXTI_Line)
{
    ITStatus bitstatus = RESET;
    uint32_t enablestatus = 0;

    enablestatus = EXTI->INTENR & EXTI_Line;
    if(((EXTI->INTFR & EXTI_Line) != (uint32_t)RESET) && (enablestatus != (uint32_t)RESET))
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

void EXTI_ClearITPendingBit(uint32_t EXTI_Line)
{
    EXTI->INTFR = EXTI_Line;
}
