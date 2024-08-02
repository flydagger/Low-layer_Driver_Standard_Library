/**
 * @file pwm.h
 * @brief This file contains the declarations and definitions for the PWM initialization function for TIM3 channel 1.
 * @author Yixiang Fan
 * @date 2024-08-02
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 */

#ifndef PWM_PWM_H_
#define PWM_PWM_H_

#include "system.h"

/**
 * @brief Initializes the PWM for TIM3 channel 1 using the provided period and prescaler values.
 *
 * This function configures the GPIO, timer, and output compare settings for TIM3 channel 1 to generate a PWM signal.
 * The function enables the necessary clocks, configures the GPIO pin for alternate function, sets up the timer base,
 * and initializes the output compare channel. It also enables the preload registers and enables the timer.
 *
 * @param per The auto-reload value for the timer. This determines the PWM period.
 * @param psc The prescaler factor for the timer. This controls the PWM frequency.
 *
 * @return void
 */
void TIM3_CH1_PWM_Init(uint16_t per, uint16_t psc);

#endif  // PWM_PWM_H_
