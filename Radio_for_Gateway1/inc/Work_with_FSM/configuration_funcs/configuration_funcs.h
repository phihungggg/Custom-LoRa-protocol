


#ifndef CONFIGURATION_FUNCS_H
#define CONFIGURATION_FUNCS_H
#ifdef __cplusplus
extern "C" {
#endif
#include <STANDARD_LIB.h>
#include "enum_lora.h"



States_Config_t node_id_set (uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index);


States_Config_t key_set1(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index,uint16_t *rx_index);

States_Config_t key_set2(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index,uint16_t *rx_index);


States_Config_t key_set3(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index,uint16_t *rx_index);


States_Config_t key_set4(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index,uint16_t *rx_index);


States_Config_t key_set_result(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index,uint16_t *rx_index);



States_Config_t tx_power_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index);

States_Config_t interval_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index);

States_Config_t threshold_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index);


States_Config_t frequency_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index);
States_Config_t bandwidth_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index);

States_Config_t spreading_factor_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index);

States_Config_t codingrate_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index);

States_Config_t preamblelen_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index);


States_Config_t symbltimeout_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index);

States_Config_t fixlen_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index);

States_Config_t payloadlen_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index);


States_Config_t crcon_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index);

States_Config_t freqhopn_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index);


States_Config_t hopperiod_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index);


States_Config_t iqinverted_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index);


//States_Config_t rxcontinous_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index);

States_Config_t tx_timeout_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index ,Stage_t *output_stage);

States_Config_t add_data_to_flash_memory (uint32_t conf_address ,uint32_t *addresslater ,uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t config_data_current_index ,Stage_t *output_stage);


#ifdef __cplusplus

}
#endif

#endif /* __LORA_CONFIG_H */