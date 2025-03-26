// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

unsigned int word_count;
unsigned int hash_value;
bool is_loaded = false;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *hashtable[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    // Hash the word to get a hash value
    // (you can use the hash function you've already written)
    hash_value = hash(word);

    node *cursor = hashtable[hash_value];

    while (cursor != NULL)

    {

        // If the word in the hash_table is the same `cursor`, then return true
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    unsigned long total = 0;
    for (int i = 0, length = strlen(word); i < length; i++)
    {
        total = total + tolower(word[i]);
    }
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    FILE *file = fopen(dictionary, "r");

    // Checks if `dictionary` was sucessfylly opened
    if (file == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }

    // Create a char array word to store words from the file

    //#define LENGTH 45
    char word[LENGTH + 1];

    // While not end of file:
    while (fscanf(file, "%s", word) != EOF)
    {

        // Allocate memory for a new node
        node *new_node = malloc(sizeof(node));

        // Check if memory was successfully allocated
        if (new_node == NULL)
        {
            unload();
            return false;
        }

        // Copy the word into the node
        strcpy(new_node->word, word);
        hash_value = hash(word);
        new_node->next = hashtable[hash_value];
        hashtable[hash_value] = new_node;

        // Increment word_count
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

        node *cursor = hashtable[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }

    return true;
}
