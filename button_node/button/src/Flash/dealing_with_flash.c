


#include "Work_with_flash_memory/dealing_with_flash.h"
 


int flash_data_to_memory( uint8_t *data_to_fill, uint32_t size_of_store_data,uint32_t test_addr_original,uint32_t *test_addr_later)
                {

                                        printf(" address from flash data to memory : 0x%08X\n ",test_addr_original);
                                        printf( " every element that flash to memory flash  \n ");
                                        for ( int i =0;i<size_of_store_data;i++){                                            printf("  %d  :  0x%02X\n  ",i,*(data_to_fill+i));
                                        }
                                        *test_addr_later = test_addr_original +size_of_store_data;
                                        printf( " address after set 1 or 0 : 0x%08X\n  ",*test_addr_later);
                                        // flash_erase_page(test_addr_original);
                                            flash_program_bytes(test_addr_original, data_to_fill, size_of_store_data);
                                            for (int i = 0; i < size_of_store_data; i++) {

                                                printf (" 0x%02X\n ", *(uint8_t*)(test_addr_original + i));
                                                if (*(uint8_t*)(test_addr_original + i) != *(data_to_fill+i)) {
                                                    // error
                                                printf(" error when flash happens at %d",i);
                                                return 1;
                                                }
                                            }
                                            return 0;
                }

uint8_t* take_data_from_flash_memory(uint32_t size_of_store_data,uint32_t data_address_to_get){
    uint8_t* read_buffer;
   
    read_buffer = (uint8_t*)malloc(size_of_store_data * sizeof(uint8_t));
    for (int i = 0; i < size_of_store_data; i++) {
        read_buffer[i] = *((volatile uint8_t*)(data_address_to_get + i));
      
    }
    return read_buffer;
}       



#ifdef USE_FULL_ASSERT
void assert_failed(void* file, uint32_t line)
{
    (void)file;
    (void)line;

    while (1) { }
}
#endif
