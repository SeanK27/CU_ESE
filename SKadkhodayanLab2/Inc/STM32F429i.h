/*
 * STM32F429i.h
 *
 *  Created on: Sep 12, 2024
 *      Author: seank
 */

#ifndef STM32F429I_H_
#define STM32F429I_H_

#include <stdint.h>

// Control Macros
#define ACTIVE 1
#define NON_ACTIVE 0
#define SET 1
#define RESET 0
#define ENABLE SET
#define DISABLE RESET

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

#define RCC_BASE_ADDR 0x40023800				// RCC peripheral base address
#define GPIOG_BASE_ADDR 0x40021800				// GPIOG peripheral base address
#define RCC ((RCC_RegDef_t *) RCC_BASE_ADDR) 	// Create a pointer to the base address of the RCC register

// Enable and disable GPIOG clock macros
#define GPIOG_CLK_ENABLE() (RCC->AHB1ENR |= (1 << 6))
#define GPIOG_CLK_DISABLE() (RCC->AHB1ENR &= ~(1 << 6))

#endif /* STM32F429I_H_ */
