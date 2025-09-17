#ifndef TAKE_BYTE_FROM_FLASH_H
#define TAKE_BYTE_FROM_FLASH_H


#ifdef __cplusplus
extern "C" {
#endif

#include "STANDARD_LIB.h"

uint8_t take_byte_from_flash(uint32_t beginning_address,  uint8_t count,uint8_t *output_byte,uint32_t *address_after_jump);


#ifdef __cplusplus
}
#endif

#endif /* __LORA_CONFIG_H */