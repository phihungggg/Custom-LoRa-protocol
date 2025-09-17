#ifndef LORA_SEND_H
#define LORA_SEND_H
#ifdef __cplusplus
extern "C" {
#endif
#include <STANDARD_LIB.h>
#include "enum_lora.h"

Operation_state_t send_data_through_lora ( uint8_t *data_to_send , uint8_t size_of_data_send,uint32_t confaddr);







#ifdef __cplusplus

}
#endif

#endif /* __LORA_CONFIG_H */