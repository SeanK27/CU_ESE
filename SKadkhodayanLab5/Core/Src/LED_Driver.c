/*
 * LED_Driver.c
 *
 *  Created on: Sep 12, 2024
 *      Author: seank
 */

#include "LED_Driver.h"

void LED_Init(uint8_t LEDPin) {

	// Instantiate a GPIO_PinConfig_t struct
	GPIO_InitTypeDef* GPIOConfigH = {0};

	switch(LEDPin) {

	// Configure for Red LED
	case LED_RED_PIN:

		// Configure the GPIO struct to drive the red LED
		GPIOConfigH->Pin = LED_RED_PIN;
		GPIOConfigH->Mode = GPIO_MODE_OUTPUT_PP;
		GPIOConfigH->Speed = GPIO_SPEED_FREQ_MEDIUM;
		GPIOConfigH->Pull = GPIO_NOPULL;

		// Enable Corresponding GPIOG Clock
		__HAL_RCC_GPIOG_CLK_ENABLE();

		// Initialize the GPIO Pin
		HAL_GPIO_Init(GPIOG, GPIOConfigH);

		break;

	// Configure for Green LED
	case LED_GREEN_PIN:

		// Configure the GPIO struct to drive the green LED
		GPIOConfigH->Pin = LED_GREEN_PIN;
		GPIOConfigH->Mode = GPIO_MODE_OUTPUT_PP;
		GPIOConfigH->Speed = GPIO_SPEED_FREQ_MEDIUM;
		GPIOConfigH->Pull = GPIO_NOPULL;

		// Enable Corresponding GPIOG Clock
		__HAL_RCC_GPIOG_CLK_ENABLE();

		// Initialize the GPIO Pin
		HAL_GPIO_Init(GPIOG, GPIOConfigH);

		break;
	}
}

void ToggleLED(uint8_t LEDPin) {

	switch(LEDPin) {

	// Toggle for Red LED
	case LED_RED_PIN:

		// Toggle Red Pin
		HAL_GPIO_TogglePin(GPIOG, LED_RED_PIN);

		break;

	case LED_GREEN_PIN:

		// Toggle Green Pin
		HAL_GPIO_TogglePin(GPIOG, LED_GREEN_PIN);

		break;
	}
}

void TurnOffLED(uint8_t LEDPin) {

	switch(LEDPin) {

	// Turn off Red LED
	case LED_RED_PIN:

		// Turn off Red Pin
		HAL_GPIO_WritePin(GPIOG, LED_RED_PIN, GPIO_PIN_RESET);

		break;

	case LED_GREEN_PIN:

		// Turn off Green Pin
		HAL_GPIO_WritePin(GPIOG, LED_GREEN_PIN, GPIO_PIN_RESET);

		break;
	}
}

void TurnOnLED(uint8_t LEDPin) {

	switch(LEDPin) {

	// Turn on Red LED
	case LED_RED_PIN:

		// Turn on Red Pin
		HAL_GPIO_WritePin(GPIOG, LED_RED_PIN, GPIO_PIN_SET);

		break;

	case LED_GREEN_PIN:

		// Turn on Green Pin
		HAL_GPIO_WritePin(GPIOG, LED_GREEN_PIN, GPIO_PIN_SET);

		break;
	}
}

