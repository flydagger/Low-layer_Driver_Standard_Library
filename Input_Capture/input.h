/**
 * @file input_capture_input.h
 * @brief Header file for input capture configuration using STM32F10x microcontroller.
 * @author Yixiang Fan
 * @date 2024-08-03
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 */

#ifndef INPUT_CAPTURE_INPUT_H_
#define INPUT_CAPTURE_INPUT_H_

#include "system.h"

extern unit8_t TIM5_CH1_CAPTURE_STA;   // Input capture status
extern uint16_t TIM5_CH1_CAPTURE_VAL;  // Input capture value

/**
 * @brief Initializes the TIM5 timer for input capture.
 *
 * This function configures the GPIO, timer, and interrupt for input capture on channel 1 of TIM5.
 * The timer is set up with the given auto-reload value (arr) and prescaler (psc).
 * The input capture is configured to capture rising edges, with a filter of 0x00.
 * The interrupt for update and capture events is enabled, and the NVIC is configured for the TIM5 interrupt.
 *
 * @param arr Auto-reload value for the timer.
 * @param psc Prescaler value for the timer.
 */
void TIM5_CH1_Input_Init(uint16_t arr, uint16_t psc);

#endif  // INPUT_CAPTURE_INPUT_H_
