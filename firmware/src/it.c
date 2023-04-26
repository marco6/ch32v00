void NMI_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast"), weak));
void NMI_Handler(void) { }

void HardFault_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast"), weak));
void HardFault_Handler(void) { while (1){ } }
