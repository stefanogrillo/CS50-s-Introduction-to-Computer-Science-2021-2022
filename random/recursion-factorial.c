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
    // If the number is greater than 1 (not included)
    if (n > 1)
    {
        return n * factorialfunction(n - 1);
    }
    // If the number is smaller than 1 (not included)
    if (n < -1)
    {
        return n * factorialfunction(n + 1);
    }
    // In case the number is -1, 0, or 1
    else
    {
        return 1;
    }
}
