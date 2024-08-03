/**
 * @file main.c
 * @brief Main program file for input capture using STM32F10x microcontroller.
 * @author Yixiang Fan
 * @date 2024-08-03
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 */

#include "SysTick.h"
#include "input.h"
#include "led.h"
#include "system.h"
#include "usart.h"

int main() {
    unit8_t i = 0;
    unit32_t indata = 0;

    SysTick_Init(72);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  // Configure interrupt priority groups
    LED_Init();
    USART1_Init(9600);
    TIM5_CH1_Input_Init(0xffff, 71);  // Initialize input capture with 1 MHz frequency

    while (1) {
        if (TIM5_CH1_CAPTURE_STA & 0x80) {  // Successful capture
            indata = TIM5_CH1_CAPTURE_STA & 0x3f;
            indata *= 0xffff;                // Multiply overflow times by the count time of a single count
            indata += TIM5_CH1_CAPTURE_VAL;  // Accumulate the time of high-level capture
            printf("High-level duration: %d us\r\n", indata);  // Display the total high-level time
            TIM5_CH1_CAPTURE_STA = 0;                          // Start the next capture
        }

        i++;
        if (i % 20 == 0) {
            led1 = !led1;  // Toggle LED1 every 20 iterations
        }
        delay_ms(10);
    }
}
