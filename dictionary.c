// Implements a dictionary's functionality
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include <stdlib.h>

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Words count
int wordCount = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int bucket = hash(word);

    node *headPtr = NULL;
    headPtr = table[bucket];

    while (headPtr != NULL)
    {
        if (strcasecmp(word, headPtr->word) == 0)
        {
            return true;
        }

        else
        {
            headPtr = headPtr->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // Define hashValue as unsigned long to avoid negative integers
    unsigned long hashValue = 0;
    for (int i = 0; word[i] != '\0'; i++)
    {
        // Hashvalue will always change within the loop
        // Multiply it by a prime number and add it to the ASCII subtraction
        hashValue = (hashValue * 31) + (toupper(word[i]) - 'A');
    }

    return hashValue % N;
}

void insertHash(int bucket, node *n)
{
    // If ptr table[bucket] points as nothing, insert new node and point at it
    if (table[bucket] == NULL)
    {
        table[bucket] = n;
        n->next = NULL;
    }
    // Else make new node pointing at chain and link ptr head (table[bucket]) to it
    else
    {
        n->next = table[bucket];
        table[bucket] = n;
    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
        return false;

    // Scan and hash each word
    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        int hashValue = hash(word);
        // Allocate new memory for node, copy word in it and add it to the hash table
        node *n = malloc(sizeof(node));
        strcpy(n->word, word);
        insertHash(hashValue, n);
        wordCount++;
        size();
    }
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *headPtr = table[i];

        while (headPtr != NULL)
        {
            node *nextPointer = headPtr->next;
            free(headPtr);
            headPtr = nextPointer;
        }
    }
    return true;
}
