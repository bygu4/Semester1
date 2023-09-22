#include <stdio.h>
#include <stdlib.h>

float power(int number, int power)
{
    float poweredNumber = 1;
    for (int i = 0; i < abs(power); ++i)
    {
        if (power > 0)
        {
            poweredNumber *= number;
        }
        else
        {
            poweredNumber /= number;
        }
    }
    return poweredNumber;
}

float quickPower(int number, int power)
{
    if (power == 0)
    {
        return 1;
    }
    if (power == 1)
    {
        return (float)number;
    }
    if (power == -1)
    {
        return 1 / (float)number;
    }
    if (power % 2 == 0)
    {
        return quickPower(number, power / 2) * quickPower(number, power / 2);
    }
    return quickPower(number, power / 2) * quickPower(number, power - power / 2);
}

int main()
{
    int inputNumber = 0;
    printf("Enter a number: ");
    scanf_s("%d", &inputNumber);
    int powerOfNumber = 0;
    printf("Enter a power of the number: ");
    scanf_s("%d", &powerOfNumber);

    float poweredNumber = quickPower(inputNumber, powerOfNumber);
    printf("%d to the power of %d: %g", inputNumber, powerOfNumber, poweredNumber);
}