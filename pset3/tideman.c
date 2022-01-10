// Program to create a Tideman voting method (AKA “ranked pairs”): a ranked-choice voting method aiming to produce the
// Condorcet winner (the person who would win a two-candidate election against each of the other candidates in a plurality vote)

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer candidate i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j (true means that an edge starts from i, going to j)
// Adjacency matrix
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates (first check the number of candidates)
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    // Now populate it with names in a new variable
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }
