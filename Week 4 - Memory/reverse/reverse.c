#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "wav.h"

const int HEADER_SIZE = 44;
int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    WAVHEADER headers;
    if (argc != 3)
    {
        printf("Enter 2 command lines\n");
        return 1;
    }
    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Couldn't open the file\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Couldn't open file.\n");
        return 1;
    }
    // Read header into an array
    // TODO #3
    fread(&headers, HEADER_SIZE, 1, input);
    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(headers) != 0)
    {
        printf("file is not a WAV\n");
        return 1;
    }
    // Open output file for writing
    // TODO #5

    // Write header to file
    // TODO #6

    fwrite(&headers, HEADER_SIZE, 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int blockSize = get_block_size(headers);

    // Write reversed audio to file
    // TODO #8
    BYTE B [blockSize];
    int start = ftell(input);
    fseek(input, blockSize, SEEK_END);
    while (ftell(input) - blockSize != start)
    {
        fseek(input, -2 * blockSize, SEEK_CUR);
        fread(&B, blockSize, 1, input);
        fwrite(&B, blockSize, 1, output);
    }
    fclose(input);
    fclose(output);
    return 0;
}

int check_format(WAVHEADER header)
{
    unsigned char scope [4] =  "WAVE";
    // TODO #4
    for (int i = 0; i < 4; i++)
    {
        if (header.format [i] != scope [i])
        {
            return 1;
        }
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int BytesperSample = header.bitsPerSample / 8;
    int block_size = header.numChannels * BytesperSample;
    return block_size;
}