// Program that asks voters to insert the name of their candidate, counts it (if existing), and prints the winner
// Under construction

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates (constant chosen a priori)
#define MAX 9

// Candidates have name and vote count (create a 
typedef struct
{
    string name;
    int votes;
}
candidate;
