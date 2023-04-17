/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.0.0
 * Date               : 2022/08/08
 * Description        : Main program body.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

/*
 *@Note
 Independent watchdog routine:
This routine demonstrates the pull-down input of the PC1 pin. When the input is high,
 it will feed the dog. If you don't feed the dog,Then trigger independent watchdog reset after 4s.

*/

#include <ch32v00x/debug.h>
#include <ch32v00x/gpio.h>
#include <ch32v00x/iwdg.h>
#include <ch32v00x/rcc.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#define KEY0 GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_1)  //PA0

/**
 * Initializes KEY GPIO.
 */
void KEY_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure = { 0 };

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/**
 * Key processing funcation.
 *
 * @return  0 - Press the key.
 *          1 - Release Key.
 */
uint8_t KEY_PRESS(void) {
    if (KEY0 == 1) {
        Delay_Ms(10);
        if (KEY0 == 1) {
            return 1;
        } else {
            return 0;
        }
    }

    return 0;
}

/**
 * Initializes IWDG.
 *
 * @param IWDG_Prescaler: can be any of the IWDG_Prescaler_x macros
 * where x is 4, 8, 16, 32, 64, 128 or 256;
 * @param Reload: specifies the IWDG Reload value. It must be a 
 * number between 0 and 0x0FFF.
 */
void IWDG_Feed_Init(uint16_t prer, uint16_t rlr) {
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    IWDG_SetPrescaler(prer);
    IWDG_SetReload(rlr);
    IWDG_ReloadCounter();
    IWDG_Enable();
}

int main(void) {
    USART_Printf_Init(115200);
    printf("SystemClk:%"PRIu32"\n",SystemCoreClock);

    Delay_Init();
    KEY_Init();
    printf("IWDG test...\n");
    Delay_Ms(1000);

    IWDG_Feed_Init( IWDG_Prescaler_128, 4000 );   // 4s IWDG reset

    while (1) {
        if (KEY_PRESS() == 1) {
            printf("Feed dog\n");
            IWDG_ReloadCounter();   //Feed dog
            Delay_Ms(10);
        }
    }
}
