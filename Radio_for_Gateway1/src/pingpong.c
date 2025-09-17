
#include "pingpong.h"
#include "drv.h"
#include "algorithm.h"
#include "aes.h"
#include "enum_lora.h"
#include "structs_lora.h"
#include "Work_with_bytes/check_hexa_input.h"
#include "Work_with_uart/filter_uart_receive.h"
#include "Work_with_bytes/interval_format.h"
#include "Work_with_uart/uart_receive.h"
#include "Work_with_flash_memory/take_authentication_information_from_flash.h" 
#include "Work_with_flash_memory/dealing_with_flash.h"
#include "Work_with_bytes/reformatstring.h"
#include "Work_with_flash_memory/rewrite_data_to_flash.h"
#include "Work_with_bytes/check_if_have_done_yet_in_that_section.h"
#include "Work_with_FSM/authentication.h"
#include "Work_with_FSM/configuration.h"
#include "Work_with_FSM/operation.h"


            int app_start( void )
                                        {
                                                            uint8_t PROPERTY_ADDRESS_JUMP[] = {
                                                                0,1,2,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16
                                                            };
                                                                uint32_t test_addr = TEST_ADDR;

                                                                uint32_t test_addr_later;

                                                                uint32_t conf_addr = CONF_ADDR;

                                                                uint32_t conf_addr_later;

                                                                if ( check_if_have_done_yet_in_that_section(test_addr,'C',PROPERTY_ADDRESS_JUMP[AUTHENTICATION_YET],&test_addr_later)==1 && check_if_have_done_yet_in_that_section(conf_addr,'C',PROPERTY_ADDRESS_JUMP[CONFIG_YET],&conf_addr_later)==1)
                                                                {
                                                                    printf(" OPERATING \n");
                                                                            operate(conf_addr);
                                                                }




                                                                

                                        States_Authentication_t system_state ;
                                        Stage_t system_stage = AUTHENTICATION ; 
                                        States_Config_t system_config = NODE_ID_SET_WAITING;
                                            bool is_username_correct = false;
                                            bool is_password_correct= false;
                                            //uart 
                                            uint16_t lora_buf_size;
                                            bool new_data_available = false;
                                            uint8_t rx_buf[200];
                                            memset(rx_buf, 0, sizeof(rx_buf));
                                            uint16_t rx_index =1;



                                            States_Config_t config_state  =NODE_ID_SET;
                                            uint8_t *config_data;
                                            uint8_t config_data_current_index=0;
                                                        if ( *((volatile uint8_t*)(test_addr ))==0xFF)
                                                        {

                                                            uint32_t address_laterr_authentication ; //need
                                                            printf(" authentication haven't made  ,add authentication !! \n");
                                                            address_laterr_authentication=init_authentication_made(test_addr);
                                                        }  
                                            printf(" Press y/n  to continue or get outttt ! \n");
                                            system_state=WAITING_PRESS_FIRST_ENTER;
                                        uart_init_config();
                                        config_data = (uint8_t*)malloc(100 * sizeof(uint8_t)) ;

                                            while( 1 )
                                            {

                                            
                                                if (uart_get_interrupt_status(UART0, UART_INTERRUPT_RX_DONE) == SET||
                                                uart_get_interrupt_status(UART0, UART_INTERRUPT_RX_TIMEOUT) == SET) {
                                                    uart_clear_interrupt(UART0, UART_INTERRUPT_RX_DONE);
                                                    uart_clear_interrupt(UART0, UART_INTERRUPT_RX_TIMEOUT);
                                                        printf ( " handle uart normal \n");
                                                    new_data_available=   handle_uart_rx(&lora_buf_size,rx_buf,&rx_index);   


                                            }                                            
                                            switch ( system_stage )
                                            {
                                                case AUTHENTICATION:
                                                system_stage = Authentication(test_addr,'C',PROPERTY_ADDRESS_JUMP[AUTHENTICATION_YET],&system_state,rx_buf,&rx_index,&new_data_available,&lora_buf_size,&is_username_correct,&is_password_correct);
                                                break;
                                                case CONFIG:
                                                system_stage = Configuration(conf_addr,'C',PROPERTY_ADDRESS_JUMP[CONFIG_YET],&config_state,rx_buf,&rx_index,&new_data_available,&lora_buf_size,config_data,&config_data_current_index);
                                                break;
                                                case OPERATE:
                                                printf("  now you need to switch to go to operating !! OPERATING ");
                                                delay_ms ( 2000); 
                                                break;
                                            }
                                            }
                                        }



                                        


