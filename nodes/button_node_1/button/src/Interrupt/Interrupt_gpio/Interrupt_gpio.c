#include "Work_with_interrupt/Work_with_interrupt_gpio/interrupt_gpio.h"





void interrupt_init(gpio_t *gpiox, uint8_t  gpio_pin, gpio_intr_t intr_type,gpio_mode_t mode_of_that_pin){


    gpio_init(gpiox,gpio_pin,mode_of_that_pin);
    gpio_config_interrupt(gpiox,gpio_pin,intr_type);
    NVIC_EnableIRQ(GPIO_IRQn);
    NVIC_SetPriority(GPIO_IRQn, 2);
}








