#include "calculate.h"
#include "getString.h"
#include "test.h"
#include <stdio.h>

#define TEST_FAILED -1

int main(void)
{
    const bool allTestsArePassed = test();
    if (!allTestsArePassed)
    {
        return TEST_FAILED;
    }
    printf("Enter an arithmetic expression: ");
    char* inputString = getString('\n');
    if (inputString == NULL)
    {
        return BAD_ALLOCATION;
    }

    int errorCode = SUCCESS;
    int result = calculate(inputString, &errorCode);
    if (errorCode != SUCCESS)
    {
        printf("An error occured\n");
        return BAD_ALLOCATION;
    }
    printf("Result: %d\n", result);
}
