// #include <ch32v00x/it.h>

void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast"), weak));
void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast"), weak));

/*********************************************************************
 * @fn      NMI_Handler
 *
 * @brief   This function handles NMI exception.
 *
 * @return  none
 */
void NMI_Handler(void) { }

/*********************************************************************
 * @fn      HardFault_Handler
 *
 * @brief   This function handles Hard Fault exception.
 *
 * @return  none
 */
void HardFault_Handler(void) { while (1){ } }
