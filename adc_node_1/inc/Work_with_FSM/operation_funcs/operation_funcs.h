#ifndef OPERATION_FUNCS_H
#define OPERATION_FUNCS_H
#ifdef __cplusplus
extern "C" {
#endif
#include <STANDARD_LIB.h>
#include "enum_lora.h"


#include "tremo_rcc.h"
#include "tremo_system.h"

#include "tremo_gpio.h"

Operation_state_t take_data_from_sensor ( uint8_t *data_to_send);






Operation_state_t toggle_led (gpio_t *gpiox, uint8_t gpio_pin) ;


    


#ifdef __cplusplus

}
#endif

#endif /* __LORA_CONFIG_H */