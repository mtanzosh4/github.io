#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string s = get_string("Name: ");
    printf("%c", toupper(s[0]));
    for (int i = 1; i < strlen(s); i++)
    {
        if (s[i] == 32)
        {
            printf("%c", toupper(s[i + 1]));
        }
    }
    printf("\n");
}
