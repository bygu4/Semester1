#include <stdio.h>
#include <stdlib.h>

float power(const int number, const int power)
{
    float poweredNumber = 1;
    float multiplier = number;
    if (power < 0)
    {
        multiplier = 1 / (float)number;
    }

    int absOfPower = abs(power);
    for (int i = 0; i < absOfPower; ++i)
    {
        poweredNumber *= multiplier;
    }
    return poweredNumber;
}

float quickPower(const int number, const int power)
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

    float numberToHalfThePower = quickPower(number, power / 2);
    if (power % 2 == 0)
    {
        return numberToHalfThePower * numberToHalfThePower;
    }
    return numberToHalfThePower * numberToHalfThePower * quickPower(number, power / abs(power));
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