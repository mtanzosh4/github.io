#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>


int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int Coleman_Liau_index(float letters, float words, float sentences, string text);

int main(void)
{
    string text = get_string("Text: ");

    int letters = count_letters(text);

    int words = count_words(text);

    int sentences = count_sentences(text);

    int index = Coleman_Liau_index(letters, words, sentences, text);

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }


}

// Function to count total amount of letters in the text
// int letters = count_letters(text);
// int words = count_words(text);
// int sentences = count_sentences(text);

int Coleman_Liau_index(float letters, float words, float sentences, string text)
{
    // printf("letters: %f\n words: %f\n sentences: %f\n text: %s\n", letters, words, sentences, text);
    float L = 100.00 / (float) words * (float)letters;
    float S = 100.00 / (float) words * (float) sentences;

    int index =round(0.0588 * L - 0.296 * S - 15.8);
    // // printf("index: %f\n", index);
    // index = round(index);
    // printf("index: %f\n, L: %f\n, S: %f\n", index, L, S);
    return index;
}

// Function to count total amount of letters in the text
int count_letters(string text)
{
    int text_len = strlen(text);
    int letters_counter = 0;

    for (int i = 0; i < text_len; i ++)
    {
        if (isalpha(text[i]))
        {
            letters_counter++;
        }
    }
    return letters_counter;
}


// Function to count amount of words in the text
int count_words(string text)
{
    printf("%lu\n", strlen(text));
    char copy_text[2000];
    strcpy(copy_text, text);


    char *new_array = strtok(copy_text, " ");

    int counter = 0;

    while (new_array != NULL)
    {
        new_array = strtok(NULL, " ");
        counter++;
    }
    printf("%i\n", counter);
    return counter;

}

// Function to count amount of sentences in the text
int count_sentences(string text)
{

    int counter = 0;
    char copy_text2[2000];

    strcpy(copy_text2, text);
    char *str_array = strtok(copy_text2, ".!?");

    while (str_array != NULL)
    {
        str_array = strtok(NULL, ".!?");
        counter++;
        // printf("s%i: %s\n addrs: %p\n", counter, str_array, *(&str_array + 1));
    }
    printf("count_sentences: %i\n", counter);
    return counter;

}



