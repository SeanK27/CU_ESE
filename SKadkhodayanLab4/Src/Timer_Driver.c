/*
 * Timer_Driver.c
 *
 *  Created on: Oct 15, 2024
 *      Author: seank
 */

#include "Timer_Driver.h"
#include "InterruptControl.h"

void Timer_Init(GPTIMR_RegDef_t * TimerX, GPTimer_Config_t *TimerConfig) {

    uint32_t temp;

    // Set the clock division bits
    temp = TimerConfig->clock_division;
    TimerX->CR1 &= ~(0x3 << CLK_DIV_OFFSET);            // Clear the bits ~(111)
    TimerX->CR1 |= (temp << CLK_DIV_OFFSET);            // Set the bits

    // Set the center-aligned mode bits
    temp = TimerConfig->center_aligned_mode;
    TimerX->CR1 &= ~(0x3 << CENTER_ALIGNED_OFFSET);     // Clear the bits ~(111)
    TimerX->CR1 |= (temp << CENTER_ALIGNED_OFFSET);     // Set the bits

    // Set the counting direction bit
    if (TimerConfig->direction == TIM_DIR_UP) {
        TimerX->CR1 &= ~(1 << TIM_DIR_OFFSET);
    } else {
        TimerX->CR1 |= (1 << TIM_DIR_OFFSET);
    }

    // Set the auto-reload preload(buffer) bit
    if (TimerConfig->auto_reload_preload == TIM_ARPE_NO_BUFFER) {
        TimerX->CR1 &= ~(1 << TIM_ARPE_BUFFER_OFFSET);
    } else {
        TimerX->CR1 |= (1 << TIM_ARPE_BUFFER_OFFSET);
    }

    // Set the one-pulse mode bit
    if (TimerConfig->one_pulse_mode == TIM_OPM_NOT_STOPPED) {
        TimerX->CR1 &= ~(1 << TIM_OPR_OFFSET);
    } else {
        TimerX->CR1 |= (1 << TIM_OPR_OFFSET);
    }

    // Set the update interrupt enable bit
    if (TimerConfig->update_interrupt_enable == TIM_UIE_DISABLE) {
        TimerX->DIER &= ~(1 << TIM_UIE_OFFSET);
    } else {
        TimerX->DIER |= (1 << TIM_UIE_OFFSET);
    }

    // Set the prescaler value
    TimerX->PSC = TimerConfig->prescaler;

    // Set the auto-reload value
    TimerX->ARR = TimerConfig->auto_reload_value;

    if (TimerConfig->update_interrupt_enable == TIM_UIE_ENABLE) {
        Timer_Interrupt_Control(TimerX, ENABLE);
    } else {
        Timer_Interrupt_Control(TimerX, DISABLE);
    }
}

void Timer_Clock_Control(GPTIMR_RegDef_t * TimerX, uint8_t Status) {
    if (Status == ENABLE) {

        if (TimerX == TIM2) {
            ENABLE_TIM2_CLOCK();
        } else if (TimerX == TIM5) {
            ENABLE_TIM5_CLOCK();
        }


    } else {

        if (TimerX == TIM2) {
            DISABLE_TIM2_CLOCK();
        } else if (TimerX == TIM5) {
            DISABLE_TIM5_CLOCK();
        }
    }
}

void Timer_Start(GPTIMR_RegDef_t * TimerX) {
    TimerX->CR1 |= (1 << TIM_COUNTER_ENABLE_OFFSET);
}

void Timer_Stop(GPTIMR_RegDef_t * TimerX) {
    TimerX->CR1 &= ~(1 << TIM_COUNTER_ENABLE_OFFSET);
}

void Timer_Reset(GPTIMR_RegDef_t * TimerX) {
    TimerX->CNT &= ~(0xFFFFFFFF);
}

uint32_t Timer_Get_Auto_Reload_Value(GPTIMR_RegDef_t * TimerX) {
    return TimerX->ARR;
}

uint32_t Timer_Get_Value(GPTIMR_RegDef_t * TimerX) {
    return TimerX->CNT;
}

void Timer_Interrupt_Control(GPTIMR_RegDef_t * TimerX, uint8_t Status) {

    if (Status == ENABLE) {
        if (TimerX == TIM2) {
            NVIC_Enable_Interrupt(TIM2_IRQ_NUM);
        }
        if (TimerX == TIM5) {
            NVIC_Enable_Interrupt(TIM5_IRQ_NUM);
        }
    } else {
        if (TimerX == TIM2) {
            NVIC_Disable_Interrupt(TIM2_IRQ_NUM);
        }
        if (TimerX == TIM5) {
            NVIC_Disable_Interrupt(TIM5_IRQ_NUM);
        }
    }
}