/**
 * @file wwdg.h
 * @brief Header file for Window Watchdog (WWDG) driver.
 * @author Yixiang Fan
 * @date 2024-08-03
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 */

#ifndef WWDG_WWDG_H_
#define WWDG_WWDG_H_

#include "system.h"

/**
 * @brief Initializes the Window Watchdog (WWDG) peripheral.
 *
 * This function configures the WWDG to operate with the specified window value, timer count value,
 * and prescaler. It also enables the WWDG interrupt and sets up the NVIC for the interrupt.
 *
 * @param None
 * @return None
 */
void WWDG_Init(void);

#endif  // WWDG_WWDG_H_
