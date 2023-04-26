#ifndef __CH32V00x_FLASH_H
#define __CH32V00x_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ch32v00x/device.h>

/* FLASH Status */
typedef enum
{
    FLASH_BUSY = 1,
    FLASH_ERROR_PG,
    FLASH_ERROR_WRP,
    FLASH_COMPLETE,
    FLASH_TIMEOUT
} FLASH_Status;

/* Flash_Latency */
#define FLASH_Latency_0                  ((uint32_t)0x00000000) /* FLASH Zero Latency cycle */
#define FLASH_Latency_1                  ((uint32_t)0x00000001) /* FLASH One Latency cycle */
#define FLASH_Latency_2                  ((uint32_t)0x00000002) /* FLASH Two Latency cycles */

/* Values to be used with CH32V00x devices (1page = 64Byte) */
#define FLASH_WRProt_Pages0to15          ((uint32_t)0x00000001) /* CH32 Low and Medium density devices: Write protection of page 0 to 15 */
#define FLASH_WRProt_Pages16to31         ((uint32_t)0x00000002) /* CH32 Low and Medium density devices: Write protection of page 16 to 31 */
#define FLASH_WRProt_Pages32to47         ((uint32_t)0x00000004) /* CH32 Low and Medium density devices: Write protection of page 32 to 47 */
#define FLASH_WRProt_Pages48to63         ((uint32_t)0x00000008) /* CH32 Low and Medium density devices: Write protection of page 48 to 63 */
#define FLASH_WRProt_Pages64to79         ((uint32_t)0x00000010) /* CH32 Low and Medium density devices: Write protection of page 64 to 79 */
#define FLASH_WRProt_Pages80to95         ((uint32_t)0x00000020) /* CH32 Low and Medium density devices: Write protection of page 80 to 95 */
#define FLASH_WRProt_Pages96to111        ((uint32_t)0x00000040) /* CH32 Low and Medium density devices: Write protection of page 96 to 111 */
#define FLASH_WRProt_Pages112to127       ((uint32_t)0x00000080) /* CH32 Low and Medium density devices: Write protection of page 112 to 127 */
#define FLASH_WRProt_Pages128to143       ((uint32_t)0x00000100) /* CH32 Medium-density devices: Write protection of page 128 to 143 */
#define FLASH_WRProt_Pages144to159       ((uint32_t)0x00000200) /* CH32 Medium-density devices: Write protection of page 144 to 159 */
#define FLASH_WRProt_Pages160to175       ((uint32_t)0x00000400) /* CH32 Medium-density devices: Write protection of page 160 to 175 */
#define FLASH_WRProt_Pages176to191       ((uint32_t)0x00000800) /* CH32 Medium-density devices: Write protection of page 176 to 191 */
#define FLASH_WRProt_Pages192to207       ((uint32_t)0x00001000) /* CH32 Medium-density devices: Write protection of page 192 to 207 */
#define FLASH_WRProt_Pages208to223       ((uint32_t)0x00002000) /* CH32 Medium-density devices: Write protection of page 208 to 223 */
#define FLASH_WRProt_Pages224to239       ((uint32_t)0x00004000) /* CH32 Medium-density devices: Write protection of page 224 to 239 */
#define FLASH_WRProt_Pages240to255       ((uint32_t)0x00008000) /* CH32 Medium-density devices: Write protection of page 240 to 255 */

#define FLASH_WRProt_AllPages            ((uint32_t)0x0000FFFF) /* Write protection of all Pages */

/* Option_Bytes_IWatchdog */
#define OB_IWDG_SW                       ((uint16_t)0x0001) /* Software IWDG selected */
#define OB_IWDG_HW                       ((uint16_t)0x0000) /* Hardware IWDG selected */

/* Option_Bytes_nRST_STOP */
#define OB_STOP_NoRST                    ((uint16_t)0x0002) /* No reset generated when entering in STOP */
#define OB_STOP_RST                      ((uint16_t)0x0000) /* Reset generated when entering in STOP */

/* Option_Bytes_nRST_STDBY */
#define OB_STDBY_NoRST                   ((uint16_t)0x0004) /* No reset generated when entering in STANDBY */
#define OB_STDBY_RST                     ((uint16_t)0x0000) /* Reset generated when entering in STANDBY */

/* Option_Bytes_RST_ENandDT */
#define OB_RST_NoEN                      ((uint16_t)0x0018) /* Reset IO disable (PD7)*/
#define OB_RST_EN_DT12ms                 ((uint16_t)0x0010) /* Reset IO enable (PD7) and  Ignore delay time 12ms */
#define OB_RST_EN_DT1ms                  ((uint16_t)0x0008) /* Reset IO enable (PD7) and  Ignore delay time 1ms */
#define OB_RST_EN_DT128ms                ((uint16_t)0x0000) /* Reset IO enable (PD7) and  Ignore delay time 128ms */

/* FLASH_Interrupts */
#define FLASH_IT_ERROR                   ((uint32_t)0x00000400) /* FPEC error interrupt source */
#define FLASH_IT_EOP                     ((uint32_t)0x00001000) /* End of FLASH Operation Interrupt source */
#define FLASH_IT_BANK1_ERROR             FLASH_IT_ERROR         /* FPEC BANK1 error interrupt source */
#define FLASH_IT_BANK1_EOP               FLASH_IT_EOP           /* End of FLASH BANK1 Operation Interrupt source */

/* FLASH_Flags */
#define FLASH_FLAG_BSY                   ((uint32_t)0x00000001) /* FLASH Busy flag */
#define FLASH_FLAG_EOP                   ((uint32_t)0x00000020) /* FLASH End of Operation flag */
#define FLASH_FLAG_WRPRTERR              ((uint32_t)0x00000010) /* FLASH Write protected error flag */
#define FLASH_FLAG_OPTERR                ((uint32_t)0x00000001) /* FLASH Option Byte error flag */

#define FLASH_FLAG_BANK1_BSY             FLASH_FLAG_BSY       /* FLASH BANK1 Busy flag*/
#define FLASH_FLAG_BANK1_EOP             FLASH_FLAG_EOP       /* FLASH BANK1 End of Operation flag */
#define FLASH_FLAG_BANK1_WRPRTERR        FLASH_FLAG_WRPRTERR  /* FLASH BANK1 Write protected error flag */

/* System_Reset_Start_Mode */
#define Start_Mode_USER                  ((uint32_t)0x00000000)
#define Start_Mode_BOOT                  ((uint32_t)0x00004000)

/**
  * Sets the code latency value.
  *
  * @param FLASH_Latency specifies the FLASH Latency value.
  *    FLASH_Latency_0 - FLASH Zero Latency cycle
  *    FLASH_Latency_1 - FLASH One Latency cycle
  *    FLASH_Latency_2 - FLASH Two Latency cycles
  */
void FLASH_SetLatency(uint32_t FLASH_Latency);

/**
 * Unlocks the FLASH Program Erase Controller.
 */
void FLASH_Unlock(void);

/**
 * Locks the FLASH Program Erase Controller.
 */
void FLASH_Lock(void);

/**
 * Erases a specified FLASH page(1KB).
 *
 * @param Page_Address The page address to be erased.
 *
 * @return The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 * FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_ErasePage(uint32_t Page_Address);

/**
 * Erases all FLASH pages.
 *
 * @return The returned value can be:FLASH_BUSY, FLASH_ERROR_PG,
 * FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_EraseAllPages(void);

/**
 * Erases the FLASH option bytes.
 *
 * @return The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 * FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_EraseOptionBytes(void);

/**
 * Programs a word at a specified address.
 *
 * @param Address specifies the address to be programmed.
 * @param Data specifies the data to be programmed.
 *
 * @return The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 * FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data);

/**
 * Programs a half word at a specified address.
 *
 * @param Address specifies the address to be programmed.
 * @param Data specifies the data to be programmed.
 *
 * @return The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 * FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data);

/**
 * Programs a half word at a specified Option Byte Data address.
 *
 * @param Address specifies the address to be programmed.
 * @param Data specifies the data to be programmed.
 *
 * @return The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 * FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_ProgramOptionByteData(uint32_t Address, uint8_t Data);

/**
 * Write protects the desired sectors
 *
 * @param FLASH_Sectors specifies the address of the pages to be write protected.
 *
 * @return The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 * FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_EnableWriteProtection(uint32_t FLASH_Pages);

/**
 * Enables or disables the read out protection.
 *
 * @param Newstate new state of the ReadOut Protection(ENABLE or DISABLE).
 *
 * @return The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 * FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_ReadOutProtection(FunctionalState NewState);

/**
 * Programs the FLASH User Option Byte - IWDG_SW / RST_STOP / RST_STDBY.
 *
 * @param OB_IWDG Selects the IWDG mode
 *    OB_IWDG_SW - Software IWDG selected
 *    OB_IWDG_HW - Hardware IWDG selected
 * @param OB_STOP Reset event when entering STOP mode.
 *    OB_STOP_NoRST - No reset generated when entering in STOP
 *    OB_STOP_RST - Reset generated when entering in STOP
 * @param OB_STDBY Reset event when entering Standby mode.
 *    OB_STDBY_NoRST - No reset generated when entering in STANDBY
 *    OB_STDBY_RST - Reset generated when entering in STANDBY
 * @param OB_RST Selects the reset IO mode and Ignore delay time
 *    OB_RST_NoEN - Reset IO disable (PD7)
 *    OB_RST_EN_DT12ms - Reset IO enable (PD7) and  Ignore delay time 12ms
 *    OB_RST_EN_DT1ms - Reset IO enable (PD7) and  Ignore delay time 1ms
 *    OB_RST_EN_DT128ms - Reset IO enable (PD7) and  Ignore delay time 128ms
 *
 * @return The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 * FLASH_ERROR_WRP, FLASH_COMPLETE or FLASH_TIMEOUT.
 */
FLASH_Status FLASH_UserOptionByteConfig(uint16_t OB_IWDG, uint16_t OB_STOP, uint16_t OB_STDBY, uint16_t OB_RST);

/**
 * Returns the FLASH User Option Bytes values.
 *
 * @return The FLASH User Option Bytes values: IWDG_SW(Bit0), RST_STOP(Bit1)
 * and RST_STDBY(Bit2).
 */
uint32_t FLASH_GetUserOptionByte(void);

/**
 * Returns the FLASH Write Protection Option Bytes Register value.
 *
 * @return The FLASH Write Protection Option Bytes Register value.
 */
uint32_t FLASH_GetWriteProtectionOptionByte(void);

/**
 * Checks whether the FLASH Read Out Protection Status is set or not.
 *
 * @return FLASH ReadOut Protection Status(SET or RESET)
 */
FlagStatus FLASH_GetReadOutProtectionStatus(void);

/**
 * Enables or disables the specified FLASH interrupts.
 *
 * @param FLASH_IT specifies the FLASH interrupt sources to be enabled or disabled.
 *    FLASH_IT_ERROR - FLASH Error Interrupt
 *    FLASH_IT_EOP - FLASH end of operation Interrupt
 * @param NewState new state of the specified Flash interrupts(ENABLE or DISABLE).
 */
void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState);

/**
 * Checks whether the specified FLASH flag is set or not.
 *
 * @param FLASH_FLAG specifies the FLASH flag to check.
 *    FLASH_FLAG_BSY - FLASH Busy flag
 *    FLASH_FLAG_WRPRTERR - FLASH Write protected error flag
 *    FLASH_FLAG_EOP - FLASH End of Operation flag
 *    FLASH_FLAG_OPTERR - FLASH Option Byte error flag
 *
 * @return The new state of FLASH_FLAG (SET or RESET).
 */
FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG);

/**
 * Clears the FLASH's pending flags.
 *
 * @param FLASH_FLAG specifies the FLASH flags to clear.
 *    FLASH_FLAG_WRPRTERR - FLASH Write protected error flag
 *    FLASH_FLAG_EOP - FLASH End of Operation flag
 */
void FLASH_ClearFlag(uint32_t FLASH_FLAG);

/**
 * Returns the FLASH Status.
 *
 * @return The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 * FLASH_ERROR_WRP or FLASH_COMPLETE.
 */
FLASH_Status FLASH_GetStatus(void);

/**
 * Waits for a Flash operation to complete or a TIMEOUT to occur.
 *
 * @param Timeout FLASH programming Timeout
 *
 * @return The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 * FLASH_ERROR_WRP or FLASH_COMPLETE.
 */
FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout);

/**
 * Unlocks the Fast Program Erase Mode.
 */
void FLASH_Unlock_Fast(void);

/**
 * Unlocks the Fast Program Erase Mode.
 */
void FLASH_Lock_Fast(void);

/**
 * Flash Buffer reset.
 */
void FLASH_BufReset(void);

/**
 * Flash Buffer load(4Byte).
 *
 * @param Address specifies the address to be programmed.
 * @param Data0 specifies the data0 to be programmed.
 */
void FLASH_BufLoad(uint32_t Address, uint32_t Data0);

/**
 * Erases a specified FLASH page (1page = 64Byte).
 *
 * @param Page_Address The page address to be erased.
 */
void FLASH_ErasePage_Fast(uint32_t Page_Address);

/**
 * Program a specified FLASH page (1page = 64Byte).
 *
 * @param Page_Address The page address to be programed.
 */
void FLASH_ProgramPage_Fast(uint32_t Page_Address);

/**
 * Start mode after system reset.
 *
 * @param Mode Start mode.
 *    Start_Mode_USER - USER start after system reset
 */
void SystemReset_StartMode(uint32_t Mode);


#ifdef __cplusplus
}
#endif

#endif /* __CH32V00x_FLASH_H */
