#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define NUMBER_OF_BITS sizeof(unsigned int) * 8

enum errorCodes {
    testFailed = -1,
    success = 0,
    badAllocation = 1
};

static int compare(const bool* const bits1, const bool* const bits2)
{
    for (size_t i = 0; i < NUMBER_OF_BITS; ++i)
    {
        if (bits1[i] != bits2[i])
        {
            return bits1[i] ? -1 : 1;
        }
    }
    return 0;
}

static bool* convertToBinary(const unsigned int number)
{
    bool* bits = (bool*)malloc(NUMBER_OF_BITS);
    if (bits == NULL)
    {
        return NULL;
    }
    unsigned int bit = 1;
    for (size_t i = 0; i < NUMBER_OF_BITS; ++i)
    {
        bits[NUMBER_OF_BITS - i - 1] = number & bit ? true : false;
        bit = bit << 1;
    }
    return bits;
}

static void printFailedTest(const size_t numberOfTest)
{
    printf("Test %zu has failed\n", numberOfTest);
}

static bool testCase(const unsigned int number1, const unsigned int number2, 
    const int expectedOutput, const size_t numberOfTest)
{
    bool* bits1 = convertToBinary(number1);
    bool* bits2 = convertToBinary(number2);
    bool testIsPassed = bits1 != NULL && bits2 != NULL && compare(bits1, bits2) == expectedOutput;
    free(bits1);
    free(bits2);
    if (!testIsPassed)
    {
        printFailedTest(numberOfTest);
    }
    return testIsPassed;
}

static bool testIsPassed(void)
{
    return testCase(0, 0, 0, 1) &&
        testCase(1234, 123, -1, 2) &&
        testCase(55555, 55556, 1, 3) &&
        testCase(UINT_MAX - 1, UINT_MAX, 1, 4);
}

static bool stringsAreEqual(const char* const string1, const char* const string2)
{
    for (size_t i = 0; string1[i] != '\0' || string2[i] != '\0'; ++i)
    {
        if (string1[i] != string2[i])
        {
            return false;
        }
    }
    return true;
}

int main(const size_t argc, const char* const argv[])
{
    if (!testIsPassed())
    {
        return testFailed;
    }
    if (argc == 2 && stringsAreEqual(argv[1], "-test"))
    {
        return success;
    }
    unsigned int number1 = 0;
    unsigned int number2 = 0;
    printf("Enter number 1: ");
    scanf_s("%u", &number1);
    printf("Enter number 2: ");
    scanf_s("%u", &number2);
    printf("\n");

    bool* bits1 = convertToBinary(number1);
    bool* bits2 = convertToBinary(number2);
    if (bits1 == NULL || bits2 == NULL)
    {
        free(bits1);
        free(bits2);
        printf("An error occured\n");
        return badAllocation;
    }
    switch (compare(bits1, bits2))
    {
    case 0:
        printf("Numbers are equal\n");
        break;
    case -1:
        printf("Number 1 is greater\n");
        break;
    case 1:
        printf("Number 2 is greater\n");
        break;
    }
    free(bits1);
    free(bits2);
    return success;
}
