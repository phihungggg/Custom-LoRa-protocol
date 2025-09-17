#include "Work_with_FSM/authentication_funcs/authentication_assign.h"






uint32_t init_authentication_made(uint32_t address_you_chose){
    uint8_t size_of_username;
    uint8_t size_of_password;
    
    uint32_t address_later;
    uint32_t address_later_later;
    uint32_t address_later_later_later;
uint8_t username[] = {'L','O','R','A','U','S','E','R'};
uint8_t password[] = { 'g','r','e','e','n','s','t','r','e','a','m','m','m' };
//uint8_t gionmat[] = { 'm','m','m','m','m','m','m','m'};

size_of_username = sizeof(username);
size_of_password= sizeof(password);

uint8_t username_fullpackage[size_of_username+1];
uint8_t password_fullpackage[size_of_password+1];
uint8_t authentication_data[sizeof(username_fullpackage)+sizeof(password_fullpackage)];
for (int i = 0; i < size_of_username + 1; ++i) {
    if (i == 0) {
        username_fullpackage[0] = size_of_username;
    } else {
        username_fullpackage[i] = username[i - 1];
    }
}
printf("Kiem tra username_fullpackage:\n");
printf (" size of username full pacakge %d \n",sizeof(username_fullpackage));
for (int i = 0; i < sizeof(username_fullpackage); ++i) {
    if (i==0)
    printf("byte %d is %d\n", i, username_fullpackage[i]);
    else
        printf("byte %d is %c\n", i, username_fullpackage[i]);
}
for (int i = 0; i < size_of_password + 1; ++i) {
    if (i == 0) {
        password_fullpackage[0] = size_of_password;
    } else {
        password_fullpackage[i] = password[i - 1];
    }
}
printf("\nKiem tra password_fullpackage:\n");
printf (" size of password full pacakge %d \n",sizeof(password_fullpackage));
memcpy(&authentication_data[0], username_fullpackage, sizeof(username_fullpackage));
memcpy(&authentication_data[sizeof(username_fullpackage)], password_fullpackage, sizeof(password_fullpackage));
printf("Kiem tra authentication_data:\n");
for (int i = 0; i < sizeof(authentication_data); ++i) {
    if (i == 0 || i == (sizeof(username_fullpackage))) {
        // In size (byte đầu tiên của từng block)
        printf("byte %d is %d\n", i, authentication_data[i]);
    } else {
        // In data
        printf("byte %d is %c\n", i, authentication_data[i]);
    }
}





flash_erase_page(address_you_chose);




uint8_t err = flash_data_to_memory(authentication_data,sizeof(authentication_data),address_you_chose,&address_later);
if (err!=0){
    printf(" error happened");
    return 0;
}
    return address_later;

} 
