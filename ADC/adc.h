/**
 * @file adc.h
 * @brief Header file for the ADC peripheral and functions.
 * @author Yixiang Fan
 * @date 2024-08-08
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 */

#ifndef ADC_ADC_H_
#define ADC_ADC_H_

#include "system.h"

/**
 * @brief Initializes the ADC peripheral and GPIO for analog input.
 *
 * This function configures the ADC1 peripheral and GPIOA pin 1 for analog input.
 * It sets the ADC clock division factor to 6, ensuring the ADC maximum time does not exceed 14M.
 * The ADC is initialized in independent mode, non-scan mode, and continuous conversion is disabled.
 * Trigger detection is disabled, and the software trigger is used.
 * The ADC data is right-aligned, and only rule sequence 1 is converted.
 * The ADC is then enabled, and the calibration registers are reset and started.
 * Finally, the software conversion start function is enabled.
 *
 * @param void
 * @return void
 */
void ADCx_Init(void);

/**
 * @brief Retrieves the average ADC value for a specified channel and number of times.
 *
 * This function sets the specified ADC regular channel, a sequence, and sampling time.
 * It then performs the ADC conversion the specified number of times, accumulating the values.
 * The function returns the average of the accumulated ADC values.
 *
 * @param ch The ADC channel to be converted.
 * @param times The number of times to perform the ADC conversion and accumulate the values.
 * @return The average ADC value.
 */
uint16_t Get_ADC_Value(unit8_t ch, unit8_t times);

#endif  // ADC_ADC_H_
