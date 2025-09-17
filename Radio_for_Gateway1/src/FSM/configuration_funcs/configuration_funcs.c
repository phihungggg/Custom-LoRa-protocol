#include "Work_with_FSM/configuration_funcs/configuration_funcs.h"




#include "Work_with_bytes/check_hexa_input.h"


#include "Work_with_flash_memory/dealing_with_flash.h"


#include "Work_with_bytes/interval_format.h"





void checkconfigdata ( uint8_t config_data_index,uint8_t *config_data);


void extract_uint16_to_2_bytes(uint8_t *first_byte,uint8_t *second_byte,uint16_t input_num);





States_Config_t node_id_set (uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index) {
    States_Config_t   config_state = NODE_ID_SET;
    
    //printf(" ? \n");
    if ( new_data_available == true){
    
        printf(" node id set new data avaiable true \n");
        if ( (lora_buf_size-2 >0) && (lora_buf_size-2<=3))
        {
    
            printf(" node id is suitable \n");
          uint8_t  *nodeid= (uint8_t*)malloc(lora_buf_size * sizeof(uint8_t));
        for ( int i =1 ;i<lora_buf_size;++i)
            {   
                if( rx_buf[i] =='\n')
                {    
                    *(nodeid+(i-1)) = '\0';
                    break;
                }
                *(nodeid+(i-1)) = rx_buf[i];
                printf(" %d ",rx_buf[i]);
            } 

            int32_t node_id_byte_check = (uint16_t)atoi(nodeid);

            if ( node_id_byte_check <0){

                printf(" NODE ID be hon 0 , khong phu hop !! \n");

                return config_state;

            }



            uint16_t node_id_byte = node_id_byte_check;
            

             if (node_id_byte >255 ||node_id_byte<0){
                printf("not suitable id because bigger than 255 ! \n");   
                
                
             }
             else {
    
                    printf(" suitable node id byte \n");
    
                    uint8_t node_id_byte = (uint8_t)atoi(nodeid);
    
    
                    uint8_t root_case_address = *config_data_current_index;
    
    
                    config_data[(*config_data_current_index)++] =    1;
                    config_data[(*config_data_current_index)++]= node_id_byte;
    
    
                    printf(" node id la %d  \n",node_id_byte);
                 
                     for ( int i = root_case_address ; i <  (*config_data_current_index);++i)
                     {
    
                        printf(" config data  thu %d la nhu vay ne %d \n",i,config_data[i]);
    
                     }
    
                      printf("keyset1:\n");
                     config_state= KEY_SET1;
    
    
             }
             free(nodeid);
             nodeid=NULL;
    
        }
    }
    return config_state;
    
    }
    
    




States_Config_t key_set1(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index,uint16_t *rx_index)
{

    States_Config_t key = KEY_SET1;

    if ( new_data_available == true)
    {


        printf(" nhap key lan 1 \n");
        printf(" lora buf size -2 la %d",lora_buf_size-2);
    
        *rx_index=lora_buf_size;
        rx_buf[(*rx_index)-1] = ',';
        key = KEY_SET2;
    }



return key;
}



States_Config_t key_set2 (uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index,uint16_t *rx_index)
{

    
    States_Config_t key = KEY_SET2;


    if ( new_data_available == true)
    {


        printf(" nhap key lan 1 \n");
        printf(" lora buf size -2 la %d",lora_buf_size-2);
    
        *rx_index=lora_buf_size;
        rx_buf[(*rx_index)-1] = ',';
        key = KEY_SET3;
    }
    return key;

}



States_Config_t key_set3 (uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index,uint16_t *rx_index)
{

    
    States_Config_t key = KEY_SET3;

    if ( new_data_available == true)
    {


        printf(" nhap key lan 1 \n");
        printf(" lora buf size -2 la %d",lora_buf_size-2);
    
        *rx_index=lora_buf_size;
        rx_buf[(*rx_index)-1] = ',';
        key = KEY_SET4;
    }



    return key;


}



States_Config_t key_set4 (uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index,uint16_t *rx_index)
{

    
    States_Config_t key = KEY_SET4;


    if ( new_data_available == true)
    {


        printf(" nhap key lan 1 \n");
        printf(" lora buf size -2 la %d",lora_buf_size-2);
    
        *rx_index=lora_buf_size;
        rx_buf[(*rx_index)-1] = ',';

        printf(" KEY SET 4 \n");
        
        *rx_index=1;

        printf(" rx index la %d\n",*rx_index);
        key = KEY_SET_RESULT;
    }   

    return key;


}


States_Config_t key_set_result (uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index,uint16_t *rx_index)
{


    
    States_Config_t key_result = KEY_SET1;


    

    
    if ( lora_buf_size-2==159)
    {   
        uint8_t key_bytes[32] ;


        int num_bytes;



        num_bytes = parse_strict_hex_bytes(rx_buf+1,key_bytes,32);
        if( num_bytes ==32 )
        {
        
            for ( int i =0;i<32;++i)
            {

                printf("  0x%02X",key_bytes[i]);

            }
          //  key_result = TX_POWER_SET;
            config_data[(*(config_data_current_index))++]= 32;
            for ( int i =0 ;i<32;++i)
            {
                config_data [i+(*(config_data_current_index))] =key_bytes[i];
            }
            (*(config_data_current_index)) =(*(config_data_current_index)) +32;
        
            key_result = TX_POWER_SET;
        
        }
        else {

            printf("byteisnot32\n");
        }


     

        

    }else{

        printf(" not suitable !!! \n");

    }
                                            




    return key_result;


}





States_Config_t tx_power_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index){


    States_Config_t result = TX_POWER_SET;




    if(new_data_available==true){
 
    if ( lora_buf_size-2 >=1 && lora_buf_size-2<=2)
    {      

        uint8_t  *power= (uint8_t*)malloc(lora_buf_size * sizeof(uint8_t));

        for ( int i =1 ;i<lora_buf_size;++i)
        {   
            if( rx_buf[i] =='\n')
            {    
                *(power+(i-1)) = '\0';
                break;
            }
            *(power+(i-1)) = rx_buf[i];
            printf(" %d ",rx_buf[i]);
        } 

        int8_t power_byte_check= (int8_t)atoi(power);

        if ( power_byte_check < 0 )
        {
            printf(" small than 0 , not suitable \n");
            return result;
        }



        uint8_t  power_byte = power_byte_check;
        printf(" format dung roi do  \n");
        

        if (power_byte >22){
            printf("not suitable id because it is bigger than 22 ! \n");   

            return result;
         }
         else {
           
            
            config_data[(*(config_data_current_index))++]=1;
            config_data[(*(config_data_current_index))++]= power_byte;
            result = INTERVAL_SET;
            checkconfigdata(*(config_data_current_index),config_data);         
         }

         free(power);
         power=NULL;
    }
    else {
        printf(" tx output power sai format roi nha ! \n");
    }

}


return result;

  
}






States_Config_t interval_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index){

States_Config_t  result = INTERVAL_SET;

if (new_data_available==true){
    if ( (lora_buf_size)-2 ==11)
    {

        printf(" correct interval format  \n");

        rx_buf[lora_buf_size-1] = '\0';

        uint8_t time_bytes[4] ;


        int check = parse_time_string(rx_buf+1,time_bytes);

        if (check==0)
        {


            printf(" no error \n");

            config_data[(*(config_data_current_index)) ++] = sizeof(time_bytes);

            for ( int i =0 ; i <sizeof(time_bytes);++i)
            {
                config_data[i+(*config_data_current_index)]= time_bytes[i];


            }
            *config_data_current_index = (*config_data_current_index) + 4;


            for ( int i =0; i<*config_data_current_index;++i)
            {
                printf("%d \n",config_data[i]);
            }

            result = THRESHOLD_SET;
        
        }
        else{

            printf(" some error happens while parse time !! \n");

        }

    }
    else{


        printf("incorrect interval format \n");

    }
}



return result;
}








States_Config_t threshold_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index){


    States_Config_t result = THRESHOLD_SET;

    if(new_data_available==true){
 
    if ( lora_buf_size-2 >=1 && lora_buf_size-2<=3)
    {      

        uint8_t  *threshold= (uint8_t*)malloc(lora_buf_size * sizeof(uint8_t));

        for ( int i =1 ;i<lora_buf_size;++i)
        {   
            if( rx_buf[i] =='\n')
            {    
                *(threshold+(i-1)) = '\0';
                break;
            }
            *(threshold+(i-1)) = rx_buf[i];
            printf(" %d ",rx_buf[i]);
        } 

        int8_t threshold_byte_check= (int8_t)atoi(threshold);


        if ( threshold_byte_check < 0 )
        {
            printf("small than 0 , not suitable \n");
            return result;
        }



        uint8_t  threshold_byte = threshold_byte_check;
       // printf(" format dung roi do  \n");
        

        if (threshold_byte >100){
            printf("not suitable threshold because it is bigger than 100 ! \n");   

            return result;
         }
         else {
           
            
            config_data[(*(config_data_current_index))++]=1;
            config_data[(*(config_data_current_index))++]= threshold_byte;
            result = FREQUENCY_SET;
            checkconfigdata(*(config_data_current_index),config_data);         
         }



         free(threshold);
         threshold=NULL;

    }
    else {
        printf(" threshold sai format roi nha ! \n");
    }

}


return result;

  
}
















States_Config_t frequency_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index)
{
 
    
States_Config_t result = FREQUENCY_SET;


    if( new_data_available==true){
    if( lora_buf_size-2 ==9)
    {
        
        




        uint8_t  *frequency= (uint8_t*)malloc(lora_buf_size * sizeof(uint8_t));



        for ( int i =1 ;i<lora_buf_size;++i)
        {   
            if( rx_buf[i] =='\n')
            {    
                *(frequency+(i-1)) = '\0';
                break;
            }
            *(frequency+(i-1)) = rx_buf[i];
            printf(" %d ",rx_buf[i]);
        } 



        int64_t frequency_byte_check=strtol( frequency, NULL, lora_buf_size-1);




        if ( frequency_byte_check < 0 )
        {
            printf("small than 0 , not suitable \n");
            return result;
        }
        else {
            uint32_t frequency_byte = frequency_byte_check;

            const uint32_t AS923_FrequencyTable[20] = {
                923200000, // Index 0
                923400000, // Index 1
                923600000, // Index 2
                923800000, // Index 3
                924000000, // Index 4
                924200000, // Index 5
                924400000, // Index 6
                924600000, // Index 7
                924500000, // Index 8 - SF7BW250
                924800000, // Index 9
                925000000, // Index 10
                925200000, // Index 11
                925400000, // Index 12
                925600000, // Index 13
                925800000, // Index 14
                926000000, // Index 15
                926200000, // Index 16
                926400000, // Index 17
                926600000, // Index 18
                926800000  // Index 19
            };


            bool is_frequency_have = false;
            uint8_t get_frequency ;



            for ( uint8_t i =0 ; i < NUM_FREQ_CHANNELS;++i )
            {
                if ( frequency_byte == AS923_FrequencyTable[i])
                {
                    printf(" suitable frequency \n");



                    printf("%d",AS923_FrequencyTable[i]);
                    is_frequency_have=true;
                    get_frequency= i ;
                    break;
                    


                }

            }



            if (is_frequency_have==false){
                printf(" frequency is not suitable , please refill frequency ");
                return result;

            }else{
                config_data[(*config_data_current_index)++] =    1;
                config_data[(*config_data_current_index)++] =  get_frequency;  


                checkconfigdata(*config_data_current_index,config_data);

                result =  BANDWIDTH_SET;

            }



        }


    }
    

}


return result;
}









States_Config_t   bandwidth_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index)

{

    States_Config_t result = BANDWIDTH_SET;
if(new_data_available==true){
 
    if ( lora_buf_size-2 ==3 )
    {      

        uint8_t  *bandwidth= (uint8_t*)malloc(lora_buf_size * sizeof(uint8_t));

        for ( int i =1 ;i<lora_buf_size;++i)
        {   
            if( rx_buf[i] =='\n')
            {      
                *(bandwidth+(i-1)) = '\0';
                break;
            }
            *(bandwidth+(i-1)) = rx_buf[i];
            printf(" %d ",rx_buf[i]);
        } 


        char *endptr;


        long bandwidth_byte=  strtol(bandwidth,&endptr,10);


        if (*endptr == '\0'  ) {
            printf("So hop le: %ld\n", bandwidth_byte);
        } else {
            printf("Khong phai so hop le\n");

            return result;  

        }
      




        if (bandwidth_byte == 125  || bandwidth_byte ==250 || bandwidth_byte==500){
            printf ( " bandwidth byte la %d \n" ,bandwidth_byte);             
            config_data[(*(config_data_current_index))++]=1;
           config_data[(*(config_data_current_index))++]= bandwidth_byte;
            result = SPREADING_FACTOR_SET;
            checkconfigdata(*(config_data_current_index),config_data); 


        
         }
         else {
             
                printf("bandwidth not support\n ");
            return result;
         }

         



         free(bandwidth);
         bandwidth=NULL;

    }
    else {
        printf(" bandwidth sai format roi nha ! \n");
    }






    printf(" what is it  ? \n");
    


}



return result ;
}





States_Config_t spreading_factor_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index){

    States_Config_t result = SPREADING_FACTOR_SET;



    if ( new_data_available==true)
    {
    
        if ( lora_buf_size-2 >=1 &&  lora_buf_size-2<=2 )
        {



            uint8_t  *spreading_factor= (uint8_t*)malloc(lora_buf_size * sizeof(uint8_t));




        for ( int i =1 ;i<lora_buf_size;++i)
        {   
            if( rx_buf[i] =='\n')
            {      
                *(spreading_factor+(i-1)) = '\0';
                break;
            }
            *(spreading_factor+(i-1)) = rx_buf[i];
            printf(" %d ",rx_buf[i]);
        } 




        



        char *endptr;


        long spreading_factor_byte=  strtol(spreading_factor,&endptr,10);


        if (*endptr == '\0'  ) {
            printf("So hop le: %ld\n",spreading_factor_byte);
        } else {
            printf("Khong phai so hop le\n");

            return result;  

        }
        




        if ( spreading_factor_byte > 6 && spreading_factor_byte <13)
        {
            printf("suitable spreading factor \n");


            printf ( " bandwidth byte la %d \n" ,spreading_factor_byte);             
            config_data[(*(config_data_current_index))++]=1;
            config_data[(*(config_data_current_index))++]= spreading_factor_byte;
           
            checkconfigdata(*(config_data_current_index),config_data); 

            result = CODINGRATE_SET;

        }
        else {


            printf("not suitable sf\n");
        }



        free(spreading_factor);

        spreading_factor = NULL;
        }    
    }
    





    return result;
}








States_Config_t codingrate_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index)
{
    States_Config_t result = CODINGRATE_SET;


if ( new_data_available==true)
{

    if ( lora_buf_size-2 ==1 )
    {
        uint8_t  *codingrate= (uint8_t*)malloc(lora_buf_size * sizeof(uint8_t));



        for ( int i =1 ;i<lora_buf_size;++i)
        {   
            if( rx_buf[i] =='\n')
            {      
                *(codingrate+(i-1)) = '\0';
                break;
            }
            *(codingrate+(i-1)) = rx_buf[i];
            printf(" %d ",rx_buf[i]);
        } 




        char *endptr;


        long codingrate_byte=  strtol(codingrate,&endptr,10);


        if (*endptr == '\0'  ) {
            printf("So hop le: %ld\n",codingrate_byte);
        } else {
            printf("Khong phai so hop le\n");

            return result;  

        }
        





        if ( codingrate_byte > 0 && codingrate_byte <5)
        {
            printf("suitable codingrate  \n");


            printf ( " codingrate  byte la %d \n" ,codingrate_byte);             
            config_data[(*(config_data_current_index))++]=1;
            config_data[(*(config_data_current_index))++]= codingrate_byte;
         
            checkconfigdata(*(config_data_current_index),config_data); 

            result = PREAMBLELEN_SET;

        }
        else {


            printf("not suitable sf\n");
        }

    }
}




    return result ;
}






States_Config_t preamblelen_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index)
{


    States_Config_t result = PREAMBLELEN_SET;


if ( new_data_available==true)
{

    if ( lora_buf_size-2 >0 && lora_buf_size-2 <6 )
    {
        uint8_t  *preamble= (uint8_t*)malloc(lora_buf_size * sizeof(uint8_t));






        for ( int i =1 ;i<lora_buf_size;++i)
        {   
            if( rx_buf[i] =='\n')
            {      
                *(preamble+(i-1)) = '\0';
                break;
            }
            *(preamble+(i-1)) = rx_buf[i];
            printf(" %d ",rx_buf[i]);
        } 

        char *endptr;
        



        long preamble_byte=  strtol(preamble,&endptr,10);


        if (*endptr == '\0'  ) {
            printf("So hop le: %ld\n",preamble_byte);
        } else {
            printf("Khong phai so hop le\n");

            return result;  

        }
        

        if ( preamble_byte <6 || preamble_byte>65535){

            printf(" not suitable length ");

        }
       else
        {
            printf("suitable preamblelen  \n");


            printf ( " preamblelen  la %d \n" ,preamble_byte);    
            

            if ( preamble_byte >=6 && preamble_byte <256){

                config_data[(*(config_data_current_index))++]=2;
                config_data[(*(config_data_current_index))++]=0;
                config_data[(*(config_data_current_index))++]= preamble_byte;
             
            }
            else {
            
                uint8_t first_byte;

                uint8_t second_byte;

            extract_uint16_to_2_bytes(&first_byte,&second_byte,preamble_byte);
            config_data[(*(config_data_current_index))++]=2;
            config_data[(*(config_data_current_index))++]= first_byte;
            config_data[(*(config_data_current_index))++]= second_byte;
          
            }
            checkconfigdata(*(config_data_current_index),config_data); 

            result = FIXLEN_SET;

        }
     

    }
}




    return result ;





}
States_Config_t fixlen_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index){

    States_Config_t result = FIXLEN_SET;



    if ( new_data_available==true)
{

    if ( lora_buf_size-2==1)
    {


        printf(" suitable \n");


        if ( rx_buf[1] == '1' )
        {
           printf(" right format \n");

           config_data[(*(config_data_current_index))++]=1;
           config_data[(*(config_data_current_index))++]= 1;
           checkconfigdata(*(config_data_current_index),config_data); 


            result = CRCON_SET;


        }
        else if (rx_buf[1] == '0')
        {

            printf(" right format \n ");


         

           config_data[(*(config_data_current_index))++]=1;
           config_data[(*(config_data_current_index))++]= 0;
           checkconfigdata(*(config_data_current_index),config_data); 
            
           result = CRCON_SET;
        }
        else {


            printf(" wrong format\n");
        }
        

        


    }

    else     {

        printf(" not suitable sy");


    }   

}




    return result;



}



States_Config_t crcon_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index){


    States_Config_t result = CRCON_SET;




    if ( new_data_available==true)
    {
    
        if ( lora_buf_size-2==1)
        {
    
    
            printf(" suitable \n");
    
    
            if ( rx_buf[1] == '1' )
            {
               printf(" right format \n");
    
               config_data[(*(config_data_current_index))++]=1;
               config_data[(*(config_data_current_index))++]= 1;
    
               checkconfigdata(*(config_data_current_index),config_data); 

                result =FREQHOPON_SET;
    
    
            }
            else if (rx_buf[1] == '0')
            {
    
                printf(" right format \n ");
    
    
                
               config_data[(*(config_data_current_index))++]=1;
               config_data[(*(config_data_current_index))++]= 0;
               checkconfigdata(*(config_data_current_index),config_data); 

                
               result = FREQHOPON_SET;
            }
            else {
    
    
                printf(" wrong format\n");
            }

        }
    
        else     {
    
            printf(" not suitable sy");
    
    
        }   
    
    }




    return result;



}

States_Config_t freqhopn_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index){



    States_Config_t result =   FREQHOPON_SET;
    if ( new_data_available==true)
    {
    
        if ( lora_buf_size-2==1)
        {
    
    
            printf(" suitable \n");
    
    
            if ( rx_buf[1] == '1' )
            {
               printf(" right format \n");
    
               config_data[(*(config_data_current_index))++]=1;
               config_data[(*(config_data_current_index))++]= 1;
    
    
                result = HOPPERIOD_SET;
    
                checkconfigdata(*(config_data_current_index),config_data); 

            }
            else if (rx_buf[1] == '0')
            {
    
                printf(" right format \n ");
    
    
                
               config_data[(*(config_data_current_index))++]=1;
               config_data[(*(config_data_current_index))++]= 0;
    
                
               result = HOPPERIOD_SET;

               checkconfigdata(*(config_data_current_index),config_data); 

            }
            else {
    
    
                printf(" wrong format\n");
            }

        }
    
        else     {
    
            printf(" not suitable sy");
    
    
        }   
    
    }

    return result;
}


States_Config_t hopperiod_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index){


    States_Config_t result =   HOPPERIOD_SET;


    if ( new_data_available==true)
{

    if ( lora_buf_size-2 ==1 )
    {
        uint8_t  *hopperiod= (uint8_t*)malloc(lora_buf_size * sizeof(uint8_t));



        for ( int i =1 ;i<lora_buf_size;++i)
        {   
            if( rx_buf[i] =='\n')
            {      
                *(hopperiod+(i-1)) = '\0';
                break;
            }
            *(hopperiod+(i-1)) = rx_buf[i];
            printf(" %d ",rx_buf[i]);
        } 





        char *endptr;



        long hopperiod_byte=  strtol(hopperiod,&endptr,10);


        if (*endptr == '\0'  ) {
            printf("So hop le: %ld\n",hopperiod_byte);
        } else {
            printf("Khong phai so hop le\n");

            return result;  

        }
        





        if ( hopperiod_byte >= 0 && hopperiod_byte <5)
        {
            printf("suitable codingrate  \n");


            printf ( " hopperiod  byte la %d \n" ,hopperiod_byte);             
            config_data[(*(config_data_current_index))++]=1;
            config_data[(*(config_data_current_index))++]= hopperiod_byte;
         
            checkconfigdata(*(config_data_current_index),config_data); 

            result = IQINVERTED_SET;

        }
        else {


            printf("not suitable sf\n");
        }

    }
}
    return result;


}


States_Config_t iqinverted_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index){


    States_Config_t result =   IQINVERTED_SET;
        
    if ( new_data_available==true)
    {
    
        if ( lora_buf_size-2==1)
        {
    
    
            printf(" suitable \n");
    
    
            if ( rx_buf[1] == '1' )
            {
               printf(" right format \n");
    
               config_data[(*(config_data_current_index))++]=1;
               config_data[(*(config_data_current_index))++]= 1;
    
               checkconfigdata(*(config_data_current_index),config_data); 

                result =TX_TIMEOUT_SET;
    
    
            }
            else if (rx_buf[1] == '0')
            {
    
                printf(" right format \n ");
    
    
                
               config_data[(*(config_data_current_index))++]=1;
               config_data[(*(config_data_current_index))++]= 0;
               checkconfigdata(*(config_data_current_index),config_data); 

                
               result = TX_TIMEOUT_SET;
            }
            else {
    
    
                printf(" wrong format\n");
            }

        }
    
        else     {
    
            printf(" not suitable sy");
    
    
        }   
    
    }






    return result;


}





States_Config_t tx_timeout_set(uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t *config_data_current_index ,Stage_t *output_stage){




    States_Config_t result =  TX_TIMEOUT_SET  ;

    *output_stage = CONFIG;

    if ( new_data_available== true)
    {
        if ( lora_buf_size-2 >0  && lora_buf_size-2 <= 4)
        {
            printf(" suitable time out  !!");
            uint8_t  *timeout= (uint8_t*)malloc(lora_buf_size * sizeof(uint8_t));
            for ( int i =1 ;i<lora_buf_size;++i)
            {   
                if( rx_buf[i] =='\n')
                {      
                    *(timeout+(i-1)) = '\0';
                    break;
                }
                *(timeout+(i-1)) = rx_buf[i];
                printf(" %d ",rx_buf[i]);
            } 
            char *endptr;
            long tx_timeout_byte=  strtol(timeout,&endptr,10);
            if (*endptr == '\0'  ) {
                printf("So hop le: %ld\n",tx_timeout_byte);
            } else {
                printf("Khong phai so hop le\n");
    
                return result;  
                
            }
            if ( tx_timeout_byte <0 ){

                printf(" not suitable length ");
            }
           else
            {
                printf("suitable preamblelen  \n");
                printf ( " preamblelen  la %d \n" ,tx_timeout_byte);    
                if ( tx_timeout_byte >=0 && tx_timeout_byte<256){
                    config_data[(*(config_data_current_index))++]=2;
                    config_data[(*(config_data_current_index))++]=0;
                    config_data[(*(config_data_current_index))++]= tx_timeout_byte;

                    
                    

                   
                }
                else {
                    uint8_t first_byte;
                    uint8_t second_byte;
                extract_uint16_to_2_bytes(&first_byte,&second_byte,tx_timeout_byte);
                config_data[(*(config_data_current_index))++]=2;
                config_data[(*(config_data_current_index))++]= first_byte;
                config_data[(*(config_data_current_index))++]= second_byte;
                }
                checkconfigdata(*(config_data_current_index),config_data); 

                config_data[(*(config_data_current_index))++]= 'C';
                result = ADD_CONFIG_TO_FLASH_MEMORY;
      
               // result = FIXLEN_SET;
    
            }
        }
}
    return result;
}








States_Config_t add_data_to_flash_memory (uint32_t conf_address ,uint32_t *addresslater ,uint16_t lora_buf_size,bool new_data_available,uint8_t *rx_buf,uint8_t *config_data,uint8_t config_data_current_index ,Stage_t *output_stage)
{   



        printf(" config index  la  %d \n",config_data_current_index);

    States_Config_t result = TX_TIMEOUT_SET;


    flash_erase_page(conf_address);



      
        int something = flash_data_to_memory(config_data,config_data_current_index,conf_address,addresslater);

    (*addresslater)--;


    printf(" data tai address later sau khi flash la %d \n ",*((volatile uint8_t*)(*addresslater)));

           uint8_t * data_test= take_data_from_flash_memory(config_data_current_index,conf_address);



           printf(" kiem tra flash data sau khi duoc them \n");

           for ( int i =0 ; i <config_data_current_index;++i)
           {
            printf( " byte thu %d    %d  \n " ,i,*( data_test+i));



           }


           free( data_test);

           data_test = NULL;
        *output_stage = OPERATE;




        return result;

   

}









void extract_uint16_to_2_bytes(uint8_t *first_byte,uint8_t *second_byte,uint16_t input_num){


    if ( input_num >=0 && input_num<256 )
    {
        printf(" not suitable input \n");
     return;
    }
    else 
    {


        printf(" succesful split num into 2 bytes  " );
        *first_byte = (input_num>>8) & 0xFF;

        *second_byte = input_num & 0xFF;

    
    }




}





void checkconfigdata ( uint8_t config_data_index,uint8_t *config_data){

printf(" checck config data  ? \n");
for ( int i =0; i<config_data_index;++i)
{
printf(" byte:%d-%d \n",i,*(config_data+i));

}

}