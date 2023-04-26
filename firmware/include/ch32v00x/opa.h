#ifndef __CH32V00x_OPA_H
#define __CH32V00x_OPA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ch32v00x/device.h>

/* OPA PSEL enumeration */
typedef enum OPA_PSEL_TypeDef {
    CHP0 = 0,
    CHP1
} OPA_PSEL_TypeDef;

/* OPA NSEL enumeration */
typedef enum OPA_NSEL_TypeDef {
    CHN0 = 0,
    CHN1
} OPA_NSEL_TypeDef;


/* OPA Init Structure definition */
typedef struct OPA_InitTypeDef {
    OPA_PSEL_TypeDef PSEL;    /* Specifies the positive channel of OPA */
    OPA_NSEL_TypeDef NSEL;    /* Specifies the negative channel of OPA */
} OPA_InitTypeDef;

/**
 * Deinitializes the OPA peripheral registers to their default
 * reset values.
 */
void OPA_DeInit(void);

/**
 * Initializes the OPA peripheral according to the specified
 * parameters in the OPA_InitStruct.
 *
 * @param OPA_InitStruct pointer to a OPA_InitTypeDef structure
 */
void OPA_Init(OPA_InitTypeDef *OPA_InitStruct);

/**
 * Fills each OPA_StructInit member with its reset value.
 *
 * @param OPA_StructInit pointer to a OPA_InitTypeDef structure
 */
void OPA_StructInit(OPA_InitTypeDef *OPA_InitStruct);

/**
 * Enables or disables the specified OPA peripheral.
 *
 * @param NewState ENABLE or DISABLE.
 */
void OPA_Cmd(FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif
