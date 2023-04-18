#ifndef __CH32V00x_OPA_H
#define __CH32V00x_OPA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ch32v00x/device.h>

/* OPA PSEL enumeration */
typedef enum
{
    CHP0 = 0,
    CHP1
} OPA_PSEL_TypeDef;

/* OPA NSEL enumeration */
typedef enum
{
    CHN0 = 0,
    CHN1
} OPA_NSEL_TypeDef;


/* OPA Init Structure definition */
typedef struct
{
    OPA_PSEL_TypeDef PSEL;    /* Specifies the positive channel of OPA */
    OPA_NSEL_TypeDef NSEL;    /* Specifies the negative channel of OPA */
} OPA_InitTypeDef;

void OPA_DeInit(void);
void OPA_Init(OPA_InitTypeDef *OPA_InitStruct);
void OPA_StructInit(OPA_InitTypeDef *OPA_InitStruct);
void OPA_Cmd(FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif
