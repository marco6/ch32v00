/**
 * Multiprocessor communication mode routine:
 * Master:USART1_Tx(PD5)\USART1_Rx(PD6).
 * Slave:USART1_Tx(PD5)\USART1_Rx(PD6).
 *
 * This routine demonstrates that one board acts as the master, 
 * and the other acts as the slave.
 * The master sends address 0x02 to make the slave exit Silent 
 * mode, complete follow-up communication.
 *
 * Hardware connection:
 *  PD5 -- PD6
 *  PD6 -- PD5
 *  PDO -- LED
 */

#include <ch32v00x/gpio.h>
#include <ch32v00x/nvic.h>
#include <ch32v00x/rcc.h>
#include <ch32v00x/usart.h>

/* USART Mode Definition */
#define USART_HOST_MODE 0
#define USART_SLAVE_MODE 1

/* USART Communication Mode Selection */
#if defined(HOST_MODE)
# define USART_MODE   USART_HOST_MODE
#elif defined(SLAVE_MODE)
# define USART_MODE   USART_SLAVE_MODE
#else
# error Please define either HOST_MODE or SLAVE_MODE macros to select the behavior.
#endif

/**
 * Initializes GPIOA.0
 */
void GPIO_Toggle_INIT(void) {
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_SetBits(GPIOD, GPIO_Pin_0);
}

/**
 * Initializes the USART1 peripheral.
 */
void USARTx_CFG(void) {
    GPIO_InitTypeDef  GPIO_InitStructure = {0};
    USART_InitTypeDef USART_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_USART1, ENABLE);

    /* USART1 TX-->D.5   RX-->D.6 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_9b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USART1, &USART_InitStructure);

    USART_Cmd(USART1, ENABLE);

#if(USART_MODE == USART_HOST_MODE)
    USART_SetAddress(USART1, 0x1);
#elif(USART_MODE == USART_SLAVE_MODE)
    USART_SetAddress(USART1, 0x2);
    USART_WakeUpConfig(USART1, USART_WakeUp_AddressMark);
    USART_ReceiverWakeUpCmd(USART1, ENABLE); /* USART1 Into Silence */
#endif
}

int main(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    GPIO_Toggle_INIT();
    USARTx_CFG();
    Delay_Ms(1000);

#if(USART_MODE == USART_HOST_MODE)
    while (1) {
        Delay_Ms(1000);
 
        USART_SendData(USART1, 0x102);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) { }

        USART_SendData(USART1, 0xAA);
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) { }
    }
#elif(USART_MODE == USART_SLAVE_MODE)
    uint8_t i = 0;
    while (1) {
        if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) != RESET) {
            if (USART_ReceiveData(USART1) == 0xAA) {
                GPIO_WriteBit(GPIOD, GPIO_Pin_0, (i == 0) ? (i = Bit_SET) : (i = Bit_RESET));
            }
        }
    }
#endif
}
