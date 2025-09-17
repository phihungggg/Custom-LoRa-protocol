



#include "Work_with_flash_memory/take_authentication_information_from_flash.h" 

#include "Work_with_flash_memory/dealing_with_flash.h"



//this will follow this (numberofusername)xxxx(numberofpassword)yyyy, you will read number of username then number of password in order to take exactly username and password
void get_username_and_password ( uint32_t address_you_chose , uint8_t **username_data,uint8_t **password_data, uint32_t *real_address_of_user_name, uint32_t *real_address_of_password,uint8_t *size_of_username,uint8_t *size_of_password) {


    printf(" address first  : 0x%08X\n ",address_you_chose);

   * real_address_of_user_name = address_you_chose+1;
   
  uint8_t username_size=  *((volatile uint8_t*)(address_you_chose ));


  printf(" username size %d \n ",username_size);


    *username_data =  take_data_from_flash_memory(username_size,*real_address_of_user_name);

    for ( int i =0;i<username_size;++i)
    {        
        printf ( " dia chi la  0x%08X\n",(*real_address_of_user_name)+i);
        printf(" %c\n ", *((*username_data)+i));
    }


    *real_address_of_password = *(real_address_of_user_name)+username_size+1;

    printf( " dia chi cua password la !!!!!! 0x%08X\n",*real_address_of_password);

   uint8_t password_size=  *((volatile uint8_t*)(*(real_address_of_password)-1 ));


  printf(" password size %d \n ",password_size);
    *password_data = take_data_from_flash_memory(password_size,*real_address_of_password);


    
  
   
    for ( int i =0;i<password_size;++i)
    {

        printf(" %c\n ", *((*password_data)+i));

    }
    
   *size_of_username = username_size;

    *size_of_password=password_size;


}

