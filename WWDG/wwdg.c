/**
 * @file wwdg.c
 * @brief Window Watchdog (WWDG) peripheral driver for STM32F103C8T6 microcontroller.
 * @author Yixiang Fan
 * @date 2024-08-03
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 */

#include "wwdg.h"
#include "SysTick.h"
#include "led.h"

/**
 * @brief Initializes the Window Watchdog (WWDG) peripheral.
 *
 * This function configures the WWDG to operate with the specified window value, timer count value,
 * and prescaler. It also enables the WWDG interrupt and sets up the NVIC for the interrupt.
 *
 * @param None
 * @return None
 */
void WWDG_Init(void) {
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);  // Enable clock for window watchdog
    WWDG_SetWindowValue(0x5f);                            // Set window value
    WWDG_SetPrescaler(WWDG_Prescaler_8);                  // Set prescaler value

    NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;            // Window watchdog interrupt channel
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;  // Preemption priority
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;         // Subpriority
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            // Enable IRQ channel
    NVIC_Init(&NVIC_InitStructure);  // Initialize NVIC registers based on the specified parameters

    WWDG_Enable(0x7f);  // Enable window watchdog and initialize counter value
    WWDG_ClearFlag();   // Clear window watchdog status flag
    WWDG_EnableIT();    // Enable interrupt
}

/**
 * @brief Window Watchdog (WWDG) interrupt handler function.
 *
 * This function is called when the WWDG interrupt occurs. It reassigns the counter value, clears the
 * status flag, and toggles the LED2.
 *
 * @param None
 * @return None
 */
void WWDG_IRQHandler(void) {
    WWDG_SetCounter(0x7f);  // Reassign value
    WWDG_ClearFlag();       // Clear window watchdog status flag
    led2 = !led2;
}
