#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

void printArray(const char* array, const int sizeOfArray)
{
    for (int i = 0; i < sizeOfArray; ++i)
    {
        printf("%d", array[i]);
    }
}

const int getSizeOfBinaryRepresentation(int number)
{
    int size = 1;
    while (abs(number) >= 2)
    {
        number /= 2;
        ++size;
    }
    return size;
}

int createBinaryRepresentation(char* binaryRepresentation, const int sizeOfBinaryRepresentation, const int number)
{
    if (binaryRepresentation == NULL)
    {
        return 1;
    }
    int bit = 1;
    for (int i = 0; i < sizeOfBinaryRepresentation; ++i)
    {
        binaryRepresentation[sizeOfBinaryRepresentation - i - 1] = number & bit ? 1 : 0;
        bit = bit << 1;
    }
    return 0;
}

int binaryAddition(const char* binaryRepresentation1, const char* binaryRepresentation2, char* sum, const int size)
{
    if (sum == NULL)
    {
        return 1;
    }
    char* transferBit = (char*)calloc(size + 1, sizeof(char));
    if (transferBit == NULL)
    {
        return 1;
    }

    for (int i = 0; i < size; ++i)
    {
        int sumOfDigits = binaryRepresentation1[size - i - 1] + binaryRepresentation2[size - i - 1] + transferBit[size - i];
        sum[size - i - 1] = sumOfDigits % 2;
        transferBit[size - i - 1] = sumOfDigits / 2;
    }
    free(transferBit);
    return 0;
}

int binaryToDecimal(const char* binaryRepresentation, const int sizeOfBinaryRepresentation)
{
    int decimal = 0;
    for (int i = 0; i < sizeOfBinaryRepresentation; ++i)
    {
        decimal += binaryRepresentation[i] << (sizeOfBinaryRepresentation - i - 1);
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

bool testOneIsPassed()
{
    int size = getSizeOfBinaryRepresentation(511);
    return size == 9;
}

bool testTwoIsPassed()
{
    int size = getSizeOfBinaryRepresentation(0);
    return size == 1;
}

bool testThreeIsPassed()
{
    int number = 255;
    char binary[8] = { 0 };
    int errorCode = createBinaryRepresentation(binary, 8, number);
    if (errorCode != 0)
    {
        return false;
    }
    char expectedBinary[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };
    return arraysAreEqual(binary, expectedBinary, 8);
}

bool testFourIsPassed()
{
    int number = -9;
    char binary[4] = { 0 };
    int errorCode = createBinaryRepresentation(binary, 4, number);
    if (errorCode != 0)
    {
        return false;
    }
    char expectedBinary[4] = { 0, 1, 1, 1 };
    return arraysAreEqual(binary, expectedBinary, 4);
}

bool testFiveIsPassed()
{
    int number = -0;
    char binary[1] = { 0 };
    int errorCode = createBinaryRepresentation(binary, 1, number);
    if (errorCode != 0)
    {
        return false;
    }
    char expectedBinary[1] = { 0 };
    return arraysAreEqual(binary, expectedBinary, 1);
}

bool testSixIsPassed()
{
    int number1 = -100;
    int number2 = 100;
    char binary1[7] = { 0 };
    char binary2[7] = { 0 };
    int errorCode = createBinaryRepresentation(binary1, 7, number1);
    if (errorCode != 0)
    {
        return false;
    }
    errorCode = createBinaryRepresentation(binary2, 7, number2);
    if (errorCode != 0)
    {
        return false;
    }
    char sum[7] = { 0 };
    errorCode = binaryAddition(binary1, binary2, sum, 7);
    if (errorCode != 0)
    {
        return false;
    }
    char expectedArray[7] = { 0 };
    return arraysAreEqual(sum, expectedArray, 7);
}

bool testSevenIsPassed()
{
    int number1 = 8;
    int number2 = 5;
    char binary1[4] = { 0 };
    char binary2[4] = { 0 };
    int errorCode = createBinaryRepresentation(binary1, 4, number1);
    if (errorCode != 0)
    {
        return false;
    }
    errorCode = createBinaryRepresentation(binary2, 4, number2);
    if (errorCode != 0)
    {
        return false;
    }
    char sum[4] = { 0 };
    errorCode = binaryAddition(binary1, binary2, sum, 4);
    if (errorCode != 0)
    {
        return false;
    }
    char expectedArray[4] = { 1, 1, 0, 1 };
    return arraysAreEqual(sum, expectedArray, 4);
}

bool testEightIsPassed()
{
    char binary[6] = { 1, 1, 0, 0, 1, 1 };
    int decimal = binaryToDecimal(binary, 6);
    return decimal == 51;
}

bool testNineIsPassed()
{
    char binary[1] = { 0 };
    int decimal = binaryToDecimal(binary, 1);
    return decimal == 0;
}

bool allTestsArePassed()
{
    return testOneIsPassed() && testTwoIsPassed() && testThreeIsPassed() && testFourIsPassed()
        && testFiveIsPassed() && testSixIsPassed() && testSevenIsPassed() && testEightIsPassed()
        && testNineIsPassed();
}

int main()
{
    if (!allTestsArePassed())
    {
        printf("\nAn error occured");
        return -1;
    }

    setlocale(LC_ALL, "rus");
    int number1 = 0;
    printf("Введите первое число: ");
    scanf_s("%d", &number1);
    const int size1 = getSizeOfBinaryRepresentation(number1);

    int number2 = 0;
    printf("Введите второе число: ");
    scanf_s("%d", &number2);
    const int size2 = getSizeOfBinaryRepresentation(number2);

    const int sizeOfBinaryRepresentation = max(size1, size2);
    char* binaryRepresentation1 = (char*)calloc(sizeOfBinaryRepresentation, sizeof(char));
    int errorCode = createBinaryRepresentation(binaryRepresentation1, sizeOfBinaryRepresentation, number1);
    if (errorCode != 0)
    {
        printf("\nAn error occured");
        return -1;
    }

    char* binaryRepresentation2 = (char*)calloc(sizeOfBinaryRepresentation, sizeof(char));
    errorCode = createBinaryRepresentation(binaryRepresentation2, sizeOfBinaryRepresentation, number2);
    if (errorCode != 0)
    {
        printf("\nAn error occured");
        return -1;
    }

    printf("\nПервое число в двоичном виде: ");
    printArray(binaryRepresentation1, sizeOfBinaryRepresentation);
    printf("\nВторое число в двоичном виде: ");
    printArray(binaryRepresentation2, sizeOfBinaryRepresentation);

    char* binarySum = (char*)calloc(sizeOfBinaryRepresentation, sizeof(char));
    errorCode = binaryAddition(binaryRepresentation1, binaryRepresentation2, binarySum, sizeOfBinaryRepresentation);
    free(binaryRepresentation1);
    free(binaryRepresentation2);
    if (errorCode != 0)
    {
        printf("\nAn error occured");
        return -1;
    }
    printf("\n\nСумма двоичных представлений: ");
    printArray(binarySum, sizeOfBinaryRepresentation);

    int decimalSum = binaryToDecimal(binarySum, sizeOfBinaryRepresentation);
    free(binarySum);
    printf("\nСумма в десятичном виде: %d", decimalSum);
}