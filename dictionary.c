// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    int index;
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;

// Hash table
node *table[SIZE];


// dict size
int dict_size = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    // printf("word: %s\n", word);
    node *current = table[0];
    while (current != NULL)
    {

       if (strcasecmp(current->word, word) == 0)
        {
            return true;
        }

        current = current->next;
    }

    return false;
}

// Hashes word to a number
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
    FILE* dict = fopen(dictionary, "r");

    if (dict == NULL)
    {
        return false;
    }


    char dict_word[LENGTH + 1];
    node *head = NULL;
    table[dict_size] = head;

    while (true)
    {
        node *new_word = malloc(sizeof(node));
        if (new_word == NULL)
        {
            return false;
        }
        fscanf(dict, "%s", dict_word);
        if (feof(dict))
        {
            free(new_word);
            return true;
        }
        // hash(*dict_word);
        // printf("dict_word: %s\n", *dict_word);
        // printf("sizeof(dict_word): %lu\n", sizeof(dict_word)/sizeof(char*));

        strcpy(new_word->word, dict_word);
        new_word->next = NULL;
        dict_size++;
        new_word->index = dict_size;
        new_word->next = head;
        head = new_word;
        table[0] = head;
    }

    // Why prints (null) instead of caterpillar
    // printf("Last table word: %s\n", table[0]->word);
    // printf("Dict size: %i\n", dict_size);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    node *current = table[0];

    while (current != NULL)
    {
        node *temp = current;
        current = current->next;
        free(temp);
    }

    if (current == NULL)
    {
        return true;
    }
    return false;
}