// Simulate genetic inheritance of blood type using malloc() and pointers

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define a data type: for each person, we need two parents and two alleles
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
}
person;

// We want 3 generations
const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

// Prototypes
person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed random number generator
    srand(time(0));

    // Create a new family with three generations
    person *p = create_family(GENERATIONS);

    // Print family tree of blood types
    print_family(p, 0);

    // Free memory
    free_family(p);
}
