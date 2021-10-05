#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



// block size used for jpeg
const int BLOCK_SIZE = 512;

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    // do  error checking for invalid argument or too many
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // open file
    char *input_file_name = argv[1];
    FILE *input = fopen(input_file_name, "r");

    if (input == NULL)
    {
        printf("Error: File Not Found");
        return 2;
    }

    // define buffer
    BYTE buffer[BLOCK_SIZE];
    int counter = 0;

    // define new output file name
    char output_name[8];

    // prepare output file
    FILE *output = NULL;

    // read until end of file
    while (fread(&buffer, BLOCK_SIZE, 1, input) == 1)
    {

        // open the new output file


        // this condition find a jpeg buffer - includes bitwise operator
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef)
        {

            if (!(counter == 0))
            {
                fclose(output);
            }

            // new file
            sprintf(output_name, "%03i.jpg", counter);
            output = fopen(output_name, "w");

            // increment file name
            counter++;


        }
        if (!(counter == 0))
        {
            fwrite(&buffer, BLOCK_SIZE, 1, output);
        }

    }

    fclose(input);
    fclose(output);

    return 0;
}