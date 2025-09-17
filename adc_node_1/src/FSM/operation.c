#include "Work_with_FSM/operation.h"



#include "Work_with_FSM/operation_funcs/lora_funcs/lora_get_config.h"
#include "Work_with_FSM/operation_funcs/operation_funcs.h"
#include "Work_with_FSM/operation_funcs/lora_funcs/lora_callback.h"

#include "Work_with_FSM/operation_funcs/lora_funcs/lora_send.h"

#include "tremo_delay.h"




#include "radio.h"


#include "enum_lora.h"


#include "Work_with_interrupt/Work_with_interrupt_gpio/interrupt_gpio.h"


#include "Work_with_TIMER/GPTIMER/gptimer_header.h"





#include "structs_with_pointer_functions.h"





#include "Work_with_RTC/init_rtc.h"


#include "Work_with_FSM/operation_funcs/lora_funcs/lora_get_config_func/lora_get_config_funcs.h"


#include "Work_with_ADC/Adc_t.h"

#include "tremo_rtc.h"



#include "tremo_pwr.h"

#include "tremo_uart.h"

#define INIT_VALUE_TOGGLE_LEFT_FOR_WARNING_LED 6


        typedef enum {

        SEND_REQUEST_PAIRING,
        WAITING_FOR_RANDOM_VALUE,

        SEND_PUBLIC_KEY ,

        WAITING_FOR_PUBLIC_KEY,
        RECEIVED_PUBLIC_KEY,    


        SEND_BACK_CONFIRMATION
        

        }PAIRING_STATE; 


uint8_t *downlink_data ; 


//buttons global variables
gpio_t *g_test_gpiox = GPIOA;

//user_button
uint8_t g_test_pin = GPIO_PIN_11;
volatile uint32_t g_gpio_interrupt_flag = 0;
static uint32_t  conf_addr_global ; 
//notification led 
uint8_t led_pin = GPIO_PIN_15;
volatile uint8_t rtc_flag = 0 ; 

 interval_t take_interval_from_flash (){
    uint8_t interval_array[4] ;
    interval_t interval_from_flash;

    bool check = get_param_from_flash(PROPERTY_ADDRESS_JUMP[INTERVAL_NUM],conf_addr_global,(void*)interval_array); 

    if ( check == false )
    {
        printf(" error for sure \n");
        while (1) {
        }
    }
    interval_from_flash.hour = interval_array [1];
    interval_from_flash.minute = interval_array[2];
    interval_from_flash.second = interval_array[3];
    return interval_from_flash;

}

uint8_t* convert_from_float_to_4_bytes (float input );


uint32_t combine_time_to_number(uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);


void wait_til_uart_tx_is_done  () {
                while (uart_get_flag_status(UART0, UART_FLAG_BUSY) == SET ||
            uart_get_flag_status(UART0, UART_FLAG_TX_FIFO_EMPTY) == RESET) {

}
}

Operation_state_t  operation_state = DONOTHING_OPERATION_STATE;

void operate( uint32_t conf_addr){

    printf(" does it here \n");
    conf_addr_global = conf_addr;
    config_lora_transmit(conf_addr);
    rtc_calendar_setup();    
    rtc_interval_setup(take_interval_from_flash());
    rtc_interrupt_init();

printf(" does it go here 2 ? \n");

    float dco_value ; 
    float gain_value ;
    float calibrated_value =0.0 ; 
 Adc_continue_mode_test(&gain_value, &dco_value);


 PAIRING_STATE pairing_state = SEND_REQUEST_PAIRING;

printf(" does it go here \n");

interrupt_init(g_test_gpiox,g_test_pin, GPIO_INTR_FALLING_EDGE,GPIO_MODE_INPUT_PULL_UP);

gpio_init(g_test_gpiox, led_pin,  GPIO_MODE_OUTPUT_PP_LOW );
    
    while(1)
    {
        if ( rtc_flag==1 )
        {
            rtc_flag = 0 ; 
            printf(" rtc  does works  \n");

                wait_til_uart_tx_is_done ();
                operation_state = TAKE_DATA_FROM_SENSORS_OPERATION_STATE;

         // Vòng lặp rỗng để chờ
     }
            //pwr_deepsleep_wfi(PWR_LP_MODE_STOP3);
            
           
        
        Radio.IrqProcess();
        
        switch (operation_state)
        {   


            case PAIRING :

                switch (pairing_state){


                    case SEND_REQUEST_PAIRING:
                    break;

                    case WAITING_FOR_RANDOM_VALUE:
                    break;

                    case RECEIVE_PUBLIC_KEY :
                    break;

                    case 
                }




            


            break;



            case REMOVE_FLASH_BUTTON_PRESSED_OPERATION_STATE:
            break;
            case TAKE_DATA_FROM_SENSORS_OPERATION_STATE :

            calibrated_value = Take_analog_data(gain_value , dco_value );
            printf(" calibration value la \n " );
            printf("%f \n ", calibrated_value);

           
            wait_til_uart_tx_is_done () ;    
           operation_state = SEND_DATA_THROUGH_LORA_OPERATION_STATE;

            //operation_state = GO_TO_SLEEP_OPERATION_STATE;
            break;  
            case SEND_DATA_THROUGH_LORA_OPERATION_STATE:

         
            uint8_t *bytes = convert_from_float_to_4_bytes ( calibrated_value);

            printf("  in thu data sau khi chuyen tu float sang byte  \n ");

            for ( int i = 0 ; i < 4 ; ++i){
                printf(" data thu %d la %d \n",i,bytes[i]);

            }
            wait_til_uart_tx_is_done () ;    
            rtc_calendar_t rtc_calendar;

             rtc_get_calendar(&rtc_calendar);



             printf(" gio in thu calendar tung thanh phan \n");


             printf("  thang %d \n",rtc_calendar.month);
             printf("  ngay %d \n",rtc_calendar.day);
             printf("  gio %d \n",rtc_calendar.hour);
             printf("  phut %d \n",rtc_calendar.minute);
             printf("   giay  %d \n",rtc_calendar.second);


            uint32_t times_mdhms= combine_time_to_number(rtc_calendar.month,rtc_calendar.day,rtc_calendar.hour,rtc_calendar.minute,rtc_calendar.second);


               operation_state =  send_data_through_lora (bytes, 4, conf_addr,times_mdhms);
             //operation_state = GO_TO_SLEEP_OPERATION_STATE;
             
            break;
            case DONOTHING_OPERATION_STATE:

            break;

            case GO_TO_SLEEP_OPERATION_STATE :
           printf(" go to sleep right now \n");
           wait_til_uart_tx_is_done();
            operation_state = TAKE_DATA_FROM_SENSORS_OPERATION_STATE;
            for ( int i = 0 ; i < 1000 ; ++i ){
            }

            rtc_interval_setup(take_interval_from_flash());
            rtc_interrupt_init();
            pwr_deepsleep_wfi(PWR_LP_MODE_STOP1);
            break;
            case TX_TIMEOUT_OPERATION_STATE:

                printf(" tx time out \n");

                for ( int i = 0 ; i < 100 ; ++i){
                }
                operation_state = GO_TO_SLEEP_OPERATION_STATE;
            break;
            
        }
    }

}











void OnTxDone( void )
{
    operation_state = GO_TO_SLEEP_OPERATION_STATE ; 

    
    Radio.Sleep ();
    
}

void OnRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr )
{
  

   
}

void OnTxTimeout( void )
{

 operation_state = TX_TIMEOUT_OPERATION_STATE;
}

void OnRxTimeout( void )
{
   

 

}

void OnRxError( void )
{
  

 
}






void rtc_IRQHandler(void)
{
    uint8_t intr_stat;

    intr_stat = rtc_get_status( RTC_CYC_SR  );
    if (intr_stat == true) {
        rtc_flag = 1 ; 
        rtc_config_interrupt(RTC_CYC_IT , DISABLE);
        rtc_set_status(RTC_CYC_SR , false);
        rtc_config_interrupt(RTC_CYC_IT , ENABLE);
        rtc_check_syn();
       // rtc_cyc_cmd( false);
    }
}













// CAC HAM DUNG TAI CHO  , KHONG VIET THANH HEADER :







uint8_t* convert_from_float_to_4_bytes (float input){ // muc dich cua ham nay la chuyen float sang 4 byte de lora transfer 


    uint8_t* return_bytes = (uint8_t*)calloc(4,sizeof(uint8_t));


    if (return_bytes == NULL)
    {
        printf(" memory allocation failed  \n");
        return 1 ;

    }


    memcpy(return_bytes , &input ,sizeof(float) );
    return return_bytes;

}





uint32_t combine_time_to_number(uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second) {
    uint32_t number = 0;
    number = month * 100000000 + day * 1000000 + hour * 10000 + minute * 100 + second;
    return number;
}












// CAC ham giai quyet cac loi o call back Error hoac timeout 












