#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

#define SIZE_OF_BINARY_REPRESENTATION sizeof(int) * 8

void printArray(const char* array, const int sizeOfArray)
{
    for (int i = 0; i < sizeOfArray; ++i)
    {
        printf("%d", array[i]);
    }
}

char* createBinaryRepresentation(const int number)
{
    char* binaryRepresentation = (char*)malloc(SIZE_OF_BINARY_REPRESENTATION);
    if (binaryRepresentation == NULL)
    {
        return NULL;
    }
    int bit = 1;
    for (int i = 0; i < SIZE_OF_BINARY_REPRESENTATION; ++i)
    {
        binaryRepresentation[SIZE_OF_BINARY_REPRESENTATION - i - 1] = number & bit ? 1 : 0;
        bit = bit << 1;
    }
    return binaryRepresentation;
}

char* binaryAddition(const char* binaryRepresentation1, const char* binaryRepresentation2)
{
    int size = SIZE_OF_BINARY_REPRESENTATION;
    char* sum = (char*)malloc(size);
    char* transferBit = (char*)calloc(size + 1, sizeof(char));
    if (sum == NULL || transferBit == NULL)
    {
        free(sum);
        free(transferBit);
        return NULL;
    }

    for (int i = 0; i < size; ++i)
    {
        int sumOfDigits = binaryRepresentation1[size - i - 1] + binaryRepresentation2[size - i - 1] + transferBit[size - i];
        sum[size - i - 1] = sumOfDigits % 2;
        transferBit[size - i - 1] = sumOfDigits / 2;
    }
    free(transferBit);
    return sum;
}

int binaryToDecimal(const char* binaryRepresentation)
{
    int decimal = 0;
    if (binaryRepresentation[0] == 1)
    {
        decimal = pow(-2, SIZE_OF_BINARY_REPRESENTATION - 1);
    }
    for (int i = 0; i < SIZE_OF_BINARY_REPRESENTATION; ++i)
    {
        decimal += binaryRepresentation[i] << (SIZE_OF_BINARY_REPRESENTATION - i - 1);
    }
    return decimal;
}

bool arraysAreEqual(const char* array1, const char* array2, const int sizeOfArray)
{
    for (int i = 0; i < sizeOfArray; ++i)
    {
        if (array1[i] != array2[i])
        {
            return false;
        }
    }
    return true;
}

bool testForBinaryRepresentation(const int number, const char* expectedRepresentation)
{
    int size = SIZE_OF_BINARY_REPRESENTATION;
    char* representation = createBinaryRepresentation(number);
    if (representation == NULL)
    {
        return false;
    }
    bool equal = arraysAreEqual(representation, expectedRepresentation, size);
    free(representation);
    return equal;
}

bool allTestsForBinaryRepresentationArePassed()
{
    int number1 = 0;
    char expectedRepresentation1[SIZE_OF_BINARY_REPRESENTATION] = { 0 };
    bool testOneIsPassed = testForBinaryRepresentation(number1, expectedRepresentation1);

    int number2 = -0;
    char expectedRepresentation2[SIZE_OF_BINARY_REPRESENTATION] = { 0 };
    bool testTwoIsPassed = testForBinaryRepresentation(number2, expectedRepresentation2);

    int number3 = -1073741824;
    char expectedRepresentation3[SIZE_OF_BINARY_REPRESENTATION] = { 1, 1 };
    bool testThreeIsPassed = testForBinaryRepresentation(number3, expectedRepresentation3);

    int number4 = 16;
    char expectedRepresentation4[SIZE_OF_BINARY_REPRESENTATION] = { 0 };
    expectedRepresentation4[SIZE_OF_BINARY_REPRESENTATION - 5] = 1;
    bool testFourIsPassed = testForBinaryRepresentation(number4, expectedRepresentation4);

    return testOneIsPassed && testTwoIsPassed && testThreeIsPassed && testFourIsPassed;
}

bool testForBinaryAddition(const int number1, const int number2, const char* expectedSum)
{
    int size = SIZE_OF_BINARY_REPRESENTATION;
    char* representation1 = createBinaryRepresentation(number1);
    char* representation2 = createBinaryRepresentation(number2);
    if (representation1 == NULL || representation2 == NULL)
    {
        free(representation1);
        free(representation2);
        return false;
    }
    char* sum = binaryAddition(representation1, representation2);
    free(representation1);
    free(representation2);
    if (sum == NULL)
    {
        return false;
    }
    bool equal = arraysAreEqual(sum, expectedSum, size);
    free(sum);
    return equal;
}

bool allTestsForBinaryAdditionArePassed()
{
    int number1 = -555;
    int number2 = 555;
    char expectedSum1[SIZE_OF_BINARY_REPRESENTATION] = { 0 };
    bool testOneIsPassed = testForBinaryAddition(number1, number2, expectedSum1);

    number1 = 1073741824;
    number2 = 1073741824;
    char expectedSum2[SIZE_OF_BINARY_REPRESENTATION] = { 1 };
    bool testTwoIsPassed = testForBinaryAddition(number1, number2, expectedSum2);

    number1 = 32;
    number2 = 16;
    char expectedSum3[SIZE_OF_BINARY_REPRESENTATION] = { 0 };
    expectedSum3[SIZE_OF_BINARY_REPRESENTATION - 5] = 1;
    expectedSum3[SIZE_OF_BINARY_REPRESENTATION - 6] = 1;
    bool testThreeIsPassed = testForBinaryAddition(number1, number2, expectedSum3);

    number1 = 1100;
    number2 = -76;
    char expectedSum4[SIZE_OF_BINARY_REPRESENTATION] = { 0 };
    expectedSum4[SIZE_OF_BINARY_REPRESENTATION - 11] = 1;
    bool testFourIsPassed = testForBinaryAddition(number1, number2, expectedSum4);

    return testOneIsPassed && testTwoIsPassed && testThreeIsPassed && testFourIsPassed;
}

bool testForBinaryToDecimal(const int number, const int expectedDecimal)
{
    char* representation = createBinaryRepresentation(number);
    if (representation == NULL)
    {
        return false;
    }
    int decimal = binaryToDecimal(representation);
    free(representation);
    return decimal == expectedDecimal;
}

bool allTestsForBinaryToDecimalArePassed()
{
    bool testOneIsPassed = testForBinaryToDecimal(-0, 0);
    bool testTwoIsPassed = testForBinaryToDecimal(pow(2, 31), -pow(2, 31));
    bool testThreeIsPassed = testForBinaryToDecimal(pow(2, 31) - 1, pow(2, 31) - 1);
    bool testFourIsPassed = testForBinaryToDecimal(-1234567, -1234567);
    bool testFiveIsPassed = testForBinaryToDecimal(5555555, 5555555);

    return testOneIsPassed && testTwoIsPassed && testThreeIsPassed && testFourIsPassed && testFiveIsPassed;
}

bool allTestsArePassed()
{
    return allTestsForBinaryRepresentationArePassed() && allTestsForBinaryAdditionArePassed()
        && allTestsForBinaryToDecimalArePassed();
}

int main()
{
    setlocale(LC_ALL, "rus");
    if (!allTestsArePassed())
    {
        printf("Возникла ошибка :(");
        return -1;
    }

    int number1 = 0;
    printf("Введите первое число: ");
    scanf_s("%d", &number1);
    char* binaryRepresentation1 = createBinaryRepresentation(number1);
    if (binaryRepresentation1 == NULL)
    {
        printf("\nВозникла ошибка :(");
        return -1;
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
        return -1;
    }
    printf("Второе число в двоичном виде: ");
    printArray(binaryRepresentation2, SIZE_OF_BINARY_REPRESENTATION);

    char* binarySum = binaryAddition(binaryRepresentation1, binaryRepresentation2);
    free(binaryRepresentation1);
    free(binaryRepresentation2);
    if (binarySum == NULL)
    {
        printf("\nВозникла ошибка :(");
        return -1;
    }
    printf("\n\nСумма двоичных представлений: ");
    printArray(binarySum, SIZE_OF_BINARY_REPRESENTATION);

    int decimalSum = binaryToDecimal(binarySum);
    free(binarySum);
    printf("\nСумма в десятичном виде: %d", decimalSum);
}