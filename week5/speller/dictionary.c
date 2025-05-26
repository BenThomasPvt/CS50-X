#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 26; // Number of buckets in hash table

// Hash table
node *table[N];

// Hashes word to a number
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open the dictionary file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        return false; // Could not open file
    }

    char word[LENGTH + 1];
    while (fscanf(source, "%s", word) != EOF)
    {
        // Create a new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            fclose(source);
            unload();     // Free already allocated nodes
            return false; // Could not allocate memory
        }
        // Copy the word into the node
        strcpy(new_node->word, word);
        new_node->next = NULL;

        // Hash the word to get the index
        unsigned int index = hash(word);

        // Insert the new node into the hash table
        new_node->next = table[index];
        table[index] = new_node;
    }

    // Close the dictionary file
    fclose(source);
    return true;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Convert the word to lowercase
    char lower_word[LENGTH + 1];
    for (int i = 0; word[i] != '\0'; i++)
    {
        lower_word[i] = tolower(word[i]);
    }
    lower_word[strlen(word)] = '\0';

    // Hash the word to get the index
    unsigned int index = hash(lower_word);

    // Traverse the linked list at the hashed index
    node *cursor = table[index];
    while (cursor != NULL)
    {
        // Compare the word to the one in the node
        if (strcmp(cursor->word, lower_word) == 0)
        {
            return true; // Word found
        }
        cursor = cursor->next;
    }

    return false; // Word not found
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int count = 0;

    // Traverse the hash table
    for (unsigned int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            count++;
            cursor = cursor->next;
        }
    }

    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    bool success = true;

    // Traverse the hash table
    for (unsigned int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp); // Free each node
        }
        table[i] = NULL;
    }

    return success;
}
