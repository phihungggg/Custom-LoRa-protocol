#ifndef LORA_CALLBACK_H
#define LORA_CALLBACK_H
#ifdef __cplusplus
extern "C" {
#endif
#include <STANDARD_LIB.h>
#include "enum_lora.h"






void OnTxDone( void );

/*!
 * \brief Function to be executed on Radio Rx Done event
 */
void OnRxDone( uint8_t *payload, uint16_t size, int16_t rssi, int8_t snr );

/*!
 * \brief Function executed on Radio Tx Timeout event
 */
void OnTxTimeout( void );

/*!
 * \brief Function executed on Radio Rx Timeout event
 */
void OnRxTimeout( void );

/*!
 * \brief Function executed on Radio Rx Error event
 */
void OnRxError( void );


#ifdef __cplusplus

}
#endif

#endif /* __LORA_CONFIG_H */