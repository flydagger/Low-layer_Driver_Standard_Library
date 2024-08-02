/**
 * @file    timer.c
 * @brief   This file contains the implementation of the TIM4 timer initialization and interrupt handler.
 *          The TIM4 timer is configured to generate an interrupt on update event and toggle the LED2 state.
 * @author  Yixiang Fan
 * @date    2024-08-02
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 */

#include "time.h"
#include "led.h"

/**
 * @brief Initializes the TIM4 timer with the given period and prescaler values.
 *        Configures the timer to generate an interrupt on update event and enables the timer.
 *
 * @param per The auto-reload value for the timer.
 * @param psc The prescaler factor for the timer.
 *
 * @return void
 */
void TIM4_Init(uint16_t per, uint16_t psc) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  // Enable TIM4 clock

    TIM_TimeBaseInitStructure.TIM_Period = per;   // Auto-reload value
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;  // Prescaler factor
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  // Set up count mode
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);

    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);  // Enable timer interrupt
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);

    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  // Timer interrupt channel
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  // Preemption priority
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  // Sub-priority
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  // Enable IRQ channel
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM4, ENABLE);  // Enable timer
}

/**
 * @brief Interrupt handler for the TIM4 timer.
 *        Toggles the LED2 state when the timer generates an update event.
 *
 * @return void
 */
void TIM4_IRQHandler(void) {
    if (TIM_GetITStatus(TIM4, TIM_IT_Update)) {
        led2 = !led2;
    }
    TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
}
