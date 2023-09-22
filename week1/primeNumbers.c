#include <stdio.h>
#include <stdbool.h>

bool isPrime(int number)
{
    for (int i = 2; i * i <= number; ++i)
    {
        if (number % i == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int enteredNumber = 0;
    printf("Enter a positive number: ");
    scanf_s("%d", &enteredNumber);
    if (enteredNumber >= 0)
    {
        printf("Here is all the prime numbers not greater than yours: \n");
        for (int i = 2; i <= enteredNumber; ++i)
        {
            if (isPrime(i))
            {
                printf("%d\n", i);
            }
        }
        printf("Done");
    }
    else
    {
        printf("Incorrect input");
    }
}