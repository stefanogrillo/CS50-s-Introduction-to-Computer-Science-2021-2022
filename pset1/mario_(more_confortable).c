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
}
