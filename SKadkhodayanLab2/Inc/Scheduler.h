/*
 * Scheduler.h
 *
 *  Created on: Sep 12, 2024
 *      Author: seank
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

uint32_t getScheduledEvents();
void addSchedulerEvent(uint32_t event);
void removeScheduledEvent(uint32_t event);

#endif /* SCHEDULER_H_ */

