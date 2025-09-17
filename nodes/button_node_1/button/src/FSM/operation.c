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





#define INIT_VALUE_TOGGLE_LEFT_FOR_WARNING_LED 6


uint8_t *downlink_data ; 









//buttons global variables
gpio_t *g_test_gpiox = GPIOA;

//user_button
uint8_t g_test_pin = GPIO_PIN_11;
volatile uint32_t g_gpio_interrupt_flag = 0;







//timer0  global variables 
timer_gp_t * GLOBAL_TIMER_IN_THIS_FILE= TIMER0;
timer_sr_t GLOBAL_TIMER_SR_TYPE_IN_THIS_FILE =  TIMER_SR_UIF;
volatile uint8_t timer0_interrupt_flag = 0; // Declare flag as volatile




//timer1 global variables

timer_gp_t * GLOBAL_TIMER_IN_THIS_FILE_2= TIMER1;
volatile uint8_t timer1_interrupt_flag  = 0;




//notification led 
uint8_t led_pin = GPIO_PIN_15;




void gptim0_IRQHandler(void);


Operation_state_t  operation_state = DONOTHING;

void operate( uint32_t conf_addr){





        //init timer 
    rcc_enable_peripheral_clk(RCC_PERIPHERAL_TIMER0, true);    
    GLOBAL_TIMER_IN_THIS_FILE = TIMER0;
    GLOBAL_TIMER_SR_TYPE_IN_THIS_FILE = TIMER_SR_UIF;



    gptimer_simple_timer(GLOBAL_TIMER_IN_THIS_FILE,UPDATE_INTERRUPT,23999,TIMER_COUNTERMODE_UP,7000,FDTS_EQUAL_FPCLK,REINITIALIZE_THE_COUNTER_AND_GENERATES_AND_UPDATE,GLOBAL_TIMER_SR_TYPE_IN_THIS_FILE);
   

    NVIC_SetPriority(TIMER0_IRQn, 4);
    NVIC_EnableIRQ(TIMER0_IRQn);
    

   // timer_cmd(GLOBAL_TIMER_IN_THIS_FILE, false);


    config_lora_transmit(conf_addr);
    uint8_t button_pressed [] = {1};
    uint32_t count = 0 ;
    uint32_t count2 = 0 ; 


// here is where you will let your program know how many times should the led warning toggle 




            uint8_t  how_many_toggle_left_for_warning_led = INIT_VALUE_TOGGLE_LEFT_FOR_WARNING_LED;

            bool do_you_need_to_toggle_led_again = false ; 



            bool stop_toggle_for_now = true;


    bool you_have_to_toggle= false ;

    bool you_are_allowed_to_press_again  = true ; 



interrupt_init(g_test_gpiox,g_test_pin, GPIO_INTR_FALLING_EDGE,GPIO_MODE_INPUT_PULL_UP);



gpio_init(g_test_gpiox, led_pin,  GPIO_MODE_OUTPUT_PP_LOW );
    
    while(1)
    {
        Radio.IrqProcess();
        count ++;
        count2++;

        if ( count == 5000000  )
           {
            
            you_are_allowed_to_press_again = true ; 
        count = 0;
           }
        if ( g_gpio_interrupt_flag==1)
        {

            g_gpio_interrupt_flag = 0 ; 
                printf(" interrupt does happens \n");

            if ( you_are_allowed_to_press_again == true)
            {
            operation_state = SEND_DATA_THROUGH_LORA;   
            you_are_allowed_to_press_again = false ; 
            }
        }

        else if ( timer0_interrupt_flag ==1     )
        {
            printf(" does time out \n");
            timer0_interrupt_flag = 0 ;

            timer_cmd(GLOBAL_TIMER_IN_THIS_FILE, false);
            operation_state = ERROR_HANDLING_WHEN_GATEWAY_NOT_RESPONSE;
            //you_have_to_toggle = true; 
                how_many_toggle_left_for_warning_led = INIT_VALUE_TOGGLE_LEFT_FOR_WARNING_LED;
            stop_toggle_for_now  = false;
                
        }


    
        switch (operation_state)
        {   
            case REMOVE_FLASH_BUTTON_PRESSED:
            break;
            case SEND_DATA_THROUGH_LORA:
            printf(" does happens \n");

            printf(" size of button pressed la %d \n",sizeof(button_pressed));
            operation_state =  send_data_through_lora(button_pressed,sizeof(button_pressed),conf_addr);
            break;
            case LISTEN:
            Radio.Rx(0);
            printf(" does listen \n");
            timer_cmd(GLOBAL_TIMER_IN_THIS_FILE, true);
            operation_state = DONOTHING;
            break;
            case TOGGLE_LED_WHEN_DOWNLINK_RECEIVED:
            break;

            case DONOTHING:
            


            if ( do_you_need_to_toggle_led_again == true  && how_many_toggle_left_for_warning_led != 0  )
            {
                do_you_need_to_toggle_led_again = false;

                how_many_toggle_left_for_warning_led -- ; 
                printf("%d",how_many_toggle_left_for_warning_led);
                gpio_toggle ( g_test_gpiox,led_pin);

                if ( how_many_toggle_left_for_warning_led == 0 )
                {   
                    printf(" here ? \n "); 
                    stop_toggle_for_now = true;

                }
                
            }
            
            break;
            case ERROR_HANDLING_WHEN_GATEWAY_NOT_RESPONSE:
        
        //    printf(" %d \n" ,count2);
            Radio.Sleep();
     
            


            do_you_need_to_toggle_led_again = true ; 
            
            
            operation_state = DONOTHING ;

            


            break;
            case ERROR_HANDLING_WHEN_RECEIVE_WRONG_PACKET:
            break;
    
            case WRONG_ADDRESS:

            break; 
            
            case HANDLING_INCOMING_DOWNLINK :

        
            break;

            case REICEIVED:
            break;

            case RTC_INTERVAL_OPERATE:
            break;

 



        }

        if ( count2 == 500000)
        {   



            if (
                 stop_toggle_for_now == false
            )
            do_you_need_to_toggle_led_again = true ; 

            count2 = 0 ;
            // printf(" you have  to toggle , hehe \n");
        }

        



    }

}














void OnTxDone( void )
{

printf(" On tx done  \n");



operation_state = LISTEN;
    
}

void OnRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr )
{
  

    printf(" On rx done  \n");

    printf(" downlink is \n");


    downlink_data = (uint8_t *) calloc (size,sizeof(uint8_t));


    downlink_data =  payload ;


    for ( int i = 0 ; i <size;++i)
    {   printf(" %c ",*(payload+i));



    }

    operation_state=HANDLING_INCOMING_DOWNLINK;
}

void OnTxTimeout( void )
{

    printf(" On tx timeout  \n");

    operation_state = DONOTHING;
 
}

void OnRxTimeout( void )
{
   

    printf(" on rx timeout \n");

operation_state= ERROR_HANDLING_WHEN_GATEWAY_NOT_RESPONSE;


}

void OnRxError( void )
{
  

    printf(" on rx error \n");
    operation_state= ERROR_HANDLING_WHEN_GATEWAY_NOT_RESPONSE;
}






void GPIO_IRQHandler(void)
{
    if (gpio_get_interrupt_status(g_test_gpiox, g_test_pin) == SET) {
        gpio_clear_interrupt(g_test_gpiox, g_test_pin);
        g_gpio_interrupt_flag = 1;
    }
}









// CAC HAM DUNG TAI CHO  , KHONG VIET THANH HEADER :






void gptim0_IRQHandler(void)
{
    bool state;

    timer_get_status(GLOBAL_TIMER_IN_THIS_FILE, GLOBAL_TIMER_SR_TYPE_IN_THIS_FILE, &state);

    if (state) {
        timer_clear_status(GLOBAL_TIMER_IN_THIS_FILE, GLOBAL_TIMER_SR_TYPE_IN_THIS_FILE);
        timer0_interrupt_flag = 1;
    }
}








void TIMER0_IRQHandler(void)
{
    gptim0_IRQHandler();
}




// CAC ham giai quyet cac loi o call back Error hoac timeout 









void dealing_with_tx_timeout ()  {


    printf(" tutu roi code tiep nha \n");


}






void TIMER1_IRQHandler(void)
{
    gptim1_IRQHandler();
}





void gptim1_IRQHandler(){

    bool state;

    timer_get_status(GLOBAL_TIMER_IN_THIS_FILE_2, GLOBAL_TIMER_SR_TYPE_IN_THIS_FILE, &state);

    if (state) {
        timer_clear_status(GLOBAL_TIMER_IN_THIS_FILE_2, GLOBAL_TIMER_SR_TYPE_IN_THIS_FILE);
        timer1_interrupt_flag = 1;
    }

}



