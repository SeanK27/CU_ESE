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

    // Initialize the red LED
    redLEDInit();

    // Initialize the green LED
    greenLEDInit();

    // Add the scheduler event to toggle the red LED
    addSchedulerEvent(RED_TOGGLE_EVENT);

    // Add the scheduler event to delay
    addSchedulerEvent(DELAY_EVENT);

    // Add the scheduler event to toggle the green LED
    addSchedulerEvent(GREEN_TOGGLE_EVENT);
}





