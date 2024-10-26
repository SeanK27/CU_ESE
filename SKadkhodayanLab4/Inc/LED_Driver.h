/*
 * LED_Driver.h
 *
 *  Created on: Sep 12, 2024
 *      Author: seank
 */

#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

#include "STM32F429i.h"
#include "Timer_Driver.h"
#include "GPIO_Driver.h"

#define LED_RED_PIN 14
#define LED_GREEN_PIN 13

// Initializes the specified LED
void LED_Init(uint8_t LEDPin);

// Toggles the specified LED
void ToggleLED(uint8_t LEDPin);

// Turn off specified LED
void TurnOffLED(uint8_t LEDPin);

// Turn on the specified LED
void TurnOnLED(uint8_t LEDPin);

// Initialize timer2 for the LED
void LED_Timer2_Init();

// Starts timer2 for the LED
void LED_Timer2_Start();

// Stops timer2 for the LED
void LED_Timer2_Stop();

// Resets timer2 for the LED
void LED_Timer2_Reset();

// Initialize timer5 for the LED
void LED_Timer5_Init();

// Starts timer5 for the LED
void LED_Timer5_Start();

// Stops timer5 for the LED
void LED_Timer5_Stop();

// Resets timer5 for the LED
void LED_Timer5_Reset();

// Returns auto-reload value of timer5
uint32_t LED_Timer5_Get_Auto_Reload_Value(GPTIMR_RegDef_t * TimerX);

// Returns value of timer5
uint32_t LED_Timer5_Get_Value(GPTIMR_RegDef_t * TimerX);

// Reconfigures auto reload of timer5 for the LED
void LED_Timer5_Reconfigure_Auto_Reload(GPTIMR_RegDef_t * TimerX, uint32_t AutoReloadValue);

// Start Timer5
void LED_Timer5_Start_Specific(GPTIMR_RegDef_t * TimerX, uint32_t startValue);

#endif /* LED_DRIVER_H_ */
