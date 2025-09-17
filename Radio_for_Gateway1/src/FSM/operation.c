#include "Work_with_FSM/operation.h"



#include "Work_with_FSM/operation_funcs/lora_funcs/lora_get_config.h"
#include "Work_with_FSM/operation_funcs/operation_funcs.h"
#include "Work_with_FSM/operation_funcs/lora_funcs/lora_callback.h"

#include "Work_with_FSM/operation_funcs/lora_funcs/lora_send.h"

#include "tremo_delay.h"


#include "Work_with_uart/uart_receive.h"

#include "radio.h"


#include "Work_with_uart/uart_transmitter.h"





void add_indicator_and_send_data_uart ( uint8_t *payload ,uint8_t length ,uint8_t type_indicator) ;


Operation_state_t  operation_state = LISTEN;

void operate( uint32_t conf_addr){

   
  



    config_lora_transmit(conf_addr);

    uint8_t testdata[8];

bool new_data_available = false;
uint16_t lora_buf_size;

uint8_t rx_buf[200];
uint16_t rx_index=1; //always equal to 1 

    bool downlink_uart_incoming = false;

    while(1)
    {        
        Radio.IrqProcess(); 
        if (uart_get_interrupt_status(UART0, UART_INTERRUPT_RX_DONE) == SET||
        uart_get_interrupt_status(UART0, UART_INTERRUPT_RX_TIMEOUT) == SET) {
            uart_clear_interrupt(UART0, UART_INTERRUPT_RX_DONE);
            uart_clear_interrupt(UART0, UART_INTERRUPT_RX_TIMEOUT);

            printf(" uart receive does happens \n");
                //printf ( " handle uart normal \n");
            new_data_available=   handle_uart_rx(&lora_buf_size,rx_buf,&rx_index);   
            operation_state  = TAKE_COMMANDS_FROM_UART;
            if ( downlink_uart_incoming ==true ){
                downlink_uart_incoming = false ;


                operation_state = SEND_DATA_THROUGH_LORA;
            }
    }  
          
        switch (operation_state)
        {  
            case TAKE_COMMANDS_FROM_UART:
   
            operation_state = check_if_uart_command_suitable_or_not (rx_buf,lora_buf_size-2) ;
            break;
            case PREPARE_DATA_ACK_SEND_TO_NODE:
            operation_state = prepare_data_for_ACK(testdata);
            break;
            case REMOVE_FLASH_BUTTON_PRESSED:
            break;
            case REMOVE_FLASH_HAPPENING:
           // printf(" remove flash happening \n");
            operation_state = LISTEN;
            break;
            case WAITING_SEND_DATA_THROUGH_LORA:
            downlink_uart_incoming= true;
            break;
            case SEND_DATA_THROUGH_LORA:     
            //printf(" send data through lora state \n"); 
            operation_state =  send_data_through_lora(rx_buf+1,lora_buf_size-2);
            break;
            case LISTEN:
          //  printf(" listen start \n");
            Radio.Rx(0);
            operation_state = DONOTHING;
            break;
            case DONOTHING:
            break;
            case CHECK_AES_KEY:
            //printf(" check aes key \n");
            operation_state = LISTEN;
            break;
            case SYNCH_AES_KEY:
            //printf(" synch aes key \n");
            operation_state = LISTEN;
            break;
            case REICEIVED:
            break;
        }
        new_data_available =false;


    }

}














void OnTxDone( void )
{
operation_state = LISTEN;
    
}

void OnRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr )
{
 

    uart_send_data_array(UART0,payload,size,UPLINK_PAYLOAD,TRASH);
    
    for ( int i = 0 ; i < 10000;++i)

    operation_state= LISTEN;
}


void OnTxTimeout( void )
{


    uart_send_data_array(UART0,' ',0,ERROR_PAYLOAD,TX_TIMEOUT_NOTIFY);



    operation_state= LISTEN;
 
}

void OnRxTimeout( void )
{
   
uart_send_data_array(UART0,' ',0,ERROR_PAYLOAD,RX_TIMEOUT_NOTIFY);


operation_state=LISTEN;


}

void OnRxError( void )
{
    
    uart_send_data_array(UART0,' ',0,ERROR_PAYLOAD,RX_ERROR);


}







