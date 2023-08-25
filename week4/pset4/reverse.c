#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

typedef uint8_t BYTE;

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    // Read header
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, inptr);

    // Use check_format to ensure WAV format
    if (!check_format(header))
    {
        printf("%s is not wav file.\n", infile);
        return 1;
    }

    // Open output file for writing
    char *outfile = argv[2];
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        printf("Could not open %s.\n", outfile);
        return 1;
    }

    // Write header to file
    fwrite(&header, sizeof(WAVHEADER), 1, outptr);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);

    // Write reversed audio to file
    fseek(inptr, block_size, SEEK_END);

    while (ftell(inptr) - block_size > sizeof(header))
    {
        fseek(inptr, -2 * block_size, SEEK_CUR);
        BYTE buffer[block_size];
        fread(buffer, 1, block_size, inptr);
        fwrite(buffer, 1, block_size, outptr);
    }

    fclose(outptr);
    fclose(inptr);
    return 0;
}

int check_format(WAVHEADER header)
{
    char wav[] = "WAVE";
    int n = sizeof(wav) / sizeof(char);
    for (int i = 0; wav[i]; i++)
    {
        if (header.format[i] != wav[i])
        {
            return 0;
        }
    }
    return 1;
}

int get_block_size(WAVHEADER header)
{
    return header.bitsPerSample / 8 * header.numChannels;
}