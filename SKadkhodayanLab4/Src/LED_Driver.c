/*
 * LED_Driver.c
 *
 *  Created on: Sep 12, 2024
 *      Author: seank
 */

#include "LED_Driver.h"

void LED_Init(uint8_t LEDPin) {

	// Instantiate a GPIO_PinConfig_t struct
	GPIO_PinConfig_t GPIOConfig = {0};

	switch(LEDPin) {

	// Configure for Red LED
	case LED_RED_PIN:

		// Configure the GPIO struct to drive the red LED
		GPIOConfig.PinNumber = LED_RED_PIN;
		GPIOConfig.PinMode = GPIO_PinMode_GPOut;
		GPIOConfig.PinSpeed = GPIO_Speed_Medium;
		GPIOConfig.PinPuPdControl = GPIO_PUPDR_None;

		// Initialize the GPIO Pin
		GPIO_Init(GPIOG, GPIOConfig);

		break;

	// Configure for Green LED
	case LED_GREEN_PIN:

		// Configure the GPIO struct to drive the green LED
		GPIOConfig.PinNumber = LED_GREEN_PIN;
		GPIOConfig.PinMode = GPIO_PinMode_GPOut;
		GPIOConfig.PinSpeed = GPIO_Speed_Medium;
		GPIOConfig.PinPuPdControl = GPIO_PUPDR_None;

		// Initialize the GPIO Pin
		GPIO_Init(GPIOG, GPIOConfig);

		break;
	}
}

void ToggleLED(uint8_t LEDPin) {

	switch(LEDPin) {

	// Toggle for Red LED
	case LED_RED_PIN:

		// Toggle Red Pin
		GPIO_ToggleOutputPin(GPIOG, LED_RED_PIN);

		break;

	case LED_GREEN_PIN:

		// Toggle Green Pin
		GPIO_ToggleOutputPin(GPIOG, LED_GREEN_PIN);

		break;
	}
}

void TurnOffLED(uint8_t LEDPin) {

	switch(LEDPin) {

	// Turn off Red LED
	case LED_RED_PIN:

		// Turn off Red Pin
		GPIO_WriteToOutputPin(GPIOG, LED_RED_PIN, 0);

		break;

	case LED_GREEN_PIN:

		// Turn off Green Pin
		GPIO_WriteToOutputPin(GPIOG, LED_GREEN_PIN, 0);

		break;
	}
}

void TurnOnLED(uint8_t LEDPin) {

	switch(LEDPin) {

	// Turn on Red LED
	case LED_RED_PIN:

		// Turn on Red Pin
		GPIO_WriteToOutputPin(GPIOG, LED_RED_PIN, 1);

		break;

	case LED_GREEN_PIN:

		// Turn on Green Pin
		GPIO_WriteToOutputPin(GPIOG, LED_GREEN_PIN, 1);

		break;
	}
}

void LED_Timer2_Init() {

	// Instantiate a GPTimer_Config_t struct
	GPTimer_Config_t TimerConfig = {0};

	// Configure the Timer 2 struct
	TimerConfig.auto_reload_value = TIM2_ARR_VALUE;
	TimerConfig.clock_division = TIM_CKD_1X;
	TimerConfig.prescaler = TIM2_PSC_VALUE;
	TimerConfig.center_aligned_mode = TIM_CMS_EDGE_ALIGNED;
	TimerConfig.auto_reload_preload = TIM_ARPE_NO_BUFFER;
	TimerConfig.direction = TIM_DIR_UP;
	TimerConfig.update_interrupt_enable = TIM_UIE_ENABLE;
	TimerConfig.one_pulse_mode = TIM_OPM_NOT_STOPPED;

	// Enable Clock for Timer 2
	Timer_Clock_Control(TIM2, ENABLE);

	// Initialize Timer 2
	Timer_Init(TIM2, &TimerConfig);

	// Enable Timer 2 Interrupt
	NVIC_Enable_Interrupt(TIM2_IRQ_NUM);
}

void LED_Timer2_Start() {

	// Start Timer 2
	Timer_Start(TIM2);
}

void LED_Timer2_Stop() {

	// Stop Timer 2
	Timer_Stop(TIM2);
}

void LED_Reset_Timer2() {

	// Reset Timer 2
	Timer_Reset(TIM2);
}

void LED_Timer5_Init() {

	// Instantiate a GPTimer_Config_t struct
	GPTimer_Config_t TimerConfig = {0};

	// Configure the Timer 5 struct
	TimerConfig.auto_reload_value = TIM2_ARR_VALUE;
	TimerConfig.clock_division = TIM_CKD_1X;
	TimerConfig.prescaler = TIM_NO_PRESCALER;
	TimerConfig.center_aligned_mode = TIM_CMS_EDGE_ALIGNED;
	TimerConfig.auto_reload_preload = TIM_ARPE_NO_BUFFER;
	TimerConfig.direction = TIM_DIR_UP;
	TimerConfig.update_interrupt_enable = TIM_UIE_ENABLE;
	TimerConfig.one_pulse_mode = TIM_OPM_NOT_STOPPED;

	// Enable Clock for Timer 5
	Timer_Clock_Control(TIM5, ENABLE);

	// Initialize Timer 5
	Timer_Init(TIM5, &TimerConfig);

	// Enable Timer 5 Interrupt
	NVIC_Enable_Interrupt(TIM5_IRQ_NUM);
}

void LED_Timer5_Start() {

	// Start Timer 5
	Timer_Start(TIM5);
}

void LED_Timer5_Stop() {

	// Stop Timer 5
	Timer_Stop(TIM5);
}

void LED_Reset_Timer5() {

	// Reset Timer 5
	Timer_Reset(TIM5);
}

uint32_t LED_Timer5_Get_Auto_Reload_Value(GPTIMR_RegDef_t * TimerX) {

	// Return the auto-reload value of Timer 5
	return TimerX->ARR;
}

uint32_t LED_Timer5_Get_Value(GPTIMR_RegDef_t * TimerX) {

	// Return the value of Timer 5
	return TimerX->CNT;
}

void LED_Timer5_Reconfigure_Auto_Reload(GPTIMR_RegDef_t * TimerX, uint32_t AutoReloadValue) {

	// Reconfigure the auto-reload value of Timer 5
	TimerX->ARR = AutoReloadValue;
}
