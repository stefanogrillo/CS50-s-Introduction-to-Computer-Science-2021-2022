// Encryption of a message rotating the characters by a value key given by the sender

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
        // argv[1] must be numeric
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            // If there are non-numeric elements inside argv[1] return error
            if (isdigit(argv[1][i]) == false)
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        // Use the numeric argument of argv as a key to encrypt (from string to integer)
        int key = atoi(argv[1]);
        // Ask for the text to be encrypted and print encryption
        string text = get_string("plaintext: ");
        printf("ciphertext: ");

        // Read and encrypt the text
        for (int i = 0, n = strlen(text); i < n; i++)
        {
            // Uppercase characters
            if (text[i] >= 'A' && text[i] <= 'Z')
            {
                printf("%c", (((text[i] - 'A' + key) % 26) + 'A'));
            }
            // Lowercase characters
            else if (text[i] >= 'a' && text[i] <= 'z')
            {
                printf("%c", (((text[i] - 'a' + key) % 26) + 'a'));
            }
            else
            {
                printf("%c", text[i]);
            }
        }
        printf("\n");
        return 0;
    }
    else if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}
