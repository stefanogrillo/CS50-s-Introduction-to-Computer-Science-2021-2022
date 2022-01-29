// Implements a dictionary's functionality

#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

// Create a counter for only-positive values   
unsigned int imported_words = 0;

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table (26^3)
const unsigned int N = 17576;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Find the Hash Value for Word
    int number = hash(word);
    // Go to that place in the Table
    node *cursor = table[number];

    // Loop the cursor till end of Linked List (traverse the LL)
    while (cursor != NULL)
    {
        // The function "strcasecmp" is case insensitive
        // There is no need for "tolower(word[i])" inside a "for (int i...)" loop
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        // Go to the next node
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number (this version is slow) (26^3 buckets needed)
//
//unsigned int hash(const char *word)
//{
//    unsigned int count = 0;
//    for (int i = 0; i < 3; i++)
//    {
//        int j = 0;
//        if (word[i] != 'a' + j)
//        {
//            j++;
//        }
//        if (word[i] == 'a' + i)
//        {
//            count += j*26^(2 - i);
//        }
//    }
//    return count;
//}

// Fast Hashing function retrieved from:
// https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/
//
//unsigned int hash(const char *word)
//{
//    unsigned int number = 0;
//    for (int i=0, n=strlen(word); i<n; i++)
//    {
//        number = (number << 2) ^ word[i];
//    }
//    return number % N;
//}

// My revisited version of an hash table
// TIME IN TOTAL : 0.12 (LALALAND.TXT)
//
unsigned int hash(const char *word)
{
    unsigned int count = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        count += tolower(word[i]);
    }
    count = count % N;
    return count;
}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Declare a temporary storage
    char buffer[LENGTH + 1];

    // Open the dictionary
    FILE *inp_dictionary = fopen(dictionary, "r");
    if (inp_dictionary == NULL)
    {
        printf("Could not load %s", dictionary);
    }

    // Read the dictionary
    // Function: fscanf (FILE to be read, length to be read (in this case, a string), where to store)
    // fscanf must be till the End Of File (EOF)
    while (fscanf(inp_dictionary, "%s", buffer) != EOF)
    {
        // Create a new node
        node *newnode = malloc(sizeof(node));
        if (newnode == NULL)
        {
            return false;
        }
        strcpy(newnode->word, buffer);
        newnode->next = NULL;
        int position = hash(newnode->word); // Save the position in the hash table

        if (table[position] == NULL)
        {
            table[position] = newnode;
        }
        else
        {
            // Set the node into the hash
            newnode->next = table[position];
            table[position] = newnode;
        }
        imported_words++;
    }
    fclose(inp_dictionary);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return imported_words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // For every bucket
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}
