




#ifndef TAKE_AUTHENTICATION_INFORMATION_FROM_FLASH_H
#define TAKE_AUTHENTICATION_INFORMATION_FROM_FLASH_H



#ifdef __cplusplus
extern "C" {
#endif





#include <STANDARD_LIB.h>



void get_username_and_password ( uint32_t address_you_chose , uint8_t **username_data,uint8_t **password_data, uint32_t *real_address_of_user_name, uint32_t *real_address_of_password,uint8_t *size_of_username,uint8_t *size_of_password);


#ifdef __cplusplus
}
#endif

#endif /* __LORA_CONFIG_H */