#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    // unless there is exactly 1 command line argument, retry
    if (argc != 2)
    {
        printf("Invalid command-line argument. Please try again.\n");
        return 1;
    }

    // opens input file
    FILE *file = fopen(argv[1], "r");

    // if input file is null, return 1
    if (file == NULL)
    {
        return 1;
    }

    // create a buffer, jpeg counter, file counter, and initialize an empty image on which to write later
    unsigned char buffer[512];
    bool isValid = false;
    int FILEcounter = 0;
    FILE* image = NULL;

    while (fread(buffer, 512, 1, file) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (isValid)
            {
                fclose(image);
            }

            else
            {
                isValid = true;
            }

            char name[8];
            sprintf(name, "%03d.jpg", FILEcounter);

            image = fopen(name, "a");
            FILEcounter++;
        }

        if (isValid==true)
        {
            fwrite(&buffer, 512, 1, image);
        }

    }

    fclose(file);
    fclose(image);
    return 0;
}
