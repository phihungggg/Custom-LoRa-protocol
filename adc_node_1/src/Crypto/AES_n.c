#include "Work_with_crypto/AES/AES_n.h"


#include "algorithm.h"
#include "aes.h"


uint8_t allocation(U8 **allocated_data_for, uint8_t inlength) {
    // Round up to the nearest multiple of 16
    uint8_t size = ((inlength + 15) / 16) * 16;

    *allocated_data_for = (U8 *)calloc(size, sizeof(U8));
    return size;
}

void aes_ecb(U8 *datain, uint8_t inlength, U8 *dataout, U8 de_or_en, U8 *AES_KEY, uint8_t KEY_LENGTH)
{


    for ( int i = 0 ; i < inlength;++i)
    {
        *(dataout+i) = 0;

    }
    if (KEY_LENGTH != 16 && KEY_LENGTH != 24 && KEY_LENGTH != 32) {
        printf("KEY LENGTH chỉ có thể là 16 / 24 / 32 bytes\n");
        return;
    }

    // Round input length to multiple of 16 for AES block
    uint8_t padded_length = ((inlength + 15) / 16) * 16;

    // Allocate padded input buffer
    U8 *padded_input = (U8 *)calloc(padded_length, sizeof(U8));
    if (!padded_input) {
        printf("Failed to allocate memory for AES input\n");
        return;
    }

    // Copy input data and pad with zeros (can modify to use PKCS7 if needed)
    memcpy(padded_input, datain, inlength);

    // Init AES context
    aes_init(AES_KEY, KEY_LENGTH, 0, NULL);

    // Perform encryption or decryption
    aes_crypto(padded_input, padded_length, de_or_en, dataout);

    // Clean up
    free(padded_input);
    aes_close();
}