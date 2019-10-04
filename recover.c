// Detects if a file is a JPEG

#include <stdio.h>
#include <stdbool.h>

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

    // Read first three bytes
    unsigned char bytes[512];
    int file_number = 0;
    char file_name[8];
    sprintf(file_name, "%03i.jpg", file_number);
    FILE *recoveredfile = fopen(file_name, "w");
    bool start = false;
    int bytes_read;
    while (true)
    {
        bytes_read = fread(bytes, 1, 512, rawfile);
        if (bytes_read != 512)
        {
            printf("%i bytes\n", bytes_read);
            break;
        }
        // Check first three bytes
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0 == 0xe0))
        {
            start = true;
            // save previous file and start new file
            if (file_number != 0)
            {
                fclose(recoveredfile);
                file_number++;
                sprintf(file_name, "%03i.jpg", file_number);
                recoveredfile = fopen(file_name, "w");
            }
        }
        if (start)
        {
            fwrite(bytes, 1, bytes_read, recoveredfile);
        }
    }
    fwrite(bytes, 1, bytes_read, recoveredfile);
    fclose(recoveredfile);

    // Close file
    fclose(rawfile);
}
