



#ifndef UART_TRANSMITTER_H
#define UART_TRANSMITTER_H



#ifdef __cplusplus
extern "C" {
#endif


#include "STANDARD_LIB.h"
#include "tremo_uart.h"
#include "tremo_gpio.h"
#include "tremo_rcc.h"
#include "tremo_delay.h"
#include "enum_lora.h"



void uart_send_data_array(uart_t* uartx, const uint8_t* data,uint8_t length, type_indicator transmit_uart_payload_type ,error_payload_type  transmit_error_payload_type);










#ifdef __cplusplus
}
#endif

#endif /* __LORA_CONFIG_H */