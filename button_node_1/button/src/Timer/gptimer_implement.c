#include "Work_with_TIMER/GPTIMER/gptimer_header.h"





void gptimer_simple_timer(timer_gp_t* TIMERx,timer_interrupt_t timer_interrupt_type,uint32_t prescaler,timer_count_mode_t counter_mode,uint32_t period,timer_ckd_t  clock_division , timer_egr_t  egr_event,timer_sr_t status)
{
    timer_init_t timerx_init;

    timer_config_interrupt(TIMERx, timer_interrupt_type, ENABLE);

    timerx_init.prescaler          = prescaler; 
    timerx_init.counter_mode       = counter_mode;
    timerx_init.period             = period;  
    timerx_init.clock_division     = clock_division;
    timerx_init.autoreload_preload = false;
    timer_init(TIMERx, &timerx_init);

    timer_generate_event(TIMERx, egr_event, ENABLE);
    timer_clear_status(TIMERx, status);

   
}




