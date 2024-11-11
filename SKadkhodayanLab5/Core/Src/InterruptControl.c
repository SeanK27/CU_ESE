/*
 * InterruptControl.c
 *
 *  Created on: Sep 28, 2024
 *      Author: seank
 */

#include "InterruptControl.h"

void NVIC_Enable_Interrupt(uint8_t IRQnum) {

//    if (IRQnum < 32) {
//        // Enable the interrupt in the NVIC_ISER0 register
//        *NVIC_ISER0 |= (1 << IRQnum);
//    }
//    else {
//        // Enable the interrupt in the NVIC_ISER0 register
//        *NVIC_ISER1 |= (1 << (IRQnum % 32));
//    }

	HAL_NVIC_EnableIRQ(IRQnum);
}

void NVIC_Disable_Interrupt(uint8_t IRQnum) {

//    if (IRQnum < 32) {
//        // Disable the interrupt in the NVIC_ICER0 register
//        *NVIC_ICER0 |= (1 << IRQnum);
//    }
//    else {
//        // Disable the interrupt in the NVIC_ICER0 register
//        *NVIC_ICER1 |= (1 << (IRQnum % 32));
//    }

	HAL_NVIC_DisableIRQ(IRQnum);

}

void NVIC_Clear_Pending_Interrupt(uint8_t IRQnum) {

//    if (IRQnum < 32) {
//        // Clear the pending interrupt in the NVIC_ICPR0 register
//        *NVIC_ICPR0 |= (1 << IRQnum);
//    }
//    else {
//        // Clear the pending interrupt in the NVIC_ICPR0 register
//        *NVIC_ICPR1 |= (1 << (IRQnum % 32));
//    }

	HAL_NVIC_ClearPendingIRQ(IRQnum);

}

void NVIC_Set_Pending_Interrupt(uint8_t IRQnum) {

//    if (IRQnum < 32) {
//        // Set the pending interrupt in the NVIC_ISPR0 register
//        *NVIC_ISPR0 |= (1 << IRQnum);
//    }
//    else {
//        // Set the pending interrupt in the NVIC_ISPR0 register
//        *NVIC_ISPR1 |= (1 << (IRQnum % 32));
//    }

	HAL_NVIC_SetPendingIRQ(IRQnum);

}

void NVIC_Clear_Pending_EXTI_Bit(uint8_t pinNum) {

    // Clear the pending bit in the EXTI register
    EXTI->PR |= (1 << pinNum);
}
