#include <stddef.h>
#include "codecB.h"

void codecB_encode(char *str)
{
    for (size_t i = 0; str[i]; ++i)
    {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
        { // check if the character is a letter
            if (str[i] >= 'a' && str[i] <= 'z')
            {
                str[i] = ((str[i] - 'a' + 3) % 26) + 'a'; // lowercase
            }
            else
            {
                str[i] = ((str[i] - 'A' + 3) % 26) + 'A'; // uppercase
            }
        }
    }
}

void codecB_decode(char *str)
{
    for (size_t i = 0; str[i]; ++i)
    {
        str[i] = (str[i] + 128 - 3) % 128; // Subtract 3 and handle underflow
    }
}
