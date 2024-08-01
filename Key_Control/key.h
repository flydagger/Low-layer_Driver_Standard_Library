/**
 * @file key.h
 * @brief This file contains the declarations and definitions for the keypad module.
 * @author Yixiang Fan
 * @date 2024-08-01
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 *
 * The keypad module is responsible for initializing the GPIO pins used for keypad scanning,
 * providing functions to scan the keypad for a pressed key, and handling the key press events.
 */

#ifndef KEY_CONTROL_KEY_H_
#define KEY_CONTROL_KEY_H_

#include "system.h"

#define KEY_LEFT_Pin    GPIO_Pin_2    // Define K_LEFT pin
#define KEY_DOWN_Pin    GPIO_Pin_3    // Define K_DOWN pin
#define KEY_RIGHT_Pin   GPIO_Pin_4   // Define K_RIGHT pin
#define KEY_UP_Pin      GPIO_Pin_0  // Define KEY_UP pin

#define KEY_Port GPIOE  // Define port
#define KEY_UP_Port GPIOA  // Define port

// Use bitwise operation definitions
#define K_UP    PAin(0)
#define K_DOWN  PEin(3)
#define K_LEFT  PEin(2)
#define K_RIGHT PEin(4)

// Use library function definitions for reading pin status
// #define K_UP      GPIO_ReadInputDataBit(KEY_UP_Port,KEY_UP_Pin)
// #define K_DOWN    GPIO_ReadInputDataBit(KEY_Port,KEY_DOWN_Pin)
// #define K_LEFT    GPIO_ReadInputDataBit(KEY_Port,KEY_LEFT_Pin)
// #define K_RIGHT   GPIO_ReadInputDataBit(KEY_Port,KEY_RIGHT_Pin)

// Define key values
#define KEY_UP    1
#define KEY_DOWN  2
#define KEY_LEFT  3
#define KEY_RIGHT 4

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
void KEY_Init(void);

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
uint8_t KEY_Scan(uint8_t mode);

#endif  // KEY_CONTROL_KEY_H_
