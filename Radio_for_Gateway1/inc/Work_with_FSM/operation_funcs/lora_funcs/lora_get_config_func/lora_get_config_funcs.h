#ifndef LORA_GET_CONFIG_FUNCS_H
#define LORA_GET_CONFIG_FUNCS_H
#ifdef __cplusplus
extern "C" {
#endif
#include <STANDARD_LIB.h>
#include "enum_lora.h"

/*
uint32_t get_frequenc_from_flash(uint8_t where_to_get);
int8_t get_tx_power_from_flash(uint8_t where_to_get);
uint32_t get_bandwidth_from_flash(uint8_t where_to_get);
uint32_t get_datarate_aka_spreadingfactor_from_flash(uint8_t where_to_get);
uint8_t get_coderate_from_flash(uint8_t where_to_get);
uint16_t get_preamble_len_from_flash(uint8_t where_to_get);
bool get_fix_len_from_flash(uint8_t where_to_get);
bool get_crc_on_from_flash(uint8_t where_to_get);
bool get_freqhoppon_from_flash(uint8_t where_to_get);
uint8_t get_hopperiod_from_flash(uint8_t where_to_get);
bool get_iqInverted_from_flash(uint8_t where_to_get);
uint32_t get_timeout_from_flash(uint8_t where_to_get);
*/




bool get_param_from_flash(uint8_t where_to_get,uint32_t conf_addr, void *result) ;
#ifdef __cplusplus

}
#endif

#endif /* __LORA_CONFIG_H */