#include "test.h"
#include "isAccepted.h"
#include <stdio.h>

static void printFailedTest(const size_t numberOfTest)
{
    printf("Test %zu has failed\n", numberOfTest);
}

static bool testCase(const char* const sequence, const bool expectedOutput,
    const size_t numberOfTest)
{
    bool testPassed = isAccepted(sequence) == expectedOutput;
    if (!testIsPassed)
    {
        printFailedTest(numberOfTest);
    }
    return testIsPassed;
}

bool testIsPassed(void)
{
    return testCase("", false, 1) &&
        testCase("G", true, 2) &&
        testCase("a_5454", true, 3) &&
        testCase("5", false, 4) &&
        testCase("AB gfgfg_32", false, 5) &&
        testCase("a_", true, 6) &&
        testCase("A133_BD5_2", true, 7) &&
        testCase("Aa_999_ab@23", false, 8) &&
        testCase("_ABCD31_", false, 9);
}
