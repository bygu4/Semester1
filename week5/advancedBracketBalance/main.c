#include "checkBracketBalance.h"
#include "getString.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>

#define TEST_FAILED -1
#define BAD_ALLOCATION 1

int main(void)
{
    bool allTestsArePassed = test();
    if (!allTestsArePassed)
    {
        return TEST_FAILED;
    }

    printf("Input a bracket sequence: ");
    char* inputString = getString('\n');
    if (inputString == NULL)
    {
        printf("An error occured\n");
        return BAD_ALLOCATION;
    }

    bool errorOccured = false;
    bool sequenceIsCorrect = checkBracketBalance(inputString, &errorOccured);
    free(inputString);
    if (errorOccured)
    {
        printf("An error occured\n");
        return BAD_ALLOCATION;
    }
    printf(sequenceIsCorrect ? "Correct\n" : "Incorrect\n");
}
