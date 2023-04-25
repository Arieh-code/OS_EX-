#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Function to compare two files and check if they are equal or not
bool compare_files(const char *file1, const char *file2, bool verbose, bool ignore_case)
{
    FILE *f1, *f2;
    char c1, c2;

    // Open the two files in read mode
    f1 = fopen(file1, "rb");
    f2 = fopen(file2, "rb");

    // Check if both files are opened successfully
    if (f1 == NULL || f2 == NULL)
    {
        printf("Error: One or both files not found.\n");
        return false;
    }

    // Compare the files character by character
    if (ignore_case)
    {
        // If ignore_case flag is set, convert characters to lowercase and compare
        while ((c1 = fgetc(f1)) != EOF && (c2 = fgetc(f2)) != EOF)
        {
            if (tolower(c1) != tolower(c2))
            {
                fclose(f1);
                fclose(f2);
                return false;
            }
        }
    }
    else
    {
        // If ignore_case flag is not set, compare characters as is
        while ((c1 = fgetc(f1)) != EOF && (c2 = fgetc(f2)) != EOF)
        {
            if (c1 != c2)
            {
                fclose(f1);
                fclose(f2);
                return false;
            }
        }
    }

    // Close the files
    fclose(f1);
    fclose(f2);

    // If verbose flag is set, print "equal"
    if (verbose)
    {
        printf("equal\n");
    }

    // Return true if files are equal, false otherwise
    return true;
}

// Main function
int main(int argc, char *argv[])
{
    // Check if correct number of command-line arguments are provided
    if (argc < 3)
    {
        printf("Usage: cmp <file1> <file2> [-v] [-i]\n");
        return 1;
    }

    const char *file1 = argv[1];
    const char *file2 = argv[2];
    bool verbose = false;
    bool ignore_case = false;

    // Parse command-line arguments to set verbose and ignore_case flags
    for (int i = 3; i < argc; i++)
    {
        if (strcmp(argv[i], "-v") == 0)
        {
            verbose = true;
        }
        else if (strcmp(argv[i], "-i") == 0)
        {
            ignore_case = true;
        }
    }

    // Call compare_files function to compare the two files
    bool result = compare_files(file1, file2, verbose, ignore_case);

    // Return 0 if files are equal, 1 otherwise
    return result ? 0 : 1;
}
