/*
 * STM32F429i.h
 *
 *  Created on: Sep 12, 2024
 *      Author: seank
 */

#ifndef STM32F429I_H_
#define STM32F429I_H_

#include <stdint.h>
#include <stdbool.h>

// Control Macros
#define ACTIVE 1
#define NON_ACTIVE 0
#define SET 1
#define RESET 0
#define ENABLE SET
#define DISABLE RESET

// Interrupt Macros
#define NVIC_ISER0 ((volatile uint32_t*) 0xE000E100)
#define NVIC_ICER0 ((volatile uint32_t*) 0xE000E180)
#define NVIC_ISPR0 ((volatile uint32_t*) 0xE000E200)
#define NVIC_ICPR0 ((volatile uint32_t*) 0xE000E280)

#define NVIC_ISER1 ((volatile uint32_t*) 0xE000E104)
#define NVIC_ICER1 ((volatile uint32_t*) 0xE000E184)
#define NVIC_ISPR1 ((volatile uint32_t*) 0xE000E204)
#define NVIC_ICPR1 ((volatile uint32_t*) 0xE000E284)

typedef struct // GPIO_RegDef_t struct
{
    volatile uint32_t MODER;        // GPIO port mode register               Address offset: 0x00
    volatile uint32_t OTYPER;       // GPIO port output type register        Address offset: 0x04
    volatile uint32_t OSPEEDR;      // GPIO port output speed register       Address offset: 0x08
    volatile uint32_t PUPDR;        // GPIO port pull-up/pull-down register  Address offset: 0x0C
    volatile uint32_t IDR;          // GPIO port input data register         Address offset: 0x10
    volatile uint32_t ODR;          // GPIO port output data register        Address offset: 0x14
    volatile uint32_t BSRR;         // GPIO port bit set/reset register      Address offset: 0x18
    volatile uint32_t LCKR;         // GPIO port configuration lock register Address offset: 0x1C
    volatile uint32_t AFR[2];       // GPIO alternate function registers     Address offset: 0x20-0x24
} GPIO_RegDef_t;

typedef struct // RCC_RegDef_t struct
{
    volatile uint32_t CR;          // 0x00: Clock control register
    volatile uint32_t PLLCFGR;     // 0x04: PLL configuration register
    volatile uint32_t CFGR;        // 0x08: Clock configuration register
    volatile uint32_t CIR;         // 0x0C: Clock interrupt register
    volatile uint32_t AHB1RSTR;    // 0x10: AHB1 peripheral reset register
    volatile uint32_t AHB2RSTR;    // 0x14: AHB2 peripheral reset register
    volatile uint32_t AHB3RSTR;    // 0x18: AHB3 peripheral reset register
    uint32_t RESERVED0;            // 0x1C: Reserved, 0x1C
    volatile uint32_t APB1RSTR;    // 0x20: APB1 peripheral reset register
    volatile uint32_t APB2RSTR;    // 0x24: APB2 peripheral reset register
    uint32_t RESERVED1[2];         // 0x28 - 0x2C: Reserved
    volatile uint32_t AHB1ENR;     // 0x30: AHB1 peripheral clock enable register
    volatile uint32_t AHB2ENR;     // 0x34: AHB2 peripheral clock enable register
    volatile uint32_t AHB3ENR;     // 0x38: AHB3 peripheral clock enable register
    uint32_t RESERVED2;            // 0x3C: Reserved, 0x3C
    volatile uint32_t APB1ENR;     // 0x40: APB1 peripheral clock enable register
    volatile uint32_t APB2ENR;     // 0x44: APB2 peripheral clock enable register
    uint32_t RESERVED3[2];         // 0x48 - 0x4C: Reserved
    volatile uint32_t AHB1LPENR;   // 0x50: AHB1 peripheral clock enable in low-power mode register
    volatile uint32_t AHB2LPENR;   // 0x54: AHB2 peripheral clock enable in low-power mode register
    volatile uint32_t AHB3LPENR;   // 0x58: AHB3 peripheral clock enable in low-power mode register
    uint32_t RESERVED4;            // 0x5C: Reserved, 0x5C
    volatile uint32_t APB1LPENR;   // 0x60: APB1 peripheral clock enable in low-power mode register
    volatile uint32_t APB2LPENR;   // 0x64: APB2 peripheral clock enable in low-power mode register
    uint32_t RESERVED5[2];         // 0x68 - 0x6C: Reserved, 0x68 - 0x6C
    volatile uint32_t BDCR;        // 0x70: Backup domain control register
    volatile uint32_t CSR;         // 0x74: Clock control & status register
    uint32_t RESERVED6[2];         // 0x78 - 0x7C: Reserved
    volatile uint32_t SSCGR;       // 0x80: Spread spectrum clock generation register
    volatile uint32_t PLLI2SCFGR;  // 0x84: PLLI2S configuration register
    volatile uint32_t PLLSAICFGR;  // 0x88: PLLSAI configuration register
    volatile uint32_t DCKCFGR;     // 0x8C: Dedicated clocks configuration register
} RCC_RegDef_t;

typedef struct {
    volatile uint32_t MEMRMP;       // 0x00: SYSCFG memory remap register
    volatile uint32_t PMC;          // 0x04: SYSCFG peripheral mode configuration register
    volatile uint32_t EXTICR[4];    // 0x08 - 0x14: SYSCFG external interrupt configuration register 1-4
    uint32_t RESERVED0[2];          // 0x18 - 0x1C: Reserved
    volatile uint32_t CMPCR;        // 0x20: Compensation cell control register
} SYSFG_RegDef_t;

typedef struct {
    volatile uint32_t IMR;          // 0x00: Interrupt mask register
    volatile uint32_t EMR;          // 0x04: Event mask register
    volatile uint32_t RTSR;         // 0x08: Rising trigger selection register
    volatile uint32_t FTSR;         // 0x0C: Falling trigger selection register
    volatile uint32_t SWIER;        // 0x10: Software interrupt event register
    volatile uint32_t PR;           // 0x14: Pending register
} EXTI_RegDef_t;

#define AHB1_BASE_ADDR 0x40020000					// AHB1 peripheral base address
#define APB2_BASE_ADDR 0x40010000					// APB2 peripheral base address
#define RCC_BASE_ADDR (AHB1_BASE_ADDR + 0x3800)     // RCC peripheral base address
#define GPIOG_BASE_ADDR (AHB1_BASE_ADDR + 0x1800)	// GPIOG peripheral base address
#define GPIOA_BASE_ADDR (AHB1_BASE_ADDR + 0x0000)	// GPIOA peripheral base address (For USER Button)
#define GPIOA ((GPIO_RegDef_t*) GPIOA_BASE_ADDR)	// Create a pointer to the base address of GPIOA
#define GPIOG ((GPIO_RegDef_t*) GPIOG_BASE_ADDR)	// Create a pointer to the base address of GPIOG
#define RCC ((RCC_RegDef_t *) RCC_BASE_ADDR) 		// Create a pointer to the base address of the RCC register

// GPIO AHB1ENR register bit definitions
#define GPIOA_AHB1ENR_BIT 0
#define GPIOG_AHB1ENR_BIT 6

// Enable and disable GPIOG clock macros
#define ENABLE_AHB1ENR_CLOCK(inputBit) (RCC->AHB1ENR |= (1 << (inputBit)))
#define DISABLE_AHB1ENR_CLOCK(inputBit) (RCC->AHB1ENR &= ~(1 << (inputBit)))

#define SYSFG_BASE_ADDR (APB2_BASE_ADDR + 0x3800)	// System configuration controller base address
#define EXTI_BASE_ADDR (APB2_BASE_ADDR + 0x3C00)	// External interrupt/event controller base address

#define SYSCFG ((SYSFG_RegDef_t *) SYSFG_BASE_ADDR)	// Create a pointer to the base address of the SYSCFG register
#define EXTI ((EXTI_RegDef_t *) EXTI_BASE_ADDR)		// Create a pointer to the base address of the EXTI register

#define ENABLE_SYSCFG_CLOCK() (RCC->APB2ENR |= (1 << 14))	// Enable the SYSCFG clock
#define DISABLE_SYSCFG_CLOCK() (RCC->APB2ENR &= ~(1 << 14))	// Disable the SYSCFG clock



#endif /* STM32F429I_H_ */













