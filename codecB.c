#include <stddef.h>

void codecB_encode(char *str) {
    for (size_t i = 0; str[i]; ++i) {
        str[i] = (str[i] + 3) % 128;  // Wrap around to handle overflow
    }
}

void codecB_decode(char *str) {
    for (size_t i = 0; str[i]; ++i) {
        str[i] = (str[i] + 125) % 128;  // Wrap around to handle underflow
    }
}
