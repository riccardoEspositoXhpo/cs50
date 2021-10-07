// Implements a dictionary's functionality

#include <stdbool.h>
#include "dictionary.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26 * 26 * 26;

// Hash table
node *table[N];

int node_size = sizeof(node);
int hash_value;
int word_count;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    hash_value = hash(word);

    node *arrow = table[hash_value];

    while (arrow != NULL)
    {
        //check if the word matches
        if (strcasecmp(word, arrow->word) == 0)
        {
            return true;
        }

        arrow = arrow->next;

    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hash;

    // simplistic hash function creates one node for AAA, AAB, etc.
    char c1 = toupper(word[0]);
    char c2 = toupper(word[1]);
    char c3 = toupper(word[2]);


    // perform a loop here
    hash = (c1 - 65) * 100 +
           (c2 = 65) * 10  +
           (c3 - 65) * 1;

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    FILE *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        return false;

    }

    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        node *n = malloc(node_size);

        if (n == NULL)
        {

            return false;
            break;

        }

        strcpy(n->word, word);
        hash_value = hash(word);

        n->next = table[hash_value];
        table[hash_value] = n;
        word_count++;

    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{


    for (int i = 0; i < N; i++)
    {

        node *arrow = table[i];

        while (arrow)
        {
            // Create temp
            node *tmp = arrow;
            // Move arrow to next node
            arrow = arrow->next;
            // Free up temp
            free(tmp);
        }

        // we have reached the end of the loop
        if (i == N - 1 && arrow == NULL)
        {
            return true;
        }
    }
    return false;
}
