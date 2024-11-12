/*
 * ApplicationCode.c
 *
 *  Created on: Sep 12, 2024
 *      Author: seank
 */

#include "ApplicationCode.h"
#include "stm32f4xx_hal_gpio.h"

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
	HAL_GPIO_WritePin(GPIOG, LED_GREEN_PIN, SET);
}

void activateRedLED() {

    // Activate the red LED
	HAL_GPIO_WritePin(GPIOG, LED_RED_PIN, SET);
}

void deactivateGreenLED() {

    // Deactivate the green LED
	HAL_GPIO_WritePin(GPIOG, LED_GREEN_PIN, RESET);
}

void deactivateRedLED() {

    // Deactivate the red LED
	HAL_GPIO_WritePin(GPIOG, LED_RED_PIN, RESET);
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

    // Initialize Gyro
    Gyro_Init();

    // Initialize the GPIOA clock
	User_Button_Enable_Clock();

    // Initialize the user button
    InitializeUserButton();

    // Add Gyro ID event to scheduler
    addSchedulerEvent(GET_GYRO_ID_EVENT);

    // Add Gyro power on event to scheduler
    addSchedulerEvent(POWER_ON_GYRO_EVENT);

    // Compiler flags to only compile interrupt code if the flag is 1
    #if USE_INTERRUPT_FOR_BUTTON == 1

        // Initialize the user button as an interrupt
        InitializeUserButtonAsInterrupt();

    #endif

    // Compiler flags to only compile polling code if the flag is 0
    #if USE_INTERRUPT_FOR_BUTTON == 0

        // Initialize the user button as a polling routine
        executeButtonPollingRoutine();

        // Add button polling event to scheduler
        addSchedulerEvent(POLL_BUTTON_EVENT);

    #endif

}

// Compiler flags to only compile interrupt code if the flag is 1
#if USE_INTERRUPT_FOR_BUTTON == 1

void InitializeUserButtonAsInterrupt() {
    
    // Initialize the user button as an interrupt
    User_Button_Interrupt_Enable();
}

void EXTI0_IRQHandler() {

    // Disable the interrupt so it doesn't trigger during execution
    NVIC_Disable_Interrupt(EXTI0_IRQ_NUM);

    // Get the Gyro ID
    getGyroID();

    // Get the Gyro temperature
    getGyroTemperature();

    // Clear the pending bit to allow for another interrupt in the future
    NVIC_Clear_Pending_EXTI_Bit(USER_BUTTON_PIN);

    // Clear the pending interrupt in the NVIC register to prevent another 
    NVIC_Clear_Pending_Interrupt(EXTI0_IRQ_NUM);

    // Re-enable the interrupt
    NVIC_Enable_Interrupt(EXTI0_IRQ_NUM);
}

#endif

void getGyroID(){
    
    Gyro_GetID();
}

void powerOnGyro(){
    
    Gyro_PowerOn();
}

void getGyroTemperature(){
    
    Gyro_GetTemperature();
}

void configureGyro(){
    
    Gyro_Config();
}

void getGyroConfiguration(){
    
    Gyro_ReadConfig();
}

void checkGyroStatus(){
    
    Gyro_CheckHALStatus();
}