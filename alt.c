#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 256
#define MAX_NUM_STRINGS 100
#define MAX_NUM_SPECIAL_CHARS 100

int main(int argc, char **argv)
{
    // Open the input files
    FILE *strings_file = fopen("output.txt", "r");
    FILE *special_chars_file = fopen("special_characters.txt", "r");
    if (!strings_file || !special_chars_file)
    {
        printf("Error opening input files!\n");
        return 1;
    }

    // Open the output file
    FILE *output_file = fopen("output2.txt", "w");
    if (!output_file)
    {
        printf("Error opening output file!\n");
        return 1;
    }

    // Read the strings from the input file and store them in an array
    char strings[MAX_NUM_STRINGS][MAX_STRING_LENGTH];
    int num_strings = 0;
    char line[MAX_STRING_LENGTH];
    while (fgets(line, sizeof(line), strings_file) && num_strings < MAX_NUM_STRINGS)
    {
        // Remove the newline character from the end of the line
        size_t len = strlen(line);
        if (line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
        }

        // Copy the string to the array
        strcpy(strings[num_strings], line);
        num_strings++;
    }

    // Read the special characters from the input file and store them in an array
    char special_chars[MAX_NUM_SPECIAL_CHARS];
    int num_special_chars = 0;
    while (fscanf(special_chars_file, "%c", &special_chars[num_special_chars]) && num_special_chars < MAX_NUM_SPECIAL_CHARS)
    {
        num_special_chars++;
    }

    // Generate all possible variations of the strings and special characters and write them to the output file
    for (int i = 0; i < num_strings; i++)
    {
        for (int j = 0; j < num_special_chars; j++)
        {
            fprintf(output_file, "%s%c\n", strings[i], special_chars[j]);
        }
    }

    // Close the input and output files
    fclose(strings_file);
    fclose(special_chars_file);
    fclose(output_file);

    return 0;
}
