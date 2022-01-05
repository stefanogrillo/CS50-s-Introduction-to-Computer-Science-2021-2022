// Given a key (a set of 26 non-repeating letters) this program aims to encrypt any message requested by the user

#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // There must be only two arguments
    if (argc == 2)
    {
        // Requisites for the Key (1: lenght = 26)
        if (strlen(argv[1]) == 26)
        {
            // Requisites for the Key: argv[1] must be alphabetical and non repetitive
            for (int i = 0, n = strlen(argv[1]); i < n; i++)
            {
                // Requisites for the Key (2: key must not contain numbers)
                if (isalpha(argv[1][i]) == false)
                {
                    printf("Key must only contain alphabetic characters.\n");
                    return 1;
                }
                // Requisites for the Key (3: key must not have repetitive elements) 
                // Check if subsequent characters are equal to the current one (if character at position i, then start from i + 1)
                for (int j = i + 1, m = strlen(argv[1]); j < m; j++)
                {
                    if (toupper(argv[1][i]) == toupper(argv[1][j]))
                    {
                        printf("Key must not contain repeated characters.\n");
                        return 1;
                    }
                }
            }
            // Get the text from the user
            string text = get_string("plaintext: ");
            printf("ciphertext: ");
            // Program
            for (int i = 0, n = strlen(text); i < n; i++)
            {
                // Lowercase letters must be encrypted into a new lowercase character 
                if (isalpha(text[i]) && islower(text[i]))
                {
                    printf("%c", tolower(argv[1][text[i] - 97]));
                }
                // Uppercase letters must be encrypted into a new uppercase character 
                else if (isalpha(text[i]) && isupper(text[i]))
                {
                    printf("%c", toupper(argv[1][text[i] - 65]));
                }
                // Maintain punctuations and numbers
                else
                {
                    printf("%c", text[i]);
                }
            }
            printf("\n");
            return 0;
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution KEY\n");
        return 1;
    }
}
