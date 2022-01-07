// Program that asks voters to insert the name of their candidate, counts it (if existing), and prints the winner
// Under construction

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates (constant chosen a priori)
#define MAX 9

// Candidates have name and vote count (create a new data type saving both name and votes)
typedef struct
{
    string name;
    int votes;
}
candidate;

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);
