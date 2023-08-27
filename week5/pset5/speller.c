// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 1e5;
int word_cnt = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Prepare a mirrored string by converting the original string to lowercase
    int word_length = strlen(word);
    char word_mirror[word_length + 1];
    strcpy(word_mirror, word);
    for (int i = 0; i < word_length; i++)
    {
        word_mirror[i] = tolower(word_mirror[i]);
    }

    // Calculate the index hash bucket for the string using a hash function
    int idx = hash(word_mirror);

    // Traverse the hash bucket, comparing words case-insensitively
    node *bucket = table[idx];
    while (bucket)
    {
        if (strcasecmp(bucket->word, word_mirror) == 0)
        {
            return true;
        }
        else
        {
            bucket = bucket->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Improve this hash function
    unsigned int idx = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        idx = (idx * 31 + word[i]) % N;
    }
    return idx;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file and peform validation
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Use fscanf loop to read words from the file utill the end
    char buffer[LENGTH + 1];
    while (fscanf(file, "%s", buffer) != EOF)
    {
        // Create a new node and store the currently read word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            unload();
            return false;
        }

        strcpy(new_node->word, buffer);

        // Calculate the word's hash bucket and insert the word using a head insertion approach
        int idx = hash(buffer);
        node *bucket = table[idx];

        new_node->next = bucket;
        table[idx] = new_node;
        word_cnt++;

        memset(buffer, 0, sizeof(buffer));
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_cnt;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *head = table[i];
        node *cursor = head;
        node *tmp = head;

        while (cursor)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
