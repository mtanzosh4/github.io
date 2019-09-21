#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    string s = get_string("Text: ");

    float letters = 0;
    float words = 1;
    float sentences = 0;

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if(islower(s[i]) || isupper(s[i]))
        {
            letters++;
        }
        if (s[i] == ' ' && s[i+1] != ' ')
        {
            words++;
        }
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sentences++;
        }
    }

    printf("%f letter(s)\n", letters);
    printf("%f word(s)\n", words);
    printf("%f sentence(s)\n", sentences);

    float L = 100 * letters / words;
    float S = 100 * sentences / words;
    int X = round(0.0588 * L - 0.296 * S - 15.8);

    if (X > 16)
    {
        printf("Grade 16+");
    }
    else if (X < 1)
    {
        printf("Before Grade 1");
    }
    else
    {
        printf("Grade %i", X);
    }
    printf("\n");
}