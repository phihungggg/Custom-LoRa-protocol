#ifndef ADC_T_H
#define ADC_T_H


#ifdef __cplusplus
extern "C" {
#endif


#include "STANDARD_LIB.h"

#include "tremo_gpio.h"

#include "tremo_adc.h"

void Adc_continue_mode_test(float *gain_value, float* dco_value);

float Take_analog_data (float gain_value, float dco_value);
#ifdef __cplusplus
}
#endif

#endif