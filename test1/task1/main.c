#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#define NUMBER_OF_BITS sizeof(unsigned int) * 8

enum errorCodes {
    testFailed = -1,
    success = 0
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

int main(void)
{
    return testIsPassed() ? success : testFailed;
}
