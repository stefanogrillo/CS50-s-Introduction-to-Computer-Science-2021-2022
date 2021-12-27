#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // Ask for input
    float owed;
    do
    {
        owed = get_float("Cash owed: ");
        owed = roundf(owed * 100) / 100;
    }
    while (owed < 0.009);
    // To control: printf("%.2f\n", owed);
      
    int coins = 0;

    // How many .25 coins?
    while (owed >= 0.249)
    {
        owed -= 0.25;
        coins++;
    }

    // How many .10 coins?
    while (owed >= 0.099)
    {
        owed -= 0.10;
        coins++;
    }

}
