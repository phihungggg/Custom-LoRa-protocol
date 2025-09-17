










#ifndef __ENUM_LORA_H
#define __ENUM_LORA_H

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include "tremo_system.h"
typedef enum {
    FLASH_MEMORY,
AUTHENTICATION,
CONFIG,
OPERATE
}Stage_t;


typedef enum
{
    WAITING_PRESS_FIRST_ENTER,

    RE_WAITING_PRESS_FIRST_ENTER,

    USERNAME_TYPING,

    USERNAME_TYPING_WAITING,

    PASSWORD_TYPING,

    PASSWORD_TYPING_WAITING,

    AUTHENTICATION_RESULT,

    AUTHENTICATION_COMPLETE,
}States_Authentication_t;






extern const uint8_t PROPERTY_ADDRESS_JUMP[] ;



typedef enum{

    NODE_ID_SET_WAITING,
    NODE_ID_SET,
    KEY_SET1,
    KEY_SET2,
    KEY_SET3,
    KEY_SET4,
    KEY_SET_RESULT,
    TX_POWER_SET,
    INTERVAL_SET,
    THRESHOLD_SET,
    FREQUENCY_SET,
    BANDWIDTH_SET,
    SPREADING_FACTOR_SET,
    CODINGRATE_SET,
    PREAMBLELEN_SET,
    SYMBTIMEOUT_SET,
    FIXLEN_SET,
    PAYLOADLEN_SET,

    FREQHOPON_SET,
    CRCON_SET,

    HOPPERIOD_SET,
    IQINVERTED_SET,

    TX_TIMEOUT_SET,
    
   // RXCONTINOUS_SET,

    AUTHENTICATION_KEY_SET,

    NODE_ADDRESS_SET,
    ADD_CONFIG_TO_FLASH_MEMORY


}States_Config_t;



typedef enum {
    FREQ_INDEX_0,   // 923.2 MHz 
    FREQ_INDEX_1,   // 923.4 MHz  
    FREQ_INDEX_2,   // 923.6 MHz  
    FREQ_INDEX_3,   // 923.8 MHz  
    FREQ_INDEX_4,   // 924.0 MHz  
    FREQ_INDEX_5,   // 924.2 MHz  
    FREQ_INDEX_6,   // 924.4 MHz  
    FREQ_INDEX_7,   // 924.6 MHz  
    FREQ_INDEX_8,   // 924.5 MHz - SF7BW250 (high-speed / RX2)
    FREQ_INDEX_9,   // 924.8 MHz  
    FREQ_INDEX_10,  // 925.0 MHz  
    FREQ_INDEX_11,  // 925.2 MHz  
    FREQ_INDEX_12,  // 925.4 MHz  
    FREQ_INDEX_13,  // 925.6 MHz  
    FREQ_INDEX_14,  // 925.8 MHz  
    FREQ_INDEX_15,  // 926.0 MHz  
    FREQ_INDEX_16,  // 926.2 MHz  
    FREQ_INDEX_17,  // 926.4 MHz  
    FREQ_INDEX_18,  // 926.6 MHz  
    FREQ_INDEX_19   // 926.8 MHz  
} AS923_ChannelIndex_t;

#define NUM_FREQ_CHANNELS 20






typedef enum {
trash,
db1, db2, db3, db4, db5, db6, db7,
db8, db9, db10, db11, db12, db13, db14,
db15, db16, db17, db18, db19, db20, db21,
db22, db23, db24, db25, db26, db27, db28,
db29, db30, db31, db32, db33, db34, db35,
db36, db37, db38, db39, db40, db41, db42,
db43, db44, db45, db46, db47, db48, db49,
db50, db51, db52, db53, db54, db55, db56,
db57, db58, db59, db60, db61, db62, db63,
db64, db65, db66, db67, db68, db69, db70,
db71, db72, db73, db74,
}TX_OUTPUT_PWER_t;






typedef enum {

    AESKEY_TYPING,
    AESKEY_NOT_TYPING


}AESKEY_TYPING_OR_NOT;





typedef enum {

    //AUTHENTICATION DATA 
    USERNAME_ELEMENTS_NUM,
    PASSWORD_ELEMENTS_NUM,
    AUTHENTICATION_YET,



    //CONFIG DATA
    NODEID_NUM,
    KEY_NUM,
    TX_OUTPUT_PWR_NUM,
    INTERVAL_NUM,
    THRESHOLD_NUM,
    FREQ_NUM,
    BANDWIDTH,
    SPREADINGFACTOR,
    CODINGRATE,
    PRE,
    FIXLEN,
    CRCC,
    FREQHOP,
    HOPPERIOD,
    IQINVERTED,
    TX_TIMEOUT,


    AUTHENTICATIONKEY_SET_INDEX,
    ADDRESS_SET_INDEX,
    
    CONFIG_YET,




}ADDR_INDEX_OF_EACH_PROPERTY;






typedef enum {

    TAKE_DATA_FROM_SENSORS,



    REMOVE_FLASH_BUTTON_PRESSED,


    SEND_DATA_THROUGH_LORA,


    RTC_INTERVAL_OPERATE,

    LISTEN,

    DONOTHING , 


    REICEIVED,
    READ_DATA_FROM_GPIO,

    USER_BUTTON_IS_PRESSED, 

    TOGGLE_LED_WHEN_DOWNLINK_RECEIVED,

    ERROR_HANDLING_WHEN_GATEWAY_NOT_RESPONSE,

    ERROR_HANDLING_WHEN_RECEIVE_WRONG_PACKET,

    


    WRONG_ADDRESS, 

    HANDLING_INCOMING_DOWNLINK , 

    

    
}Operation_state_t;











typedef struct {

    uint8_t day;        /*!< day*/
    uint8_t hour;       /*!< hour*/
    uint8_t minute;     /*!< minute*/
    uint8_t second;     /*!< second*/
   
} interval_t;















//extern  uint8_t PROPERTY_ADDRESS_JUMP [];





#ifdef __cplusplus
}
#endif

#endif /* __LORA_CONFIG_H */
