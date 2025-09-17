#ifndef TOGGLE_GPIO_PIN_H
#define TOGGLE_GPIO_PIN_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <STANDARD_LIB.h>
//#include <enum_lora.h>
#include <tremo_gpio.h>
//#include "tremo_system.h"
uint8_t Toggle_GPIO_PIN(gpio_t* gpiox,uint8_t pin, uint32_t interval_each_toggle_session,bool will_you_stop_toggle);

#ifdef __cplusplus
}
#endif

#endif /* __LORA_CONFIG_H */

