

///#include "enum_lora.h"

#include "Work_with_uart/uart_receive.h"


#define UART_RX_BUF_SIZE 200




typedef enum {

    AESKEY_TYPING,
    AESKEY_NOT_TYPING


}AESKEY_TYPING_OR_NOT;








uint8_t test=0;

void uart_init_config(void);
bool handle_uart_rx(uint16_t *lora_buf_size,uint8_t *rx_buf,uint16_t *rx_index);
char* run_uart(void); // prototype

void uart_init_config(void)
{
    rcc_enable_peripheral_clk(RCC_PERIPHERAL_UART0, true);
    rcc_enable_peripheral_clk(RCC_PERIPHERAL_GPIOB, true);
    gpio_set_iomux(GPIOB, GPIO_PIN_0, 1); // UART0_RX
    gpio_set_iomux(GPIOB, GPIO_PIN_1, 1); // UART0_TX
    uart_config_t uart_config;
    uart_config_init(&uart_config);
    uart_config.baudrate = UART_BAUDRATE_115200;
    uart_config.data_width = UART_DATA_WIDTH_8;
    uart_config.parity = UART_PARITY_NO;
    uart_config.stop_bits = UART_STOP_BITS_1;
    uart_config.flow_control = UART_FLOW_CONTROL_DISABLED;
    uart_config.mode = UART_MODE_TXRX;
    uart_config.fifo_mode = 1;
    uart_init(UART0, &uart_config);
    uart_cmd(UART0, true);
    uart_config_interrupt(UART0, UART_INTERRUPT_RX_DONE, true);
    uart_config_interrupt(UART0, UART_INTERRUPT_RX_TIMEOUT , true);

//      NVIC_EnableIRQ(UART0_IRQn);
  //  NVIC_SetPriority(UART0_IRQn,2);



}




bool handle_uart_rx(uint16_t *lora_buf_size,uint8_t *rx_buf,uint16_t *rx_index)
{
   // *rx_index = 1;
    bool new_data_available=false;

    
    while (uart_get_flag_status(UART0, UART_FLAG_RX_FIFO_EMPTY) != SET

) {
        char ch = uart_receive_data(UART0);
          //  printf(" %c",ch);

       printf("%c",ch);
      if (*rx_index < UART_RX_BUF_SIZE - 1) {

            rx_buf[(*rx_index)++] = ch;
            if (ch == '\n' || ch=='\r') {
                printf(" end of line" );
                rx_buf[*rx_index] = '\0'; // null-terminate
                *lora_buf_size = *rx_index;
                *rx_index = 1;
                //printf(" rx buf tai vi tri 1 la %c",rx_buf[(*(lora_buf_size))-2]  );
                new_data_available = true;
                break; //?
                
            }
        } else {
            // buffer overflow protection
            rx_index = 1;
            new_data_available = false;
        }

       
    }
    return new_data_available;
}



/*
void handle_uart_rx_for_aes_key () {

    
    while (uart_get_flag_status(UART0, UART_FLAG_RX_FIFO_EMPTY) != SET
) {
        char ch = uart_receive_data(UART0);

       printf("%c ",ch);
      if (rx_index < UART_RX_BUF_SIZE - 1) {
           rx_buf[rx_index++] = ch;
            if (ch == '\n' || ch=='\r') {
                printf(" end of line" );
                rx_buf[rx_index] = '\0'; // null-terminate
                lora_buf_size = rx_index;
                printf(" lora buf size %d\n", lora_buf_size);
                rx_index = 1;
                new_data_available = true;
               
            }
        } else {
            // buffer overflow protection
            rx_index = 1;
            new_data_available = false;
        }
    }
    

}




*/