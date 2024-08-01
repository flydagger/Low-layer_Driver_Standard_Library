/**
 * @file SysTick.c
 * @brief SysTick timer initialization and delay functions.
 * @author Yixiang Fan
 * @date 2024-08-01
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 *
 * This file contains the implementation of the SysTick delay functions.
 */

#include "SysTick.h"

static u8 fac_us = 0;  // Multiplier for microsecond delay
static u16 fac_ms = 0;  // Multiplier for millisecond delay

/**
 * @brief Initializes the delay functions using SysTick.
 *
 * The SysTick clock source is set to AHB clock divided by 8.
 * The us and ms delay multipliers are calculated based on the system clock frequency.
 *
 * @param sysclk System clock frequency in MHz.
 */
void SysTick_Init(u8 sysclk) {
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);
    fac_us = SYSCLK / 8;
    fac_ms = (u16)fac_us * 1000;
}

/**
 * @brief Delays the program execution for a specified number of microseconds.
 *
 * Uses SysTick to delay the program execution for the specified number of microseconds.
 * The maximum delay is limited by the SysTick counter size (24 bits) and the system clock frequency.
 *
 * @param nus Number of microseconds to delay. Maximum value is 798915us (2^24/fac_us@fac_us=21).
 */
void delay_us(u32 nus) {
    u32 temp;
    SysTick->LOAD = nus * fac_us;  // Time to load
    SysTick->VAL = 0x00;  // Clear the counter
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  // Start counting
    do {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16)));  // Wait for the count to reach zero
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  // Stop counting
    SysTick->VAL = 0X00;  // Clear the counter
}

/**
 * @brief Delays the program execution for a specified number of milliseconds.
 *
 * Uses SysTick to delay the program execution for the specified number of milliseconds.
 * The maximum delay is limited by the SysTick counter size (24 bits) and the system clock frequency.
 *
 * @param nms Number of milliseconds to delay. Maximum value depends on the system clock frequency.
 * For a 72MHz system clock, the maximum delay is approximately 1864ms.
 */
void delay_ms(u16 nms) {
    u32 temp;
    SysTick->LOAD = (u32)nms * fac_ms;  // Time to load (SysTick->LOAD is a 24-bit register)
    SysTick->VAL = 0x00;  // Clear the counter
    SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  // Start counting
    do {
        temp = SysTick->CTRL;
    } while ((temp & 0x01) && !(temp & (1 << 16)));  // Wait for the count to reach zero
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;  // Stop counting
    SysTick->VAL = 0X00;  // Clear the counter
}

