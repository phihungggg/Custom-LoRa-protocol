#include "Work_with_RTC/init_rtc.h"


#include "tremo_rtc.h"


void rtc_calendar_setup(){

    rtc_calendar_t time            = { 2019, 4, 12, 12, 23, 58, 19, 0 };
   
    rtc_set_calendar(&time);
    rtc_calendar_cmd(true);
}


void rtc_interval_setup( interval_t interval){
    uint32_t hours_to_seconds = (interval.hour)*3600;
    uint32_t minutes_to_seconds = (interval.minute)*60;
    uint32_t general_ticks = hours_to_seconds + minutes_to_seconds + interval.second;
    rtc_config_cyc_max(general_ticks*32768);
    rtc_config_cyc_wakeup(ENABLE);
    rtc_config_interrupt(RTC_CYC_IT , ENABLE);
    rtc_cyc_cmd( true);     
}





void rtc_interrupt_init (){

    NVIC_EnableIRQ(RTC_IRQn);
    NVIC_SetPriority(RTC_IRQn, 1);

}