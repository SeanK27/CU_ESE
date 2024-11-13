/*
 * ApplicationCode.h
 *
 *  Created on: Sep 12, 2024
 *      Author: seank
 */

#ifndef APPLICATIONCODE_H_
#define APPLICATIONCODE_H_

#include "LED_Driver.h"
#include "Scheduler.h"
#include "Button_Driver.h"
#include "Gyro.h"

#define NAMELENGTH 4
#define DELAYMAGNIFIER 60000

#define USE_INTERRUPT_FOR_BUTTON 1

void applicationInit();
void greenLEDInit();
void redLEDInit();
void toggleGreenLED();
void toggleRedLED();
void activateGreenLED();
void activateRedLED();
void deactivateGreenLED();
void deactivateRedLED();
void AppDelay(uint32_t time);

void InitializeUserButton();
void executeButtonPollingRoutine();

void InitializeUserButtonAsInterrupt();

void getGyroID();
void powerOnGyro();
void getGyroTemperature();
void configureGyro();
void getGyroConfiguration();
void checkGyroStatus();

#endif /* APPLICATIONCODE_H_ */
