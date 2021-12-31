// Re-created the Coleman-Liau Index, a readability test to gauge the understandability of a text 

#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Prototypes
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Get the text from the user
    string text = get_string("Text: ");
    // To check: printf("%s\n", text);

    // Count the letters
    int letters = count_letters(text);
    // To check: printf("L: %i\n", letters);

    // Count the words
    int words = count_words(text);
    // To check: printf("W: %i\n", words);

    // Count the sentences
    int sentences = count_sentences(text);
    // To check: printf("S: %i\n", sentences);

    // Coleman-Liau: construct the pieces to be implemented into the formula
    float L = 100.0 * letters / words; // average letters per 100 words
    float S = 100.0 * sentences / words; // average words per 100 sentences
    float index = 0.0588 * L - 0.296 * S - 15.8; // formula
    float rounded = round(index);

    // Print the results, grouping grades under 1 && grades 16+ into into 2 special categories
    if (rounded > 16)
    {
        printf("Grade 16+\n");
    }
    else if (rounded < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %0.0f\n", rounded);
    }
}

// Functions
int count_letters(string text)
{
    int letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Consider only letters between A && Z, and between a && z, otherwise don't increase the variable
        if ((text[i] >= 'A' && text[i] <= 'Z') || (text[i] >= 'a' && text[i] <= 'z'))
        {
            letters ++;
        }
    }
    return letters;
}

int count_words(string text)
{
    int words = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Count the spaces to count the words
        if (text[i] == ' ')
        {
            words++;
        }
    }
    // Count 1 space more because the final dot has no space but still it's a word
    if (strlen(text) > 0)
    {
        words++;
    }
    return words;
}

int count_sentences(string text)
{
    int sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        // Count for the signals that a sentence is concluded 
        if ((text[i] == '.') || (text[i] == '?') || (text[i] == '!'))
        {
            sentences++;
        }
    }
    return sentences;
}
