#include "test.h"
#include "calculate.h"
#include <stdbool.h>
#include <stdio.h>

static bool testForCalculateIsPassed(void)
{
    int errorCode = -1;
    bool testOneIsPassed = calculate("9 6 - 1 2 +", &errorCode) == 9 && errorCode == SUCCESS;
    if (!testOneIsPassed)
    {
        printf("Test 1 has failed\n");
        return false;
    }

    bool testTwoIsPassed = calculate("a b +", &errorCode) == 0 && errorCode == BAD_INPUT;
    if (!testTwoIsPassed)
    {
        printf("Test 2 has failed\n");
        return false;
    }

    bool testThreeIsPassed = calculate("2 2 + 9 3 / 7 2 -", &errorCode) == 60 && errorCode == SUCCESS;
    if (!testThreeIsPassed)
    {
        printf("Test 3 has failed\n");
        return false;
    }

    bool testFourIsPassed = calculate("9 2 - 7 /", &errorCode) == 1 && errorCode == SUCCESS;
    if (!testFourIsPassed)
    {
        printf("Test 4 has failed\n");
        return false;
    }

    bool testFiveIsPassed = calculate("4 9 6 - +", &errorCode) == 7 && errorCode == SUCCESS;
    if (!testFiveIsPassed)
    {
        printf("Test 5 has failed\n");
        return false;
    }

    bool testSixIsPassed = calculate("8", &errorCode) == 8 && errorCode == SUCCESS;
    if (!testSixIsPassed)
    {
        printf("Test 6 has failed\n");
        return false;
    }

    bool testSevenIsPassed = calculate("", &errorCode) == 0 && errorCode == SUCCESS;
    if (!testSevenIsPassed)
    {
        printf("Test 7 has failed\n");
        return false;
    }

    bool testEightIsPassed = calculate("9 /", &errorCode) == 0 && errorCode == BAD_INPUT;
    if (!testEightIsPassed)
    {
        printf("Test 8 has failed\n");
        return false;
    }

    return true;
}

bool test(void)
{
    return testForCalculateIsPassed();
}
