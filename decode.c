#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include "codecA.h"
#include "codecB.h"

typedef void (*DecodeFunc)(char *); // Define a function pointer type for the decode function

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: decode <codec> <message>\n");
        return 1;
    }

    char *codecName = argv[1]; // Get the codec library name from command line argument
    char *message = argv[2];   // Get the message to decode from command line argument

    char libName[100];
    sprintf(libName, "lib%s.so", codecName);

    void *handle = dlopen(libName, RTLD_LAZY); // Load the codec library dynamically
    if (!handle)
    {
        printf("Failed to load codec library: %s\n", dlerror()); // Print error message if library loading fails
        return 1;
    }

    char funcName[100];
    sprintf(funcName, "codec%s_decode", strrchr(codecName, 'A') ? "A" : "B");
    DecodeFunc decode = (DecodeFunc)dlsym(handle, funcName); // Get the address of the decode function from the loaded library
    if (!decode)
    {
        printf("Failed to find decode function: %s\n", dlerror()); // Print error message if decode function is not found
        return 1;
    }

    decode(message);                          // Call the decode function with the message to decode
    printf("Decoded message: %s\n", message); // Print the decoded message

    dlclose(handle); // Close the loaded library
    return 0;
}
