/**
 * FLASH erase/read/write, and fast programming:
 * Includes Standard Erase and Program, Fast Erase and Program.
 */

#include <ch32v00x/debug.h>
#include <ch32v00x/flash.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

typedef enum TestStatus {
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

#define PAGE_WRITE_START_ADDR          ((uint32_t)0x08003000) /* Start from 12K */
#define PAGE_WRITE_END_ADDR            ((uint32_t)0x08004000) /* End at 16K */
#define FLASH_PAGE_SIZE                1024
#define FLASH_PAGES_TO_BE_PROTECTED    FLASH_WRProt_Pages240to255

volatile uint32_t EraseCounter = 0x0, Address = 0x0;
volatile uint16_t Data = 0xAAAA;
volatile uint32_t WRPR_Value = 0xFFFFFFFF, ProtectedPages = 0x0;
volatile uint32_t NbrOfPage;
volatile FLASH_Status FLASHStatus = FLASH_COMPLETE;
volatile TestStatus MemoryProgramStatus = PASSED;
volatile TestStatus MemoryEraseStatus = PASSED;

static uint32_t buf[16];

/**
 * Config Option byte and enable reset pin.
 */
void Option_Byte_CFG(void) {
    FLASH_Unlock();
    FLASH_EraseOptionBytes();
    FLASH_UserOptionByteConfig(OB_IWDG_SW, OB_STOP_NoRST, OB_STDBY_NoRST, OB_RST_EN_DT12ms);
    FLASH_Lock();
}

/**
 * Flash Program Test.
 */
void Flash_Test(void) {
    FLASH_Unlock();
    WRPR_Value = FLASH_GetWriteProtectionOptionByte();

    NbrOfPage = (PAGE_WRITE_END_ADDR - PAGE_WRITE_START_ADDR) / FLASH_PAGE_SIZE;

    if ((WRPR_Value & FLASH_PAGES_TO_BE_PROTECTED) != 0x00) {
        FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_WRPRTERR);

        for (EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++) {
            FLASHStatus = FLASH_ErasePage(PAGE_WRITE_START_ADDR + (FLASH_PAGE_SIZE * EraseCounter));
            if(FLASHStatus != FLASH_COMPLETE) {
                printf("FLASH Erase ERR at Page%"PRIu32"\n", EraseCounter + 60);
            }

            printf("FLASH Erase Page%"PRIu32"...\n", EraseCounter + 60);
        }

        Address = PAGE_WRITE_START_ADDR;
        printf("Erase Cheking...\n");
        while ((Address < PAGE_WRITE_END_ADDR) && (MemoryEraseStatus != FAILED)) {
            if ((*(__IO uint16_t *)Address) != 0xFFFF) {
                MemoryEraseStatus = FAILED;
            }

            Address += 2;
        }

        if(MemoryEraseStatus == FAILED) {
            printf("Erase Flash FAIL!\n");
            printf("\n");
        } else {
            printf("Erase Flash PASS!\n");
            printf("\n");
        }

        Address = PAGE_WRITE_START_ADDR;
        printf("Programing...\n");
        while((Address < PAGE_WRITE_END_ADDR) && (FLASHStatus == FLASH_COMPLETE)) {
            FLASHStatus = FLASH_ProgramHalfWord(Address, Data);
            Address = Address + 2;
        }

        Address = PAGE_WRITE_START_ADDR;
        printf("Program Cheking...\n");

        while ((Address < PAGE_WRITE_END_ADDR) && (MemoryProgramStatus != FAILED)) {
            if ((*(__IO uint16_t *)Address) != Data) {
                MemoryProgramStatus = FAILED;
            }
            Address += 2;
        }

        if (MemoryProgramStatus == FAILED) {
            printf("Memory Program FAIL!\n");
            printf("\n");
        } else {
            printf("Memory Program PASS!\n");
            printf("\n");
        }
    } else {
        MemoryProgramStatus = FAILED;
        printf("Error to program the flash : The desired pages are write protected\n");
    }

    FLASH_Lock();
}

/**
 * Flash Fast Program Test.
 */
void Flash_Test_Fast(void) {
    uint8_t verity_flag = 0;

    for (uint8_t i = 0; i < 16; i++) {
        buf[i] = i;
    }

    FLASH_Unlock_Fast();

    FLASH_ErasePage_Fast(0x08003000);

    printf("64Byte Page Erase Suc\n");

    FLASH_BufReset();
    for (uint8_t i = 0; i < 16; i++) {
        FLASH_BufLoad(0x08003000+4*i, buf[i]);
    }

    FLASH_ProgramPage_Fast(0x08003000);

    printf("64Byte Page Program Su\n");

    FLASH_Lock_Fast();

    for (uint8_t i = 0; i < 16; i++) {
        if (buf[i] == *(uint32_t *)(0x08003000 + 4 * i)) {
            verity_flag = 0;
        } else {
            verity_flag = 1;
            break;
        }
    }

    if (verity_flag) {
        printf("64Byte Page Verity Fail\n");
    } else {
        printf("64Byte Page Verity Suc\n");
    }
}

int main(void) {
    Delay_Init();
    Delay_Ms(1000);
    USART_Printf_Init(115200);
    SystemCoreClockUpdate();
    printf("SystemClk-1:%"PRIu32"\n", SystemCoreClock);

    Flash_Test();
    Flash_Test_Fast();

    while(1) { } // FIXME this should be part of the outro (like end obj or something)
}
