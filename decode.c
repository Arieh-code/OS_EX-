#include <stdio.h>
#include <dlfcn.h>

typedef void (*DecodeFunc)(char *);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: decode <codec> <message>\n");
        return 1;
    }

    char *codecName = argv[1];
    char *message = argv[2];

    void *handle = dlopen(codecName, RTLD_LAZY);
    if (!handle) {
        printf("Failed to load codec library: %s\n", dlerror());
        return 1;
    }

    DecodeFunc decode = (DecodeFunc)dlsym(handle, "codecA_decode");
    if (!decode) {
        printf("Failed to find decode function: %s\n", dlerror());
        return 1;
    }

    decode(message);
    printf("Decoded message: %s\n", message);

    dlclose(handle);
    return 0;
}
