#ifndef AES_N_H
#define AES_N_H


#ifdef __cplusplus
extern "C" {
#endif

#include "STANDARD_LIB.h"
#include "tremo_flash.h"
#include "tremo_system.h"
#include "drv.h"




void aes_ecb(U8 *datain, uint8_t inlength, U8 *dataout, U8 de_or_en,U8 *AES_KEY,uint8_t KEY_LENGTH);


uint8_t allocation(U8 **allocated_data_for, uint8_t inlength) ;




#ifdef __cplusplus
}
#endif

#endif