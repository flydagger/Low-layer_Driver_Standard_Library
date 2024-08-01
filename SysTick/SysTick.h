/**
 * @file SysTick.h
 * @brief SysTick timer initialization and delay functions.
 * @author Your Name
 * @date 2024-08-01
 * @copyright Copyright 2024 Your Name. All rights reserved.
 *
 * This file contains the implementation of the SysTick timer initialization and delay functions.
 */

#ifndef SYSTICK_SYSTICK_H_
#define SYSTICK_SYSTICK_H_

#include "system.h"

/**
 * @brief Initializes the SysTick timer with the given system clock frequency.
 *
 * This function configures the SysTick timer to generate interrupts at a specified frequency.
 * The timer is used for delay functions provided in this module.
 *
 * @param sysclk The system clock frequency in MHz.
 */
void SysTick_Init(uint8_t sysclk);

/**
 * @brief Delays the program execution for the specified number of milliseconds.
 *
 * This function uses the SysTick timer to generate a delay of the specified number of milliseconds.
 * The actual delay may vary due to interrupt processing.
 *
 * @param nms The number of milliseconds to delay.
 */
void delay_ms(uint16_t nms);

/**
 * @brief Delays the program execution for the specified number of microseconds.
 *
 * This function uses the SysTick timer to generate a delay of the specified number of microseconds.
 * The actual delay may vary due to interrupt processing.
 *
 * @param nus The number of microseconds to delay.
 */
void delay_us(uint32_t nus);

#endif  // SYSTICK_SYSTICK_H_
