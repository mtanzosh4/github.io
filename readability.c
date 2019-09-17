#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // prompt for string
    string text = get_string("Enter some text: ");
    // count the number of letters, words and sentences
    int letters = count_letters(text);
    // printf("%i letter(s)\n", letters);

    int words = count_words(text);
    // printf("%i words(s)\n", words);

    int sentences = count_sentences(text);
    printf("%i sentence(s)\n", sentences);

    float l = round((float) letters * 100 / words);
    float s = round((float) sentences * 100 / words);

    int level = round (0.0588 * l - 0.296 * s - 15.8);

    if (level > 16)
    {
        printf("Grade 16+\n");
    }
    else if (level < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
         printf("Grade %i\n", level);
    }

}

int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, l = strlen(text); i < l; i++)
    {
        if (text[i] == '.' || text[i] == '?' || text[i] == '!')
        {
            count++;
            i++;
        }
    }
    return count;
}

int count_words(string text)
{
    int count = 0;
    for (int i = 0, l = strlen(text); i < l; i++)
    {
        if (isspace(text[i]) || i == l - 1)
        {
            count++;
            i++;
        }
    }
    return count;
}

int count_letters(string text)
{
    int count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            count++;
        }
    }
    return count;
}