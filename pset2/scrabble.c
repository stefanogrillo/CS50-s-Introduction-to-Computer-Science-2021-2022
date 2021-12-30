// Instead of using ASCII (as suggested) I decided to consider a string of letters where to find the position of the single character
// I then used the position to find the relative score, then I summed the scores

#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet & alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int ALPHA[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie!\n");
    }
    else
    {
        printf("Player 2 wins!\n");
    }
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    int score = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        // Uppercase
        word[i] = toupper(word[i]);

        // What's the position of the letter? Use the position to find the relative value in POINTS. Sum POINTS for each string
        for (int e = 0; ALPHA[e]; e++)
        {
            if (word[i] == ALPHA[e])
            {
                score = POINTS[e] + score;
            }
        }
    }
    return score;
}
