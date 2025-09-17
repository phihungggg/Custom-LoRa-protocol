#include "Work_with_FSM/authentication.h"

#include "Work_with_bytes/check_if_have_done_yet_in_that_section.h"
#include "Work_with_flash_memory/take_authentication_information_from_flash.h"

States_Authentication_t first_enter ( bool new_data_available, uint16_t lora_buf_size,uint8_t *rx_buf);
States_Authentication_t username_enter( bool new_data_available, uint16_t lora_buf_size,uint8_t *rx_buf,uint32_t address_authentication,bool *is_user_name_correct);
States_Authentication_t password_enter ( bool new_data_available, uint16_t lora_buf_size,uint8_t *rx_buf,uint32_t address_authentication,bool *is_password_correct);
//Authentication function
Stage_t Authentication (uint32_t authentication_address ,uint8_t checkbyte,int count ,States_Authentication_t *output_state,uint8_t *rx_buf,uint16_t *rx_index,bool *new_data_available,uint16_t *lora_buf_size ,bool *is_user_name_correct,bool *is_password_correct)
{

    
 
    Stage_t Stage = AUTHENTICATION;
    uint8_t *username ;
    uint8_t *password ;

    uint32_t address_later; //?
    if( check_if_have_done_yet_in_that_section(authentication_address,checkbyte,count,&address_later)==1)   
    {   

        printf(" da authentication , gio chuyen sang config nhe \n");
        return CONFIG;
    }
    else {
        switch ( *output_state)
        {
            case WAITING_PRESS_FIRST_ENTER:
            *output_state = first_enter(*new_data_available,*lora_buf_size,rx_buf);
            if (*output_state==RE_WAITING_PRESS_FIRST_ENTER ||*output_state==USERNAME_TYPING)
            {
                *new_data_available=false;
            }
            break;

            
            case RE_WAITING_PRESS_FIRST_ENTER:
            printf(" Press y/n  to continue/getoutttt !\n \n");
            *output_state= WAITING_PRESS_FIRST_ENTER;
            break;
            case USERNAME_TYPING:
                *output_state= username_enter(*new_data_available,*lora_buf_size,rx_buf,authentication_address,is_user_name_correct);               

                if (*output_state==PASSWORD_TYPING){

                    *new_data_available=false;
                }
                            break;
            case PASSWORD_TYPING:
      
                *output_state = password_enter(*new_data_available,*lora_buf_size,rx_buf,authentication_address,is_password_correct);

                if( *output_state ==AUTHENTICATION_RESULT)
                {
                    *new_data_available=false;

                }

                break;
            case AUTHENTICATION_RESULT:
            printf(" authentication result  ? \n");
                if(*is_password_correct==true && *is_user_name_correct==true)
                {
                    printf(" correct authentication \n");

                    printf(" now you will go to config stage \n");


                    printf(" now you set node id  \n");

                    uint8_t size;
                                    uint8_t datain[] = {'C'};
                                    uint8_t latersize;
                                    uint32_t funny =  rewritedata(authentication_address,&size,datain,sizeof(datain),&latersize); 


                    Stage= CONFIG;

                    return Stage;
                }
                else {


                    *output_state = USERNAME_TYPING;
                }

                *new_data_available =false;
                break;


            
        }
       return Stage ;
    }
}
States_Authentication_t first_enter ( bool new_data_available, uint16_t lora_buf_size,uint8_t *rx_buf)
{
   






    States_Authentication_t output_state;

    output_state = WAITING_PRESS_FIRST_ENTER;


   
    if(new_data_available==true){


       
        printf(" data available la true \n");
     
        if ( lora_buf_size-2>1)
            {
                printf(" %d  \n",lora_buf_size-2);
                output_state = RE_WAITING_PRESS_FIRST_ENTER;


             
                return output_state;
            }
        else if ( lora_buf_size-2==1)
        {

            printf(" lora buf size-2 ==1 \n");
            printf(" %d  \n",lora_buf_size-2);
          
            switch (rx_buf[1]){
                case 'y':
                printf("Fill username\n");
                rx_buf[0]="\0";
                output_state= USERNAME_TYPING;
                return output_state;
                break;
                case 'n':
                output_state = RE_WAITING_PRESS_FIRST_ENTER;
                printf(" case authentication ? \n ");

                if (  new_data_available==true){
           
                   printf (" new data avaiable duoi authentication la true \n");
           
                }
                else
                {
                   printf(" new data avai ab le duoi auathentication la false ");
                }
                printf(" re waiting \n");
                break;
                return output_state;
                default:

                printf(" default at first enter ?  \n");
                break;
            }   
        }
        else {
            printf("  ???? \n");
            printf(" %d  \n",lora_buf_size-2);
        }


    }
    else {


    
    }
  


    return output_state;

}


States_Authentication_t username_enter( bool new_data_available, uint16_t lora_buf_size,uint8_t *rx_buf,uint32_t address_authentication,bool *is_user_name_correct)
{
    States_Authentication_t output_state;

    output_state = USERNAME_TYPING;

    if ( new_data_available==true)
    { 
        rx_buf[0]=lora_buf_size-2;
        printf(" lora buf size-2 la %d \n",lora_buf_size-2);
        uint8_t *username;
        uint8_t size_of_username;
        uint8_t *password;
        uint8_t size_of_password;
        uint32_t address_of_username;
        uint32_t address_of_password;
        get_username_and_password(address_authentication,&username,&password,&address_of_username,&address_of_password,&size_of_username,&size_of_password);
        for ( int i=0;i<size_of_username;++i){
            printf("phan tu thu %d la %d",i,*(username+i));
        }

        printf("%s",rx_buf+1);
        if( strncmp( ( const char* )rx_buf+1, ( const char* )username, size_of_username ) == 0 && (lora_buf_size-2)==size_of_username)
        {   
         printf(" now fill password");
            *is_user_name_correct= true;
      
        }
        else {
            printf(" user name is not correctttttttt \n");
            *is_user_name_correct= false;
           
        }
        output_state =PASSWORD_TYPING;


        free(username);
        free(password);
    }
return output_state;
}

    












States_Authentication_t password_enter ( bool new_data_available, uint16_t lora_buf_size,uint8_t *rx_buf,uint32_t address_authentication,bool *is_password_correct)
{
    States_Authentication_t output_state;

    output_state = PASSWORD_TYPING;

    if ( new_data_available==true)
    {
      
        printf(" data true password enter \n");
        rx_buf[0]=lora_buf_size-2;
    


        printf(" lora buf size-2 la %d \n",lora_buf_size-2);


        uint8_t *username;

        uint8_t size_of_username;
        uint8_t *password;
        uint8_t size_of_password;
        uint32_t address_of_username;

        uint32_t address_of_password;
        get_username_and_password(address_authentication,&username,&password,&address_of_username,&address_of_password,&size_of_username,&size_of_password);
     

        printf("%s",rx_buf+1);
        if( strncmp( ( const char* )rx_buf+1, ( const char* )password, size_of_password ) == 0 && (lora_buf_size-2)==size_of_password)
        {   
            *is_password_correct= true;
            output_state  = AUTHENTICATION_RESULT;
        }
        else {
            printf("  password is not correct \n");
            *is_password_correct= false;    
        }
        output_state =AUTHENTICATION_RESULT;


        free(username);
        free(password);
    }
return output_state;
}


