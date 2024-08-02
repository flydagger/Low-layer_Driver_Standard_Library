/**
 * @file timer_time.h
 * @brief This file declares the function prototypes for the Timer 4 initialization in the timer_time.c file.
 * @author Yixiang Fan
 * @date 2024-08-02
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 */

#ifndef TIMER_TIME_H_
#define TIMER_TIME_H_

#include "system.h"

void TIM4_Init(uint16_t per, uint16_t psc);

#endif  // TIMER_TIME_H_
