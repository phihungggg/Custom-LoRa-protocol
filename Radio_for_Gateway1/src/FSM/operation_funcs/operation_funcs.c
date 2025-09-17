#include  "Work_with_FSM/operation_funcs/operation_funcs.h"







#define UART_COMMAND_LIST {"REMOVE_FLASH","SEND_DOWNLINK"}


typedef enum {
    UART_REMOVE_FLASSH,
    UART_SEND_DOWNLINK,

}Uart_command_list_t;




Operation_state_t prepare_data_for_ACK( uint8_t *data_to_send){
    Operation_state_t operate_state = PREPARE_DATA_ACK_SEND_TO_NODE;
            for ( int i =0;  i<8;++i)
            {   
                data_to_send[i] = i;
            }
            operate_state = SEND_DATA_THROUGH_LORA;
    return  operate_state;
}




Operation_state_t   check_if_uart_command_suitable_or_not (uint8_t* rx_buf , uint8_t size ){

Operation_state_t result= LISTEN;

const uint8_t *uart_command_list[] = UART_COMMAND_LIST;


uint8_t  list_size = sizeof(uart_command_list) / sizeof(uart_command_list[0]);

bool check_if_suitable_command = false;



for ( int i =0 ; i<list_size;++i)
{   
    printf(" chuoi thu %d la %s \n" ,i,uart_command_list[i]);

    printf(" input la %s \n",rx_buf+1);

    if (strncmp( ( const char* )(rx_buf+1), ( const char* )uart_command_list[i], strlen((char *)uart_command_list[i])) == 0  && size == strlen((char *)uart_command_list[i]) ) 
    {   

        printf(" does exist %d \n", i );
        
            switch (i)
            {
                case UART_REMOVE_FLASSH:
                result = REMOVE_FLASH_HAPPENING;

                printf(" uart remove flash \n");

                break;
                case UART_SEND_DOWNLINK:
                result = WAITING_SEND_DATA_THROUGH_LORA;
                printf(" waiting_send_data_through_lora  \n");
                break;

                default:
                printf(" error input uart command \n");
                break;
            }
        check_if_suitable_command = true;
        break;  
    }

    



    
}


if ( check_if_suitable_command == false)
{
    printf(" command type is not suitable , please refill \n");

result = LISTEN;
}




return result;
}









