#ifndef IWDG_IWDG_H_
#define IWDG_IWDG_H_

#include "system.h"

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
void IWDG_Init(u8 pre, u16 rlr);

/**
 * @brief Feeds the Independent Watchdog (IWDG).
 *
 * This function reloads the IWDG counter with the initial value, preventing a watchdog reset.
 * The IWDG must be initialized before calling this function.
 *
 * @return void
 */
void IWDG_FeedDog(void);

#endif  // IWDG_IWDG_H_
