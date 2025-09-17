




#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H
#ifdef __cplusplus
extern "C" {
#endif
#include <STANDARD_LIB.h>
#include "enum_lora.h"



Stage_t Authentication (uint32_t authentication_address ,uint8_t checkbyte,int count ,States_Authentication_t *output_state,uint8_t *rx_buf,uint16_t *rx_index,bool *new_data_available,uint16_t *lora_buf_size ,bool *is_user_name_correct,bool *is_password_correct);


#ifdef __cplusplus
}
#endif

#endif /* __LORA_CONFIG_H */