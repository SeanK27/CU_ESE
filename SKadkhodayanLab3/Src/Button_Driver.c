/*
 * Button_Driver.c
 *
 *  Created on: Sep 28, 2024
 *      Author: seank
 */

#include "Button_Driver.h"
#include "GPIO_Driver.h"
#include <stdbool.h>

GPIO_PinConfig_t GPIOConfig = {0};

void User_Button_Enable_Clock() {
    // Enable the clock for the user button
    RCC->AHB1ENR |= (1 << USER_BUTTON_PORT);
}

void User_Button_Init() {

    // Instantiate a GPIO_PinConfig_t struct
    GPIOConfig.PinNumber = USER_BUTTON_PIN;
    GPIOConfig.PinMode = GPIO_PinMode_Input;
    GPIOConfig.PinSpeed = GPIO_Speed_Medium;
    GPIOConfig.PinPuPdControl = GPIO_PUPDR_PD;

    // Enable the clock for the user button
    User_Button_Enable_Clock();

    // Initialize the GPIO Pin
    GPIO_Init(GPIOA, GPIOConfig);
}

bool User_Button_Is_Pressed() {

    // Check if the button is pressed
    if (GPIO_ReadFromInputPin(GPIOA, USER_BUTTON_PIN) == USER_BUTTON_PRESSED) {
        return true;
    }
    else {
        return false;
    }
}

void User_Button_Interrupt_Enable() {

    // Instantiate a GPIO_PinConfig_t struct
    GPIOConfig.PinNumber = USER_BUTTON_PIN;
    GPIOConfig.PinMode = GPIO_PinMode_Input;
    GPIOConfig.PinSpeed = GPIO_Speed_Medium;
    GPIOConfig.PinPuPdControl = GPIO_PUPDR_PD;
    GPIOConfig.PinInterruptMode = GPIO_PinInterrupt_RisingFallingEdge;

    // Enable the clock for the user button
    User_Button_Enable_Clock();

    // Initialize the GPIO Pin
    GPIO_Init(GPIOA, GPIOConfig);

    // Enable the interrupt in the EXTI register
    GPIO_InterruptConfig(6, ENABLE);
}
