#include "console.h"
#include "test.h"
#include <stdio.h>

#define SUCCESS 0
#define TEST_FAILED -1
#define BAD_ALLOCATION 1

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
