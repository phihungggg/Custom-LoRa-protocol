#ifndef PINGPONG_H
#define PINGPONG_H



#ifdef __cplusplus
extern "C" {
#endif
#include "STANDARD_LIB.h"

#include "delay.h"
#include "timer.h"
#include "radio.h"
#include "tremo_system.h"
#include "tremo_uart.h"
#include "tremo_delay.h"



#define TEST_ADDR 0x0800D000

#define CONF_ADDR (TEST_ADDR + 4096)


int app_start (void);






#ifdef __cplusplus
}
#endif

#endif /* __LORA_CONFIG_H */