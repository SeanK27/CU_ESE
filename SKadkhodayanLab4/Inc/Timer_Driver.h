/*
 * Timer_Driver.h
 *
 *  Created on: Oct 15, 2024
 *      Author: seank
 */

#ifndef TIMER_DRIVER_H_
#define TIMER_DRIVER_H_

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
