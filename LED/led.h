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
 * @brief LED initialization function.
 *
 * This function initializes the LED port and sets it to push-pull output mode.
 * The LED is initially turned off by setting the port pin to high.
 *
 * @param void
 * @return void
 */
void LED_Init(void);

#endif  // LED_LED_H_
