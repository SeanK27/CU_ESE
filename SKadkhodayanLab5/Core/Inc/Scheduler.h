/*
 * Scheduler.h
 *
 *  Created on: Sep 12, 2024
 *      Author: seank
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "stm32f4xx_hal.h"

#define RED_TOGGLE_EVENT                (1 << 0)
#define DELAY_EVENT                     (1 << 1)
#define GREEN_TOGGLE_EVENT              (1 << 2)
#define POLL_BUTTON_EVENT               (1 << 3)
#define APP_DELAY_FLAG_EVENT            (1 << 4)
#define DEVICE_ID_AND_TEMP_EVENT        (1 << 5)

uint32_t getScheduledEvents();
void addSchedulerEvent(uint32_t event);
void removeScheduledEvent(uint32_t event);

#endif /* SCHEDULER_H_ */

