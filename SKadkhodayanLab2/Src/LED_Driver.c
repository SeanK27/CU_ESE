/*
 * LED_Driver.c
 *
 *  Created on: Sep 12, 2024
 *      Author: seank
 */

#include "LED_Driver.h"
#include "GPIO_Driver.h"

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












