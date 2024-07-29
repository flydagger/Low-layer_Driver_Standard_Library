/**
 * @file led.c
 * @brief LED initialization function.
 * @author Yixiang Fan
 * @date 2024-07-29
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 *
 * This file contains the implementation of the LED initialization function.
 */

/**
 * @brief LED initialization function.
 *
 * This function initializes the LED port and sets it to push-pull output mode.
 * The LED is initially turned off by setting the port pin to high.
 *
 * @param void
 * @return void
 */
void LED_Init() {
    GPIO_InitTypeDef GPIO_InitStructure;  // Define structure variable

    // Enable the clock for the LED port
    RCC_APB2PeriphClockCmd(LED_PORT_RCC, ENABLE);

    // Configure the LED pin
    GPIO_InitStructure.GPIO_Pin = LED_PIN;  // Select the pin to be configured
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // Set output mode to push-pull
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;  // Set the output speed
    GPIO_Init(LED_PORT, &GPIO_InitStructure);  // Initialize the GPIO

    // Set the LED port pin to high to turn off the LED
    GPIO_SetBits(LED_PORT, LED_PIN);
}
