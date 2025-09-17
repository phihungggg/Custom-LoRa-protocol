#include "Work_with_FSM/operation_funcs/lora_funcs/lora_get_config.h"


#include "radio.h"

#include "tremo_system.h"

#include "Work_with_bytes/take_byte_from_flash.h"
#include "Work_with_FSM/operation_funcs/lora_funcs/lora_callback.h"

#include "Work_with_FSM/operation_funcs/lora_funcs/lora_get_config_func/lora_get_config_funcs.h"
#include "Work_with_flash_memory/dealing_with_flash.h"







void config_lora_transmit(uint32_t conf_addr){
   static RadioEvents_t RadioEvents;

    RadioEvents.TxDone = OnTxDone;
    RadioEvents.RxDone = OnRxDone;
    RadioEvents.TxTimeout = OnTxTimeout;
    RadioEvents.RxTimeout = OnRxTimeout;
    RadioEvents.RxError = OnRxError;



    Radio.Init( &RadioEvents );


    int8_t power;
    uint32_t bandwidth;
    uint32_t codingrate;
    uint16_t preamblelen;

    bool fixlen;
    bool freqHopOnp;
    bool crcon;


    uint8_t hopperiod;
    bool iqinverted;
    uint16_t timeout_tx;

   uint8_t PROPERTY_ADDRESS_JUMP[] = {
                                                                0,1,2,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16
                                                            };


uint32_t  spreading_factor ;
bool hihi = get_param_from_flash(PROPERTY_ADDRESS_JUMP[SPREADINGFACTOR],conf_addr,&spreading_factor);


//printf(" gio in thu spreading factor ra xem lay dung chua : %d \n",spreading_factor);




uint32_t  frequency ;
 hihi = get_param_from_flash(PROPERTY_ADDRESS_JUMP[FREQ_NUM],conf_addr,&frequency);


//printf(" gio in thu frequency ra xem lay dung chua : %d \n",frequency);







 hihi = get_param_from_flash(PROPERTY_ADDRESS_JUMP[BANDWIDTH],conf_addr,&bandwidth);


//printf(" gio in thu bandwidth ra xem lay dung chua : %d \n",bandwidth);

if ( bandwidth ==125 )
{
  bandwidth=0;
}
else if (bandwidth == 250)
{
  bandwidth =1;

}
else if (bandwidth == 500)
{

  bandwidth=2;
}






hihi = get_param_from_flash(PROPERTY_ADDRESS_JUMP[CODINGRATE],conf_addr,&codingrate);


//printf(" gio in thu codingrate ra xem lay dung chua : %d \n",codingrate);





uint8_t key[32];



hihi = get_param_from_flash(PROPERTY_ADDRESS_JUMP[KEY_NUM],conf_addr,(void*)key);

//printf(" gio in thu key ra xem lay dung chua: \n"); 
//printf(" key index thu 0 la %d \n",*(key));

for ( int i =0 ; i <32 ;++i )
{
    printf(" byte %d la %d ",i,*(key+i));


}

// printf(" \n" );




hihi = get_param_from_flash(PROPERTY_ADDRESS_JUMP[TX_OUTPUT_PWR_NUM],conf_addr,&power);
//printf(" gio in thu power ra xem lay dung chua: \n"); 
// printf(" gio in thu power ra xem lay dung chua : %d \n",power);

hihi = get_param_from_flash(PROPERTY_ADDRESS_JUMP[PRE],conf_addr,&preamblelen);




//printf("  pre ra xem lay dung chua : %d \n",preamblelen);





hihi = get_param_from_flash(PROPERTY_ADDRESS_JUMP[FIXLEN],conf_addr,&fixlen);
// printf("  fixlen ra xem lay dung chua : %d \n",fixlen);


hihi = get_param_from_flash(PROPERTY_ADDRESS_JUMP[CRCC],conf_addr,&crcon);
// printf("  crcon ra xem lay dung chua : %d \n",crcon);


hihi = get_param_from_flash(PROPERTY_ADDRESS_JUMP[FREQHOP],conf_addr,&freqHopOnp);
// printf("  freqhop ra xem lay dung chua : %d \n",freqHopOnp);


hihi = get_param_from_flash(PROPERTY_ADDRESS_JUMP[IQINVERTED],conf_addr,&iqinverted);
// printf("  iqinverted ra xem lay dung chua : %d \n",iqinverted);



hihi = get_param_from_flash(PROPERTY_ADDRESS_JUMP[HOPPERIOD],conf_addr,&hopperiod);
// printf("  hopperiod ra xem lay dung chua : %d \n",hopperiod);


hihi = get_param_from_flash(PROPERTY_ADDRESS_JUMP[TX_TIMEOUT],conf_addr,&timeout_tx);
// printf("  tx timeot ra xem lay dung chua : %d \n",timeout_tx);








Radio.SetChannel(frequency);

Radio.SetTxConfig( 1, power, 0, bandwidth,
  spreading_factor, codingrate,
  preamblelen, fixlen,
  crcon, freqHopOnp, hopperiod, iqinverted, timeout_tx );



  Radio.SetRxConfig(1,bandwidth,spreading_factor,codingrate,0,preamblelen,0,fixlen,0,crcon,freqHopOnp,hopperiod,iqinverted,true);

 NVIC_SetPriority(LORA_IRQn, 3);

}






/*



    uint8_t freq_num_byte ;
    uint32_t address_after_jump;
    int8_t check =  take_byte_from_flash(conf_addr,PROPERTY_ADDRESS_JUMP[FREQ_NUM],&freq_num_byte,&address_after_jump);



    printf(" freq num byte la %d \n",freq_num_byte);


        address_after_jump ++;
    {

      uint8_t* frequency_get=  take_data_from_flash_memory(freq_num_byte,address_after_jump);



      printf(" in thu xem lay frequency dung khong nha \n");


      for ( int i =0 ; i<freq_num_byte;++i)
      {
        printf(" byte thu %d   la  %d",i,*(frequency_get+i));
      }
    
    }

*/













