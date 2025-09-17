#include "Work_with_uart/filter_uart_receive.h"


uint8_t* filter_uart_input(uint8_t size_of_uart,uint8_t *input  ){
    uint8_t *return_string = (uint8_t*)malloc(size_of_uart * sizeof(uint8_t)) ;
    for ( int i =1;i<=(size_of_uart);++i){
        *(return_string+(i-1))= *(input+i);
    }


    printf(" in thu ben trong filter uart data :\n");

    for ( int i =0 ; i<size_of_uart;++i){

        printf("%d", *(return_string+i));
    }
    return return_string;
}






