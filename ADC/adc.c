/**
 * @file adc.c
 * @brief Source file for the ADC peripheral and functions.
 * @author Yixiang Fan
 * @date 2024-08-08
 * @copyright Copyright 2024 Yixiang Fan. All rights reserved.
 */

#include "adc.h"
#include "SysTick.h"

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
void ADCx_Init(void) {
    GPIO_InitTypeDef GPIO_InitStructure;  // Define structure variable
    ADC_InitTypeDef ADC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1, ENABLE);

    RCC_ADCCLKConfig(
        RCC_PCLK2_Div6);  // Set ADC clock division factor to 6, 72M/6=12, ADC maximum time should not exceed 14M

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;      // ADC
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;  // Analog input
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;        // Non-scan mode
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;  // Disable continuous conversion
    ADC_InitStructure.ADC_ExternalTrigConv =
        ADC_ExternalTrigConv_None;                          // Disable trigger detection, use software trigger
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;  // Right alignment
    ADC_InitStructure.ADC_NbrOfChannel = 1;  // 1 conversion in the rule sequence, i.e., only convert rule sequence 1
    ADC_Init(ADC1, &ADC_InitStructure);      // ADC initialization

    ADC_Cmd(ADC1, ENABLE);  // Enable ADC

    ADC_ResetCalibration(ADC1);  // Reset the calibration register of the specified ADC
    while (ADC_GetResetCalibrationStatus(ADC1)) {
    }  // Get the status of the ADC reset calibration register

    ADC_StartCalibration(ADC1);  // Start the calibration status of the specified ADC
    while (ADC_GetCalibrationStatus(ADC1)) {
    }  // Get the calibration status of the specified ADC

    // Enable or disable the software conversion start function of the specified
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

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
uint16_t Get_ADC_Value(unit8_t ch, unit8_t times) {
    uint32_t temp_val = 0;
    uint8_t t;
    // Set the specified ADC regular channel, a sequence, and sampling time
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5);  // ADC1, ADC channel, 239.5 cycles

    for (t = 0; t < times; ++t) {
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);  // Enable the software conversion start function of the specified ADC1
        while (!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)) {}  // Wait for the conversion to end
        temp_val += ADC_GetConversionValue(ADC1);
        delay_ms(5);
    }
    return temp_val / times;
}
