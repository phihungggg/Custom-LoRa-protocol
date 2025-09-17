#ifndef STRUCTS_WITH_POINTER_FUNCTIONS_H
#define STRUCTS_WITH_POINTER_FUNCTIONS_H
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <STANDARD_LIB.h>
#include <enum_lora.h>
#include <tremo_gpio.h>
#include "tremo_system.h"
typedef struct {
    uint8_t  (*Toggle_GPIO_PIN_state_when_GATEWAY_not_reponse) (gpio_t* gpiox,uint8_t pin, bool will_you_stop_toggle);
}error_handling;




extern const error_handling  error_handling_object ;
#ifdef __cplusplus
}
#endif

#endif /* __LORA_CONFIG_H */