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
