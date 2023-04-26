#include <ch32v00x/opa.h>


void OPA_DeInit(void)
{
    EXTEN->EXTEN_CTR &= ~(uint32_t)(7 << 16);
}

void OPA_Init(OPA_InitTypeDef *OPA_InitStruct)
{
    uint32_t tmp = 0;
    tmp = EXTEN->EXTEN_CTR;
    tmp &= ~(uint32_t)(3<<17);
    tmp |= (OPA_InitStruct->PSEL << 18) | (OPA_InitStruct->NSEL << 17);
    EXTEN->EXTEN_CTR = tmp;
}

void OPA_StructInit(OPA_InitTypeDef *OPA_InitStruct)
{
    OPA_InitStruct->PSEL = CHP0;
    OPA_InitStruct->NSEL = CHN0;
}

void OPA_Cmd(FunctionalState NewState)
{
    if(NewState == ENABLE)
    {
        EXTEN->EXTEN_CTR |= (uint32_t)(1 << 16);
    }
    else
    {
        EXTEN->EXTEN_CTR &= ~(uint32_t)(1 << 16);
    }
}
