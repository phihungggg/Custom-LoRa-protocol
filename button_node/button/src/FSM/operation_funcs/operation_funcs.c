#include  "Work_with_FSM/operation_funcs/operation_funcs.h"


#include "Work_with_FSM/operation_funcs/lora_funcs/lora_get_config_func/lora_get_config_funcs.h"




#include "radio.h"


#include "enum_lora.h"

#include "Work_with_crypto/AES/AES_n.h"


bool check_if_data_match_or_not ( uint8_t *datain1 , uint8_t size_of_datain_and_o ,uint8_t *datain2 );



void aes_ecb(U8 *datain, uint8_t inlength, U8 *dataout, U8 de_or_en,U8 *AES_KEY,uint8_t KEY_LENGTH);


Operation_state_t take_data_from_sensor ( uint8_t *data_to_send) {

Operation_state_t operate_state = TAKE_DATA_FROM_SENSORS;
            for ( int i =0;  i<8;++i)
            {   
                data_to_send[i] = i;
            }
            operate_state = SEND_DATA_THROUGH_LORA;
    return  operate_state;
}




Operation_state_t toggle_led (gpio_t *gpiox, uint8_t gpio_pin){
    gpio_toggle(gpiox, gpio_pin);
return DONOTHING;
}


//
Operation_state_t error_handling_when_gateway_not_response () {     

    


    



    return DONOTHING;
}


Operation_state_t handling_downlink_data( uint8_t *payload,uint8_t size_of_payload,uint32_t confaddr ){
            Operation_state_t result = ERROR_HANDLING_WHEN_GATEWAY_NOT_RESPONSE;


            //get aes_key 
            uint8_t aes_key[32];
            bool something = get_param_from_flash(PROPERTY_ADDRESS_JUMP[ KEY_NUM],confaddr,aes_key);


            //get address key 
            uint8_t address[2];

            something = get_param_from_flash ( PROPERTY_ADDRESS_JUMP[ADDRESS_SET_INDEX],confaddr,address);






            //get_authentication_key 
            uint8_t authentication_key[4];


            something = get_param_from_flash ( PROPERTY_ADDRESS_JUMP[AUTHENTICATIONKEY_SET_INDEX],confaddr,address);






            for ( int i = 0 ; i < sizeof(address);++i)
            {
                if (payload[i]!= address[i] )
                return ERROR_HANDLING_WHEN_GATEWAY_NOT_RESPONSE;


                
            }





            if ( (size_of_payload-2) % 16  ==1)
            {
                printf("  nham size roi , deo dung \n");




                Radio.Rx(0);



                return  DONOTHING;
            }


            

            uint8_t after_decoded_data[size_of_payload-2] ;


            aes_ecb(payload+2,size_of_payload-2,after_decoded_data,1,aes_key,32);





            printf(" check thu xem decode downlink dung chua \n");
            for ( int i =0 ; i<sizeof(after_decoded_data);++i)
            {

                printf(" in thu xem nhu the nao %d \n ", after_decoded_data[i]);


            }





            printf(" now will check if correct authentication key ");


                if ( check_if_data_match_or_not(authentication_key,4,after_decoded_data) == false)
                {



                    
                    return DONOTHING ;
                }
        







            return result ; 

}










bool check_if_data_match_or_not ( uint8_t *datain1 , uint8_t size_of_datain_and_o ,uint8_t *datain2 )
{
bool result = true;

    for ( int i = 0 ; i < size_of_datain_and_o ; ++i)
    {
        if ( datain1[i]!= datain2[i] )

        {
            result = false ;


        }


    }

    return result;

}