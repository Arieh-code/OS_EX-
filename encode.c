#include <stdio.h>
#include <dlfcn.h>

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

    void *handle = dlopen(codecName, RTLD_LAZY);
    if (!handle)
    {
        printf("Failed to load codec library: %s\n", dlerror());
        return 1;
    }

    EncodeFunc encode = (EncodeFunc)dlsym(handle, "codecA_encode");
    if (!encode)
    {
        printf("Failed to find encode function: %s\n", dlerror());
        return 1;
    }

    encode(message);
    printf("Encoded message: %s\n", message);

    dlclose(handle);
    return 0;
}
