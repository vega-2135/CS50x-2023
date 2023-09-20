
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


#define BLOCK_SIZE 512
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
// Check for invalid usage
    if (argc != 2)
    {
        printf("Please add forensic image\n");
        return 1;
    }

    // Open the forensic image file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Set a buffer into which to read from card
    BYTE buffer[BLOCK_SIZE];

    // Set a counter for number of jpgs found
    int file_counter = 0;

    // Making an output file where all the images will be transferred
    FILE *output_file = NULL;

    // Read blocks of 512 bytes in file until end of file
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {

        // Look for beginning of a jpg file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (output_file != NULL)
            {
                fclose(output_file);
            }
            // Make jpg file
            char file_name[8];
            sprintf(file_name, "%03i.jpg", file_counter);
            output_file = fopen(file_name, "w");
            if (output_file == NULL)
            {
                printf("Could not open file.\n");
                return 1;
            }

            file_counter += 1;

        }

        // Write block with jpg image to output_file
        if (output_file != NULL)
        {
            fwrite(buffer, BLOCK_SIZE, 1, output_file);
        }

    }

    // Close output_file if open
    fclose(output_file);

    // Close memory card
    fclose(file);

}