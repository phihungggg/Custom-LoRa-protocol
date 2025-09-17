#include "Work_with_FSM/operation_funcs/lora_funcs/lora_send.h"


#include "radio.h"


Operation_state_t send_data_through_lora ( uint8_t *data_to_send , uint8_t size_of_data_send){

Operation_state_t result = DONOTHING;



printf(" in thu data se gui la \n");


for ( int i = 0 ; i<size_of_data_send ;++i)
{
    printf("%d \n", *(data_to_send+i));
}





/*
for ( int i = 0 ; i < size_of_data_send;++i)
{

    printf( "%c \n ", *(data_to_send+i));

}
    */



printf(" did send data through lora \n");
Radio.Send(data_to_send,size_of_data_send);


return result ;
    
}