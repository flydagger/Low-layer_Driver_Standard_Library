/**
 * @file hse.c
 * @brief Configures the High Speed External (HSE) clock, divides it, and sets the PLL.
 * @author Yixiang Fan
 * @date 2024-07-29
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 *
 * This file contains the implementation of the RCC_HSE_Config function, which configures the HSE clock,
 * divides it, and sets the PLL. It allows the user to customize the system time by modifying the clock.
 */

/**
 * @brief Configures the High Speed External (HSE) clock, divides it, and sets the PLL.
 *
 * This function allows the user to configure the HSE clock, set the division factor, and PLL multiplier.
 * It then enables the PLL and waits for it to be ready. Finally, it sets the system clock source to the PLL.
 *
 * @param div Division factor for the HSE clock. This parameter can be one of the following values:
 * - RCC_SYSCLK_Div1: HSE clock not divided
 * - RCC_SYSCLK_Div2: HSE clock divided by 2
 * - RCC_SYSCLK_Div4: HSE clock divided by 4
 * - RCC_SYSCLK_Div8: HSE clock divided by 8
 * - RCC_SYSCLK_Div16: HSE clock divided by 16
 *
 * @param pllm PLL multiplication factor. This parameter must be a number between 2 and 63.
 *
 * @return None
 */
void RCC_HSE_Config(uint32_t div, uint32_t pllm) {  // Customize system time (can modify clock)

    RCC_DeInit();  // Reset the peripheral RCC registers to their default values
    RCC_HSEConfig(RCC_HSE_ON);  // Set the external high-speed oscillator (HSE)
    if (RCC_WaitForHSEStartUp() == SUCCESS) {  // Wait for HSE to start up
        RCC_HCLKConfig(RCC_SYSCLK_Div1);  // Set the AHB clock (HCLK)
        RCC_PCLK1Config(RCC_HCLK_Div2);  // Set the low-speed AHB clock (PCLK1)
        RCC_PCLK2Config(RCC_HCLK_Div1);  // Set the high-speed AHB clock (PCLK2)
        RCC_PLLConfig(div, pllm);  // Set the PLL clock source and multiplication factor
        RCC_PLLCmd(ENABLE);  // Enable or disable the PLL
        // Check if the specified RCC flag is set or not, PLL ready
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) {}
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);  // Set the system clock (SYSCLK)
        // Return the clock source used as the system clock, 0x08: PLL as the system clock
        while (RCC_GetSYSCLKSource() != 0x08) {}
    }
}
