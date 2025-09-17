#ifndef REWRITE_DATA_TO_FLASH_H
#define REWRITE_DATA_TO_FLASH_H



#ifdef __cplusplus
extern "C" {
#endif




#include "STANDARD_LIB.h"
#include "tremo_flash.h"

#include "tremo_delay.h"






uint32_t jumping_jack ( uint32_t input_address );


uint32_t rewritedata (uint32_t beginning_address,uint8_t * size,uint8_t *datain,uint8_t sizeof_datain,uint8_t *later_size );




#ifdef __cplusplus
}
#endif

#endif /* __LORA_CONFIG_H */

