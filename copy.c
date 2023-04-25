#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool copy_file(const char *file1, const char *file2, bool verbose, bool force)
{
    FILE *f1, *f2;
    char c;

    f1 = fopen(file1, "rb"); // Open source file in read mode

    if (f1 == NULL) // Check if source file was not found
    {
        printf("Error: Source file not found.\n");
        return false;
    }

    if (force) // Check if force flag is enabled
    {
        f2 = fopen(file2, "w"); // Open target file in write mode (overwrite if exists)
    }
    else
    {
        f2 = fopen(file2, "wx"); // Open target file in exclusive write mode (create new file, error if exists)
    }

    if (f2 == NULL) // Check if target file already exists
    {
        printf("Error: Target file already exists.\n");
        fclose(f1);
        return false;
    }

    // Copy contents of source file to target file character by character
    while ((c = fgetc(f1)) != EOF)
    {
        fputc(c, f2);
    }

    fclose(f1); // Close source file
    fclose(f2); // Close target file

    if (verbose) // Check if verbose flag is enabled
    {
        printf("success\n"); // Print success message
    }

    return true;
}

int main(int argc, char *argv[])
{
    if (argc < 3) // Check if there are enough command line arguments
    {
        printf("Usage: copy <file1> <file2> [-v] [-f]\n"); // Print usage message
        return 1;
    }

    const char *file1 = argv[1]; // Get source file name from command line argument
    const char *file2 = argv[2]; // Get target file name from command line argument
    bool verbose = false;        // Initialize verbose flag as false
    bool force = false;          // Initialize force flag as false

    for (int i = 3; i < argc; i++) // Loop through remaining command line arguments
    {
        if (strcmp(argv[i], "-v") == 0) // Check if verbose flag is provided
        {
            verbose = true; // Set verbose flag as true
        }
        else if (strcmp(argv[i], "-f") == 0) // Check if force flag is provided
        {
            force = true; // Set force flag as true
        }
    }

    bool result = copy_file(file1, file2, verbose, force); // Call copy_file function with provided arguments

    return result ? 0 : 1; // Return 0 if success, 1 if failure
}
