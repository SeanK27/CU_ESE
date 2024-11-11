/*
 * LED_Driver.h
 *
 *  Created on: Sep 12, 2024
 *      Author: seank
 */

#ifndef LED_DRIVER_H_
#define LED_DRIVER_H_

#include "stm32f4xx_hal.h"


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

#endif /* LED_DRIVER_H_ */
