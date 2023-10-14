#include "test.h"
#include "binary.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

#define SIZE_OF_BINARY_REPRESENTATION sizeof(int) * 8

bool arraysAreEqual(const char* const array1, const char* const array2, const size_t sizeOfArray)
{
    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        if (array1[i] != array2[i])
        {
            return false;
        }
    }
    return true;
}

bool testForBinaryRepresentation(const int number, const char* const expectedRepresentation)
{
    const size_t size = SIZE_OF_BINARY_REPRESENTATION;
    char* representation = createBinaryRepresentation(number);
    if (representation == NULL)
    {
        return false;
    }
    bool equal = arraysAreEqual(representation, expectedRepresentation, size);
    free(representation);
    return equal;
}

bool allTestsForBinaryRepresentationArePassed(int* const errorCode)
{
    int number1 = 0;
    char expectedRepresentation1[SIZE_OF_BINARY_REPRESENTATION] = { 0 };
    bool testOneIsPassed = testForBinaryRepresentation(number1, expectedRepresentation1);
    if (!testOneIsPassed)
    {
        *errorCode = 1;
        return false;
    }

    int number2 = -0;
    char expectedRepresentation2[SIZE_OF_BINARY_REPRESENTATION] = { 0 };
    bool testTwoIsPassed = testForBinaryRepresentation(number2, expectedRepresentation2);
    if (!testTwoIsPassed)
    {
        *errorCode = 2;
        return false;
    }

    int number3 = INT_MIN / 2;
    char expectedRepresentation3[SIZE_OF_BINARY_REPRESENTATION] = { 1, 1 };
    bool testThreeIsPassed = testForBinaryRepresentation(number3, expectedRepresentation3);
    if (!testThreeIsPassed)
    {
        *errorCode = 3;
        return false;
    }

    int number4 = 80;
    char expectedRepresentation4[SIZE_OF_BINARY_REPRESENTATION] = { 0 };
    expectedRepresentation4[SIZE_OF_BINARY_REPRESENTATION - 5] = 1;
    expectedRepresentation4[SIZE_OF_BINARY_REPRESENTATION - 7] = 1;
    bool testFourIsPassed = testForBinaryRepresentation(number4, expectedRepresentation4);
    if (!testFourIsPassed)
    {
        *errorCode = 4;
        return false;
    }

    return true;
}

bool testForBinaryAddition(const int number1, const int number2, const char* const expectedSum)
{
    const size_t size = SIZE_OF_BINARY_REPRESENTATION;
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

bool allTestsForBinaryAdditionArePassed(int* const errorCode)
{
    int number1 = -555;
    int number2 = 555;
    char expectedSum1[SIZE_OF_BINARY_REPRESENTATION] = { 0 };
    bool testOneIsPassed = testForBinaryAddition(number1, number2, expectedSum1);
    if (!testOneIsPassed)
    {
        *errorCode = 1;
        return false;
    }

    number1 = INT_MIN / 2;
    number2 = INT_MIN / 2;
    char expectedSum2[SIZE_OF_BINARY_REPRESENTATION] = { 1 };
    bool testTwoIsPassed = testForBinaryAddition(number1, number2, expectedSum2);
    if (!testTwoIsPassed)
    {
        *errorCode = 2;
        return false;
    }

    number1 = 32;
    number2 = 16;
    char expectedSum3[SIZE_OF_BINARY_REPRESENTATION] = { 0 };
    expectedSum3[SIZE_OF_BINARY_REPRESENTATION - 5] = 1;
    expectedSum3[SIZE_OF_BINARY_REPRESENTATION - 6] = 1;
    bool testThreeIsPassed = testForBinaryAddition(number1, number2, expectedSum3);
    if (!testThreeIsPassed)
    {
        *errorCode = 3;
        return false;
    }

    number1 = 1100;
    number2 = -76;
    char expectedSum4[SIZE_OF_BINARY_REPRESENTATION] = { 0 };
    expectedSum4[SIZE_OF_BINARY_REPRESENTATION - 11] = 1;
    bool testFourIsPassed = testForBinaryAddition(number1, number2, expectedSum4);
    if (!testFourIsPassed)
    {
        *errorCode = 4;
        return false;
    }

    return true;
}

bool testForBinaryToDecimal(const int number)
{
    char* representation = createBinaryRepresentation(number);
    if (representation == NULL)
    {
        return false;
    }
    int decimal = binaryToDecimal(representation);
    free(representation);
    return decimal == number;
}

bool allTestsForBinaryToDecimalArePassed(int* const errorCode)
{
    bool testOneIsPassed = testForBinaryToDecimal(0);
    if (!testOneIsPassed)
    {
        *errorCode = 1;
        return false;
    }

    bool testTwoIsPassed = testForBinaryToDecimal(INT_MAX);
    if (!testTwoIsPassed)
    {
        *errorCode = 2;
        return false;
    }

    bool testThreeIsPassed = testForBinaryToDecimal(INT_MIN);

    if (!testThreeIsPassed)
    {
        *errorCode = 3;
        return false;
    }

    bool testFourIsPassed = testForBinaryToDecimal(-1234567);
    if (!testFourIsPassed)
    {
        *errorCode = 4;
        return false;
    }

    bool testFiveIsPassed = testForBinaryToDecimal(5555555);
    if (!testFiveIsPassed)
    {
        *errorCode = 5;
        return false;
    }

    return true;
}

bool test(void)
{
    int errorCode = 0;
    bool testOneIsPassed = allTestsForBinaryRepresentationArePassed(&errorCode);
    if (!testOneIsPassed)
    {
        printf("Test %d has failed in test for binaryRepresentation", errorCode);
        return false;
    }

    bool testTwoIsPassed = allTestsForBinaryAdditionArePassed(&errorCode);
    if (!testTwoIsPassed)
    {
        printf("Test %d has failed in test for binaryAddition", errorCode);
        return false;
    }

    bool testThreeIsPassed = allTestsForBinaryToDecimalArePassed(&errorCode);
    if (!testThreeIsPassed)
    {
        printf("Test %d has failed in test for binaryToDecimal", errorCode);
        return false;
    }

    return true;
}
