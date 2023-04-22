#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool copy_file(const char *file1, const char *file2, bool verbose, bool force)
{
    FILE *f1, *f2;
    char c;

    f1 = fopen(file1, "r");

    if (f1 == NULL)
    {
        printf("Error: Source file not found.\n");
        return false;
    }

    if (force)
    {
        f2 = fopen(file2, "w");
    }
    else
    {
        f2 = fopen(file2, "wx");
    }

    if (f2 == NULL)
    {
        printf("Error: Target file already exists.\n");
        fclose(f1);
        return false;
    }

    while ((c = fgetc(f1)) != EOF)
    {
        fputc(c, f2);
    }

    fclose(f1);
    fclose(f2);

    if (verbose)
    {
        printf("success\n");
    }

    return true;
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: copy <file1> <file2> [-v] [-f]\n");
        return 1;
    }

    const char *file1 = argv[1];
    const char *file2 = argv[2];
    bool verbose = false;
    bool force = false;

    for (int i = 3; i < argc; i++)
    {
        if (strcmp(argv[i], "-v") == 0)
        {
            verbose = true;
        }
        else if (strcmp(argv[i], "-f") == 0)
        {
            force = true;
        }
    }

    bool result = copy_file(file1, file2, verbose, force);

    return result ? 0 : 1;
}
