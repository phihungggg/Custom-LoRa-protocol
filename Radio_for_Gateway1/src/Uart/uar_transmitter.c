#include "Work_with_uart/uart_transmitter.h"
void uart_send_data_array(uart_t* uartx, const uint8_t* data,uint8_t length,type_indicator transmit_uart_payload_type,error_payload_type  transmit_error_payload_type ){
switch (transmit_uart_payload_type)
{
case UPLINK_PAYLOAD:
        for ( uint8_t i =0; i <= length+1;++i)
        {
        if ( i ==0 )
        {   
            //uint8_t a = 0 ; 
            //printf("%d\n",a);
            uart_send_data(uartx,0);
        }
            else if ( i == 1 )
            {
                uart_send_data(uartx,length);
             // printf("%d\n",length);
            }
            else
            {
            uart_send_data(uartx,*(data-2));

           // printf("%d\n",*(data-2));
            }
            data++;
        }
        break;


        
case ERROR_PAYLOAD:
            uart_send_data(uartx,1);
            uint16_t count = 0 ; 
            while (1){
            count ++;
            if ( count == 500)
            break;
            }
            switch( transmit_error_payload_type)
            {
                case RX_ERROR:
                printf("rxerror\n");
                break;
                case RX_TIMEOUT_NOTIFY:
                printf("rxtimeout\n");
                break;
                case TX_ERROR:
                printf("txerror\n");
                break;
                case TX_TIMEOUT_NOTIFY:
                printf("txtimeout\n");
                break;
            }
break;
default:
break;
}





















}