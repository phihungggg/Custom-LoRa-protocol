#include "Work_with_FSM/operation_funcs/lora_funcs/lora_send.h"

#include "Work_with_crypto/AES/AES_n.h"

#include "radio.h"

#include "enum_lora.h"

#include "Work_with_FSM/operation_funcs/lora_funcs/lora_get_config_func/lora_get_config_funcs.h"

void divide_uint16_data_into_two_bytes(uint16_t input , uint8_t * output );

void divide_uint32_data_into_four_bytes( uint32_t input , uint8_t * output );

void push_data_to_payload (uint8_t *current_index,uint8_t *payload, uint8_t *data_to_push, uint8_t size_of_data_to_push );
    Operation_state_t send_data_through_lora ( uint8_t *data_to_send , uint8_t size_of_data_send,uint32_t confaddr,uint32_t rtc_input){

        printf(" size of button pressed la %d \n",size_of_data_send);
                static uint16_t languithun=0;
                languithun++;

                uint8_t languithun_bytes[2] ;

                divide_uint16_data_into_two_bytes(languithun,languithun_bytes);


                uint8_t rtc_times_mdhms[4] ;
                divide_uint32_data_into_four_bytes(rtc_input,rtc_times_mdhms);
              
                Operation_state_t result = DONOTHING_OPERATION_STATE;
                uint8_t *prepare_payload ;
                uint8_t address[2];
                bool something = get_param_from_flash(PROPERTY_ADDRESS_JUMP[ADDRESS_SET_INDEX],confaddr,address);
                uint8_t authentication_keyy[4] ;
                something = get_param_from_flash(PROPERTY_ADDRESS_JUMP[AUTHENTICATIONKEY_SET_INDEX],confaddr,authentication_keyy);
                uint8_t aes_key[32];
                something = get_param_from_flash(PROPERTY_ADDRESS_JUMP[ KEY_NUM],confaddr,aes_key);
                uint8_t current_index=0;
                uint8_t tongbytegui= 13+size_of_data_send; // recognize_payload (1 byte)+ authentication_key ( 4 byte) + size_of_data_send(1 byte) +data_send(n_byte) + so lan gui ( 2 byte) + 4 byte rtc ( thang+ngay+gio+phut+giay)
                uint8_t recognize_payload_type = 0 ; // 0 mean normal data - 1 mean ping 
                uint8_t size = allocation(&prepare_payload,tongbytegui);
                printf( " size la %d \n",size);
                push_data_to_payload ( &current_index,prepare_payload,&tongbytegui,1);
                push_data_to_payload (&current_index,prepare_payload,&recognize_payload_type,1);
                push_data_to_payload ( &current_index,prepare_payload,authentication_keyy,sizeof(authentication_keyy));
                push_data_to_payload(&current_index,prepare_payload,&size_of_data_send,1);
                push_data_to_payload  ( &current_index,prepare_payload,data_to_send,size_of_data_send);
                push_data_to_payload ( &current_index ,  prepare_payload , languithun_bytes,2);
                push_data_to_payload (&current_index, prepare_payload, rtc_times_mdhms,4 );


                
                printf(" in thu prepare payload \n");
                for ( int i = 0 ; i<size ; ++i)
                {
                    printf(" %d \n",*(prepare_payload+i));
                }   
                uint8_t encoded_payload[size];
                aes_ecb(prepare_payload,size,encoded_payload,0,aes_key,32);



                uint8_t somethingintheway[16] ;
                aes_ecb (encoded_payload,size,somethingintheway,1,aes_key,32);
                printf(" gio in thu coi nhu the nao sau khi giai ma \n");
                for ( int i = 0 ; i <16;++i)
                {
                        printf(" %d \n",somethingintheway[i]);
                }


                    
                uint8_t sending_payload[size+2];
                for ( int i = 0 ; i < sizeof(address);++i)
                {
                    sending_payload[i] =address[i];
                }
                current_index = sizeof(address);
                push_data_to_payload( &current_index,sending_payload,encoded_payload,size);
                printf(" in thu sending payload \n");
                for ( int i = 0 ; i < sizeof(sending_payload);++i)
                {
                        printf(" thu %d la %d \n ",i,sending_payload[i] );
                }
                Radio.Send(sending_payload,sizeof(sending_payload));



                if ( languithun == 65535)
                {
                    languithun =0 ;
                }
                return result ;   
}








void push_data_to_payload (uint8_t *current_index,uint8_t *payload, uint8_t *data_to_push, uint8_t size_of_data_to_push )
{

    uint8_t temp_index = *current_index;

        for ( int i = (*current_index), j = 0;i<temp_index+size_of_data_to_push,j<size_of_data_to_push;++i,j++)
        {
            *(payload+i) = *(data_to_push+j);

            (*current_index) ++;
        }
        

}   







void divide_uint16_data_into_two_bytes(uint16_t input, uint8_t *output) {
    if (output == NULL) return;

    // byte cao
    output[0] = (input >> 8) & 0xFF;
    // byte thấp
    output[1] = input & 0xFF;
}


void divide_uint32_data_into_four_bytes(uint32_t input, uint8_t *output) {
    // Giả sử output có ít nhất 4 phần tử
    output[0] = (input >> 24) & 0xFF;  // byte cao nhất
    output[1] = (input >> 16) & 0xFF;
    output[2] = (input >> 8)  & 0xFF;
    output[3] = input & 0xFF;          // byte thấp nhất
}