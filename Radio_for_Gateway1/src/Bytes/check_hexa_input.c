

#include "Work_with_bytes/check_hexa_input.h"

static int hex_char_to_nibble(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

int parse_strict_hex_bytes(const char *input, uint8_t *output, int max_bytes) {
    const char *ptr = input;
    int count = 0;

    while (count < max_bytes) {
        // Check for "0x" prefix
        if (ptr[0] != '0' || ptr[1] != 'x') return -1;

        int high = hex_char_to_nibble(ptr[2]);
        int low  = hex_char_to_nibble(ptr[3]);
        if (high < 0 || low < 0) return -1;

        output[count++] = (uint8_t)((high << 4) | low);
        ptr += 4; // Move past "0xXX"

        // Expect either ',' or end of string
        if (*ptr == ',') {
            ptr++;
        } else if (*ptr == '\0') {
            break;
        } else {
            return -1; // Invalid separator
        }
    }

    return (*ptr == '\0') ? count : -1;
}