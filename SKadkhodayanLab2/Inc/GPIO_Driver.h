/*
 * GPIO_Driver.h
 *
 *  Created on: Sep 12, 2024
 *      Author: seank
 */

#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

// Include board properties
#include "STM32F429i.h"

// GPIO Pin Macros
#define GPIO_PIN_NUM_0 0
#define GPIO_PIN_NUM_1 1
#define GPIO_PIN_NUM_2 2
#define GPIO_PIN_NUM_3 3
#define GPIO_PIN_NUM_4 4
#define GPIO_PIN_NUM_5 5
#define GPIO_PIN_NUM_6 6
#define GPIO_PIN_NUM_7 7
#define GPIO_PIN_NUM_8 8
#define GPIO_PIN_NUM_9 9
#define GPIO_PIN_NUM_10 10
#define GPIO_PIN_NUM_11 11
#define GPIO_PIN_NUM_12 12
#define GPIO_PIN_NUM_13 13
#define GPIO_PIN_NUM_14 14
#define GPIO_PIN_NUM_15 15
#define GPIO_PIN_NUM_16 16

// GPIO Pin Mode Macros
#define GPIO_PinMode_Input 00
#define GPIO_PinMode_GPOut 01
#define GPIO_PinMode_Alternate 10
#define GPIO_PinMode_Analog 11

// GPIO Output Type Macros
#define GPIO_OPType_PushPull 0
#define GPIO_OPType_OpenDrain 1

// GPIO Speed Macros
#define GPIO_Speed_Low 00
#define GPIO_Speed_Medium 01
#define GPIO_Speed_High 10
#define GPIO_Speed_VeryHigh 11

// GPIO Pull-Up Pull-Down Macros
#define GPIO_PUPDR_None 00
#define GPIO_PUPDR_PU 01
#define GPIO_PUPDR_PD 10
#define GPIO_PUPDR_Reserved 11


typedef struct	// GPIO_PinConfig_t struct
{
uint8_t PinNumber; 		// Pin Number
uint8_t PinMode; 		// Pin Mode
uint8_t OPType; 		// Output Type
uint8_t PinSpeed; 		// Pin Speed
uint8_t PinPuPdControl; // Pin Push up/ Pull Down Control
uint8_t PinAltFunMode; 	// Alternate Function mode
} GPIO_PinConfig_t;


// Initializes the GPIO peripheral based on the configurations provided
void GPIO_Init(GPIO_RegDef_t * GPIOPort, GPIO_PinConfig_t * PinConfig);

// Enables or disables the appropriate clock given the GPIO port
void GPIO_ClockControl(GPIO_RegDef_t * GPIOPort, uint8_t * PinStatus);

// Reads the value from the specified input pin from the specified GPIO port
void GPIO_ReadFromInputPin(GPIO_RegDef_t * GPIOPort, uint8_t * ReadPin);

// Writes to the specified output pin of the provided GPIO port
void GPIO_WriteToOutputPin(GPIO_RegDef_t * GPIOPort, uint8_t * WritePin, uint9_t * WriteVal);

// Toggles the specified pin in the specified GPIO Port
void GPIO_ToggleOutputPin(GPIO_RegDef_t * GPIOPort, uint8_t * TogglePin);



#endif /* GPIO_DRIVER_H_ */
