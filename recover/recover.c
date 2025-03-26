#include <cs50.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./ recover IMAGE\n");
        return 1;
    }

    char *file = argv[1];
    FILE *input_file = fopen(argv[1], "r");
    if (!input_file)
    {
        printf("Could not open file");
        return 1;
    }

    bool found_jpg = false; // Flag to keep track of whether a JPEG has been found
    uint8_t buffer[BLOCK_SIZE];
    int counter = 0;

    // char filename[8];
    char file_name[8];
    FILE *output_file = NULL;

    // Read the forensic image block by block (blocks of 512 bytes)
    while (fread(buffer, BLOCK_SIZE, 1, input_file) == 1)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        // only checks the first four bits (the most significant four bits) of the byte at buffer[3]. It doesn't care about the last
        // four bits.
        {

            if (found_jpg)
            {
                fclose(output_file);
            }
            else
            {
                found_jpg = true;
            }

            // Write the JPEG filnames
            sprintf(file_name, "%03i.jpg", counter);
            output_file = fopen(file_name, "w");

            if (!output_file)
            {
                fclose(input_file);
                printf("Could not create the file.\n");
                return 3;
            }
            counter++;
        }

        if (found_jpg)
        {
            fwrite(buffer, BLOCK_SIZE, 1, output_file);
        }
    }

    // Close the forensic image file and the last JPEG file, if one was open
    fclose(input_file);
    if (found_jpg)
    {
        fclose(output_file);
    }

    return 0;
}