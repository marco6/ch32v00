#include "glue.h"

#include <ch32v00x/usart.h>

/**
 * Writes one byte to the default USART port
 */
void outbyte(char byte) {    
    while ((USART1->STATR & USART_FLAG_TC) == RESET) { }
    USART1->DATAR = (byte & (uint16_t)0x01FF);
}
