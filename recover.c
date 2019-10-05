// Detects if a file is a JPEG

#include <stdio.h>

int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        return 1;
    }

    // Open file
    FILE *rawfile = fopen(argv[1], "r");
    if (!rawfile)
    {
        return 2;
    }

    // Read first four bytes
    unsigned char bytes[512];
    int file_number = 0;
    char file_name[8];
    sprintf(file_name, "%03i.jpg", file_number);

    // Declare file pointer
    FILE *recoveredfile = fopen(file_name, "w");

    while (fread(bytes, 1, 512, rawfile) == 512)
    {

        // Check first three bytes
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {

            // printf("New jpeg!");

            // save previous file and start new file
            if (file_number)
            {
                fclose(recoveredfile);
                sprintf(file_name, "%03i.jpg", file_number);
                recoveredfile = fopen(file_name, "w");
            }

            file_number++;
        }


        if (file_number)
        {
            fwrite(bytes, 1, 512, recoveredfile);
        }
    }

    fwrite(bytes, 1, 512, recoveredfile);
    fclose(recoveredfile);

    // Close file
    fclose(rawfile);

    // end
    return 0;
}
