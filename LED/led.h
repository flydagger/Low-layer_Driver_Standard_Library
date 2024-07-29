/**
 * @file led.h
 * @brief LED initialization function.
 * @author Yixiang Fan
 * @date 2024-07-29
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 *
 * This file contains the implementation of the LED initialization function.
 */

#ifndef LED_LED_H_
#define LED_LED_H_

/*  defind RCC and pin of LED */
#define LED_PORT GPIOC
#define LED_PIN (GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7)
#define LED_PORT_RCC RCC_APB2Periph_GPIOC

/**
 * @brief Initializes the LEDs on the STM32F10x board.
 *
 * This function configures the GPIO pins connected to the LEDs as output pins.
 * The LEDs are connected to the GPIOC port, and the pins used are GPIO_Pin_0 to GPIO_Pin_7.
 * The function also enables the clock for the GPIOC peripheral.
 *
 * @param None
 *
 * @return None
 */
void LED_Init(void);

#endif  // LED_LED_H_
