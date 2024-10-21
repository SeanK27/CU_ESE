/*
 * Timer_Driver.h
 *
 *  Created on: Oct 15, 2024
 *      Author: seank
 */

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

#include "STM32F429i.h"
#include <stdbool.h>

typedef struct {
    uint32_t auto_reload_value;         // Auto-reload value (ARR) 16 bits
    uint8_t master_mode;                // Master mode selection (MMS) 3 bits
    uint8_t clock_division;             // Clock division selection (CKD) 2 bits
    uint16_t prescaler;                 // Prescaler value (PSC) 16 bits
    uint8_t center_aligned_mode;        // Center-aligned mode selection (CMS) 2 bits
    uint8_t auto_reload_preload;        // Auto-reload preload enable (ARPE) 1 bit
    uint8_t direction;                  // Counter direction (DIR) 1 bit
    uint8_t update_interrupt_enable;    // Update interrupt enable (UIE) 1 bit
    uint8_t one_pulse_mode;             // One-pulse mode (OPM) 1 bit

} GPTimer_Config_t;

// Initialize the timer
void Timer_Init(GPTIMR_RegDef_t TimerX, GPTimer_Config_t *TimerConfig);

// Enables or disables the timer clock
void Timer_Clock_Control(GPTIMR_RegDef_t TimerX, uint8_t Status);

// Starts the timer
void Timer_Start(GPTIMR_RegDef_t TimerX);

// Stops the timer
void Timer_Stop(GPTIMR_RegDef_t TimerX);

// Resets the timer
void Timer_Reset(GPTIMR_RegDef_t TimerX);

// Returns the value of the timer
uint32_t Timer_Get_Value(GPTIMR_RegDef_t TimerX);

// Enables or disables the timer interrupt
void Timer_Interrupt_Control(GPTIMR_RegDef_t TimerX, uint8_t Status);

// Returns the auto-reload value of the timer
uint32_t Timer_Get_Auto_Reload_Value(GPTIMR_RegDef_t TimerX);


#endif /* TIMER_DRIVER_H_ */
