#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string pw = get_string("");

    if (strlen(pw) < 8)
    {
        printf("Password must be at least 8 characters long!\n");
        return 1;
    }

    bool upper = false;
    bool lower = false;
    bool digit = false;
    bool special = false;

    for (int i = 0; i < strlen(pw); i++)
    {
        if (isupper(pw[i]))
        {
            upper = true;
        }
        else if (islower(pw[i]))
        {
            lower = true;
        }
        else if (isdigit(pw[i]))
        {
            digit = true;
        }
        else if (ispunct(pw[i]))
        {
            special = true;
        }
    }

    if (upper && lower && digit && special)
    {
        printf("Your password is good!\n");
    }
    else
    {
        printf("Passes\n");
    }
}