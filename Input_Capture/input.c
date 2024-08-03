/**
 * @file input.c
 * @brief Input capture configuration for TIM5 using STM32F10x microcontroller.
 * @author Yixiang Fan
 * @date 2024-08-03
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 */

#include "input.h"

unit8_t TIM5_CH1_CAPTURE_STA;   // Input capture status
uint16_t TIM5_CH1_CAPTURE_VAL;  // Input capture value

/**
 * @brief Initializes the TIM5 timer for input capture.
 *
 * This function configures the GPIO, timer, and interrupt for input capture on channel 1 of TIM5.
 * The timer is set up with the given auto-reload value (arr) and prescaler (psc).
 * The input capture is configured to capture rising edges, with a filter of 0x00.
 * The interrupt for update and capture events is enabled, and the NVIC is configured for the TIM5 interrupt.
 *
 * @param arr Auto-reload value for the timer.
 * @param psc Prescaler value for the timer.
 */
void TIM5_CH1_Input_Init(uint16_t arr, uint16_t psc) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);  // Enable TIM5 clock

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;      // Pin configuration
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;  // Set pull-down input mode
    GPIO_Init(GPIOA, &GPIO_InitStructure);         // Initialize GPIO

    TIM_TimeBaseInitStructure.TIM_Period = arr;     // Auto-reload value
    TIM_TimeBaseInitStructure.TIM_Prescaler = psc;  // Prescaler
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  // Set up count mode
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStructure);

    TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;                 // Channel 1
    TIM_ICInitStructure.TIM_ICFilter = 0x00;                         // Filter
    TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;      // Capture polarity
    TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;            // Prescaler
    TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;  // Direct mapping to TI1
    TIM_ICInit(TIM5, &TIM_ICInitStructure);
    TIM_ITConfig(TIM5, TIM_IT_Update | TIM_IT_CC1, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;            // Interrupt channel
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  // Preemption priority
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;         // Subpriority
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            // Enable IRQ channel
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM5, ENABLE);  // Enable timer
}

/**
 * @brief Interrupt handler for TIM5.
 *
 * This function handles the interrupt for TIM5. It checks for update and capture interrupts,
 * and updates the capture status and value accordingly.
 */
void TIM5_IRQHandler(void) {
    if ((TIM5_CH1_CAPTURE_STA & 0x80) == 0) {                 // Not yet successfully captured
        if (TIM_GetITStatus(TIM5, TIM_IT_Update)) {           // Update interrupt occurred
            if (TIM5_CH1_CAPTURE_STA & 0x40) {                // Captured high level
                if ((TIM5_CH1_CAPTURE_STA & 0x3f) == 0x3f) {  // High level time too long
                    TIM5_CH1_CAPTURE_STA |= 0x80;             // Flag successful capture
                    TIM5_CH1_CAPTURE_VAL = 0xffff;
                } else {
                    TIM5_CH1_CAPTURE_STA++;
                }
            }
        }
        if (TIM_GetITStatus(TIM5, TIM_IT_CC1)) {  // Capture interrupt occurred
            if (TIM5_CH1_CAPTURE_STA & 0x40) {    // Captured low level
                TIM5_CH1_CAPTURE_STA |= 0x80;     // Successfully captured one high level
                TIM5_CH1_CAPTURE_VAL = TIM_GetCapture1(TIM5);
                TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Rising);  // Set rising edge capture
            } else {
                TIM5_CH1_CAPTURE_STA = 0;
                TIM5_CH1_CAPTURE_VAL = 0;
                TIM5_CH1_CAPTURE_STA |= 0x40;  // Captured high level flag
                TIM_Cmd(TIM5, DISABLE);
                TIM_SetCounter(TIM5, 0);                              // Timer initial value is 0
                TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Falling);  // Set falling edge capture
                TIM_Cmd(TIM5, ENABLE);
            }
        }
    }
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1 | TIM_IT_Update);
}
