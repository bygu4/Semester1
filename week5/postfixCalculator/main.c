#include "calculate.h"
#include "getString.h"
#include "test.h"
#include <stdio.h>

int main(const unsigned int argc, const char argv[])
{
    const bool allTestsArePassed = test();
    if (!allTestsArePassed)
    {
        return TEST_FAILED;
    }
    if (argc == 2 && argv[1] == 't')
    {
        return SUCCESS;
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
        return errorCode;
    }
    printf("Result: %d\n", result);
}
