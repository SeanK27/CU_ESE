/*
 * ErrorHandling.c
 *
 *  Created on: Nov 10, 2024
 *      Author: seank
 */

#include "ErrorHandling.h"

// Go into infinite loop if input is false
void APPLICATION_ASSERT(bool condition) {

	if (!condition) {
		while(1) {}
	}
}
