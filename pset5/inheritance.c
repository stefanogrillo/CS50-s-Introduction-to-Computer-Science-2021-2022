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

// Create a new individual with `generations`
person *create_family(int generations)
{
    // Allocate memory for new person
    person *p = malloc(sizeof(person));
    if (p == NULL)
    {
        return NULL;
    }

    // If there are still generations left to be created
    if (generations > 1)
    {
        // Create two new parents for current person by recursively calling create_family
        person *parent0 = create_family(generations - 1);
        person *parent1 = create_family(generations - 1);

        // Set parent pointers for current person
        p->parents[0] = parent0;
        p->parents[1] = parent1;

        // Randomly assign current person's alleles based on the alleles of their parents
        p->alleles[0] = p->parents[0]->alleles[rand() % 2];
        p->alleles[1] = p->parents[1]->alleles[rand() % 2];
        // [rand() % 2] Means that you simply randomly choose one allele (a number) out of parent's two
    }

    // If there are no generations left to be created
    else
    {
        // Set parent pointers to NULL
        p->parents[0] = NULL;
        p->parents[1] = NULL;

        // Randomly assign alleles
        p->alleles[0] = random_allele();
        p->alleles[1] = random_allele();
    }

    // Return newly created person
    return p;
}
