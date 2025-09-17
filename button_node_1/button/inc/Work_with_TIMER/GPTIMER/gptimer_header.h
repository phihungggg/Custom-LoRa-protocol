





#ifndef GPTIMER_HEADER_H
#define GPTIMER_HEADER_H




#ifdef __cplusplus
extern "C" {
#endif

// Your declarations go here
// For example:
// void debug_print(const char* message);


#include "STANDARD_LIB.h"

#include "tremo_rcc.h"
#include "tremo_timer.h"




//For timer_interrupt_t

#define UPDATE_INTERRUPT  TIMER_DIER_UIE
#define CAPTURE_OR_COMPARE_0_INTERRUPT TIMER_DIER_CC0IE
#define CAPTURE_OR_COMPARE_1_INTERRUPT TIMER_DIER_CC1IE
#define CAPTURE_OR_COMPARE_2_INTERRUPT TIMER_DIER_CC2IE
#define CAPTURE_OR_COMPARE_3_INTERRUPT TIMER_DIER_CC3IE
#define TRIGGER_INTERRUPT  TIMER_DIER_TIE





//For timer_egr_t
#define  REINITIALIZE_THE_COUNTER_AND_GENERATES_AND_UPDATE      TIMER_EGR_UG 
#define A_CAPTURE_OR_COMPARE_EVENT_IS_GENERATED_ON_CHANNEL_0    TIMER_EGR_CC0G
#define A_CAPTURE_OR_COMPARE_EVENT_IS_GENERATED_ON_CHANNEL_1    TIMER_EGR_CC1G
#define A_CAPTURE_OR_COMPARE_EVENT_IS_GENERATED_ON_CHANNEL_2    TIMER_EGR_CC2G
#define A_CAPTURE_OR_COMPARE_EVENT_IS_GENERATED_ON_CHANNEL_3    TIMER_EGR_CC3G
#define A_TRIGGER_EVENT_IS_GENERATED                            TIMER_EGR_TG





//For timer_ckd_t


#define FDTS_EQUAL_FPCLK                TIMER_CKD_FPCLK_DIV1
#define FDTS_EQUAL_FPCLK_DIVIDED_BY_2   TIMER_CKD_FPCLK_DIV2
#define FDTS_EQUAL_FPCLK_DIVIDED_BY_4   TIMER_CKD_FPCLK_DIV4
#define RESERVED                        TIMER_CKD_FPCLK_RESV







void gptimer_simple_timer(timer_gp_t* TIMERx,timer_interrupt_t timer_interrupt_type,uint32_t prescaler,timer_count_mode_t counter_mode,uint32_t period,timer_ckd_t  clock_division , timer_egr_t  egr_event,timer_sr_t status);





#ifdef __cplusplus
}
#endif

#endif // DEBUG_DATA_H




