#include <stdio.h>
#include <stdlib.h>

int partialQuotient(int number1, int number2)
{
    int quotient = 0;
    int remainder = number1 - number2 * quotient;
    while (remainder < 0 || remainder >= abs(number2))
    {
        if (number1 * number2 > 0)
        {
            ++quotient;
        }
        else
        {
            --quotient;
        }
        remainder = number1 - number2 * quotient;
    }
    return quotient;
}

int main()
{
    int number1 = 0;
    int number2 = 0;
    printf("Enter number a: ");
    scanf_s("%d", &number1);
    printf("Enter number b: ");
    scanf_s("%d", &number2);

    if (number2 == 0)
    {
        printf("Incorrect input");
    }
    else
    {
        int quotient = partialQuotient(number1, number2);
        printf("Partial quotient of a/b: %d", quotient);
    }
}