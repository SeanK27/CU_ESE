/*
 * GPIO_Driver.h
 *
 *  Created on: Sep 12, 2024
 *      Author: seank
 */

#ifndef GPIO_DRIVER_H_
#define GPIO_DRIVER_H_

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
