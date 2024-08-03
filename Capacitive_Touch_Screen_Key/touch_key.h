#ifndef _touch_key_H
#define _touch_key_H

#include "system.h"

extern uint16_t touch_default_val;  //未按下触摸按键时的值

void TIM2_CH1_Input_Init(unit32_t arr, uint16_t psc);
void Touch_Reset(void);
uint16_t Touch_Get_Val(void);
unit8_t Touch_Key_Init(unit8_t psc);
uint16_t Touch_Get_MaxVal(unit8_t n);
unit8_t Touch_Key_Scan(unit8_t mode);

#endif
