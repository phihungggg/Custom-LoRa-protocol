#ifndef STRUCTS_LORA_H
#define STRUCTS_LORA_H



#ifdef __cplusplus
extern "C" {
#endif




#include <stdio.h>

#include <STANDARD_LIB.h>

#include <enum_lora.h>

#include <tremo_gpio.h>


#include "tremo_system.h"






typedef struct {
uint8_t days;
uint8_t hours;
uint8_t minutes;
uint8_t seconds;

}Times_properties_t;





#ifdef __cplusplus
}
#endif

#endif /* __LORA_CONFIG_H */