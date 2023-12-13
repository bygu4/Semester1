#include "test.h"
#include "logic.h"
#include <stdio.h>

static void printFailedTest(const size_t numberOfTest)
{
    printf("Test %zu has failed\n", numberOfTest);
}

static bool testCase(const unsigned int number, const unsigned int expectedOutput, 
    const size_t numberOfTest)
{
    bool errorOccured = false;
    unsigned int output = permutateToGetMinimal(number, &errorOccured);
    bool testIsPassed = !errorOccured && output == expectedOutput;
    if (!testIsPassed)
    {
        printFailedTest(numberOfTest);
    }
    return testIsPassed;
}

bool test(void)
{
    return testCase(3, 3, 1) && testCase(21, 12, 2) && testCase(321, 123, 3) &&
        testCase(98127634, 12346789, 4) && testCase(999, 999, 5) && testCase(554, 455, 6);
}
