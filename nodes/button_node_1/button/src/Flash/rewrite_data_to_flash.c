

#include "Work_with_flash_memory/rewrite_data_to_flash.h"


#include "Work_with_flash_memory/dealing_with_flash.h"













uint32_t rewritedata (uint32_t beginning_address, uint8_t * size ,uint8_t *datain,uint8_t sizeof_datain,uint8_t *later_size){


    uint8_t *data_return;

    uint32_t final_address ;
     

    uint32_t global_size=0;


    

    printf( " bat dau ham rewrite \n ");
  


  printf(" dia chi luc dau : 0x%08X  \n ",beginning_address);





    uint32_t init_address = beginning_address;
    uint32_t temp_address = beginning_address;

    while (1) {

        if ( *((volatile uint8_t*)(temp_address )) == 0xFF)
        {
            //printf(" it is over \n ");
            break;
        }
        global_size = global_size+ 1 + *((volatile uint8_t*)(temp_address ));
     temp_address= jumping_jack ( temp_address);
       // printf(" temp address tam thoi  tiep theo la 0x%08X ",temp_address);


    }










//printf ( " kiem tra global size %d  ", global_size);

uint8_t * get_data = take_data_from_flash_memory(global_size,init_address);

//printf(" lay data ra xem nhu the nao \n ");


/*
for ( int i =0;i<global_size;++i){
printf(" byte index :%d ",i);
printf(" %d",*(get_data+i));

}
*/



uint16_t final_global_size = global_size + sizeof_datain;


*later_size = final_global_size;

for ( int i =global_size;i<final_global_size;++i)
{
    get_data[i] = datain[i-global_size];
}



//printf(" lay data ra xem nhu the nao lan hai \n ");

for ( int i =0;i<final_global_size;++i){
    printf(" byte index :%d ",i);
    printf(" %d",*(get_data+i));
    
    }

    
    


uint32_t ending_address;

flash_erase_page(init_address);

uint8_t result_flash_data=  flash_data_to_memory(get_data,final_global_size,init_address,&ending_address);





uint8_t *getdata2 = take_data_from_flash_memory(final_global_size,init_address);








//printf(" lay data ra xem nhu the nao lan ba \n ");

for ( int i =0;i<final_global_size;++i){
printf(" byte index :%d ",i);
printf(" %d",*(getdata2+i));

}






//uint32_t latersize= global_size+ sizeof_datain;




free(get_data);

free(getdata2);





return ending_address;

}












uint32_t jumping_jack ( uint32_t input_address )
{

uint32_t begin_addr = input_address;

uint8_t value =  *((volatile uint8_t*)(input_address));

return begin_addr + value+1;


}