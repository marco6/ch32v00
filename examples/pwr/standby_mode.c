/**
 * Low power, standby mode routine: AWU automatically wakes up
 * This example demonstrates that WFI enters standby mode and wakes up automatically.
 * 
 * Note: In order to reduce power consumption as much as possible, it is recommended
 * to set the unused GPIO to pull-down mode.
 */

#include <ch32v00x/exti.h>
#include <ch32v00x/gpio.h>
#include <ch32v00x/nvic.h>
#include <ch32v00x/pwr.h>
#include <ch32v00x/rcc.h>
#include <ch32v00x/usart.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

/**
 * Initializes EXTI collection.
 */
void EXTI_INT_INIT(void) {
    EXTI_InitTypeDef EXTI_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    EXTI_InitStructure.EXTI_Line = EXTI_Line9;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

int main(void) {
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Ms(1000);
    Delay_Ms(1000);
    EXTI_INT_INIT();

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    USART_Printf_Init(115200);
    printf("SystemClk:%"PRIu32"\n", SystemCoreClock);
    printf("Standby Mode Test\n");
    printf("0x1FFFF800-%08"PRIx32"\n", *(uint32_t*)0x1FFFF800);

    RCC_LSICmd(ENABLE);
    while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET) { }

    PWR_AWU_SetPrescaler(PWR_AWU_Prescaler_10240);
    PWR_AWU_SetWindowValue(25);
    PWR_AutoWakeUpCmd(ENABLE);
    PWR_EnterSTANDBYMode(PWR_STANDBYEntry_WFE);

    USART_Printf_Init(115200);
    printf("\n Auto wake up \n");

    while(1) {
        Delay_Ms(1000);
        printf("Run in main\n");
    }
}
