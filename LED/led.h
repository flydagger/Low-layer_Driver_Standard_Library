#ifndef _led_H
#define _led_H

#include "stm32f10x.h"

/*  defind RCC and pin of LED */
#define LED_PORT 			GPIOC
#define LED_PIN 			(GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7)
#define LED_PORT_RCC		RCC_APB2Periph_GPIOC

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

#endif
