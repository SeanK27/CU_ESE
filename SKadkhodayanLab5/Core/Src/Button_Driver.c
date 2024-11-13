/*
 * Button_Driver.c
 *
 *  Created on: Sep 28, 2024
 *      Author: seank
 */

#include "Button_Driver.h"
#include <stdbool.h>

//GPIO_PinConfig_t GPIOConfig = {0};

GPIO_InitTypeDef GPIOConfigH = {0};

void User_Button_Enable_Clock() {
    // Enable the clock for the user button
//    RCC->AHB1ENR |= (1 << USER_BUTTON_PORT);

	__HAL_RCC_GPIOA_CLK_ENABLE();
}

void User_Button_Init() {

    // Instantiate a GPIO_PinConfig_t struct
//    GPIOConfig.PinNumber = USER_BUTTON_PIN;
//    GPIOConfig.PinMode = GPIO_PinMode_Input;
//    GPIOConfig.PinSpeed = GPIO_Speed_Medium;
//    GPIOConfig.PinPuPdControl = GPIO_PUPDR_PD;

	GPIOConfigH.Pin = GPIO_PIN_0;
	GPIOConfigH.Mode = GPIO_MODE_INPUT;
	GPIOConfigH.Speed = GPIO_SPEED_FREQ_MEDIUM;
	GPIOConfigH.Pull = GPIO_PULLDOWN;

    // Enable the clock for the user button
    User_Button_Enable_Clock();

    // Initialize the GPIO Pin
//    GPIO_Init(GPIOA, GPIOConfig);

    HAL_GPIO_Init(GPIOA, &GPIOConfigH);
}

bool User_Button_Is_Pressed() {

    // Check if the button is pressed
//    if (GPIO_ReadFromInputPin(GPIOA, USER_BUTTON_PIN) == USER_BUTTON_PRESSED) {
//        return true;
//    }
//    else {
//        return false;
//    }

	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == USER_BUTTON_PRESSED) {
	        return true;
	}
	else {
		return false;
	}
}

void User_Button_Interrupt_Enable() {

    // Instantiate a GPIO_PinConfig_t struct
//    GPIOConfig.PinNumber = USER_BUTTON_PIN;
//    GPIOConfig.PinMode = GPIO_PinMode_Input;
//    GPIOConfig.PinSpeed = GPIO_Speed_Medium;
//    GPIOConfig.PinPuPdControl = GPIO_PUPDR_PD;
//    GPIOConfig.PinInterruptMode = GPIO_PinInterrupt_RisingFallingEdge;

	GPIOConfigH.Pin = GPIO_PIN_0;
	GPIOConfigH.Mode = GPIO_MODE_IT_RISING;
	GPIOConfigH.Speed = GPIO_SPEED_FREQ_MEDIUM;
	GPIOConfigH.Pull = GPIO_PULLDOWN;

    // Enable the clock for the user button
    User_Button_Enable_Clock();

    // Initialize the GPIO Pin
//    GPIO_Init(GPIOA, GPIOConfig);

    HAL_GPIO_Init(GPIOA, &GPIOConfigH);

    // Enable the interrupt in the EXTI register
//    GPIO_InterruptConfig(6, ENABLE);

    HAL_NVIC_EnableIRQ(EXTI0_IRQ_NUM);
}
