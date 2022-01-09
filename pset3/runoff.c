// Similarly to plurality, we want to find the winner of the elections; however, people can set preferences:
// So if their main choice is unavailable because the candidate has been eliminated, their second choice is counted 

#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes (here is the voter)
    for (int i = 0; i < voter_count; i++)
    {
        // Query for each rank (here are his/her preferences)
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }
        printf("\n");
    }
    
    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);
        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Check if voted names == candidates' names; if so, increase their votes
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            // Add the candidate's number/code to the voter's ranking (in the preference array)
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Update each voters' vote to candidates that are still in the race
    for (int i = 0, n = voter_count; i < n; i++)
    {
        for (int j = 0, m = candidate_count; j < m; j++)
        {
            if (candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // For each candidate not eliminated
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        // If the candidate has more than 50% of votes
        if (candidates[i].votes > voter_count / 2)
        {
            // Declare him/her winner
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    // Otherwise eliminate a candidate, recount votes, and retry
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Set the highest possible amount of votes for the current situation
    int min = voter_count;
    // Check which candidate is not eliminated && has fewer votes
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        if ((candidates[i].eliminated == false) && (candidates[i].votes < min))
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        // If all remaining candidates have votes different from min then it's not a tie
        if ((candidates[i].eliminated == false) && (candidates[i].votes != min))
        {
            return false;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Find the candidate with the smallest amount of votes and eliminate it (with the boolean value)
    for (int i = 0, n = candidate_count; i < n; i++)
    {
        if ((candidates[i].eliminated == false) && (candidates[i].votes == min))
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
