//We have a population of n llamas. Each year, n / 3 new llamas are born, and n / 4 llamas pass away. How many years are needed to reach a population of m llamas?

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Ask the user for the initial population (that must be above 9)
    int start_pop;
    do
    {
        start_pop = get_int("Start size: ");
    }
    while (start_pop < 9);

    // TODO: Ask for the ending population (in this case, higher than initial pop)
    int ending_pop;
    do
    {
        ending_pop = get_int("Ending size: ");
    }
    while (ending_pop < start_pop);
    
    // TODO: Calculate number of years until we reach objective
    int y = 0;
    while (ending_pop > start_pop)
    {
        start_pop = start_pop + start_pop / 3 - start_pop / 4;
        y++;
    }
    
    // TODO: Print number of years
    printf("Years: %i \n", y);
}
