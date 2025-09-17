#include "Work_with_bytes/check_if_have_done_yet_in_that_section.h"






uint8_t check_if_have_done_yet_in_that_section(uint32_t beginning_address, uint8_t byte_to_check,uint8_t count,uint32_t *address_after_jump) {
    uint32_t current_address = beginning_address;
  
   // printf(" count khi check la %d\n", count );
    while (count > 0) {

       // delay_ms ( 2000);
        // Đọc số bước
        uint8_t step = *((volatile uint8_t*)(current_address));
     //   printf("Đọc bước: %d tại địa chỉ: 0x%08X\n", step, current_address);
        
        // Tăng địa chỉ tới phần dữ liệu cần bỏ qua
        current_address += step + 1;  // +1 để nhảy qua byte độ dài

        // Kiểm tra byte cuối cùng với byte_to_check
        uint8_t final_byte = *((volatile uint8_t*)(current_address));
      //  printf("So sánh byte cuối: %c tại địa chỉ: 0x%08X\n", final_byte, current_address);

       

        // Giảm số lần đọc còn lại
        count--;
        if ( count ==0 )
            {
               //     printf(" final byte la %d ",final_byte);

        }

         if (final_byte == byte_to_check) {
            // Kiểm tra byte kế tiếp
            uint8_t next_byte = *((volatile uint8_t*)(current_address+1));
              
            // Nếu byte sau '?' là 0xFF và count vẫn còn, báo lỗi
            if (next_byte == 0xFF && count > 0) {
              
                return 0;
            }

            // Nếu không lỗi, trả về tìm thấy
            return 1;
        }
        
    }


    *address_after_jump = current_address;


    // Nếu kết thúc vòng lặp mà gặp '?' nhưng không có lỗi, trả về 1
    uint8_t final_byte =*((volatile uint8_t*)(current_address));

   // printf(" final byte  la %d \n" , final_byte);
    if (final_byte == byte_to_check) {
      //  printf("Đã tìm thấy byte '?' mà không gặp lỗi!\n");
        return 1;
    }
     //printf(" byte thu %d la %d \n",i,*((volatile uint8_t*)(current_address))) ;

    return 0;  // Không tìm thấy
}

