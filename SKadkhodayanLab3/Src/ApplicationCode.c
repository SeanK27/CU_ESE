/*
 * ApplicationCode.c
 *
 *  Created on: Sep 12, 2024
 *      Author: seank
 */

#include "ApplicationCode.h"
#include "LED_Driver.h"
#include "Scheduler.h"
#include "GPIO_Driver.h"
#include "Button_Driver.h"
#include "InterruptControl.h"

// Create name array for AppDelay
uint32_t nameArray[NAMELENGTH] = {'S', 'E', 'A', 'N'};

void greenLEDInit() {

    // Initialize the green LED
    LED_Init(LED_GREEN_PIN);
}

void redLEDInit() {

    // Initialize the red LED
    LED_Init(LED_RED_PIN);
}

void toggleGreenLED() {

    // Toggle the green LED
    ToggleLED(LED_GREEN_PIN);
}

void toggleRedLED() {

    // Toggle the red LED
    ToggleLED(LED_RED_PIN);
}

void activateGreenLED() {

    // Activate the green LED
    GPIO_WriteToOutputPin(GPIOG, LED_GREEN_PIN, SET);
}

void activateRedLED() {

    // Activate the red LED
    GPIO_WriteToOutputPin(GPIOG, LED_RED_PIN, SET);
}

void deactivateGreenLED() {

    // Deactivate the green LED
    GPIO_WriteToOutputPin(GPIOG, LED_GREEN_PIN, RESET);
}

void deactivateRedLED() {

    // Deactivate the red LED
    GPIO_WriteToOutputPin(GPIOG, LED_RED_PIN, RESET);
}

void InitializeUserButton() {
    
    // Initialize the user button
	User_Button_Init();
}

void executeButtonPollingRoutine() {

    // Check if the user button is pressed
    if (User_Button_Is_Pressed() == true) {

        // Turn on the green LED
        activateGreenLED();
    }
    else {
            
        // Turn off the green LED
        deactivateGreenLED();
    }
}

void AppDelay(uint32_t time) {

	// Create two arrays to store the name
	char sean[NAMELENGTH] = {'S', 'E', 'A', 'N'};
	[[maybe_unused]] char destinationArray[NAMELENGTH];

	// Iterate through the array to create a crude delay function
	for (int i = 0; i < time; i++) {

		for (int j = 0; j < NAMELENGTH; j++) {

			destinationArray[j] = sean[j];
		}
	}
}

void applicationInit() {

    // Initialize the GPIO clock
	GPIO_ClockControl(GPIOG, ENABLE);

    // Initialize the GPIOA clock
	User_Button_Enable_Clock();

    // Initialize the user button
    InitializeUserButton();

    // Initialize the green LED
    greenLEDInit();

    // Initialize the red LED
    redLEDInit();

    // Deactivate the red LED
    deactivateRedLED();

    // Deactivate the green LED
    deactivateGreenLED();

    #if USE_INTERRUPT_FOR_BUTTON == 1

        // Initialize the user button as an interrupt
        InitializeUserButtonAsInterrupt();

    #endif

    #if USE_INTERRUPT_FOR_BUTTON == 0

        // Initialize the user button as a polling routine
        executeButtonPollingRoutine();

        // Add button polling event to scheduler
        addSchedulerEvent(POLL_BUTTON_EVENT);

    #endif

    // Add the scheduler event to toggle the red LED
    addSchedulerEvent(RED_TOGGLE_EVENT);

    // Add the scheduler event to delay
    addSchedulerEvent(DELAY_EVENT);

    // Add the scheduler event to toggle the green LED
    addSchedulerEvent(GREEN_TOGGLE_EVENT);

}

#if USE_INTERRUPT_FOR_BUTTON == 1

void InitializeUserButtonAsInterrupt() {
    
    // Initialize the user button as an interrupt
    User_Button_Interrupt_Enable();
}

void EXTI0_IRQHandler() {

    // Disable the interrupt
    NVIC_Disable_Interrupt(EXTI0_IRQ_NUM);

    // Toggle the green LED
    toggleGreenLED();

    // Clear the pending bit
    NVIC_Clear_Pending_EXTI_Bit(USER_BUTTON_PIN);

    // Clear the pending interrupt
    NVIC_Clear_Pending_Interrupt(EXTI0_IRQ_NUM);

    // Re-enable the interrupt
    NVIC_Enable_Interrupt(EXTI0_IRQ_NUM);
}

#endif
