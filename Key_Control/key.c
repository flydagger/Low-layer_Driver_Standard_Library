/**
 * @file key.c
 * @brief This file contains the implementation of key input handling functions.
 * @author Yixiang Fan
 * @date 2024-08-01
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 *
 * The key.c file provides functions for initializing the key input pins using GPIO and
 * scanning the key inputs to detect the pressed key. The KEY_Init() function configures
 * the GPIO pins for the key inputs, and the KEY_Scan() function continuously scans the
 * key inputs and returns the pressed key.
 */

#include "key.h"
#include "SysTick.h"

/**
 * @brief Initializes the key input pins using GPIO.
 *
 * This function configures the GPIO pins for the key inputs (K_UP, K_DOWN, K_LEFT, K_RIGHT)
 * by setting the appropriate pin, mode, and speed. The function uses the GPIO_InitTypeDef
 * structure to define the initialization parameters and then calls the GPIO_Init() function
 * to apply the settings.
 *
 * @param void No parameters are required for this function.
 *
 * @return void The function does not return any value.
 */
void KEY_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;  // Define structure variable
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE, ENABLE);

    GPIO_InitStructure.GPIO_Pin = KEY_UP_Pin;  // Select the IO pin you want to set
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;  // Pull-down input
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  // Set the transmission speed
    GPIO_Init(KEY_UP_Port, &GPIO_InitStructure);  // Initialize GPIO

    GPIO_InitStructure.GPIO_Pin = KEY_DOWN_Pin | KEY_LEFT_Pin | KEY_RIGHT_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  // Pull-up input
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(KEY_Port, &GPIO_InitStructure);
}

/**
 * @brief Scans the key inputs and returns the pressed key.
 *
 * This function continuously scans the key inputs (K_UP, K_DOWN, K_LEFT, K_RIGHT) and
 * returns the pressed key. It implements a debounce mechanism to ensure accurate key
 * detection. The function also supports continuous key press detection based on the
 * provided mode parameter.
 *
 * @param mode An unit8_t value indicating the mode of key scanning.
 *              - 0: Non-continuous key press detection. The function returns the
 *                   first detected key press and stops scanning until no key is pressed.
 *              - 1: Continuous key press detection. The function continuously scans
 *                   for key presses and returns the detected key press.
 *
 * @return An unit8_t value representing the pressed key.
 *         - 0: No key is pressed.
 *         - KEY_UP: The K_UP key is pressed.
 *         - KEY_DOWN: The K_DOWN key is pressed.
 *         - KEY_LEFT: The K_LEFT key is pressed.
 *         - KEY_RIGHT: The K_RIGHT key is pressed.
 */
unit8_t KEY_Scan(unit8_t mode) {
    static unit8_t key = 1;
    if (key == 1 && (K_UP == 1 || K_DOWN == 0 || K_LEFT == 0 || K_RIGHT == 0)) {  // While any key is pressed
        delay_ms(10);  // Debounce
        key = 0;
        if (K_UP == 1) {
            return KEY_UP;
        } else if (K_DOWN == 0) {
            return KEY_DOWN;
        } else if (K_LEFT == 0) {
            return KEY_LEFT;
        } else {
            return KEY_RIGHT;
        }
    } else if (K_UP == 0 && K_DOWN == 1 && K_LEFT == 1 && K_RIGHT == 1) {  // No key is pressed
        key = 1;
    }
    if (mode == 1) {  // Continuous key press
        key = 1;
    }
    return 0;
}
