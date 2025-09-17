#ifndef DEALING_WITH_FLASH_H
#define DEALING_WITH_FLASH_H


#ifdef __cplusplus
extern "C" {
#endif

#include "STANDARD_LIB.h"
#include "tremo_flash.h"




int flash_data_to_memory( uint8_t *data_to_fill, uint32_t size_of_store_data,uint32_t test_addr_original,uint32_t *test_addr_later);



uint8_t* take_data_from_flash_memory(uint32_t size_of_store_data,uint32_t data_address_to_get);
#ifdef __cplusplus
}
#endif

#endif