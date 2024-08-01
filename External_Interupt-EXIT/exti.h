/**
 * @file exti.h
 * @brief This file contains the initialization and interrupt handler functions for external interrupt.
 * @author Yixiang Fan
 * @date 2024-08-01
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 */
#ifndef EXTERNAL_INTERUPT_EXIT_EXTI_H_
#define EXTERNAL_INTERUPT_EXIT_EXTI_H_

#include "system.h"

/**
 * @brief Initializes external interrupt lines and NVIC.
 *
 * This function configures the GPIO pins for external interrupt lines, sets up the NVIC for the
 * corresponding EXTI interrupt channels, and initializes the EXTI registers. It enables the
 * specified GPIO pins as inputs with pull-up or pull-down resistors, and configures the EXTI
 * lines to trigger on rising or falling edges.
 *
 * @param void
 * @return void
 * @note This function should be called before using any external interrupt features in the application.
 * @warning Make sure to configure the GPIO pins and clocks properly before calling this function.
 */
void My_EXTI_Init(void);

#endif  // EXTERNAL_INTERUPT_EXIT_EXTI_H_
