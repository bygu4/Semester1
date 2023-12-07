#include "checkBracketBalance.h"
#include "getString.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>

#define BAD_ALLOCATION 1

int main(const unsigned int argc, const char argv[])
{
    bool allTestsArePassed = test();
    if (!allTestsArePassed)
    {
        return TEST_FAILED;
    }
    if (argc == 2 && argv[1] == 't')
    {
        return SUCCESS;
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
    return SUCCESS;
}
