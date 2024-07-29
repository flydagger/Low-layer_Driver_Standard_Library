/**
 * @file system.h
 * @brief Header file for GPIO bit-band operations on STM32F10x microcontrollers.
 * @author Yixiang Fan
 * @date 2024-07-29
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 *
 * This file contains macro definitions for GPIO bit-band operations, which allow for efficient manipulation
 * of individual bits in memory-mapped registers. The macros are used to perform input and output operations
 * on specific GPIO ports, and they are designed to work with the STM32F10x microcontroller family.
 */

#ifndef BIT_BAND_SYSTEM_H_
#define BIT_BAND_SYSTEM_H_

#include "stm32f10x.h"

// GPIO port bit-band operation macro definition
#define BITBAND(addr, bitnum) ((addr & 0xF0000000) + 0x2000000 + ((addr & 0xFFFFF) << 5) + (bitnum << 2))
#define MEM_ADDR(addr) *((volatile uint32_t *)(addr))
#define BIT_ADDR(addr, bitnum) MEM_ADDR(BITBAND(addr, bitnum))

// GPIO port address mapping
#define GPIOA_ODR_Addr (GPIOA_BASE + 12)  // 0x4001080C
#define GPIOB_ODR_Addr (GPIOB_BASE + 12)  // 0x40010C0C
#define GPIOC_ODR_Addr (GPIOC_BASE + 12)  // 0x4001100C
#define GPIOD_ODR_Addr (GPIOD_BASE + 12)  // 0x4001140C
#define GPIOE_ODR_Addr (GPIOE_BASE + 12)  // 0x4001180C
#define GPIOF_ODR_Addr (GPIOF_BASE + 12)  // 0x40011A0C
#define GPIOG_ODR_Addr (GPIOG_BASE + 12)  // 0x40011E0C

#define GPIOA_IDR_Addr (GPIOA_BASE + 8)  // 0x40010808
#define GPIOB_IDR_Addr (GPIOB_BASE + 8)  // 0x40010C08
#define GPIOC_IDR_Addr (GPIOC_BASE + 8)  // 0x40011008
#define GPIOD_IDR_Addr (GPIOD_BASE + 8)  // 0x40011408
#define GPIOE_IDR_Addr (GPIOE_BASE + 8)  // 0x40011808
#define GPIOF_IDR_Addr (GPIOF_BASE + 8)  // 0x40011A08
#define GPIOG_IDR_Addr (GPIOG_BASE + 8)  // 0x40011E08

// GPIO port operation, only for a single GPIO port!
// Ensure that the value of n is less than 16!
#define PAout(n) BIT_ADDR(GPIOA_ODR_Addr, n)  // Output
#define PAin(n) BIT_ADDR(GPIOA_IDR_Addr, n)  // Input

#define PBout(n) BIT_ADDR(GPIOB_ODR_Addr, n)  // Output
#define PBin(n) BIT_ADDR(GPIOB_IDR_Addr, n)  // Input

#define PCout(n) BIT_ADDR(GPIOC_ODR_Addr, n)  // Output
#define PCin(n) BIT_ADDR(GPIOC_IDR_Addr, n)  // Input

#define PDout(n) BIT_ADDR(GPIOD_ODR_Addr, n)  // Output
#define PDin(n) BIT_ADDR(GPIOD_IDR_Addr, n)  // Input

#define PEout(n) BIT_ADDR(GPIOE_ODR_Addr, n)  // Output
#define PEin(n) BIT_ADDR(GPIOE_IDR_Addr, n)  // Input

#define PFout(n) BIT_ADDR(GPIOF_ODR_Addr, n)  // Output
#define PFin(n) BIT_ADDR(GPIOF_IDR_Addr, n)  // Input

#define PGout(n) BIT_ADDR(GPIOG_ODR_Addr, n)  // Output
#define PGin(n) BIT_ADDR(GPIOG_IDR_Addr, n)  // Input

#endif  // BIT_BAND_SYSTEM_H_
