#include "Work_with_FSM/operation_funcs/lora_funcs/lora_get_config_func/lora_get_config_funcs.h"



#include "Work_with_bytes/take_byte_from_flash.h"



#include "Work_with_flash_memory/dealing_with_flash.h"


uint64_t convert_n_bytes_to_one_var(uint8_t *inputbyte, uint8_t bytes_num, bool *check) ;

bool get_param_from_flash(uint8_t where_to_get,uint32_t conf_addr, void *result) {


bool check_if_successful_or_not=  false ; 



    uint8_t num_byte ;
    uint32_t address_after_jump;
    int8_t check =  take_byte_from_flash(conf_addr,where_to_get,&num_byte,&address_after_jump);




        address_after_jump ++;
    

      uint8_t* byte_get=  take_data_from_flash_memory(num_byte,address_after_jump);



    


    if ( where_to_get == PROPERTY_ADDRESS_JUMP[INTERVAL_NUM])
    {
        if ( num_byte == 4)
        {
        memcpy(result, byte_get, 4);
        check_if_successful_or_not = true ; 
        }
        else {
            printf(" error \n");
            
        }


    }



   else if ( where_to_get == PROPERTY_ADDRESS_JUMP[TX_OUTPUT_PWR_NUM])
    {

        *(int8_t*)result=  *(byte_get);
        check_if_successful_or_not = true ; 
     
    }
    else if (where_to_get == PROPERTY_ADDRESS_JUMP[KEY_NUM])
    {   
        if ( num_byte ==32)
      {  memcpy(result, byte_get, 32);
        check_if_successful_or_not = true ; 
      }
        else{


            printf("error\n");
          //  check_if_successful_or_not = false ; 
        }

       
    }
    else if ( where_to_get==PROPERTY_ADDRESS_JUMP[FREQ_NUM])
    {
        
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




        *(uint32_t*)result = AS923_FrequencyTable[*byte_get];
        check_if_successful_or_not = true ; 

    }
    else if ( where_to_get == PROPERTY_ADDRESS_JUMP[BANDWIDTH])
    {



        const uint16_t bandwidth_table[] = {
         
            125,250,500
        };

        bool does_band_width_have_flag = false;
        uint32_t get_bandwidth ;
        for ( int i =0 ; i < sizeof(bandwidth_table);++i)
        {
            if ( bandwidth_table[i] == *(byte_get))
                {
                    does_band_width_have_flag = true;
                    get_bandwidth= *(byte_get);
                }
        }

        if ( does_band_width_have_flag == true)
        {
            *(uint32_t*)result  = get_bandwidth;
            check_if_successful_or_not = true ; 

        }


    }
    else if ( where_to_get == PROPERTY_ADDRESS_JUMP[SPREADINGFACTOR])
    {
            *(uint32_t*)result=  *(byte_get);
            check_if_successful_or_not = true ; 

    }
    else if ( where_to_get == PROPERTY_ADDRESS_JUMP[CODINGRATE])
    {
        
        *(uint32_t*)result=  *(byte_get);
        check_if_successful_or_not = true ; 

    
    }
    else if ( where_to_get == PROPERTY_ADDRESS_JUMP[PRE])
    {   


        if ( num_byte !=2 )
        {

            printf(" error  error error error error error error \n");
        }

        else{
                bool check = false;
            
           *(uint16_t*)result = convert_n_bytes_to_one_var(byte_get,2,&check);
           check_if_successful_or_not = true ; 

            if ( check == false)
            {

                check_if_successful_or_not = false ; 
                printf(" wrong byte nums \n");
            }
            else{

                printf(" right format nums \n");
            }


            }
                
    }

    else if ( where_to_get == PROPERTY_ADDRESS_JUMP[FIXLEN]||where_to_get == PROPERTY_ADDRESS_JUMP[CRCC]|| where_to_get == PROPERTY_ADDRESS_JUMP[FREQHOP]|| where_to_get == PROPERTY_ADDRESS_JUMP[ IQINVERTED])

    {

        *(bool*)result=  *(byte_get);
        check_if_successful_or_not = true ; 
     
    }

   
    else if ( where_to_get == PROPERTY_ADDRESS_JUMP[HOPPERIOD])
    {
        *(uint8_t*)result=  *(byte_get);
        check_if_successful_or_not = true ; 
      }
  
    else if ( where_to_get == PROPERTY_ADDRESS_JUMP[TX_TIMEOUT])
    { 


        if ( num_byte !=2 )
        {

            printf(" error  error error error error error error \n");

        }

        else{
                bool check = false;
            
           *(uint16_t*)result = convert_n_bytes_to_one_var(byte_get,2,&check);
           check_if_successful_or_not = true ; 

            if ( check == false)
            {

                printf(" wrong byte nums \n");

                check_if_successful_or_not = false ; 
            }
            else{

                printf(" right format nums \n");
            }


            }

        


    }

    else if (where_to_get == PROPERTY_ADDRESS_JUMP[AUTHENTICATIONKEY_SET_INDEX])
    {
        

        printf(" num byte la %d \n",num_byte);
        if ( num_byte !=4 )
        {

            printf(" error  error error error error error error \n");
            
        }

        {
            memcpy(result, byte_get, 4);
            check_if_successful_or_not = true ; 

        }


    }else if ( where_to_get == PROPERTY_ADDRESS_JUMP[ADDRESS_SET_INDEX])
    {


        printf(" num byte la %d \n",num_byte);
        if ( num_byte !=2 )
        {

            printf(" error  error error error error error error \n");
            
        }

        {
            memcpy(result, byte_get, 2);
            check_if_successful_or_not = true ; 

        }



    }

  

    free(byte_get);
    byte_get=NULL;


  //  free(byte_get);

    return check_if_successful_or_not;


    

}










uint64_t convert_n_bytes_to_one_var(uint8_t *inputbyte, uint8_t bytes_num, bool *check) {
    if (bytes_num != 2 && bytes_num != 4 && bytes_num != 8) {
      //  fprintf(stderr, "Error: Invalid byte length. Supported lengths are 2, 4, or 8 bytes.\n");
        printf(" error \n");
        *check= false;
        return 0;
    }
    *check =true;
    uint64_t temp = 0;
    for (uint8_t i = 0; i < bytes_num; ++i) {
        temp |= ((uint64_t)inputbyte[i]) << (8 * (bytes_num - 1 - i));
    }
    return temp;
}