#ifndef CHECK_HEXA_INPUT_H
#define CHECK_HEXA_INPUT_H


#ifdef __cplusplus
extern "C" {
#endif


#include "STANDARD_LIB.h"


int parse_strict_hex_bytes(const char *input, uint8_t *output, int max_bytes);

#ifdef __cplusplus
}
#endif

#endif