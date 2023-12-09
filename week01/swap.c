#include <stdio.h>

int main()
{
    int number1 = 0;
    int number2 = 0;
    printf("Enter number a: ");
    scanf_s("%d", &number1);
    printf("Enter number b: ");
    scanf_s("%d", &number2);

    printf("Swapping...\n");
    number1 = number1 + number2;
    number2 = number1 - number2;
    number1 = number1 - number2;

    printf("a: %d\n", number1);
    printf("b: %d", number2);
}