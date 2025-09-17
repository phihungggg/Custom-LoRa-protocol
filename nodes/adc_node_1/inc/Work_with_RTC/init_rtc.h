#ifndef INIT_RTC_H
#define INIT_RTC_H


#ifdef __cplusplus
extern "C" {
#endif


#include "STANDARD_LIB.h"
#include "enum_lora.h"


void rtc_calendar_setup();


void rtc_interval_setup( interval_t interval);



void rtc_interrupt_init ();




#ifdef __cplusplus
}
#endif

#endif