/**
 * @file    wkup.c
 * @brief   This file contains functions for entering the Standby mode.
 * @author Yixiang Fan
 * @date 2024-08-03
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 */

#include "wkup.h"

/**
 * @brief  Enters the Standby mode.
 * @note   This function configures the system to enter Standby mode. In this mode,
 *         all I/O pins keep their state, the RTC continues to count, and the voltage regulator is switched off.
 *         The wake-up from Standby mode is done by an external interrupt on the WKUP pin or a RTC alarm.
 * @param  None
 * @retval None
 */
void Enter_Standby_Mode(void) {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);  // Enable clock for PWR peripheral

    PWR_ClearFlag(PWR_FLAG_WU);  // Clear Wake-up flag

    PWR_WakeUpPinCmd(ENABLE);  // Enable wake-up pin (enable or disable wake-up pin functionality)

    PWR_EnterSTANDBYMode();  // Enter Standby mode
}
