#include "binary.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

#define SIZE_OF_BINARY_REPRESENTATION sizeof(int) * 8
#define TEST_FAILED -1
#define BAD_ALLOCATION 1

void printArray(const char* const array, const size_t sizeOfArray)
{
    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        printf("%d", array[i]);
    }
}

int main(void)
{
    setlocale(LC_ALL, "rus");
    const bool allTestsArePassed = test();
    if (!allTestsArePassed)
    {
        return TEST_FAILED;
    }

    int number1 = 0;
    printf("Введите первое число: ");
    scanf_s("%d", &number1);
    char* binaryRepresentation1 = createBinaryRepresentation(number1);
    if (binaryRepresentation1 == NULL)
    {
        printf("\nВозникла ошибка :(");
        return BAD_ALLOCATION;
    }
    printf("Первое число в двоичном виде: ");
    printArray(binaryRepresentation1, SIZE_OF_BINARY_REPRESENTATION);

    int number2 = 0;
    printf("\nВведите второе число: ");
    scanf_s("%d", &number2);
    char* binaryRepresentation2 = createBinaryRepresentation(number2);
    if (binaryRepresentation2 == NULL)
    {
        printf("\nВозникла ошибка :(");
        free(binaryRepresentation1);
        return BAD_ALLOCATION;
    }
    printf("Второе число в двоичном виде: ");
    printArray(binaryRepresentation2, SIZE_OF_BINARY_REPRESENTATION);

    char* binarySum = binaryAddition(binaryRepresentation1, binaryRepresentation2);
    free(binaryRepresentation1);
    free(binaryRepresentation2);
    if (binarySum == NULL)
    {
        printf("\nВозникла ошибка :(");
        return BAD_ALLOCATION;
    }
    printf("\n\nСумма двоичных представлений: ");
    printArray(binarySum, SIZE_OF_BINARY_REPRESENTATION);

    int decimalSum = binaryToDecimal(binarySum);
    free(binarySum);
    printf("\nСумма в десятичном виде: %d\n", decimalSum);
}
