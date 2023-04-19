#include "glue.h"

#include <ch32v00x/usart.h>

/**
 * reads one byte from the USART port
 */
char inbyte (void) {
    while ((USART1->STATR & USART_FLAG_RXNE) == RESET) { }
    return (uint16_t)(USART1->DATAR & (uint16_t)0x01FF);
}
