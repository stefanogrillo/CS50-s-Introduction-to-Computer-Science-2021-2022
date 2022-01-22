#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BUFFER_SIZE 512

typedef uint8_t byte;

int main(int argc, char *argv[])
{
    // Check arguments
    if (argc != 2)
    {
        printf("Usage: ./recover CARD\n");
        return 1;
    }

    // Open the input file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 2;
    }

    // Declare a temporary storage (buffer) called "block"
    byte block[BUFFER_SIZE];
    // Declare output file buffer
    FILE *JPG = NULL;
    // Initialize a counter for images
    int n_images = 0;

    // Read 512 bytes and store them in the block (the buffer)
    while (fread(block, sizeof(BUFFER_SIZE), 1, input) == 1)
    {
        // If we find a header
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0)
        {
            // Store space to hold the file's name
            char filename[8];
            // Give each JPEG a name, as counted
            sprintf(filename, "%03i.jpg", n_images);

            // Open an output file and write into
            JPG = fopen(filename, "w");

            // Count the image
            n_images++;
        }
        // If we have found a header, write it in JPG
        if (JPG != NULL)
        {
            fwrite(block, sizeof(BUFFER_SIZE), 1, JPG);
        }
    }
    // Close everything, signal success
    fclose(input);
    fclose(JPG);
    return 0;
}
