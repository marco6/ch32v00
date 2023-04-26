#ifndef __CH32V00x_DMA_H
#define __CH32V00x_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ch32v00x/device.h>

/**
 * DMA Init structure definition
 */
typedef struct DMA_InitTypeDef {
    /**
     * Specifies the peripheral base address for DMAy Channelx. 
     */
    uint32_t DMA_PeripheralBaseAddr;

    /**
     * Specifies the memory base address for DMAy Channelx. 
     */
    uint32_t DMA_MemoryBaseAddr;

    /**
     * Specifies if the peripheral is the source or destination.
     * This parameter can be a value of @ref DMA_data_transfer_direction 
     */
    uint32_t DMA_DIR;

    /**
     * Specifies the buffer size, in data unit, of the specified Channel.
     * The data unit is equal to the configuration set in DMA_PeripheralDataSize
     * or DMA_MemoryDataSize members depending in the transfer direction. 
     */
    uint32_t DMA_BufferSize;

    /**
     * Specifies whether the Peripheral address register is incremented or not.
     * This parameter can be a value of @ref DMA_peripheral_incremented_mode 
     */
    uint32_t DMA_PeripheralInc;

    /**
     * Specifies whether the memory address register is incremented or not.
     * This parameter can be a value of @ref DMA_memory_incremented_mode 
     */
    uint32_t DMA_MemoryInc;

    /**
     * Specifies the Peripheral data width.
     * This parameter can be a value of @ref DMA_peripheral_data_size 
     */
    uint32_t DMA_PeripheralDataSize;

    /**
     * Specifies the Memory data width.
     * This parameter can be a value of @ref DMA_memory_data_size 
     */
    uint32_t DMA_MemoryDataSize;

    /**
     * Specifies the operation mode of the DMAy Channelx.
     * This parameter can be a value of @ref DMA_circular_normal_mode.
     * @note: The circular buffer mode cannot be used if the memory-to-memory
     * data transfer is configured on the selected Channel
     
     */
    uint32_t DMA_Mode;

    /**
     * Specifies the software priority for the DMAy Channelx.
     * This parameter can be a value of @ref DMA_priority_level 
     */
    uint32_t DMA_Priority;

    /**
     * Specifies if the DMAy Channelx will be used in memory-to-memory transfer.
     * This parameter can be a value of @ref DMA_memory_to_memory 
     */
    uint32_t DMA_M2M;
} DMA_InitTypeDef;

/* DMA_data_transfer_direction */
#define DMA_DIR_PeripheralDST              ((uint32_t)0x00000010)
#define DMA_DIR_PeripheralSRC              ((uint32_t)0x00000000)

/* DMA_peripheral_incremented_mode */
#define DMA_PeripheralInc_Enable           ((uint32_t)0x00000040)
#define DMA_PeripheralInc_Disable          ((uint32_t)0x00000000)

/* DMA_memory_incremented_mode */
#define DMA_MemoryInc_Enable               ((uint32_t)0x00000080)
#define DMA_MemoryInc_Disable              ((uint32_t)0x00000000)

/* DMA_peripheral_data_size */
#define DMA_PeripheralDataSize_Byte        ((uint32_t)0x00000000)
#define DMA_PeripheralDataSize_HalfWord    ((uint32_t)0x00000100)
#define DMA_PeripheralDataSize_Word        ((uint32_t)0x00000200)

/* DMA_memory_data_size */
#define DMA_MemoryDataSize_Byte            ((uint32_t)0x00000000)
#define DMA_MemoryDataSize_HalfWord        ((uint32_t)0x00000400)
#define DMA_MemoryDataSize_Word            ((uint32_t)0x00000800)

/* DMA_circular_normal_mode */
#define DMA_Mode_Circular                  ((uint32_t)0x00000020)
#define DMA_Mode_Normal                    ((uint32_t)0x00000000)

/* DMA_priority_level */
#define DMA_Priority_VeryHigh              ((uint32_t)0x00003000)
#define DMA_Priority_High                  ((uint32_t)0x00002000)
#define DMA_Priority_Medium                ((uint32_t)0x00001000)
#define DMA_Priority_Low                   ((uint32_t)0x00000000)

/* DMA_memory_to_memory */
#define DMA_M2M_Enable                     ((uint32_t)0x00004000)
#define DMA_M2M_Disable                    ((uint32_t)0x00000000)

/* DMA_interrupts_definition */
#define DMA_IT_TC                          ((uint32_t)0x00000002)
#define DMA_IT_HT                          ((uint32_t)0x00000004)
#define DMA_IT_TE                          ((uint32_t)0x00000008)

#define DMA1_IT_GL1                        ((uint32_t)0x00000001)
#define DMA1_IT_TC1                        ((uint32_t)0x00000002)
#define DMA1_IT_HT1                        ((uint32_t)0x00000004)
#define DMA1_IT_TE1                        ((uint32_t)0x00000008)
#define DMA1_IT_GL2                        ((uint32_t)0x00000010)
#define DMA1_IT_TC2                        ((uint32_t)0x00000020)
#define DMA1_IT_HT2                        ((uint32_t)0x00000040)
#define DMA1_IT_TE2                        ((uint32_t)0x00000080)
#define DMA1_IT_GL3                        ((uint32_t)0x00000100)
#define DMA1_IT_TC3                        ((uint32_t)0x00000200)
#define DMA1_IT_HT3                        ((uint32_t)0x00000400)
#define DMA1_IT_TE3                        ((uint32_t)0x00000800)
#define DMA1_IT_GL4                        ((uint32_t)0x00001000)
#define DMA1_IT_TC4                        ((uint32_t)0x00002000)
#define DMA1_IT_HT4                        ((uint32_t)0x00004000)
#define DMA1_IT_TE4                        ((uint32_t)0x00008000)
#define DMA1_IT_GL5                        ((uint32_t)0x00010000)
#define DMA1_IT_TC5                        ((uint32_t)0x00020000)
#define DMA1_IT_HT5                        ((uint32_t)0x00040000)
#define DMA1_IT_TE5                        ((uint32_t)0x00080000)
#define DMA1_IT_GL6                        ((uint32_t)0x00100000)
#define DMA1_IT_TC6                        ((uint32_t)0x00200000)
#define DMA1_IT_HT6                        ((uint32_t)0x00400000)
#define DMA1_IT_TE6                        ((uint32_t)0x00800000)
#define DMA1_IT_GL7                        ((uint32_t)0x01000000)
#define DMA1_IT_TC7                        ((uint32_t)0x02000000)
#define DMA1_IT_HT7                        ((uint32_t)0x04000000)
#define DMA1_IT_TE7                        ((uint32_t)0x08000000)

/* DMA_flags_definition */
#define DMA1_FLAG_GL1                      ((uint32_t)0x00000001)
#define DMA1_FLAG_TC1                      ((uint32_t)0x00000002)
#define DMA1_FLAG_HT1                      ((uint32_t)0x00000004)
#define DMA1_FLAG_TE1                      ((uint32_t)0x00000008)
#define DMA1_FLAG_GL2                      ((uint32_t)0x00000010)
#define DMA1_FLAG_TC2                      ((uint32_t)0x00000020)
#define DMA1_FLAG_HT2                      ((uint32_t)0x00000040)
#define DMA1_FLAG_TE2                      ((uint32_t)0x00000080)
#define DMA1_FLAG_GL3                      ((uint32_t)0x00000100)
#define DMA1_FLAG_TC3                      ((uint32_t)0x00000200)
#define DMA1_FLAG_HT3                      ((uint32_t)0x00000400)
#define DMA1_FLAG_TE3                      ((uint32_t)0x00000800)
#define DMA1_FLAG_GL4                      ((uint32_t)0x00001000)
#define DMA1_FLAG_TC4                      ((uint32_t)0x00002000)
#define DMA1_FLAG_HT4                      ((uint32_t)0x00004000)
#define DMA1_FLAG_TE4                      ((uint32_t)0x00008000)
#define DMA1_FLAG_GL5                      ((uint32_t)0x00010000)
#define DMA1_FLAG_TC5                      ((uint32_t)0x00020000)
#define DMA1_FLAG_HT5                      ((uint32_t)0x00040000)
#define DMA1_FLAG_TE5                      ((uint32_t)0x00080000)
#define DMA1_FLAG_GL6                      ((uint32_t)0x00100000)
#define DMA1_FLAG_TC6                      ((uint32_t)0x00200000)
#define DMA1_FLAG_HT6                      ((uint32_t)0x00400000)
#define DMA1_FLAG_TE6                      ((uint32_t)0x00800000)
#define DMA1_FLAG_GL7                      ((uint32_t)0x01000000)
#define DMA1_FLAG_TC7                      ((uint32_t)0x02000000)
#define DMA1_FLAG_HT7                      ((uint32_t)0x04000000)
#define DMA1_FLAG_TE7                      ((uint32_t)0x08000000)


/**
 * Deinitializes the DMAy Channelx registers to their default
 * reset values.
 *
 * @param DMAy_Channelx here y can be 1 to select the DMA and x can be
 * 1 to 7 for DMA1 to select the DMA Channel.
 */
void DMA_DeInit(DMA_Channel_TypeDef *DMAy_Channelx);

/**
 * Initializes the DMAy Channelx according to the specified
 * parameters in the DMA_InitStruct.
 *
 * @param DMAy_Channelx here y can be 1 to select the DMA and x can be
 * 1 to 7 for DMA1 to select the DMA Channel.
 * @param DMA_InitStruct pointer to a DMA_InitTypeDef structure that contains
 * contains the configuration information for the specified DMA Channel.
 */
void DMA_Init(DMA_Channel_TypeDef *DMAy_Channelx, DMA_InitTypeDef *DMA_InitStruct);

/**
 * Fills each DMA_InitStruct member with its default value.
 *
 * @param DMAy_Channelx here y can be 1 to select the DMA and x can be
 * 1 to 7 for DMA1 to select the DMA Channel.
 * @param DMA_InitStruct pointer to a DMA_InitTypeDef structure that contains
 * contains the configuration information for the specified DMA Channel.
 */
void DMA_StructInit(DMA_InitTypeDef *DMA_InitStruct);

/**
 * Enables or disables the specified DMAy Channelx.
 *
 * @param DMAy_Channelx here y can be 1 to select the DMA and x can be
 * 1 to 7 for DMA1 to select the DMA Channel.
 * @param NewState new state of the DMAy Channelx(ENABLE or DISABLE).
 */
void DMA_Cmd(DMA_Channel_TypeDef *DMAy_Channelx, FunctionalState NewState);

/**
 * Enables or disables the specified DMAy Channelx interrupts.
 *
 * @param DMAy_Channelx here y can be 1 to select the DMA and x can be
 * 1 to 7 for DMA1 to select the DMA Channel.
 * @param DMA_IT specifies the DMA interrupts sources to be enabled
 * or disabled.
 *    DMA_IT_TC - Transfer complete interrupt mask
 *    DMA_IT_HT - Half transfer interrupt mask
 *    DMA_IT_TE - Transfer error interrupt mask
 * @param NewState new state of the DMAy Channelx(ENABLE or DISABLE).
 */
void DMA_ITConfig(DMA_Channel_TypeDef *DMAy_Channelx, uint32_t DMA_IT, FunctionalState NewState);

/**
 * Sets the number of data units in the current DMAy Channelx transfer.
 *
 * @param DMAy_Channelx here y can be 1 to select the DMA and x can be
 * 1 to 7 for DMA1 to select the DMA Channel.
 * @param DataNumber The number of data units in the current DMAy Channelx
 * transfer.
 */
void DMA_SetCurrDataCounter(DMA_Channel_TypeDef *DMAy_Channelx, uint16_t DataNumber);

/**
 * Returns the number of remaining data units in the current
 * DMAy Channelx transfer.
 *
 * @param DMAy_Channelx here y can be 1 to select the DMA and x can be
 * 1 to 7 for DMA1 to select the DMA Channel.
 *
 * @return The number of remaining data units in the current
 * DMAy Channelx transfer.
 */
uint16_t DMA_GetCurrDataCounter(DMA_Channel_TypeDef *DMAy_Channelx);

/**
 * Checks whether the specified DMAy Channelx flag is set or not.
 *
 * @param DMAy_FLAG specifies the flag to check.
 *    DMA1_FLAG_GL1 - DMA1 Channel1 global flag.
 *    DMA1_FLAG_TC1 - DMA1 Channel1 transfer complete flag.
 *    DMA1_FLAG_HT1 - DMA1 Channel1 half transfer flag.
 *    DMA1_FLAG_TE1 - DMA1 Channel1 transfer error flag.
 *    DMA1_FLAG_GL2 - DMA1 Channel2 global flag.
 *    DMA1_FLAG_TC2 - DMA1 Channel2 transfer complete flag.
 *    DMA1_FLAG_HT2 - DMA1 Channel2 half transfer flag.
 *    DMA1_FLAG_TE2 - DMA1 Channel2 transfer error flag.
 *    DMA1_FLAG_GL3 - DMA1 Channel3 global flag.
 *    DMA1_FLAG_TC3 - DMA1 Channel3 transfer complete flag.
 *    DMA1_FLAG_HT3 - DMA1 Channel3 half transfer flag.
 *    DMA1_FLAG_TE3 - DMA1 Channel3 transfer error flag.
 *    DMA1_FLAG_GL4 - DMA1 Channel4 global flag.
 *    DMA1_FLAG_TC4 - DMA1 Channel4 transfer complete flag.
 *    DMA1_FLAG_HT4 - DMA1 Channel4 half transfer flag.
 *    DMA1_FLAG_TE4 - DMA1 Channel4 transfer error flag.
 *    DMA1_FLAG_GL5 - DMA1 Channel5 global flag.
 *    DMA1_FLAG_TC5 - DMA1 Channel5 transfer complete flag.
 *    DMA1_FLAG_HT5 - DMA1 Channel5 half transfer flag.
 *    DMA1_FLAG_TE5 - DMA1 Channel5 transfer error flag.
 *    DMA1_FLAG_GL6 - DMA1 Channel6 global flag.
 *    DMA1_FLAG_TC6 - DMA1 Channel6 transfer complete flag.
 *    DMA1_FLAG_HT6 - DMA1 Channel6 half transfer flag.
 *    DMA1_FLAG_TE6 - DMA1 Channel6 transfer error flag.
 *    DMA1_FLAG_GL7 - DMA1 Channel7 global flag.
 *    DMA1_FLAG_TC7 - DMA1 Channel7 transfer complete flag.
 *    DMA1_FLAG_HT7 - DMA1 Channel7 half transfer flag.
 *    DMA1_FLAG_TE7 - DMA1 Channel7 transfer error flag.
 *
 * @return The new state of DMAy_FLAG (SET or RESET).
 */
FlagStatus DMA_GetFlagStatus(uint32_t DMAy_FLAG);

/**
 * Clears the DMAy Channelx's pending flags.
 *
 * @param DMAy_FLAG specifies the flag to check.
 *    DMA1_FLAG_GL1 - DMA1 Channel1 global flag.
 *    DMA1_FLAG_TC1 - DMA1 Channel1 transfer complete flag.
 *    DMA1_FLAG_HT1 - DMA1 Channel1 half transfer flag.
 *    DMA1_FLAG_TE1 - DMA1 Channel1 transfer error flag.
 *    DMA1_FLAG_GL2 - DMA1 Channel2 global flag.
 *    DMA1_FLAG_TC2 - DMA1 Channel2 transfer complete flag.
 *    DMA1_FLAG_HT2 - DMA1 Channel2 half transfer flag.
 *    DMA1_FLAG_TE2 - DMA1 Channel2 transfer error flag.
 *    DMA1_FLAG_GL3 - DMA1 Channel3 global flag.
 *    DMA1_FLAG_TC3 - DMA1 Channel3 transfer complete flag.
 *    DMA1_FLAG_HT3 - DMA1 Channel3 half transfer flag.
 *    DMA1_FLAG_TE3 - DMA1 Channel3 transfer error flag.
 *    DMA1_FLAG_GL4 - DMA1 Channel4 global flag.
 *    DMA1_FLAG_TC4 - DMA1 Channel4 transfer complete flag.
 *    DMA1_FLAG_HT4 - DMA1 Channel4 half transfer flag.
 *    DMA1_FLAG_TE4 - DMA1 Channel4 transfer error flag.
 *    DMA1_FLAG_GL5 - DMA1 Channel5 global flag.
 *    DMA1_FLAG_TC5 - DMA1 Channel5 transfer complete flag.
 *    DMA1_FLAG_HT5 - DMA1 Channel5 half transfer flag.
 *    DMA1_FLAG_TE5 - DMA1 Channel5 transfer error flag.
 *    DMA1_FLAG_GL6 - DMA1 Channel6 global flag.
 *    DMA1_FLAG_TC6 - DMA1 Channel6 transfer complete flag.
 *    DMA1_FLAG_HT6 - DMA1 Channel6 half transfer flag.
 *    DMA1_FLAG_TE6 - DMA1 Channel6 transfer error flag.
 *    DMA1_FLAG_GL7 - DMA1 Channel7 global flag.
 *    DMA1_FLAG_TC7 - DMA1 Channel7 transfer complete flag.
 *    DMA1_FLAG_HT7 - DMA1 Channel7 half transfer flag.
 *    DMA1_FLAG_TE7 - DMA1 Channel7 transfer error flag.
 */
void DMA_ClearFlag(uint32_t DMAy_FLAG);

/**
 * Checks whether the specified DMAy Channelx interrupt has
 * occurred or not.
 *
 * @param DMAy_IT specifies the DMAy interrupt source to check.
 *    DMA1_IT_GL1 - DMA1 Channel1 global flag.
 *    DMA1_IT_TC1 - DMA1 Channel1 transfer complete flag.
 *    DMA1_IT_HT1 - DMA1 Channel1 half transfer flag.
 *    DMA1_IT_TE1 - DMA1 Channel1 transfer error flag.
 *    DMA1_IT_GL2 - DMA1 Channel2 global flag.
 *    DMA1_IT_TC2 - DMA1 Channel2 transfer complete flag.
 *    DMA1_IT_HT2 - DMA1 Channel2 half transfer flag.
 *    DMA1_IT_TE2 - DMA1 Channel2 transfer error flag.
 *    DMA1_IT_GL3 - DMA1 Channel3 global flag.
 *    DMA1_IT_TC3 - DMA1 Channel3 transfer complete flag.
 *    DMA1_IT_HT3 - DMA1 Channel3 half transfer flag.
 *    DMA1_IT_TE3 - DMA1 Channel3 transfer error flag.
 *    DMA1_IT_GL4 - DMA1 Channel4 global flag.
 *    DMA1_IT_TC4 - DMA1 Channel4 transfer complete flag.
 *    DMA1_IT_HT4 - DMA1 Channel4 half transfer flag.
 *    DMA1_IT_TE4 - DMA1 Channel4 transfer error flag.
 *    DMA1_IT_GL5 - DMA1 Channel5 global flag.
 *    DMA1_IT_TC5 - DMA1 Channel5 transfer complete flag.
 *    DMA1_IT_HT5 - DMA1 Channel5 half transfer flag.
 *    DMA1_IT_TE5 - DMA1 Channel5 transfer error flag.
 *    DMA1_IT_GL6 - DMA1 Channel6 global flag.
 *    DMA1_IT_TC6 - DMA1 Channel6 transfer complete flag.
 *    DMA1_IT_HT6 - DMA1 Channel6 half transfer flag.
 *    DMA1_IT_TE6 - DMA1 Channel6 transfer error flag.
 *    DMA1_IT_GL7 - DMA1 Channel7 global flag.
 *    DMA1_IT_TC7 - DMA1 Channel7 transfer complete flag.
 *    DMA1_IT_HT7 - DMA1 Channel7 half transfer flag.
 *    DMA1_IT_TE7 - DMA1 Channel7 transfer error flag.
 *
 * @return The new state of DMAy_IT (SET or RESET).
 */
ITStatus DMA_GetITStatus(uint32_t DMAy_IT);

/**
 * Clears the DMAy Channelx's interrupt pending bits.
 *
 * @param DMAy_IT specifies the DMAy interrupt source to check.
 *    DMA1_IT_GL1 - DMA1 Channel1 global flag.
 *    DMA1_IT_TC1 - DMA1 Channel1 transfer complete flag.
 *    DMA1_IT_HT1 - DMA1 Channel1 half transfer flag.
 *    DMA1_IT_TE1 - DMA1 Channel1 transfer error flag.
 *    DMA1_IT_GL2 - DMA1 Channel2 global flag.
 *    DMA1_IT_TC2 - DMA1 Channel2 transfer complete flag.
 *    DMA1_IT_HT2 - DMA1 Channel2 half transfer flag.
 *    DMA1_IT_TE2 - DMA1 Channel2 transfer error flag.
 *    DMA1_IT_GL3 - DMA1 Channel3 global flag.
 *    DMA1_IT_TC3 - DMA1 Channel3 transfer complete flag.
 *    DMA1_IT_HT3 - DMA1 Channel3 half transfer flag.
 *    DMA1_IT_TE3 - DMA1 Channel3 transfer error flag.
 *    DMA1_IT_GL4 - DMA1 Channel4 global flag.
 *    DMA1_IT_TC4 - DMA1 Channel4 transfer complete flag.
 *    DMA1_IT_HT4 - DMA1 Channel4 half transfer flag.
 *    DMA1_IT_TE4 - DMA1 Channel4 transfer error flag.
 *    DMA1_IT_GL5 - DMA1 Channel5 global flag.
 *    DMA1_IT_TC5 - DMA1 Channel5 transfer complete flag.
 *    DMA1_IT_HT5 - DMA1 Channel5 half transfer flag.
 *    DMA1_IT_TE5 - DMA1 Channel5 transfer error flag.
 *    DMA1_IT_GL6 - DMA1 Channel6 global flag.
 *    DMA1_IT_TC6 - DMA1 Channel6 transfer complete flag.
 *    DMA1_IT_HT6 - DMA1 Channel6 half transfer flag.
 *    DMA1_IT_TE6 - DMA1 Channel6 transfer error flag.
 *    DMA1_IT_GL7 - DMA1 Channel7 global flag.
 *    DMA1_IT_TC7 - DMA1 Channel7 transfer complete flag.
 *    DMA1_IT_HT7 - DMA1 Channel7 half transfer flag.
 *    DMA1_IT_TE7 - DMA1 Channel7 transfer error flag.
 */
void DMA_ClearITPendingBit(uint32_t DMAy_IT);


#ifdef __cplusplus
}
#endif

#endif /*__CH32V00x_DMA_H */
