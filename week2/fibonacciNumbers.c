#include <stdio.h>

int getFibonacciNumberByRecursion(int number)
{
    if (number <= 2)
    {
        return 1;
    }
    return getFibonacciNumberByRecursion(number - 1) + getFibonacciNumberByRecursion(number - 2);
}

int getFibonacciNumberByIteration(int number)
{
    int arrayOfSteps[3] = { 1, 1, 2 };
    int count = 0;
    while (number - count > 3)
    {
        arrayOfSteps[0] = arrayOfSteps[1];
        arrayOfSteps[1] = arrayOfSteps[2];
        arrayOfSteps[2] = arrayOfSteps[0] + arrayOfSteps[1];
        ++count;
    }
    return arrayOfSteps[number - count - 1];
}

int main()
{
    int inputNumber = 0;
    printf("Enter a number (step of Fibonacci sequence): ");
    scanf_s("%d", &inputNumber);
    if (inputNumber > 0)
    {
        int fibonacciNumber = getFibonacciNumberByIteration(inputNumber);
        printf("The %d number of Fibonacci sequence: %d", inputNumber, fibonacciNumber);
    }
    else
    {
        printf("Incorrect input");
    }
}