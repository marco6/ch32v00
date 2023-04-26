#include <ch32v00x/dbgmcu.h>

#define IDCODE_DEVID_MASK    ((uint32_t)0x0000FFFF)

uint32_t DBGMCU_GetREVID(void)
{
    return ((*(uint32_t *)0x1FFFF7C4) >> 16);
}

uint32_t DBGMCU_GetDEVID(void)
{
    return ((*(uint32_t *)0x1FFFF7C4) & IDCODE_DEVID_MASK);
}

uint32_t __get_DEBUG_CR(void)
{
    uint32_t result;

    __asm volatile("csrr %0,""0x7C0" : "=r"(result));
    return (result);
}

void __set_DEBUG_CR(uint32_t value)
{
    __asm volatile("csrw 0x7C0, %0" : : "r"(value));
}

void DBGMCU_Config(uint32_t DBGMCU_Periph, FunctionalState NewState)
{
    uint32_t val;

    if(NewState != DISABLE)
    {
        __set_DEBUG_CR(DBGMCU_Periph);
    }
    else
    {
        val = __get_DEBUG_CR();
        val &= ~(uint32_t)DBGMCU_Periph;
        __set_DEBUG_CR(val);
    }

}
