#include "Work_with_ADC/Adc_t.h"


void Adc_continue_mode_test(float *gain_value, float* dco_value){

    uint32_t i;
    gpio_t *gpiox;
    uint32_t pin;
 

    adc_get_calibration_value(false, gain_value, dco_value);

    gpiox = GPIOA;
    pin = GPIO_PIN_8;
    gpio_init(gpiox, pin, GPIO_MODE_ANALOG);
   // pin = GPIO_PIN_11;
    //gpio_init(gpiox, pin, GPIO_MODE_ANALOG);

    adc_init();

    adc_config_clock_division(20); //sample frequence 150K

   // adc_config_sample_sequence(0, 1);
    adc_config_sample_sequence(0, 2);

    adc_config_conv_mode(ADC_CONV_MODE_DISCONTINUE);
    adc_enable(true);
  adc_start(true);

  while(!adc_get_interrupt_status(ADC_ISR_EOC));
  (void)adc_get_data();

}


float Take_analog_data (float gain_value, float dco_value){

    uint8_t digital_value ; 
adc_start(true);


while(!adc_get_interrupt_status(ADC_ISR_EOC));
(void)adc_get_data();   




adc_start(true);

while(!adc_get_interrupt_status(ADC_ISR_EOC));
digital_value= adc_get_data();

adc_start(false);
adc_enable(false);

float calibrated_value = ((1.2/4096) * digital_value - dco_value) / gain_value;

adc_enable(true);
return calibrated_value;
}