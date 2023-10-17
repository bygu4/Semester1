#include "test.h"
#include "checkBracketBalance.h"
#include <stdio.h>

static bool testForCheckBracketBalanceIsPassed(int* const errorCode)
{
    bool errorOccured = false;
    bool testOneIsPassed = checkBracketBalance("[({}[])]", &errorOccured) && !errorOccured;
    if (!testOneIsPassed)
    {
        *errorCode = 1;
        return false;
    }

    bool testTwoIsPassed = !checkBracketBalance("{}{", &errorOccured) && !errorOccured;
    if (!testTwoIsPassed)
    {
        *errorCode = 2;
        return false;
    }

    bool testThreeIsPassed = !checkBracketBalance(")", &errorOccured) && !errorOccured;
    if (!testThreeIsPassed)
    {
        *errorCode = 3;
        return false;
    }

    bool testFourIsPassed = !checkBracketBalance("([)]", &errorOccured) && !errorOccured;
    if (!testFourIsPassed)
    {
        *errorCode = 4;
        return false;
    }

    bool testFiveIsPassed = checkBracketBalance("(a + b)^2 = (a^2 + 2ab + b^2)", &errorOccured) && !errorOccured;
    if (!testFiveIsPassed)
    {
        *errorCode = 5;
        return false;
    }

    bool testSixIsPassed = checkBracketBalance("", &errorOccured) && !errorOccured;
    if (!testSixIsPassed)
    {
        *errorCode = 6;
        return false;
    }

    return true;
}

bool test(void)
{
    int errorCode = 0;
    bool testIsPassed = testForCheckBracketBalanceIsPassed(&errorCode);
    if (!testIsPassed)
    {
        printf("Test %d has failed in test for checkBracketBalance\n", errorCode);
        return false;
    }
    return true;
}
