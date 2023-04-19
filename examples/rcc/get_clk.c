/**
 * Get system-HCLK-AHB1-AHB2 clock routine:
 * MCO(PC4)
 * This example demonstrates MCO(PC4) pin output system clock and get clock;
 *   - RCC_GetClocksFreq() function to get systemclk-HCLK-AHB1-AHB2 clock
 *   - SystemCoreClockUpdate() function to get HCLK clock
*/

#include <ch32v00x/gpio.h>
#include <ch32v00x/nvic.h>
#include <ch32v00x/rcc.h>
#include <ch32v00x/system.h>
#include <ch32v00x/usart.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
    GPIO_InitTypeDef  GPIO_InitStructure={0};
    RCC_ClocksTypeDef RCC_ClocksStatus={0};

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    USART_Printf_Init(115200);
    SystemCoreClockUpdate();
    printf("SystemClk:%"PRIu32"\n",SystemCoreClock);

    RCC_GetClocksFreq(&RCC_ClocksStatus);
    printf("SYSCLK_Frequency-%"PRIu32"\n", RCC_ClocksStatus.SYSCLK_Frequency);
    printf("HCLK_Frequency-%"PRIu32"\n", RCC_ClocksStatus.HCLK_Frequency);
    printf("PCLK1_Frequency-%"PRIu32"\n", RCC_ClocksStatus.PCLK1_Frequency);
    printf("PCLK2_Frequency-%"PRIu32"\n", RCC_ClocksStatus.PCLK2_Frequency);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* MCO Output GPIOC 4 */
    RCC_MCOConfig( RCC_MCO_SYSCLK );
    // RCC_MCOConfig( RCC_MCO_HSI );
    // RCC_MCOConfig( RCC_MCO_HSE );
    // RCC_MCOConfig( RCC_MCO_PLLCLK );

    while(1) { } // FIXME outro
}
