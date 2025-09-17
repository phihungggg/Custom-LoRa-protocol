

#include "Work_with_bytes/take_byte_from_flash.h"







uint8_t take_byte_from_flash(uint32_t beginning_address,  uint8_t count,uint8_t *output_byte,uint32_t *address_after_jump) {
    uint32_t current_address = beginning_address;
    // printf(" count khi check la %d\n", count );
     while (count > 0) {
         uint8_t step = *((volatile uint8_t*)(current_address));
         current_address += step + 1; 
         uint8_t final_byte = *((volatile uint8_t*)(current_address));       
         count--;
         if ( count ==0 )
             {
              break;
         }
     }
     *address_after_jump = current_address;
     // Nếu kết thúc vòng lặp mà gặp '?' nhưng không có lỗi, trả về 1
     *output_byte =*((volatile uint8_t*)(current_address));
     return 1;
 
}