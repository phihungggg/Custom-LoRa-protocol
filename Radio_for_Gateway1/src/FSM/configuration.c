#include "Work_with_FSM/configuration.h"


#include "Work_with_FSM/configuration_funcs/configuration_funcs.h"

#include "Work_with_bytes/check_if_have_done_yet_in_that_section.h"

void testcasewhichstate ( States_Config_t casee);







Stage_t Configuration (uint32_t conf_address ,uint8_t checkbyte,int count ,States_Config_t *output_state,uint8_t *rx_buf,uint16_t *rx_index,bool *new_data_available,uint16_t *lora_buf_size,uint8_t *configdata, uint8_t *current_index){

    Stage_t Stage = CONFIG;
    uint8_t *username ;
    uint8_t *password ;

    uint32_t address_later; //?
    if( check_if_have_done_yet_in_that_section(conf_address,checkbyte,count,&address_later)==1)   
    {

        printf("it is already config , now operation ");
        Stage = OPERATE;
    }
    else {
        uint8_t *stringg ;

       // testcasewhichstate( *output_state);
        switch ( *output_state)
        {
        
                case NODE_ID_SET:



                stringg = "NODEID SET ";
                testcase(stringg);

               *output_state = node_id_set(*lora_buf_size,*new_data_available,rx_buf,configdata,current_index);

            
               




                break;

                case KEY_SET1:
              
                stringg = "KEY set 1";
                testcase(stringg);

                *output_state = key_set1(*lora_buf_size,*new_data_available,rx_buf,configdata,current_index,rx_index);

                

                break;

                case KEY_SET2:
               

                stringg = "KEY set 2 ";
                testcase(stringg);

               *output_state = key_set2(*lora_buf_size,*new_data_available,rx_buf,configdata,current_index,rx_index);

                
                break;

        
                case KEY_SET3:
             
                stringg = "KEY set 3 ";
                testcase(stringg);

                *output_state = key_set3(*lora_buf_size,*new_data_available,rx_buf,configdata,current_index,rx_index);




                
                break;



                case KEY_SET4:
          

                stringg = "KEY set 4 ";
                testcase(stringg);

                *output_state = key_set4(*lora_buf_size,*new_data_available,rx_buf,configdata,current_index,rx_index);

                 
                break;


                case KEY_SET_RESULT:





                *output_state = key_set_result(*lora_buf_size,*new_data_available,rx_buf,configdata,current_index,rx_index);

         
                 
                 break;
                



                case TX_POWER_SET:

             
                stringg = "tx power set ";
                testcase(stringg);

                *output_state  = tx_power_set(*lora_buf_size,*new_data_available,rx_buf,configdata,current_index);

                
                break;



                
                case INTERVAL_SET:
                stringg = "INTERVAL_SET";
                testcase(stringg);


                *output_state  = interval_set(*lora_buf_size,*new_data_available,rx_buf,configdata,current_index);
                 

                break;


                case THRESHOLD_SET:
               

                *output_state  = threshold_set(*lora_buf_size,*new_data_available,rx_buf,configdata,current_index);
                

                break;  

                

                case FREQUENCY_SET:


                
                *output_state  = frequency_set(*lora_buf_size,*new_data_available,rx_buf,configdata,current_index);
                

                break;



                case BANDWIDTH_SET:

                stringg = "band_SET\n";
                testcase(stringg);
              
                *output_state  = bandwidth_set(*lora_buf_size,*new_data_available,rx_buf,configdata,current_index);
            

                break;


                case SPREADING_FACTOR_SET:
             



                stringg = "SPREADING_FACTOR_SET\n";
                testcase(stringg);

               *output_state  = spreading_factor_set(*lora_buf_size,*new_data_available,rx_buf,configdata,current_index);
                \
                break;



                case CODINGRATE_SET:


                stringg = "CODINGRATE_SET\n";
                testcase(stringg);



                *output_state  = codingrate_set(*lora_buf_size,*new_data_available,rx_buf,configdata,current_index);
             

                break;



                case PREAMBLELEN_SET:



                stringg = "PRE_SET\n";
                testcase(stringg);
               *output_state  = preamblelen_set(*lora_buf_size,*new_data_available,rx_buf,configdata,current_index);
            
                break;

                case FIXLEN_SET:


                stringg = "FIX_SET\n";
                testcase(stringg);
                *output_state  = fixlen_set(*lora_buf_size,*new_data_available,rx_buf,configdata,current_index);
            

                break;
                case CRCON_SET:



                stringg = "CRCON_SET\n";
                testcase(stringg);
                *output_state  = crcon_set(*lora_buf_size,*new_data_available,rx_buf,configdata,current_index);
            

                break;


                case FREQHOPON_SET:



                stringg = "FREQHOPN_SET\n";
                testcase(stringg);
                *output_state  = freqhopn_set(*lora_buf_size,*new_data_available,rx_buf,configdata,current_index);
            

                break;


                case HOPPERIOD_SET:


                stringg = "HOPPERIOD_SET\n";
                testcase(stringg);
                *output_state  = hopperiod_set(*lora_buf_size,*new_data_available,rx_buf,configdata,current_index);
             

                break;



                case IQINVERTED_SET:


                stringg = "IQINVERTED_SET\n";
                testcase(stringg);
                *output_state  = iqinverted_set(*lora_buf_size,*new_data_available,rx_buf,configdata,current_index);
             

                break;



                case TX_TIMEOUT_SET:

                stringg = "TX TIMEOUT _SET\n";
                testcase(stringg);

                *output_state  = tx_timeout_set(*lora_buf_size,*new_data_available,rx_buf,configdata,current_index,&Stage);

                


                break;



                case ADD_CONFIG_TO_FLASH_MEMORY:

                *output_state =  add_data_to_flash_memory (conf_address,&address_later,lora_buf_size,new_data_available,rx_buf,configdata,*current_index,&Stage);




                break;

        }   

        *new_data_available = false;
     
    }

    return Stage ;

}

























void testcase( uint8_t stringg){
    static uint32_t count=0;
  
    if( count == 200000)
    {
    printf(" this is case  %s \n",stringg);
        count= 0 ;
    }
count++;
}






void testcasewhichstate ( States_Config_t casee){
    static uint32_t count=0;
    if( count == 200000)
    {
        printf(" hello it is %d",casee);

        count = 0;

    }

count++;
}