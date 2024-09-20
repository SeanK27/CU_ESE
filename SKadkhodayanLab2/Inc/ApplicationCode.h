/*
 * ApplicationCode.h
 *
 *  Created on: Sep 12, 2024
 *      Author: seank
 */

#ifndef APPLICATIONCODE_H_
#define APPLICATIONCODE_H_

#include "STM32F429i.h"

#define NAMELENGTH 4
#define DELAYMAGNIFIER 6000

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

#endif /* APPLICATIONCODE_H_ */
