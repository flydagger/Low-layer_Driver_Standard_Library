/**
 * @file SysTick.h
 * @brief SysTick timer initialization and delay functions.
 * @author Yixiang Fan
 * @date 2024-08-01
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 *
 * This file contains the implementation of the SysTick timer initialization and delay functions.
 */

#ifndef SYSTICK_SYSTICK_H_
#define SYSTICK_SYSTICK_H_

#include "system.h"

/**
 * @brief Initializes the delay functions using SysTick.
 *
 * The SysTick clock source is set to AHB clock divided by 8.
 * The us and ms delay multipliers are calculated based on the system clock frequency.
 *
 * @param sysclk System clock frequency in MHz.
 */
void SysTick_Init(uint8_t sysclk);

/**
 * @brief Delays the program execution for a specified number of milliseconds.
 *
 * Uses SysTick to delay the program execution for the specified number of milliseconds.
 * The maximum delay is limited by the SysTick counter size (24 bits) and the system clock frequency.
 *
 * @param nms Number of milliseconds to delay. Maximum value depends on the system clock frequency.
 * For a 72MHz system clock, the maximum delay is approximately 1864ms.
 */
void delay_ms(uint16_t nms);

/**
 * @brief Delays the program execution for a specified number of microseconds.
 *
 * Uses SysTick to delay the program execution for the specified number of microseconds.
 * The maximum delay is limited by the SysTick counter size (24 bits) and the system clock frequency.
 *
 * @param nus Number of microseconds to delay. Maximum value is 798915us (2^24/fac_us@fac_us=21).
 */
void delay_us(uint32_t nus);

#endif  // SYSTICK_SYSTICK_H_
