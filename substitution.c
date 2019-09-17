#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define KEY_LENGTH 26

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];
    if (strlen(key) != KEY_LENGTH)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < KEY_LENGTH; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Must use all alpha characters!\n");
            return 1;
        }
    }

    bool letters[26] = {false};
    for (int i = 0; i < KEY_LENGTH; i++)
    {
        letters[(int) toupper(key[i] - 65)] = true;
    }

    for (int i = 0; i < KEY_LENGTH; i++)
    {
        if (!letters[i])
        {
            printf("Key can only contain each letter once!\n");
            return 1;
        }
    }

    // get plaintext
    string plaintext = get_string("plaintext: ");

    // print out ciphertext
    printf("ciphertext: ");
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isupper(plaintext[i]))
        {
            printf("%c", toupper(key[plaintext[i] - 65]));
        }
        else if (islower(plaintext[i]))
        {
            printf("%c", tolower(key[plaintext[i] - 97]));
        }
        else
        {
            printf("%c", plaintext[i]);
        }
    }
    printf("\n");

}