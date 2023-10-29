#include "console.h"
#include "test.h"
#include <stdio.h>

int main(void)
{
    const bool allTestsArePassed = test();
    if (!allTestsArePassed)
    {
        return TEST_FAILED;
    }
    const bool errorOccured = console();
    if (errorOccured)
    {
        printf("An error occured\n");
        return BAD_ALLOCATION;
    }
    return SUCCESS;
}
