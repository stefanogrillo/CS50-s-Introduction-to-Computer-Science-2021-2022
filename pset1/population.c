#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start_pop;
    do
    {
        start_pop = get_int("Start size: ");
    }
    while (start_pop < 9);

    // TODO: Prompt for end size
    int ending_pop;
    do
    {
        ending_pop = get_int("Ending size: ");
    }
    while (ending_pop < start_pop);
    
    // TODO: Calculate number of years until we reach threshold
    int y = 0;
    while (ending_pop > start_pop)
    {
        start_pop = start_pop + start_pop / 3 - start_pop / 4;
        y++;
    }
    
    // TODO: Print number of years
    printf("Years: %i \n", y);
}
