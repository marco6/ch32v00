#include <ch32v00x/flash.h>

/* Flash Access Control Register bits */
#define ACR_LATENCY_Mask           ((uint32_t)0x00000038)

/* Flash Control Register bits */
#define CR_PG_Set                  ((uint32_t)0x00000001)
#define CR_PG_Reset                ((uint32_t)0xFFFFFFFE)
#define CR_PER_Set                 ((uint32_t)0x00000002)
#define CR_PER_Reset               ((uint32_t)0xFFFFFFFD)
#define CR_MER_Set                 ((uint32_t)0x00000004)
#define CR_MER_Reset               ((uint32_t)0xFFFFFFFB)
#define CR_OPTPG_Set               ((uint32_t)0x00000010)
#define CR_OPTPG_Reset             ((uint32_t)0xFFFFFFEF)
#define CR_OPTER_Set               ((uint32_t)0x00000020)
#define CR_OPTER_Reset             ((uint32_t)0xFFFFFFDF)
#define CR_STRT_Set                ((uint32_t)0x00000040)
#define CR_LOCK_Set                ((uint32_t)0x00000080)
#define CR_PAGE_PG                 ((uint32_t)0x00010000)
#define CR_PAGE_ER                 ((uint32_t)0x00020000)
#define CR_BUF_LOAD                ((uint32_t)0x00040000)
#define CR_BUF_RST                 ((uint32_t)0x00080000)

/* FLASH Status Register bits */
#define SR_BSY                     ((uint32_t)0x00000001)
#define SR_WRPRTERR                ((uint32_t)0x00000010)
#define SR_EOP                     ((uint32_t)0x00000020)

/* FLASH Mask */
#define RDPRT_Mask                 ((uint32_t)0x00000002)
#define WRP0_Mask                  ((uint32_t)0x000000FF)
#define WRP1_Mask                  ((uint32_t)0x0000FF00)
#define WRP2_Mask                  ((uint32_t)0x00FF0000)
#define WRP3_Mask                  ((uint32_t)0xFF000000)

/* FLASH Keys */
#define RDP_Key                    ((uint16_t)0x00A5)
#define FLASH_KEY1                 ((uint32_t)0x45670123)
#define FLASH_KEY2                 ((uint32_t)0xCDEF89AB)

/* FLASH BANK address */
#define FLASH_BANK1_END_ADDRESS    ((uint32_t)0x807FFFF)

/* Delay definition */
#define EraseTimeout               ((uint32_t)0x000B0000)
#define ProgramTimeout             ((uint32_t)0x00002000)

/* Flash Program Vaild Address */
#define ValidAddrStart             (FLASH_BASE)
#define ValidAddrEnd               (FLASH_BASE + 0x4000)

void FLASH_SetLatency(uint32_t FLASH_Latency)
{
    uint32_t tmpreg = 0;

    tmpreg = FLASH->ACTLR;
    tmpreg &= ACR_LATENCY_Mask;
    tmpreg |= FLASH_Latency;
    FLASH->ACTLR = tmpreg;
}

void FLASH_Unlock(void)
{
    /* Authorize the FPEC of Bank1 Access */
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;
}

void FLASH_Lock(void)
{
    FLASH->CTLR |= CR_LOCK_Set;
}

FLASH_Status FLASH_ErasePage(uint32_t Page_Address)
{
    FLASH_Status status = FLASH_COMPLETE;

    status = FLASH_WaitForLastOperation(EraseTimeout);

    if(status == FLASH_COMPLETE)
    {
        FLASH->CTLR |= CR_PER_Set;
        FLASH->ADDR = Page_Address;
        FLASH->CTLR |= CR_STRT_Set;

        status = FLASH_WaitForLastOperation(EraseTimeout);

        FLASH->CTLR &= CR_PER_Reset;
    }

    return status;
}

FLASH_Status FLASH_EraseAllPages(void)
{
    FLASH_Status status = FLASH_COMPLETE;

    status = FLASH_WaitForLastOperation(EraseTimeout);
    if(status == FLASH_COMPLETE)
    {
        FLASH->CTLR |= CR_MER_Set;
        FLASH->CTLR |= CR_STRT_Set;

        status = FLASH_WaitForLastOperation(EraseTimeout);

        FLASH->CTLR &= CR_MER_Reset;
    }

    return status;
}

FLASH_Status FLASH_EraseOptionBytes(void)
{
    uint16_t rdptmp = RDP_Key;

    FLASH_Status status = FLASH_COMPLETE;
    if(FLASH_GetReadOutProtectionStatus() != RESET)
    {
        rdptmp = 0x00;
    }
    status = FLASH_WaitForLastOperation(EraseTimeout);
    if(status == FLASH_COMPLETE)
    {
        FLASH->OBKEYR = FLASH_KEY1;
        FLASH->OBKEYR = FLASH_KEY2;

        FLASH->CTLR |= CR_OPTER_Set;
        FLASH->CTLR |= CR_STRT_Set;
        status = FLASH_WaitForLastOperation(EraseTimeout);

        if(status == FLASH_COMPLETE)
        {
            FLASH->CTLR &= CR_OPTER_Reset;
            FLASH->CTLR |= CR_OPTPG_Set;
            OB->RDPR = (uint16_t)rdptmp;
            status = FLASH_WaitForLastOperation(ProgramTimeout);

            if(status != FLASH_TIMEOUT)
            {
                FLASH->CTLR &= CR_OPTPG_Reset;
            }
        }
        else
        {
            if(status != FLASH_TIMEOUT)
            {
                FLASH->CTLR &= CR_OPTPG_Reset;
            }
        }
    }
    return status;
}

FLASH_Status FLASH_ProgramWord(uint32_t Address, uint32_t Data)
{
    FLASH_Status  status = FLASH_COMPLETE;
    __IO uint32_t tmp = 0;

    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if(status == FLASH_COMPLETE)
    {
        FLASH->CTLR |= CR_PG_Set;

        *(__IO uint16_t *)Address = (uint16_t)Data;
        status = FLASH_WaitForLastOperation(ProgramTimeout);

        if(status == FLASH_COMPLETE)
        {
            tmp = Address + 2;
            *(__IO uint16_t *)tmp = Data >> 16;
            status = FLASH_WaitForLastOperation(ProgramTimeout);
            FLASH->CTLR &= CR_PG_Reset;
        }
        else
        {
            FLASH->CTLR &= CR_PG_Reset;
        }
    }

    return status;
}

FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data)
{
    FLASH_Status status = FLASH_COMPLETE;

    status = FLASH_WaitForLastOperation(ProgramTimeout);
    if(status == FLASH_COMPLETE)
    {
        FLASH->CTLR |= CR_PG_Set;
        *(__IO uint16_t *)Address = Data;
        status = FLASH_WaitForLastOperation(ProgramTimeout);
        FLASH->CTLR &= CR_PG_Reset;
    }

    return status;
}

FLASH_Status FLASH_ProgramOptionByteData(uint32_t Address, uint8_t Data)
{
    FLASH_Status status = FLASH_COMPLETE;
    status = FLASH_WaitForLastOperation(ProgramTimeout);
    if(status == FLASH_COMPLETE)
    {
        FLASH->OBKEYR = FLASH_KEY1;
        FLASH->OBKEYR = FLASH_KEY2;
        FLASH->CTLR |= CR_OPTPG_Set;
        *(__IO uint16_t *)Address = Data;
        status = FLASH_WaitForLastOperation(ProgramTimeout);
        if(status != FLASH_TIMEOUT)
        {
            FLASH->CTLR &= CR_OPTPG_Reset;
        }
    }

    return status;
}

FLASH_Status FLASH_EnableWriteProtection(uint32_t FLASH_Pages)
{
    uint16_t WRP0_Data = 0xFFFF, WRP1_Data = 0xFFFF;

    FLASH_Status status = FLASH_COMPLETE;

    FLASH_Pages = (uint32_t)(~FLASH_Pages);
    WRP0_Data = (uint16_t)(FLASH_Pages & WRP0_Mask);
    WRP1_Data = (uint16_t)((FLASH_Pages & WRP1_Mask) >> 8);

    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if(status == FLASH_COMPLETE)
    {
        FLASH->OBKEYR = FLASH_KEY1;
        FLASH->OBKEYR = FLASH_KEY2;
        FLASH->CTLR |= CR_OPTPG_Set;
        if(WRP0_Data != 0xFF)
        {
            OB->WRPR0 = WRP0_Data;
            status = FLASH_WaitForLastOperation(ProgramTimeout);
        }
        if((status == FLASH_COMPLETE) && (WRP1_Data != 0xFF))
        {
            OB->WRPR1 = WRP1_Data;
            status = FLASH_WaitForLastOperation(ProgramTimeout);
        }

        if(status != FLASH_TIMEOUT)
        {
            FLASH->CTLR &= CR_OPTPG_Reset;
        }
    }
    return status;
}

FLASH_Status FLASH_ReadOutProtection(FunctionalState NewState)
{
    FLASH_Status status = FLASH_COMPLETE;
    status = FLASH_WaitForLastOperation(EraseTimeout);
    if(status == FLASH_COMPLETE)
    {
        FLASH->OBKEYR = FLASH_KEY1;
        FLASH->OBKEYR = FLASH_KEY2;
        FLASH->CTLR |= CR_OPTER_Set;
        FLASH->CTLR |= CR_STRT_Set;
        status = FLASH_WaitForLastOperation(EraseTimeout);
        if(status == FLASH_COMPLETE)
        {
            FLASH->CTLR &= CR_OPTER_Reset;
            FLASH->CTLR |= CR_OPTPG_Set;
            if(NewState != DISABLE)
            {
                OB->RDPR = 0x00;
            }
            else
            {
                OB->RDPR = RDP_Key;
            }
            status = FLASH_WaitForLastOperation(EraseTimeout);

            if(status != FLASH_TIMEOUT)
            {
                FLASH->CTLR &= CR_OPTPG_Reset;
            }
        }
        else
        {
            if(status != FLASH_TIMEOUT)
            {
                FLASH->CTLR &= CR_OPTER_Reset;
            }
        }
    }
    return status;
}

FLASH_Status FLASH_UserOptionByteConfig(uint16_t OB_IWDG, uint16_t OB_STOP, uint16_t OB_STDBY, uint16_t OB_RST)
{
    FLASH_Status status = FLASH_COMPLETE;

    FLASH->OBKEYR = FLASH_KEY1;
    FLASH->OBKEYR = FLASH_KEY2;
    status = FLASH_WaitForLastOperation(ProgramTimeout);

    if(status == FLASH_COMPLETE)
    {
        FLASH->CTLR |= CR_OPTPG_Set;

        OB->USER = OB_IWDG | (uint16_t)(OB_STOP | (uint16_t)(OB_STDBY | (uint16_t)(OB_RST | (uint16_t)0xE0)));

        status = FLASH_WaitForLastOperation(ProgramTimeout);
        if(status != FLASH_TIMEOUT)
        {
            FLASH->CTLR &= CR_OPTPG_Reset;
        }
    }
    return status;
}

uint32_t FLASH_GetUserOptionByte(void)
{
    return (uint32_t)(FLASH->OBR >> 2);
}

uint32_t FLASH_GetWriteProtectionOptionByte(void)
{
    return (uint32_t)(FLASH->WPR);
}

FlagStatus FLASH_GetReadOutProtectionStatus(void)
{
    FlagStatus readoutstatus = RESET;
    if((FLASH->OBR & RDPRT_Mask) != (uint32_t)RESET)
    {
        readoutstatus = SET;
    }
    else
    {
        readoutstatus = RESET;
    }
    return readoutstatus;
}

void FLASH_ITConfig(uint32_t FLASH_IT, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        FLASH->CTLR |= FLASH_IT;
    }
    else
    {
        FLASH->CTLR &= ~(uint32_t)FLASH_IT;
    }
}

FlagStatus FLASH_GetFlagStatus(uint32_t FLASH_FLAG)
{
    FlagStatus bitstatus = RESET;

    if(FLASH_FLAG == FLASH_FLAG_OPTERR)
    {
        if((FLASH->OBR & FLASH_FLAG_OPTERR) != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }
    else
    {
        if((FLASH->STATR & FLASH_FLAG) != (uint32_t)RESET)
        {
            bitstatus = SET;
        }
        else
        {
            bitstatus = RESET;
        }
    }
    return bitstatus;
}

void FLASH_ClearFlag(uint32_t FLASH_FLAG)
{
    FLASH->STATR = FLASH_FLAG;
}

FLASH_Status FLASH_GetStatus(void)
{
    FLASH_Status flashstatus = FLASH_COMPLETE;

    if((FLASH->STATR & FLASH_FLAG_BSY) == FLASH_FLAG_BSY)
    {
        flashstatus = FLASH_BUSY;
    }
    else
    {
        if((FLASH->STATR & FLASH_FLAG_WRPRTERR) != 0)
        {
            flashstatus = FLASH_ERROR_WRP;
        }
        else
        {
            flashstatus = FLASH_COMPLETE;
        }
    }
    return flashstatus;
}

/**
 * Returns the FLASH Bank1 Status.
 *
 * @return The returned value can be: FLASH_BUSY, FLASH_ERROR_PG,
 * FLASH_ERROR_WRP or FLASH_COMPLETE.
 */
static FLASH_Status FLASH_GetBank1Status(void) {
    FLASH_Status flashstatus = FLASH_COMPLETE;

    if((FLASH->STATR & FLASH_FLAG_BANK1_BSY) == FLASH_FLAG_BSY)
    {
        flashstatus = FLASH_BUSY;
    }
    else
    {
        if((FLASH->STATR & FLASH_FLAG_BANK1_WRPRTERR) != 0)
        {
            flashstatus = FLASH_ERROR_WRP;
        }
        else
        {
            flashstatus = FLASH_COMPLETE;
        }
    }
    return flashstatus;
}

FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout)
{
    FLASH_Status status = FLASH_COMPLETE;

    status = FLASH_GetBank1Status();
    while((status == FLASH_BUSY) && (Timeout != 0x00))
    {
        status = FLASH_GetBank1Status();
        Timeout--;
    }
    if(Timeout == 0x00)
    {
        status = FLASH_TIMEOUT;
    }
    return status;
}

void FLASH_Unlock_Fast(void)
{
    /* Authorize the FPEC of Bank1 Access */
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;

    /* Fast program mode unlock */
    FLASH->MODEKEYR = FLASH_KEY1;
    FLASH->MODEKEYR = FLASH_KEY2;
}

void FLASH_Lock_Fast(void)
{
    FLASH->CTLR |= CR_LOCK_Set;
}

void FLASH_BufReset(void)
{
    FLASH->CTLR |= CR_PAGE_PG;
    FLASH->CTLR |= CR_BUF_RST;
    while(FLASH->STATR & SR_BSY)
        ;
    FLASH->CTLR &= ~CR_PAGE_PG;
}

void FLASH_BufLoad(uint32_t Address, uint32_t Data0)
{
    if((Address >= ValidAddrStart) && (Address < ValidAddrEnd))
    {
        FLASH->CTLR |= CR_PAGE_PG;
        *(__IO uint32_t *)(Address) = Data0;
        FLASH->CTLR |= CR_BUF_LOAD;
        while(FLASH->STATR & SR_BSY)
            ;
        FLASH->CTLR &= ~CR_PAGE_PG;
    }
}

void FLASH_ErasePage_Fast(uint32_t Page_Address)
{
    if((Page_Address >= ValidAddrStart) && (Page_Address < ValidAddrEnd))
    {
        FLASH->CTLR |= CR_PAGE_ER;
        FLASH->ADDR = Page_Address;
        FLASH->CTLR |= CR_STRT_Set;
        while(FLASH->STATR & SR_BSY)
            ;
        FLASH->CTLR &= ~CR_PAGE_ER;
    }
}

void FLASH_ProgramPage_Fast(uint32_t Page_Address)
{
    if((Page_Address >= ValidAddrStart) && (Page_Address < ValidAddrEnd))
    {
        FLASH->CTLR |= CR_PAGE_PG;
        FLASH->ADDR = Page_Address;
        FLASH->CTLR |= CR_STRT_Set;
        while(FLASH->STATR & SR_BSY)
            ;
        FLASH->CTLR &= ~CR_PAGE_PG;
    }
}

void SystemReset_StartMode(uint32_t Mode)
{
    FLASH_Unlock();

    FLASH->BOOT_MODEKEYR = FLASH_KEY1;
    FLASH->BOOT_MODEKEYR = FLASH_KEY2;

    FLASH->STATR &= ~(1<<14);
    if(Mode == Start_Mode_BOOT){
        FLASH->STATR |= (1<<14);
    }

    FLASH_Lock();
}
