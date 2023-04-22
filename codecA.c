#include <ctype.h>
#include <stddef.h>

void codecA_encode(char *str) {
    for (size_t i = 0; str[i]; ++i) {
        if (islower(str[i]))
            str[i] = toupper(str[i]);
        else if (isupper(str[i]))
            str[i] = tolower(str[i]);
    }
}

void codecA_decode(char *str) {
    for (size_t i = 0; str[i]; ++i) {
        if (islower(str[i]))
            str[i] = toupper(str[i]);
        else if (isupper(str[i]))
            str[i] = tolower(str[i]);
    }
}
