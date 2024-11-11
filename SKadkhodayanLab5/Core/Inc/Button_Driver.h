/*
 * Button_Driver.h
 *
 *  Created on: Sep 28, 2024
 *      Author: seank
 */

#ifndef BUTTON_DRIVER_H_
#define BUTTON_DRIVER_H_

// Include Microcontroller specifics
#include "stm32f4xx_hal.h"
#include "InterruptControl.h"
#include <stdbool.h>

// User Button is on PA0 (Port A, Pin 0)
#define USER_BUTTON_PORT 0          // Port A is index 0 in the AHB1ENR register
#define USER_BUTTON_PIN 0           // Pin 0

#define USER_BUTTON_PRESSED 1       // Button is pressed when the pin is 0 due to internal Pull Up
#define USER_BUTTON_UNPRESSED 0     // Button is unpressed when the pin is 1 due to internal Pull Up

// Function to initialize the user button given a GPIO Config and Pin Config
void User_Button_Init();

// Function to enable the clock given a GPIO Config and Pin Config
void User_Button_Enable_Clock();

// Function that returns the state of the button (Pressed or Unpressed)
bool User_Button_Is_Pressed();

// Function to initialize button for "interrupt mode"
void User_Button_Interrupt_Enable();


#endif /* BUTTON_DRIVER_H_ */
