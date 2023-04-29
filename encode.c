#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "codecA.h"
#include "codecB.h"

typedef void (*EncodeFunc)(char *);

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: encode <codec> <message>\n");
        return 1;
    }

    char *codecName = argv[1];
    char *message = argv[2];

    // Load the shared library dynamically
    char libName[100];
    sprintf(libName, "lib%s.so", codecName);
    void *handle = dlopen(libName, RTLD_LAZY);
    if (!handle)
    {
        printf("Failed to load codec library: %s\n", dlerror());
        return 1;
    }

    // Get the address of the encode function from the shared library
    char funcName[100];
    sprintf(funcName, "codec%s_encode", strrchr(codecName, 'A') ? "A" : "B");
    EncodeFunc encode = (EncodeFunc)dlsym(handle, funcName);
    if (!encode)
    {
        printf("Failed to find encode function: %s\n", dlerror());
        dlclose(handle);
        return 1;
    }

    // Call the encode function and print the encoded message
    encode(message);
    printf("Encoded message: %s\n", message);

    dlclose(handle); // Close the loaded library
    return 0;
}
