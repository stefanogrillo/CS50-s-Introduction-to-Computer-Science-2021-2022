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
