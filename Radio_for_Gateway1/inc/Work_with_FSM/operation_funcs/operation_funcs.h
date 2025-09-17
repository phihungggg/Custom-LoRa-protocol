#ifndef OPERATION_FUNCS_H
#define OPERATION_FUNCS_H
#ifdef __cplusplus
extern "C" {
#endif
#include <STANDARD_LIB.h>
#include "enum_lora.h"




Operation_state_t prepare_data_for_ACK( uint8_t *data_to_send);


Operation_state_t check_if_uart_command_suitable_or_not (uint8_t* rx_buf , uint8_t size );




#ifdef __cplusplus

}
#endif

#endif /* __LORA_CONFIG_H */