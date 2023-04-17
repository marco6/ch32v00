/**
 * low power, sleep mode routine:
 * EXTI_Line0(PD0)
 * 
 * This routine demonstrates that WFI enters the sleep mode, and the PD0 pin input
 * low level triggers the external interrupt EXTI_Line0 to exit the sleep mode.
 * Program execution continues after wake-up.
 */

#include <ch32v00x/debug.h>
#include <ch32v00x/exti.h>
#include <ch32v00x/gpio.h>
#include <ch32v00x/misc.h>
#include <ch32v00x/rcc.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

/**
 * Initializes EXTI0 collection.
 */
void EXTI0_INT_INIT(void) {
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    EXTI_InitTypeDef EXTI_InitStructure = {0};
    NVIC_InitTypeDef NVIC_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOD, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* GPIOA.0 ----> EXTI_Line0 */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource0);
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = EXTI7_0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

int main(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    Delay_Ms(1000);
    Delay_Ms(1000);
    USART_Printf_Init(115200);
    printf("SystemClk:%"PRIu32"\n", SystemCoreClock);

    printf("Sleep Mode Test\n");
    EXTI0_INT_INIT();

    printf("\n ********** \n");
    __WFI();
    printf("\n ########## \n");

    while (1) {
        Delay_Ms(1000);
        printf("Run in main\n");
    }
}

void EXTI7_0_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void EXTI7_0_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
        printf("EXTI0 Wake_up\n");
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}
