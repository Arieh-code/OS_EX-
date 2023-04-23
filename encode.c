#include <stdio.h>
#include <dlfcn.h>

typedef void (*EncodeFunc)(char *); // Define a function pointer type for the encode function

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: encode <codec> <message>\n");
        return 1;
    }

    char *codecName = argv[1]; // Get the codec library name from command line argument
    char *message = argv[2];   // Get the message to encode from command line argument

    void *handle = dlopen(codecName, RTLD_LAZY); // Load the codec library dynamically
    if (!handle)
    {
        printf("Failed to load codec library: %s\n", dlerror()); // Print error message if library loading fails
        return 1;
    }

    EncodeFunc encode = (EncodeFunc)dlsym(handle, "codecA_encode"); // Get the address of the "codecA_encode" function from the loaded library
    if (!encode)
    {
        printf("Failed to find encode function: %s\n", dlerror()); // Print error message if "codecA_encode" function is not found
        return 1;
    }

    encode(message);                          // Call the encode function with the message to encode
    printf("Encoded message: %s\n", message); // Print the encoded message

    dlclose(handle); // Close the loaded library
    return 0;
}
