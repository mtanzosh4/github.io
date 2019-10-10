// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

int dictionary_size = 0;

// Number of buckets in hash table
// const unsigned int N = 1;

// Hash table
node *table[SIZE];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    char lower_word[LENGTH + 1];
    for (int i = 0; i <= LENGTH; i++)
    {
        lower_word[i] = tolower(word[i]);
    }

    int position = hash(lower_word);
    if (table[position] != NULL)
    {
        node *n = table[position];
        while (n != NULL)
        {
            if (!strcmp(n->word, lower_word))
            {
                return true;
            }
            n = n->next;
        }

    }
    return false;
}

// Hashes word to a number
// http://www.cs.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    int c = 0;

    while ((c = *word++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % SIZE;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict_pointer = fopen(dictionary, "r");
    if (dict_pointer == NULL){
        return false;
    }

    node *n = malloc(sizeof(node));
    int letter_idx = 0;

    while (true)
    {

        char c = fgetc(dict_pointer);
        if (c == EOF)
        {
            return true;
        }

        if (c == '\n')
        {
            dictionary_size++;
            n->next = NULL;
            n->word[letter_idx] = '\0';

            if (!strcmp(n->word, "la"))
            {
                printf("loading la\n");
            }

            int position = hash(n->word);
            if (table[position] == NULL)
            {
                table[position] = n;
            }
            else
            {
                // add to beginning of list
                n->next = table[position]->next;
		        table[position]->next = n;
            }
            n = malloc(sizeof(node));
            letter_idx = 0;
        }
        else
        {
            n->word[letter_idx] = c;
            letter_idx++;
        }

    }

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dictionary_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    // return false;
    return true;
}
