/*
 * ApplicationCode.h
 *
 *  Created on: Sep 12, 2024
 *      Author: seank
 */

#ifndef APPLICATIONCODE_H_
#define APPLICATIONCODE_H_

#include "STM32F429i.h"
#include "LED_Driver.h"
#include "Scheduler.h"
#include "Button_Driver.h"

#define NAMELENGTH 4
#define DELAYMAGNIFIER 60000

#define DUAL_TIMER_USAGE 0

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

#endif /* APPLICATIONCODE_H_ */
