// Implements a dictionary's functionality
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include "dictionary.h"
#include <strings.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 60;
// unsigned int num = 0;
unsigned int counter = 0;
// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // hash word to obtain an index
    int index = hash(word);

    //access linked list at that index in the hash table
    // traverse said linked list, looking for the word using strcasecmp
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        else
        {
            cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Source: djib2 by Dan Bernstein (http://www.cse.yorku.ca/~oz/hash.html)
    unsigned long hash = 5381;
    int c = *word;
    c = tolower(c);

    while (*word != 0)
    {
        hash = ((hash << 5) + hash) + c;
        c = *word++;
        c = tolower(c);
    }

    return hash % N;

}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    // open dictionary file
    // read strings from file one at a time
    // create a new node for each word
    // hash word to obtain a has value
    // insert node into hash table at that location

    // opens file, makes sure it isn't empty before proceeding
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    char buffer[LENGTH + 1];

    // loops through whole file, beginning to end, while passing through the buffer
    while ((fscanf(file, "%s", buffer)) != EOF)
    {
        // allocates enough memory for one node in linked list, makes sure it isn't empty
        node* n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }

        // copies file input from buffer into word partition of node
        strncpy(n->word, buffer, sizeof(buffer));

        // compute index of the word through a hash function
        int index = hash(n->word);

        // inserts node into hash table at the index location
        if (table[index] == NULL)
        {
            table[index] = n;
        }

        // else if a collision occurs, the node is inserted into the next space using linear probing
        else
        {
            n->next = table[index];
            table[index] = n;
        }

        // counts number of elements being scanned through; useful for size function
        counter++;

    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return counter;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
            //num++;
            //printf("things freed: %d\n", num);

        }
    }
    return true;
}
