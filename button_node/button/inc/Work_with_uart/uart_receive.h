



#ifndef UART_RECEIVE_H
#define UART_RECEIVE_H



#ifdef __cplusplus
extern "C" {
#endif


#include "STANDARD_LIB.h"
#include "tremo_uart.h"
#include "tremo_gpio.h"
#include "tremo_rcc.h"
#include "tremo_delay.h"




void uart_init_config(void);
bool handle_uart_rx(uint16_t *lora_buf_size,uint8_t *rx_buf,uint16_t *rx_index);
char* run_uart(void); // prototype











#ifdef __cplusplus
}
#endif

#endif /* __LORA_CONFIG_H */