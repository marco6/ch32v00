#ifndef __DEBUG_H
#define __DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* UART Printf Definition */
#define DEBUG_UART1    1

/* DEBUG UATR Definition */
#ifndef DEBUG
#define DEBUG   DEBUG_UART1
#endif

void Delay_Init(void);
void Delay_Us(uint32_t n);
void Delay_Ms(uint32_t n);
void USART_Printf_Init(uint32_t baudrate);

#ifdef __cplusplus
}
#endif

#endif /* __DEBUG_H */
