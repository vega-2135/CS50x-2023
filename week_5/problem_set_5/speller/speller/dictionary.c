// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of words in the dictionary
unsigned int word_count;

// TODO: Choose number of buckets in hash table
const unsigned int N = 65;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Check for apostrofhes
    int bucket_index = hash(word);
    node *n = table[bucket_index];
    while (n != NULL)
    {
        if (strcasecmp(n->word, word) == 0)
        {
            return true;
        }
        n = n->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    long long int sum = 0;
    // TODO: Improve this hash function
    for (int i = 0; i < strlen(word); i++)
    {
        sum += toupper(word[i]);
    }
    return sum % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        perror("Error opening file!");
        return false;
    }

    // Read all strings from file
    char word[LENGTH + 1];

    while (fscanf(dict, "%s", word) != EOF)
    {

        // Create a new node per word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            perror("not enough memory to allocate node");
            return false;
        }

        // Copy the string from word to node's word member
        strcpy(new_node->word, word);

        // Prepend the new node to the beginning of the linked list
        int index = hash(word);
        node *prev_head = table[index];
        new_node->next = prev_head;

        // Update the table entry with the address of the new word (since it's now the new head)
        table[index] = new_node;

        word_count += 1;
    }

    // Close file
    if (fclose(dict) != 0)
    {
        perror("could not close file");
        return false;
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *curr = table[i];
        while (curr != NULL)
        {
            node *temp = curr->next;
            free(curr);
            curr = temp;
        }
    }
    return true;
}