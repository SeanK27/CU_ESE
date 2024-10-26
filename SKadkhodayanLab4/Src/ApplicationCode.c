/*
 * ApplicationCode.c
 *
 *  Created on: Sep 12, 2024
 *      Author: seank
 */

#include "ApplicationCode.h"

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

    #if DUAL_TIMER_USAGE == 1

        // Initialize Button as Interrupt
        InitializeUserButtonAsInterrupt();

        // Initialize Timer 5
        LED_Timer5_Init();
    #endif

    #if DUAL_TIMER_USAGE == 0

        // Initialize Timer 2
        LED_Timer2_Init();

        // Start Timer 2
        LED_Timer2_Start();
    #endif

    // Add the scheduler event for Red LED
    addSchedulerEvent(RED_TOGGLE_EVENT);

    // Add the scheduler event to delay
    addSchedulerEvent(DELAY_EVENT);

}

#if DUAL_TIMER_USAGE == 1

// TODO: Do all the dual timer stuff here

void InitializeUserButtonAsInterrupt() {
    
    // Initialize the user button as an interrupt
    User_Button_Interrupt_Enable();
}

// Button Interrupt Handler
void EXTI0_IRQHandler() {

    // Disable the interrupt so it doesn't trigger during execution
    NVIC_Disable_Interrupt(EXTI0_IRQ_NUM);

    // Toggle the green LED
    toggleGreenLED();

    // Clear the pending bit to allow for another interrupt in the future
    NVIC_Clear_Pending_EXTI_Bit(USER_BUTTON_PIN);

    // Clear the pending interrupt in the NVIC register to prevent another 
    NVIC_Clear_Pending_Interrupt(EXTI0_IRQ_NUM);

    // Re-enable the interrupt
    NVIC_Enable_Interrupt(EXTI0_IRQ_NUM);
}

void TIM5_IRQHandler() {

    // Disable the interrupt so it doesn't trigger during execution
    NVIC_Disable_Interrupt(TIM5_IRQ_NUM);

    // Check if the interrupt flag is set
    if (TIM5->SR & (1 << 0)) {

        // Clear the interrupt flag
        TIM5->SR &= ~(1 << 0);

        // Toggle the green LED
        toggleGreenLED();
    }

    // Clear the pending interrupt in the NVIC register to prevent another 
    NVIC_Clear_Pending_Interrupt(TIM5_IRQ_NUM);

    // Reset the timer
    LED_Reset_Timer5();

    // Re-enable the interrupt
    NVIC_Enable_Interrupt(TIM5_IRQ_NUM);
}

#endif


// Compiler flags to only compile interrupt code if the flag is 0
#if DUAL_TIMER_USAGE == 0

// Timer 2 Interrupt Handler
void TIM2_IRQHandler() {

    // Disable the interrupt so it doesn't trigger during execution
    NVIC_Disable_Interrupt(TIM2_IRQ_NUM);

    // Check if the interrupt flag is set
    if (TIM2->SR & (1 << 0)) {

        // Clear the interrupt flag
        TIM2->SR &= ~(1 << 0);

        // Toggle the red LED
        toggleRedLED();
    }

    // Clear the pending interrupt in the NVIC register to prevent another 
    NVIC_Clear_Pending_Interrupt(TIM2_IRQ_NUM);

    // Reset the timer
    LED_Reset_Timer2();

    // Re-enable the interrupt
    NVIC_Enable_Interrupt(TIM2_IRQ_NUM);
}

#endif
