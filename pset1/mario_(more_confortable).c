// Create a pyramid printing "#" in two separated triangles, like the pyramids with the hole in the game

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Ask for pyramid size
    int height;
    do
    {
        height = get_int("Height: ");
    }
    // Size must be between 1 and 8 included
    while (height < 1 || height > 8);
    
    for (int lenght = 0; lenght < height; lenght++)
    {
        for (int space = height - lenght - 1; space > 0; space--)
        {
            // Print " " from 7 to 0 times per row, one less space each new row (to move the "#" to the right)
            printf(" ");
        }

        for (int hash = 0; hash < lenght + 1; hash++)
        {
            // Print "#" from 1 to hash times, one more hash each new row (left triangle of the pyramid)
            printf("#");
        }

        // Add a separator between right-skewed pyramid and left skewed pyramid
        printf("  ");
        
        for (int hash = 0; hash < lenght + 1; hash++)
        {
            // Print "#" from 1 to hash times, one more hash each new row (same as rows 24 : 28)
            printf("#");
        }

        // Go to a new line after each loop is completed
        printf("\n");
     }
}
