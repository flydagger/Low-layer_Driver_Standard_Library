/**
 * @file touch_key.h
 * @brief This file contains the declarations and definitions for a capacitive touch key module.
 * @author Yixiang Fan
 * @date 2024-08-03
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 */

#ifndef CAPACITIVE_TOUCH_SCREEN_KEY_TOUCH_KEY_H_
#define CAPACITIVE_TOUCH_SCREEN_KEY_TOUCH_KEY_H_

#include "system.h"

extern uint16_t touch_default_val;  // Value of the touch key when it is not pressed

void TIM2_CH1_Input_Init(unit32_t arr, uint16_t psc);
void Touch_Reset(void);
uint16_t Touch_Get_Val(void);
unit8_t Touch_Key_Init(unit8_t psc);
uint16_t Touch_Get_MaxVal(unit8_t n);
unit8_t Touch_Key_Scan(unit8_t mode);

#endif  // CAPACITIVE_TOUCH_SCREEN_KEY_TOUCH_KEY_H_
