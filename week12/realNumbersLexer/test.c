#include "test.h"
#include "isRealNumber.h"
#include <stdio.h>

static void printFailedTest(const size_t numberOfTest)
{
    printf("Test %zu has failed\n", numberOfTest);
}

static bool testCase(const char* const sequence, const bool expectedOutput,
    const size_t numberOfTest)
{
    bool testIsPassed = isRealNumber(sequence) == expectedOutput;
    if (!testIsPassed)
    {
        printFailedTest(numberOfTest);
    }
    return testIsPassed;
}

bool test(void)
{
    return testCase("", false, 1) &&
        testCase("143", true, 2) &&
        testCase("55.", false, 3) &&
        testCase(" 99.99 ", true, 4) &&
        testCase("672 . 6", false, 5) &&
        testCase("3131E65", true, 6) &&
        testCase("452.65a", false, 7) &&
        testCase("66.6E", false, 8) &&
        testCase("199.5E-", false, 9) &&
        testCase(".54E+3", false, 10) &&
        testCase("1035.4 E 3", false, 11) &&
        testCase("\n 243.576E-101 \n", true, 12);
}
