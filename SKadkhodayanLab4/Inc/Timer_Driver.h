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

#define TIM2_ARR_VALUE 100000
#define TIM2_PSC_VALUE 800

// Timer master mode selection (MMS) 3 bits
#define TIM_MMS_RESET 000
#define TIM_MMS_ENABLE 001
#define TIM_MMS_UPDATE 010
#define TIM_MMS_COMPARE_PULSE 011
#define TIM_MMS_COMPARE_OC1REF 100
#define TIM_MMS_COMPARE_OC2REF 101
#define TIM_MMS_COMPARE_OC3REF 110
#define TIM_MMS_COMPARE_OC4REF 111

// Timer clock division selection (CKD) 2 bits
#define TIM_CKD_1X 00
#define TIM_CKD_2X 01
#define TIM_CKD_4X 10
#define TIM_CKD_RESERVED 11

// Timer center-aligned mode selection (CMS) 2 bits
#define TIM_CMS_EDGE_ALIGNED 00
#define TIM_CMS_CENTER_ALIGNED_1 01
#define TIM_CMS_CENTER_ALIGNED_2 10
#define TIM_CMS_CENTER_ALIGNED_3 11

// Timer auto-reload preload enable (ARPE) 1 bit
#define TIM_ARPE_NO_BUFFER false
#define TIM_ARPE_BUFFER true

// Timer counter direction (DIR) 1 bit
#define TIM_DIR_UP false
#define TIM_DIR_DOWN true

// Timer update interrupt enable (UIE) 1 bit
#define TIM_UIE_DISABLE false
#define TIM_UIE_ENABLE true

// Timer one-pulse mode (OPM) 1 bit
#define TIM_OPM_NOT_STOPPED false
#define TIM_OPM_STOPPED true

// Timer prescaler value (PSC) 16 bits
#define TIM_NO_PRESCALER 0

// Offsets
#define CLK_DIV_OFFSET 8
#define CENTER_ALIGNED_OFFSET 5
#define TIM_DIR_OFFSET 4
#define TIM_ARPE_BUFFER_OFFSET 7
#define TIM_OPR_OFFSET 3
#define TIM_UIE_OFFSET 0
#define TIM_COUNTER_ENABLE_OFFSET 0


typedef struct {
    uint32_t auto_reload_value;         // Auto-reload value (ARR) 16 bits
    uint8_t master_mode;                // Master mode selection (MMS) 3 bits
    uint8_t clock_division;             // Clock division selection (CKD) 2 bits
    uint16_t prescaler;                 // Prescaler value (PSC) 16 bits
    uint8_t center_aligned_mode;        // Center-aligned mode selection (CMS) 2 bits
    bool auto_reload_preload;           // Auto-reload preload enable (ARPE) 1 bit
    bool direction;                     // Counter direction (DIR) 1 bit
    bool update_interrupt_enable;       // Update interrupt enable (UIE) 1 bit
    bool one_pulse_mode;                // One-pulse mode (OPM) 1 bit

} GPTimer_Config_t;

// Initialize the timer
void Timer_Init(GPTIMR_RegDef_t * TimerX, GPTimer_Config_t *TimerConfig);

// Enables or disables the timer clock
void Timer_Clock_Control(GPTIMR_RegDef_t * TimerX, uint8_t Status);

// Starts the timer
void Timer_Start(GPTIMR_RegDef_t * TimerX);

// Stops the timer
void Timer_Stop(GPTIMR_RegDef_t * TimerX);

// Resets the timer
void Timer_Reset(GPTIMR_RegDef_t * TimerX);

// Returns the value of the timer
uint32_t Timer_Get_Value(GPTIMR_RegDef_t * TimerX);

// Enables or disables the timer interrupt
void Timer_Interrupt_Control(GPTIMR_RegDef_t * TimerX, uint8_t Status);

// Returns the auto-reload value of the timer
uint32_t Timer_Get_Auto_Reload_Value(GPTIMR_RegDef_t * TimerX);


#endif /* TIMER_DRIVER_H_ */
