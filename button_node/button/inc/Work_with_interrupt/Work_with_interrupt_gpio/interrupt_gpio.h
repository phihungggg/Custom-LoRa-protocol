#ifndef INTERRUPT_GPIO_H
#define INTERRUPT_GPIO_H




#ifdef __cplusplus
extern "C" {
#endif

// Your declarations go here
// For example:
// void debug_print(const char* message);


#include "STANDARD_LIB.h"
#include "tremo_rcc.h"
#include "tremo_system.h"

#include "tremo_gpio.h"

/**
 * @brief  Cộng hai số nguyên.
 * @param  a: Số nguyên thứ nhất.
 * @param  b: Số nguyên thứ hai.
 * @retval Tổng của a và b.
 */

 void interrupt_init(gpio_t *gpiox, uint8_t  gpio_pin, gpio_intr_t intr_type,gpio_mode_t mode_of_that_pin);


#ifdef __cplusplus
}
#endif

#endif // DEBUG_DATA_H