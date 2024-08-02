/**
 * @file usart_init.c
 * @brief Initializes USART1 with the given baud rate.
 *
 * This file contains the implementation of the USART1 initialization function and the corresponding interrupt handler.
 *
 * @author Yixiang Fan
 * @date 2024-08-02
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 */

#include "usart.h"

void USART1_Init(u32 bound) {
    // GPIO port settings
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    // Configure GPIO mode and IO pins
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;  // TX: Serial output PA9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;        // Alternate push-pull output
    GPIO_Init(GPIOA, &GPIO_InitStructure);                 // Initialize serial input IO
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;             // RX: Serial input PA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  // Floating input
    GPIO_Init(GPIOA, &GPIO_InitStructure);                 // Initialize GPIO

    // USART1 initialization settings
    USART_InitStructure.USART_BaudRate = bound;                                      // Baud rate setting
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                      // Word length is 8-bit data format
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                           // One stop bit
    USART_InitStructure.USART_Parity = USART_Parity_No;                              // No parity check
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;  // No hardware data flow control
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                  // Receive and transmit mode
    USART_Init(USART1, &USART_InitStructure);                                        // Initialize USART1

    USART_Cmd(USART1, ENABLE);  // Enable USART1

    USART_ClearFlag(USART1, USART_FLAG_TC);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  // Enable relevant interrupts

    // Usart1 NVIC configuration
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;          // USART1 interrupt channel
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  // Preemption priority 3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;         // Subpriority 3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;            // Enable IRQ channel
    NVIC_Init(&NVIC_InitStructure);                            // Initialize VIC registers
}

void USART1_IRQHandler(void) {  // USART1 interrupt service program
    unit8_t r;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {  // Receive interrupt
        r = USART_ReceiveData(USART1);                        // USART1->DR: Read the received data
        USART_SendData(USART1, r);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) != SET) {
        }
    }
    USART_ClearFlag(USART1, USART_FLAG_TC);
}
