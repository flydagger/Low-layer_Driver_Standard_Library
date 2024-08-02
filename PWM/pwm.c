/**
 * @file pwm.c
 * @brief This file contains the implementation of the PWM initialization function for TIM3 channel 1.
 * @author Yixiang Fan
 * @date 2024-08-02
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 */

#include "pwm.h"

/**
 * @brief Initializes the PWM for TIM3 channel 1 using the provided period and prescaler values.
 *
 * This function configures the GPIO, timer, and output compare settings for TIM3 channel 1 to generate a PWM signal.
 * The function enables the necessary clocks, configures the GPIO pin for alternate function, sets up the timer base,
 * and initializes the output compare channel. It also enables the preload registers and enables the timer.
 *
 * @param per The auto-reload value for the timer. This determines the PWM period.
 * @param psc The prescaler factor for the timer. This controls the PWM frequency.
 *
 * @return void
 */
void TIM3_CH1_PWM_Init(uint16_t per, uint16_t psc) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    /* Enable clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    /* Configure GPIO mode and IO pins */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  // Alternate push-pull output
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);  // Change pin mapping

    TIM_TimeBaseInitStructure.TIM_Period = per;     // Auto-reload value
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;  // Prescaler factor
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  // Set up count mode
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);  // Output compare channel 1 initialization

    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  // Enable TIMx preload register on CCR1
    TIM_ARRPreloadConfig(TIM3, ENABLE);                // Enable preload register

    TIM_Cmd(TIM3, ENABLE);  // Enable timer
}
