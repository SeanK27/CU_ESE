/*
 * Scheduler.c
 *
 *  Created on: Sep 12, 2024
 *      Author: seank
 */

#include "Scheduler.h"

uint32_t ScheduledEvents = 0;

void addSchedulerEvent(uint32_t event) {

    // Add the event to the scheduled events
    ScheduledEvents |= event;
}

void removeScheduledEvent(uint32_t event) {

    // Remove the event from the scheduled events
    ScheduledEvents &= ~event;
}

uint32_t getScheduledEvents() {

    // Return the scheduled events
    return ScheduledEvents;
}