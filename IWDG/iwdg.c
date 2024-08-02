/**
 * @file iwdg.c
 * @brief Functions for managing the Independent Watchdog (IWDG) in a microcontroller.
 * @author Yixiang Fan
 * @date 2024-08-02
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 */

#include "iwdg.h"

/**
 * @brief Initializes the Independent Watchdog (IWDG).
 *
 * This function initializes the IWDG with the given prescaler and reload value.
 * The independent watchdog reset time can be calculated using the formula:
 * t = (4*2^pre*rlr)/40
 *
 * @param pre Prescaler coefficient (0-6).
 * @param rlr Reload value (12-bit range: 0xfff).
 *
 * @return void
 */
void IWDG_Init(unit8_t pre, uint16_t rlr) {
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  // Cancel register write protection
    IWDG_SetPrescaler(pre);                        // Set prescaler coefficient 0-6
    IWDG_SetReload(rlr);                           // Set reload value
    IWDG_ReloadCounter();                          // Reload initial value
    IWDG_Enable();                                 // Open independent watchdog
}

/**
 * @brief Feeds the Independent Watchdog (IWDG).
 *
 * This function reloads the IWDG counter with the initial value, preventing a watchdog reset.
 * The IWDG must be initialized before calling this function.
 *
 * @return void
 */
void IWDG_FeedDog(void) {
    IWDG_ReloadCounter();  // Reload initial value
}
