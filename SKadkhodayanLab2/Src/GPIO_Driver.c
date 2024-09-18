/*
 * GPIO_Driver.c
 *
 *  Created on: Sep 12, 2024
 *      Author: seank
 */

#include "GPIO_Driver.h"

void GPIO_ClockControl(GPIO_RegDef_t * GPIOPort, uint8_t PinStatus) {

	// Check whether pin is already enabled
	if (PinStatus == ENABLE) {

		// Check which GPIO port we will be using
		if (GPIOPort == GPIOG_BASE_ADDR) {
			RCC->AHB1ENR |= (1 << 6);	// Enabling the clock with the 6th bit corresponding to GPIOG
		}
	}

	// Check whether pin is already disabled
	if (PinStatus == DISABLE) {

		// Check which GPIO port we will be using
		if (GPIOPort == GPIOG_BASE_ADDR) {
			RCC->AHB1ENR &= ~(1 << 6);	// Disabling the clock with the 6th bit corresponding to GPIOG
		}
	}
}

void GPIO_WriteToOutputPin(GPIO_RegDef_t * GPIOPort, uint8_t * WritePin, uint8_t WriteVal) {

	// Check the write value
	if (WriteVal == 1) {
		GPIOPort->ODR |= (1 << WritePin); // Write 1 to the ODR register and shift to the proper pin
	}
	if (WriteVal == 0) {
		GPIOPort->ODR &= ~(1 << WritePin); // Write 0 to the ODR register and shift to the proper pin
	}
}

void GPIO_ToggleOutputPin(GPIO_RegDef_t * GPIOPort, uint8_t * TogglePin) {

	// XOR the corresponding bit, which flips it
	GPIOPort->ODR ^= (1 << TogglePin);
}

void GPIO_Init(GPIO_RegDef_t * GPIOPort, GPIO_PinConfig_t PinConfig) {


	///////////////////////////////////MODER Config///////////////////////
	// Create temporary variable
	uint32_t temp;

	// Configure port mode
	temp = PinConfig.PinMode << (2 * PinConfig.PinNumber);

	// Clear bits with ~(b'11) at corresponding pin
    GPIOPort->MODER &= ~(0x3 << (2 * PinConfig->PinNumber));

    // Set appropriate bits with the temp register
    GPIOPort->MODER |= temp;
    //////////////////////////////////////////////////////////////////////

    ///////////////////////////////////SPEED Config///////////////////////

   	// Configure port speed
   	temp = PinConfig.PinSpeed << (2 * PinConfig.PinNumber);

   	// Clear bits with ~(b'11) at corresponding pin
    GPIOPort->OSPEEDR &= ~(0x3 << (2 * PinConfig->PinNumber));

    // Set appropriate bits with the temp register
    GPIOPort->OSPEEDR |= temp;
    //////////////////////////////////////////////////////////////////////


    ///////////////////////////////////PUPDR Config///////////////////////

    // Configure port mode
    temp = PinConfig.PinPuPdControl << (2 * PinConfig.PinNumber);

    // Clear bits with ~(b'11) at corresponding pin
    GPIOPort->PUPDR &= ~(0x3 << (2 * PinConfig->PinNumber));

    // Set appropriate bits with the temp register
    GPIOPort->PUPDR |= temp;
    //////////////////////////////////////////////////////////////////////

    ///////////////////////////////////OPTYPE Config///////////////////////

    // Configure port mode
    temp = PinConfig.OPType << PinConfig.PinNumber;

    // Clear bits with ~(1) at corresponding pin
    GPIOPort->OTYPER &= ~(1 << (PinConfig->PinNumber));

    // Set appropriate bits with the temp register
    GPIOPort->OTYPER |= temp;
    //////////////////////////////////////////////////////////////////////

    ///////////////////////////////////AFR Config///////////////////////

    // Check if the pin mode equals alt function macro
    if (PinConfig.PinMode == GPIO_PinMode_Alternate) {

        // Bit selection
        uint32_t AFRRegSel = PinConfig.PinNumber / 8;		// Selecting proper AFR register. When pin number >8 then 1, <8 then 0
        uint32_t AFRPinPos = PinConfig.PinNumber % 8;		// Selecting proper Pin. When pin number >8 it will be the remainder, when less it will be the pin number
        uint8_t AFRBitShift = AFRPinPos * 4;				// Selecting shift amount and targeting specific bits in register

        // Bit shifting
        temp = PinConfig.PinAltFunMode << AFRBitShift;		// Shift the input AFR value accordingly and store in temp

        // Clear the original value in proper register
        uint32_t clearVal = (0xF << AFRBitShift); 			// 0xF is 1111 in binary, shift this into correct location
        GPIOPort->AFR[AFRRegSel] &= ~(clearVal);			// Invert to 0000 then store into the correct AFR register

        // Set the AFR configuration
        GPIOPort->AFR[AFRRegSel] |= temp;					// Store the configuration into the correct AFR register

    }

    //////////////////////////////////////////////////////////////////////

}





