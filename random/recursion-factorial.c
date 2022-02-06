// Create a factorial function using Recursion (for both positive and negative values)

#include<stdio.h>


int factorialfunction(int n);

int main()
{
    int number;
  
    // Get user's input
    printf("Enter an integer: ");
    // Retrieve the input, store it in "number" 
    scanf("%d", &number);

    // Print the result
    printf("Factorial of %d is %d\n", number, factorialfunction(number));
    return 0;
}

int factorialfunction(int n)
{
    // If the number is positive
    if (n > 1)
    {
        return n * factorialfunction(n - 1);
    }
    // If the number is negative
    if (n < 0)
    {
        return n * factorialfunction(n + 1);
    }
    else
    {
        return 1;
    }
}
