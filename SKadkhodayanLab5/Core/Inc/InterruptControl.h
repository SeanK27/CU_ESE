/*
 * InterruptControl.h
 *
 *  Created on: Sep 28, 2024
 *      Author: seank
 */

#ifndef INTERRUPTCONTROL_H_
#define INTERRUPTCONTROL_H_

#include "stm32f429xx.h"

#define EXTI0_IRQ_NUM 6

void NVIC_Enable_Interrupt(uint8_t IRQnum);
void NVIC_Disable_Interrupt(uint8_t IRQnum);
void NVIC_Clear_Pending_Interrupt(uint8_t IRQnum);
void NVIC_Set_Pending_Interrupt(uint8_t IRQnum);
void NVIC_Clear_Pending_EXTI_Bit(uint8_t pinNum);

#endif /* INTERRUPTCONTROL_H_ */
