// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    // Buffer for file header
    uint8_t *header_buffer = malloc(sizeof(uint8_t) * HEADER_SIZE);
    // Read from input file to buffer
    fread(header_buffer, sizeof(uint8_t), 44, input);
    // Write in output file
    fwrite(header_buffer, sizeof(uint8_t), 44, output);

    // Free alocated memory
    free(header_buffer);

    // Read samples from input file and write updated data to output file
    // Buffer for file samples
    int16_t *sample_buffer = malloc(sizeof(int16_t));
    // Read from current input file location until end
    while (fread(sample_buffer, sizeof(int16_t), 1, input))
    {
        // Multiply by factor to alter output file volume
        *sample_buffer *= factor;
        // Write in output file
        fwrite(sample_buffer, sizeof(int16_t), 1, output);
    }
    // Free alocated memory
    free(sample_buffer);

    // Close files
    fclose(input);
    fclose(output);
}
