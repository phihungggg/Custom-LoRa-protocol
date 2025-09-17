#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#ifdef __cplusplus
extern "C" {
#endif
#include <STANDARD_LIB.h>

#include <enum_lora.h>




Stage_t Configuration (uint32_t conf_address ,uint8_t checkbyte,int count ,States_Config_t *output_state,uint8_t *rx_buf,uint16_t *rx_index,bool *new_data_available,uint16_t *lora_buf_size,uint8_t *configdata, uint8_t *current_index);


#ifdef __cplusplus
}
#endif


#endif /* __LORA_CONFIG_H */