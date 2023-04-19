#include <ch32v00x/sysclk.h>
#include <ch32v00x/device.h>
#include <ch32v00x/usart.h>

#define SYSCLK_FREQ_8MHz_HSI    8000000
#define SYSCLK_FREQ_24MHz_HSI   HSI_VALUE
#define SYSCLK_FREQ_48MHz_HSI   48000000
#define SYSCLK_FREQ_8MHz_HSE    8000000
#define SYSCLK_FREQ_24MHz_HSE   HSE_VALUE
#define SYSCLK_FREQ_48MHz_HSE   48000000

uint32_t SystemCoreClock = SYSCLK_FREQ_24MHz_HSI;

/**
 * This code mimics the access to the table
 * of prescaler values. The table was so 
 * simple that this operation is both faster
 * and consumes less memory.
 */
static uint8_t AHBPrescTable(uint8_t i) {
    // The original table was defined as:
    //
    //   uint8_t AHBPrescTable[16] = {
    //       1, 2, 3, 4, 5, 6, 7, 8,
    //       1, 2, 3, 4, 5, 6, 7, 8
    //   };
    return (i&0x7) + 1;
}
 void InitSysClock(void) __attribute__((weak));
void InitSysClock(void) { }

/**
 * Setup the microcontroller system Initialize the Embedded Flash Interface,
 * the PLL and update the SystemCoreClock variable.
 */
void SystemInit(void) {
    RCC->CTLR |= (uint32_t)0x00000001;
    RCC->CFGR0 &= (uint32_t)0xFCFF0000;
    RCC->CTLR &= (uint32_t)0xFEF6FFFF;
    RCC->CTLR &= (uint32_t)0xFFFBFFFF;
    RCC->CFGR0 &= (uint32_t)0xFFFEFFFF;
    RCC->INTR = 0x009F0000;

    InitSysClock();
}

/**
 * Update SystemCoreClock variable according to Clock Register Values.
 */
void SystemCoreClockUpdate (void) {
    uint32_t tmp = 0, pllsource = 0;

    tmp = RCC->CFGR0 & RCC_SWS;

    switch (tmp) {
    case 0x00:
        SystemCoreClock = HSI_VALUE;
        break;
    case 0x04:
        SystemCoreClock = HSE_VALUE;
        break;
    case 0x08:
        pllsource = RCC->CFGR0 & RCC_PLLSRC;
        if (pllsource == 0x00) {
            SystemCoreClock = HSI_VALUE * 2;
        } else {
            SystemCoreClock = HSE_VALUE * 2;
        }
        break;
    default:
        SystemCoreClock = HSI_VALUE;
        break;
    }

    tmp = AHBPrescTable(((RCC->CFGR0 & RCC_HPRE) >> 4));

    if(((RCC->CFGR0 & RCC_HPRE) >> 4) < 8) {
        SystemCoreClock /= tmp;
    } else {
        SystemCoreClock >>= tmp;
    }
}

void InitSysClockTo_8MHz_HSI(void) {
    SystemCoreClock = SYSCLK_FREQ_8MHz_HSI;

    /* Flash 0 wait state */
    FLASH->ACTLR &= (uint32_t)((uint32_t)~FLASH_ACTLR_LATENCY);
    FLASH->ACTLR |= (uint32_t)FLASH_ACTLR_LATENCY_0;

    /* HCLK = SYSCLK = APB1 */
    RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV3;
}

void InitSysClockTo_24MHz_HSI(void) {
    SystemCoreClock = SYSCLK_FREQ_24MHz_HSI;

    /* Flash 0 wait state */
    FLASH->ACTLR &= (uint32_t)((uint32_t)~FLASH_ACTLR_LATENCY);
    FLASH->ACTLR |= (uint32_t)FLASH_ACTLR_LATENCY_0;

    /* HCLK = SYSCLK = APB1 */
    RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV1;
}

void InitSysClockTo_48MHz_HSI(void) {
    SystemCoreClock = SYSCLK_FREQ_48MHz_HSI;

    // Flash 0 wait state
    FLASH->ACTLR &= (uint32_t)((uint32_t)~FLASH_ACTLR_LATENCY);
    FLASH->ACTLR |= (uint32_t)FLASH_ACTLR_LATENCY_1;

    // HCLK = SYSCLK = APB1
    RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV1;

    // PLL configuration: PLLCLK = HSI * 2 = 48 MHz
    RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_PLLSRC));
    RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSI_Mul2);

    // Enable PLL
    RCC->CTLR |= RCC_PLLON;
    // Wait till PLL is ready
    while((RCC->CTLR & RCC_PLLRDY) == 0) { }

    // Select PLL as system clock source
    RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_SW));
    RCC->CFGR0 |= (uint32_t)RCC_SW_PLL;   
    // Wait till PLL is used as system clock source
    while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x08) { }
}

int InitSysClockTo_8MHz_HSE(void) {
    SystemCoreClock = SYSCLK_FREQ_8MHz_HSE;

    /* Close PA0-PA1 GPIO function */
    RCC->APB2PCENR |= RCC_AFIOEN;
    AFIO->PCFR1 |= (1<<15);

    RCC->CTLR |= ((uint32_t)RCC_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    for (int retry = 0; retry < HSE_STARTUP_TIMEOUT; retry++) {
        if ((RCC->CTLR & RCC_HSERDY) != RESET) {
            break;
        }
    }

    RCC->APB2PCENR |= RCC_AFIOEN;
    AFIO->PCFR1 |= (1<<15);

    if ((RCC->CTLR & RCC_HSERDY) != RESET) {
        /* Flash 0 wait state */
        FLASH->ACTLR &= (uint32_t)((uint32_t)~FLASH_ACTLR_LATENCY);
        FLASH->ACTLR |= (uint32_t)FLASH_ACTLR_LATENCY_0;

        /* HCLK = SYSCLK = APB1 */
        RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV3;

        /* Select HSE as system clock source */
        RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_SW));
        RCC->CFGR0 |= (uint32_t)RCC_SW_HSE;
        /* Wait till HSE is used as system clock source */
        while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x04) { }

        return 0;
    }

    return 1;
}

int InitSysClockTo_24MHz_HSE(void) {
    SystemCoreClock = SYSCLK_FREQ_8MHz_HSE;

    /* Close PA0-PA1 GPIO function */
    RCC->APB2PCENR |= RCC_AFIOEN;
    AFIO->PCFR1 |= (1<<15);

    RCC->CTLR |= ((uint32_t)RCC_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    for (int retry = 0; retry < HSE_STARTUP_TIMEOUT; retry++) {
        if ((RCC->CTLR & RCC_HSERDY) != RESET) {
            break;
        }
    }

    RCC->APB2PCENR |= RCC_AFIOEN;
    AFIO->PCFR1 |= (1<<15);

    if ((RCC->CTLR & RCC_HSERDY) != RESET) {
        /* Flash 0 wait state */
        FLASH->ACTLR &= (uint32_t)((uint32_t)~FLASH_ACTLR_LATENCY);
        FLASH->ACTLR |= (uint32_t)FLASH_ACTLR_LATENCY_0;

        /* HCLK = SYSCLK = APB1 */
        RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV1;

        /* Select HSE as system clock source */
        RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_SW));
        RCC->CFGR0 |= (uint32_t)RCC_SW_HSE;
        /* Wait till HSE is used as system clock source */
        while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x04) { }

        return 0;
    }

    return 1;
}

int InitSysClockTo_48MHz_HSE(void) {
    SystemCoreClock = SYSCLK_FREQ_48MHz_HSE;

    /* Close PA0-PA1 GPIO function */
    RCC->APB2PCENR |= RCC_AFIOEN;
    AFIO->PCFR1 |= (1<<15);

    RCC->CTLR |= ((uint32_t)RCC_HSEON);

    /* Wait till HSE is ready and if Time out is reached exit */
    for (int retry = 0; retry < HSE_STARTUP_TIMEOUT; retry++) {
        if ((RCC->CTLR & RCC_HSERDY) != RESET) {
            break;
        }
    }
    
    if ((RCC->CTLR & RCC_HSERDY) != RESET) {
        /* Flash 0 wait state */
        FLASH->ACTLR &= (uint32_t)((uint32_t)~FLASH_ACTLR_LATENCY);
        FLASH->ACTLR |= (uint32_t)FLASH_ACTLR_LATENCY_1;

        /* HCLK = SYSCLK = APB1 */
        RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV1;

        /* PLL configuration: PLLCLK = HSE * 2 = 48 MHz */
        RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_PLLSRC));
        RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSE_Mul2);

        /* Enable PLL */
        RCC->CTLR |= RCC_PLLON;
        /* Wait till PLL is ready */
        while((RCC->CTLR & RCC_PLLRDY) == 0) { }

        /* Select PLL as system clock source */
        RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_SW));
        RCC->CFGR0 |= (uint32_t)RCC_SW_PLL;
        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x08) { }

        return 0;
    }

    return 1;
}
