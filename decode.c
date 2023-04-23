#include <stdio.h>
#include <dlfcn.h>

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

    void *handle = dlopen(codecName, RTLD_LAZY); // Load the codec library dynamically
    if (!handle)
    {
        printf("Failed to load codec library: %s\n", dlerror()); // Print error message if library loading fails
        return 1;
    }

    DecodeFunc decode = (DecodeFunc)dlsym(handle, "codecA_decode"); // Get the address of the "codecA_decode" function from the loaded library
    if (!decode)
    {
        printf("Failed to find decode function: %s\n", dlerror()); // Print error message if "codecA_decode" function is not found
        return 1;
    }

    decode(message);                          // Call the decode function with the message to decode
    printf("Decoded message: %s\n", message); // Print the decoded message

    dlclose(handle); // Close the loaded library
    return 0;
}
