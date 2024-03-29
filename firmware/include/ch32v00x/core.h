#ifndef __CORE_RISCV_H__
#define __CORE_RISCV_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#ifdef __cplusplus
  #define     __I     volatile                /*!< defines 'read only' permissions      */
#else
  #define     __I     volatile const          /*!< defines 'read only' permissions     */
#endif
#define     __O     volatile                  /*!< defines 'write only' permissions     */
#define     __IO    volatile                  /*!< defines 'read / write' permissions   */

/* Standard Peripheral Library old types (maintained for legacy purpose) */
typedef __I uint32_t vuc32;  /* Read Only */
typedef __I uint16_t vuc16;  /* Read Only */
typedef __I uint8_t vuc8;   /* Read Only */

typedef const uint32_t uc32;  /* Read Only */
typedef const uint16_t uc16;  /* Read Only */
typedef const uint8_t uc8;   /* Read Only */

typedef __I int32_t vsc32;  /* Read Only */
typedef __I int16_t vsc16;  /* Read Only */
typedef __I int8_t vsc8;   /* Read Only */

typedef const int32_t sc32;  /* Read Only */
typedef const int16_t sc16;  /* Read Only */
typedef const int8_t sc8;   /* Read Only */

typedef __IO uint32_t  vu32;
typedef __IO uint16_t vu16;
typedef __IO uint8_t  vu8;

typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;

typedef __IO int32_t  vs32;
typedef __IO int16_t  vs16;
typedef __IO int8_t   vs8;

typedef int32_t  s32;
typedef int16_t s16;
typedef int8_t  s8;

typedef enum { NoREADY = 0, READY = !NoREADY } ErrorStatus;
typedef enum { DISABLE = 0, ENABLE = !DISABLE } FunctionalState;
typedef enum { RESET = 0, SET = !RESET } FlagStatus, ITStatus;

#define RV_STATIC_INLINE  static inline

/**
 * memory mapped structure for Program Fast Interrupt Controller (PFIC)
 */
typedef struct PFIC_Type {
    __I  uint32_t ISR[8];
    __I  uint32_t IPR[8];
    __IO uint32_t ITHRESDR;
    __IO uint32_t RESERVED;
    __IO uint32_t CFGR;
    __I  uint32_t GISR;
    __IO uint8_t VTFIDR[4];
    uint8_t RESERVED0[12];
    __IO uint32_t VTFADDR[4];
    uint8_t RESERVED1[0x90];
    __O  uint32_t IENR[8];
    uint8_t RESERVED2[0x60];
    __O  uint32_t IRER[8];
    uint8_t RESERVED3[0x60];
    __O  uint32_t IPSR[8];
    uint8_t RESERVED4[0x60];
    __O  uint32_t IPRR[8];
    uint8_t RESERVED5[0x60];
    __IO uint32_t IACTR[8];
    uint8_t RESERVED6[0xE0];
    __IO uint8_t IPRIOR[256];
    uint8_t RESERVED7[0x810];
    __IO uint32_t SCTLR;
} PFIC_Type;

/**
 * memory mapped structure for SysTick
 */
typedef struct SysTick_Type {
    __IO uint32_t CTLR;
    __IO uint32_t SR;
    __IO uint32_t CNT;
    uint32_t RESERVED0;
    __IO uint32_t CMP;
    uint32_t RESERVED1;
} SysTick_Type;

#define PFIC            ((PFIC_Type *) 0xE000E000 )
#define NVIC            PFIC
#define NVIC_KEY1       ((uint32_t)0xFA050000)
#define	NVIC_KEY2	    ((uint32_t)0xBCAF0000)
#define	NVIC_KEY3		((uint32_t)0xBEEF0000)
#define SysTick         ((SysTick_Type *) 0xE000F000)


/**
 * Enable Global Interrupt
 */
RV_STATIC_INLINE void __enable_irq() {
  uint32_t result;

  __asm volatile("csrr %0," "mstatus": "=r"(result));
  result |= 0x88;
  __asm volatile ("csrw mstatus, %0" : : "r" (result) );
}

/**
 * Disable Global Interrupt
 */
RV_STATIC_INLINE void __disable_irq() {
  uint32_t result;

  __asm volatile("csrr %0," "mstatus": "=r"(result));
  result &= ~0x88;
  __asm volatile ("csrw mstatus, %0" : : "r" (result) );
}

/**
 * nop
 */
RV_STATIC_INLINE void __NOP() {
  __asm volatile ("nop");
}

/**
 * Wait for Interrupt
 */
__attribute__((always_inline)) RV_STATIC_INLINE void __WFI(void)
{
  NVIC->SCTLR &= ~(1<<3);   // wfi
  asm volatile ("wfi");
}

/**
 * Wait for Events
 */
__attribute__((always_inline)) RV_STATIC_INLINE void __WFE(void)
{
  uint32_t t;

  t = NVIC->SCTLR;
  NVIC->SCTLR |= (1<<3)|(1<<5);     // (wfi->wfe)+(__sev)
  NVIC->SCTLR = (NVIC->SCTLR & ~(1<<5)) | ( t & (1<<5));
  asm volatile ("wfi");
  asm volatile ("wfi");
}

/**
 * Return the Machine Status Register
 *
 * @return  mstatus value
 */
uint32_t __get_MSTATUS(void);

/**
 * Set the Machine Status Register
 *
 * @param value set mstatus value
 */
void __set_MSTATUS(uint32_t value);

/**
 * Return the Machine ISA Register
 *
 * @return  misa value
 */
uint32_t __get_MISA(void);

/**
 * Set the Machine ISA Register
 *
 * @param value set misa value
 */
void __set_MISA(uint32_t value);

/**
 * Return the Machine Trap-Vector Base-Address Register
 *
 * @return  mtvec value
 */
uint32_t __get_MTVEC(void);

/**
 * Set the Machine Trap-Vector Base-Address Register
 *
 * @param value set mtvec value
 */
void __set_MTVEC(uint32_t value);

/**
 * Return the Machine Seratch Register
 *
 * @return  mscratch value
 */
uint32_t __get_MSCRATCH(void);

/**
 * Set the Machine Seratch Register
 *
 * @param value set mscratch value
 */
void __set_MSCRATCH(uint32_t value);

/**
 * Return the Machine Exception Program Register
 *
 * @return  mepc value
 */
uint32_t __get_MEPC(void);

/**
 * Set the Machine Exception Program Register
 */
void __set_MEPC(uint32_t value);

/**
 * Return the Machine Cause Register
 *
 * @return  mcause value
 */
uint32_t __get_MCAUSE(void);

/**
 * Set the Machine Cause Register
 */
void __set_MCAUSE(uint32_t value);

/**
 * Return Vendor ID Register
 *
 * @return  mvendorid value
 */
uint32_t __get_MVENDORID(void);

/**
 * Return Machine Architecture ID Register
 *
 * @return  marchid value
 */
uint32_t __get_MARCHID(void);

/**
 * Return Machine Implementation ID Register
 *
 * @return  mimpid value
 */
uint32_t __get_MIMPID(void);

/**
 * Return Hart ID Register
 *
 * @return  mhartid value
 */
uint32_t __get_MHARTID(void);

/**
 * Return SP Register
 *
 * @return  SP value
 */
uint32_t __get_SP(void);

#ifdef __cplusplus
}
#endif

#endif/* __CORE_RISCV_H__ */
