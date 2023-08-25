#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open file
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    int idx = 0;
    FILE *outptr = NULL;
    char outfile[8];

    while (fread(buffer, 1, BLOCK_SIZE, inptr) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >> 4) == 0x0e)
        {
            // Close previous output file
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            // Create new output file
            sprintf(outfile, "%03i.jpg", idx++);
            outptr = fopen(outfile, "w");
            if (outptr == NULL)
            {
                printf("Could not create %s.\n", outfile);
                return 1;
            }
        }

        if (outptr != NULL)
        {
            fwrite(buffer, 1, BLOCK_SIZE, outptr);
        }
    }

    if (outptr != NULL)
    {
        fclose(outptr);
    }

    fclose(inptr);

    return 0;
}
