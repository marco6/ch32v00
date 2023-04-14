/*
 * Window watchdog routine:
 * This routine demonstrates that the watchdog is fed between the window 0x40 - 0x5f
 * to prevent the watchdog from being reset.
 */

#include <ch32v00x/debug.h>
#include <ch32v00x/misc.h>
#include <ch32v00x/rcc.h>
#include <ch32v00x/wwdg.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#define WWDG_CNT    0X7F

/**
 * WWDG INT init.
 */
static void WWDG_NVIC_Config(void) {
    NVIC_InitTypeDef NVIC_InitStructure = {0};
    NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
 * Configure WWDG.
 *
 * @param tr - The value of the decrement counter (0x7f~0x40)
 * @param wr - Window value (0x7f~0x40)
 * @param prv - Prescaler value among WWDG_Prescaler_{1, 2, 4, 8} macros.
 */
void WWDG_Config(uint8_t tr, uint8_t wr, uint32_t prv) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);

    WWDG_SetCounter(tr);
    WWDG_SetPrescaler(prv);
    WWDG_SetWindowValue(wr);
    WWDG_Enable(WWDG_CNT);
    WWDG_ClearFlag();
    WWDG_NVIC_Config();
    WWDG_EnableIT();
}

/**
 * Feed WWDG.
 */
void WWDG_Feed(void) {
    WWDG_SetCounter(WWDG_CNT);
}

int main(void) {
    uint8_t wwdg_tr, wwdg_wr;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%"PRIu32"\n", SystemCoreClock);

    printf("WWDG Test\n");
    WWDG_Config(0x7f, 0x5f, WWDG_Prescaler_8); /* 48M/8/4096 */

    wwdg_wr = WWDG->CFGR & 0x7F;

    while(1) {
        Delay_Ms(10);

        printf("**********\n");
        wwdg_tr = WWDG->CTLR & 0x7F;
        if(wwdg_tr < wwdg_wr) {
            WWDG_Feed();
        }
        printf("##########\n");
    }
}
