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

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates: check the number, use argv[i + 1] (because the first i is ./plurality) to set candidates[i] 
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Check if voted names == candidates' names; if so, increase their votes
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // New variable to keep track of the candidates[i] with most votes
    int greatest = 0;
    // Check the candidate with most votes and keep track
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        if (candidates[i].votes > greatest)
        {
            greatest = candidates[i].votes;
        }
    }

    // Among all the candidates, print the one(s) with most votes (ones if there's a tie)
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        if (greatest == candidates[i].votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}
