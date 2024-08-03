/**
 * @file touch_key.c
 * @brief This file contains the implementation of a touch key module.
 * @author Yixiang Fan
 * @date 2024-08-03
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 */

#include "touch_key.h"
#include "SysTick.h"
#include "usart.h"

// Touch threshold value,
// meaning it must be greater than touch_default_val + TOUCH_GATE_VAL to be considered a valid touch.
#define TOUCH_GATE_VAL 100
#define TOUCH_ARR_MAX_VAL 0xffff  // Maximum ARR value

uint16_t touch_default_val = 0;  // Value when touching the touch key

/**
 * @brief Initializes the input capture for TIM5_CH2.
 *
 * @param arr Auto-reload value for the timer.
 * @param psc Prescaler value for the timer.
 *
 * @return None.
 */
void TIM5_CH2_Input_Init(uint16_t arr, uint16_t psc) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);  // Enable the TIM5 clock

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  // Floating input mode
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;      // IO port speed set to 50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                 // Initialize GPIOA

    TIM_TimeBaseInitStructure.TIM_Period = arr;     // Auto-reload value
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;  // Prescaler value
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  // Set counter mode to up
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;                 // Channel 2
    TIM_ICInitStructure.TIM_ICFilter = 0x00;                         // No filtering
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;      // Rising edge polarity
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;            // Prescaler set to 1
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;  // Directly mapped to TI1
    TIM_ICInit(TIM5, &TIM_ICInitStructure);

    TIM_Cmd(TIM5, ENABLE);  // Enable the timer
}

/**
 * @brief Resets the touch key by discharging the capacitor, then recharging it and reset the timer.
 *
 * @param None.
 *
 * @return None.
 */
void Touch_Reset(void) {
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   // Push-pull output mode
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  // IO port speed set to 50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_ResetBits(GPIOA, GPIO_Pin_0);  // Output 0 to discharge the capacitor

    delay_ms(5);
    TIM_ClearFlag(TIM5, TIM_FLAG_CC2 | TIM_FLAG_Update);  // Clear the flag
    TIM_SetCounter(TIM5, 0);                              // Reset the counter

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  // Floating input mode
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @brief Returns the captured high-level value after a touch event.
 *
 * This function first resets the touch key by discharging the capacitor, then recharging it and reset the timer.
 * It then waits for the capture of the Vcc, which means the charging capacitor is completed
 * and returns the elapsed time, which is TIM5->CC2 in this case.
 * If the timeout occurs, it returns the current counter value directly, TIM5->CNT.
 *
 * @param None.
 *
 * @return The captured high-level value after a touch event.
 */
uint16_t Touch_Get_Val(void) {
    Touch_Reset();
    // Wait for the capture of the Vcc meaning completing charging capacitor.
    while (TIM_GetFlagStatus(TIM5, TIM_FLAG_CC2) == 0) {
        // If the timeout occurs, return the current counter value directly.
        if (TIM_GetCounter(TIM5) > TOUCH_ARR_MAX_VAL - 500) {
            return TIM_GetCounter(TIM5);
        }
    }
    return TIM_GetCapture2(TIM5);  // Return the captured high-level value
}

/**
 * @brief Initializes the touch key and returns the initialization status.
 *
 * This function initializes the input capture for TIM5_CH2 with the given auto-reload value (ARR) and prescaler (PSC).
 * It then reads 10 times the high-level values during touching, ascendingly sorts them,
 * calculates their average, and stores it as the default value for touch events.
 * Finally, it checks if the initialized value exceeds Touch_ARR_MAX_VAL/2
 * and returns the initialization status accordingly.
 *
 * @param psc Prescaler value for the timer.
 *
 * @return 0 if the initialization is successful (the initialized value does not exceed Touch_ARR_MAX_VAL/2).
 * @return 1 if the initialization is unsuccessful (the initialized value exceeds Touch_ARR_MAX_VAL/2).
 */
unit8_t Touch_Key_Init(unit8_t psc) {
    unit8_t i;
    uint16_t buf[10];
    unit8_t j;
    uint16_t temp;
    TIM5_CH2_Input_Init(TOUCH_ARR_MAX_VAL, psc);

    for (i = 0; i < 10; i++) {  // Repeated reading 10 times charging time of the capacitor.
        buf[i] = Touch_Get_Val();
        delay_ms(10);
    }

    for (i = 0; i < 9; i++) {  // Sort in ascending order
        for (j = i + 1; j < 10; j++) {
            if (buf[i] > buf[j]) {
                temp = buf[i];
                buf[i] = buf[j];
                buf[j] = temp;
            }
        }
    }

    temp = 0;
    for (i = 2; i < 8; i++) {  // Sum the middle 6 values and calculate their average
        temp += buf[i];
    }
    touch_default_val = temp / 6;
    printf("touch_default_val=%d \r\n", touch_default_val);
    if (touch_default_val > TOUCH_ARR_MAX_VAL / 2) {
        return 1;  // If the initialized value exceeds Touch_ARR_MAX_VAL/2, it is considered abnormal
    }
    return 0;
}

/**
 * @brief Obtains the maximum value of the touch event samples.
 *
 * This function reads the specified number of times of the charging time of capacitor while touching,
 * obtains the maximum value from these samples, and returns it.
 *
 * @param n The number of times to read the charing time during touching.
 *
 * @return The maximum value obtained from the touch event samples.
 */
uint16_t Touch_Get_MaxVal(unit8_t n) {
    uint16_t temp = 0;
    uint16_t res = 0;
    while (n--) {
        temp = Touch_Get_Val();  // Get the value once
        if (temp > res)
            res = temp;  // Update the maximum value if the current value is greater
    }
    return res;
}

/**
 * @brief Scans the touch key and detects touch events.
 *
 * This function scans the touch key and detects touch events based on the specified mode.
 * In non-continuous touch detection mode, it returns 1 if a valid touch event is detected,
 * and 0 if no valid touch event is detected.
 * In continuous touch detection mode, it continuously detects touch events and returns 1
 * whenever a valid touch event is detected.
 *
 * @param mode The mode of touch detection.
 *             0: Non-continuous touch detection mode.
 *             1: Continuous touch detection mode.
 *
 * @return 1: a valid touch event is detected
 *         0: otherwise
 */
unit8_t Touch_Key_Scan(unit8_t mode) {
    static unit8_t keyen = 0;    // 0 means starting detecting; >0 means not starting detecting yet
    unit8_t ret = 0;             // Initialize result variable to 0
    unit8_t sample = 3;          // Default sampling times are 3
    uint16_t max_charging_time;  // Store the maximum charging time obtained from touch event samples

    if (mode) {
        sample = 6;  // If in continuous touch detection mode, set the sampling times to 6
        keyen = 0;   // Reset the keyen variable to start touch detection
    }

    max_charging_time = Touch_Get_MaxVal(sample);  // Obtain the maximum value of the touch event samples

    // If the obtained value is greater than touch_default_val + TOUCH_GATE_VAL and
    // less than 10 times touch_default_val, it is considered a valid touch event.
    if (max_charging_time > (touch_default_val + TOUCH_GATE_VAL) && max_charging_time < (10 * touch_default_val)) {
        // While in non-continue touch detection mode,
        // if the charging time is greater than touch_default_val + TOUCH_GATE_VAL,
        // it is considered a valid touch event.
        if ((keyen == 0) && (max_charging_time > (touch_default_val + TOUCH_GATE_VAL))) {
            ret = 1;  // Set the result variable to 1 to indicate a valid touch event
        }
        printf("Captured Vcc after touch event: %d\n", max_charging_time);  // Print the charging time to the console.
        // Set the keyen variable to 3 to indicate that at least 3 more samples need to be taken
        // before the touch event can be considered valid again.
        keyen = 3;
    }
    if (keyen)    // If keyen is not 0, it means that the function is not ready to detect a new touch event yet.
        keyen--;  // Decrement the keyen variable by 1.

    return ret;  // Return the result variable indicating whether a valid touch event was detected (1) or not (0)
}
