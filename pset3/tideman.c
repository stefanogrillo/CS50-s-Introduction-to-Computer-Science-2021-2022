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
    // Now populate it with names in the array previously created
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

        // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference (j is not needed because we are inside the candidate's loop)
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        
        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // For every candidate
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        // If the voted candidate exists
        if (strcmp(candidates[i], name) == 0)
        {
            // Save the preference in an array (where the ranked name are specific for the candidate considered)
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks (we're still inside the single voter's loop)
void record_preferences(int ranks[])
{
    // For every candidate
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        // (Against) every candidate
        for (int j = i + 1, m = candidate_count; j < m; j++)
        {
            // Keep track of how many voters prefer candidate i to candidate j
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // For each candidate
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        // Against each other candidate (excluded him/her-self)
        for (int j = i + 1; j < n; j++)
        {
            // Populate the array of candidates (pair)
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // A simple sorting algorithm is Bubble Sort
    // Create a temporary value to account for the position in the sorting algorithm
    pair temporary_val;
    // Check for every pair
    for (int i = 0, n = pair_count; i < n; i++)
    {
        // Against every other pair except itself
        for (int j = i + 1; j < n; j++)
        {
            // Find the greatest difference between winners and losers, and swap it in a decreasing order
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                // The swap: put pair[i] in a temporary value, move pair[j] to (old) pair[i],
                // move the temporary value to pair[j]
                temporary_val = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temporary_val;
            }
        }
    }
    return;
}

// Check for the creation of cycles
bool control_cycle(int winner, int loser)
{
    // If there's a cycle (loser/end gets back to winner/start) return true
    if (locked[loser][winner] == true)
    {
        return true;
    }
    // Recursive function (set the loser as the winner for next pair, reiterate for all candidates)
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        if (locked[i][winner] == true)
        {
            return control_cycle(i, loser);
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0, n = pair_count; i < n; i++)
    {
        // If there's no cycle, the pair can be locked
        if (!control_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // Winner has no arrows pointing at it (so has only "false")
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        int count_false = 0;
        for (int j = 0; j < n; j++)
        {
            count_false++;
            if (count_false == candidate_count)
            {
                printf("%s\n", candidates[i]);
            }
        }

    }
    return;
}
