/**
 * Memory to memory mode routine:
 * Transfer SRC_BUF[Buf_Size] to DST_BUF[Buf_Size] via DMA.
 */

#include <ch32v00x/debug.h>
#include <ch32v00x/dma.h>
#include <ch32v00x/misc.h>
#include <ch32v00x/rcc.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 32

uint32_t source[BUF_SIZE] = {0x01020304, 0x05060708, 0x090A0B0C, 0x0D0E0F10,
                         0x11121314, 0x15161718, 0x191A1B1C, 0x1D1E1F20,
                         0x21222324, 0x25262728, 0x292A2B2C, 0x2D2E2F30,
                         0x31323334, 0x35363738, 0x393A3B3C, 0x3D3E3F40,
                         0x41424344, 0x45464748, 0x494A4B4C, 0x4D4E4F50,
                         0x51525354, 0x55565758, 0x595A5B5C, 0x5D5E5F60,
                         0x61626364, 0x65666768, 0x696A6B6C, 0x6D6E6F70,
                         0x71727374, 0x75767778, 0x797A7B7C, 0x7D7E7F80};

uint32_t destination[BUF_SIZE] = {0};

/**
 * Initializes Channel3 of DMA1 collection.
 */
void DMA1_CH3_Init(void) {
    DMA_InitTypeDef DMA_InitStructure = {0};
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(source);
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)destination;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = BUF_SIZE * 4;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
    DMA_Init(DMA1_Channel3, &DMA_InitStructure);
    DMA_ClearFlag(DMA1_FLAG_TC3);

    DMA_Cmd(DMA1_Channel3, ENABLE);
}

int main(void) {
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    Delay_Init();
    USART_Printf_Init(115200);
    printf("SystemClk:%"PRIu32"\n", SystemCoreClock);

    printf("DMA MEM2MEM TEST\n");
    DMA1_CH3_Init();

    while(DMA_GetFlagStatus(DMA1_FLAG_TC3) == RESET) { }

    int diff = memcmp(source, destination, BUF_SIZE);
    if (diff) {
        printf("DMA Transfer Fail\n");
    } else {
        printf("DMA Transfer Success\n");
    }

    printf("SRC_BUF:\n");
    for (uint8_t i = 0; i < BUF_SIZE; i++) {
        printf("\t0x%08"PRIx32"\n", source[i]);
    }

    printf("DST_BUF:\n");
    for (uint8_t i = 0; i < BUF_SIZE; i++){
        printf("\t0x%08"PRIx32"\n", destination[i]);
    }

    while(1) { } // FIXME this should be part of the outro (like end obj or something)
}
