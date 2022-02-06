// Create a Fibonacci series with Recursion based on input-given length

#include <stdio.h>

int fibo(int n);

int main(void)
{
    int number;
    // Ask an input to the user
    printf("Enter Fibonacci serie's length: ");
    scanf("%d", &number);
    
    // Print as many numbers as required by the user
    for(int i = 0; i < number; i++)
    {
        printf("%d ", fibo(i));
    }
    printf("\n");
}

int fibo(int n)
{
    // Recursion is not applicable for the first two numbers of the fibonacci series (n = 0, n = 1)
    if (n == 0 || n == 1)
    {
        return n;
    }
    // But here apply recursion
    else
    {
        return fibo(n - 1) + fibo(n - 2);
    }
}
