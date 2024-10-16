/*
 * GPIO_Driver.c
 *
 *  Created on: Sep 12, 2024
 *      Author: seank
 */

#include "GPIO_Driver.h"

void GPIO_ClockControl(GPIO_RegDef_t * GPIOPort, uint8_t PinStatus) {

    // Enable the clock for the GPIO port
    if (PinStatus == ENABLE) {
        
        // Check the GPIO port and enable the clock
        if (GPIOPort == GPIOA) {
            ENABLE_AHB1ENR_CLOCK(GPIOA_AHB1ENR_BIT);
        }
        
        if (GPIOPort == GPIOG) {
            ENABLE_AHB1ENR_CLOCK(GPIOG_AHB1ENR_BIT);
        }
    }

    // Disable the clock for the GPIO port
    if (PinStatus == DISABLE) {

        // Check the GPIO port and disable the clock
        if (GPIOPort == GPIOA) {
            DISABLE_AHB1ENR_CLOCK(GPIOA_AHB1ENR_BIT);
        }

        if (GPIOPort == GPIOG) {
            DISABLE_AHB1ENR_CLOCK(GPIOG_AHB1ENR_BIT);
        }
    }
}

void GPIO_WriteToOutputPin(GPIO_RegDef_t * GPIOPort, uint8_t WritePin, uint8_t WriteVal) {

	// Check the write value
	if (WriteVal == 1) {
		GPIOPort->ODR |= (1 << WritePin); // Write 1 to the ODR register and shift to the proper pin
	}
	if (WriteVal == 0) {
		GPIOPort->ODR &= ~(1 << WritePin); // Write 0 to the ODR register and shift to the proper pin
	}
}

void GPIO_ToggleOutputPin(GPIO_RegDef_t * GPIOPort, uint8_t TogglePin) {

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
    GPIOPort->MODER &= ~(0x3 << (2 * PinConfig.PinNumber));

    // Set appropriate bits with the temp register
    GPIOPort->MODER |= temp;
    //////////////////////////////////////////////////////////////////////

    ///////////////////////////////Interrupt Config///////////////////////

    if (PinConfig.PinInterruptMode == GPIO_PinInterrupt_FallingEdge) {

        // Clear the bit in the FTSR register
        EXTI->FTSR |= (1 << PinConfig.PinNumber);

        // Set the bit in the FTSR register
        EXTI->RTSR &= ~(1 << PinConfig.PinNumber);
    }

    if (PinConfig.PinInterruptMode == GPIO_PinInterrupt_RisingEdge) {

        // Clear the bit in the RTSR register
        EXTI->RTSR |= (1 << PinConfig.PinNumber);

        // Set the bit in the RTSR register
        EXTI->FTSR &= ~(1 << PinConfig.PinNumber);
    }

    if (PinConfig.PinInterruptMode == GPIO_PinInterrupt_RisingFallingEdge) {

        // Set the bit in the RTSR register
        EXTI->RTSR |= (1 << PinConfig.PinNumber);

        // Set the bit in the FTSR register
        EXTI->FTSR |= (1 << PinConfig.PinNumber);
    }

    uint8_t tempPin = PinConfig.PinNumber / 4;
    uint8_t tempPinPos = PinConfig.PinNumber % 4;

    uint16_t tempPort = GPIO_ReturnPortNumber(GPIOPort);

    // Enable the clock for the SYSCFG peripheral (must be enabled to configure EXTI)
    ENABLE_SYSCFG_CLOCK();

    // 
    temp = tempPort << (4 * tempPinPos);        // Each pin is 4 bits, so shift the port number to the correct location
    // Clear it first
    SYSCFG->EXTICR[tempPin] |= temp;            // Set the SYSCFG register to the proper port (maps the gpio ports to the EXTI lines)

    EXTI->IMR |= (1 << PinConfig.PinNumber);    // Interrupt mask register set to enable the interrupt to trigger

    ///////////////////////////////////SPEED Config///////////////////////

   	// Configure port speed
   	temp = PinConfig.PinSpeed << (2 * PinConfig.PinNumber);

   	// Clear bits with ~(b'11) at corresponding pin
    GPIOPort->OSPEEDR &= ~(0x3 << (2 * PinConfig.PinNumber));

    // Set appropriate bits with the temp register
    GPIOPort->OSPEEDR |= temp;
    //////////////////////////////////////////////////////////////////////


    ///////////////////////////////////PUPDR Config///////////////////////

    // Configure port mode
    temp = PinConfig.PinPuPdControl << (2 * PinConfig.PinNumber);

    // Clear bits with ~(b'11) at corresponding pin
    GPIOPort->PUPDR &= ~(0x3 << (2 * PinConfig.PinNumber));

    // Set appropriate bits with the temp register
    GPIOPort->PUPDR |= temp;
    //////////////////////////////////////////////////////////////////////

    ///////////////////////////////////OPTYPE Config///////////////////////

    // Configure port mode
    temp = PinConfig.OPType << PinConfig.PinNumber;

    // Clear bits with ~(1) at corresponding pin
    GPIOPort->OTYPER &= ~(1 << (PinConfig.PinNumber));

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

uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t * GPIOPort, uint8_t ReadPin) {
    
    // Read the value from the IDR register and shift to the proper pin
    uint8_t value = (GPIOPort->IDR >> ReadPin) & 0x01;

    return value;
}

uint16_t GPIO_ReturnPortNumber(GPIO_RegDef_t * GPIOPort) {
    
        // Check the GPIO port and return the port number
        if (GPIOPort == GPIOA) {
            return PORT_GPIOA;
        }
        if (GPIOPort == GPIOG) {
            return PORT_GPIOG;
        }
    
        return 0;
}

void GPIO_InterruptConfig(uint8_t IRQNumber, uint8_t Status) {
    
        // Enable the interrupt in the NVIC register
        if (Status == ENABLE) {
        	*NVIC_ISER0 |= (1 << IRQNumber);
        }
    
        // Disable the interrupt in the NVIC register
        if (Status == DISABLE) {
        	*NVIC_ICER0 |= (1 << IRQNumber);
        }
}
