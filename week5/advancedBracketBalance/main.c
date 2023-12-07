#include "checkBracketBalance.h"
#include "getString.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>

#define BAD_ALLOCATION 1

static bool stringsAreEqual(const char* const string1, const char* const string2)
{
    for (size_t i = 0; string1[i] != '\0' || string2[i] != '\0'; ++i)
    {
        if (string1[i] != string2[i])
        {
            return false;
        }
    }
    return true;
}

int main(const unsigned int argc, const char* const argv[])
{
    bool allTestsArePassed = test();
    if (!allTestsArePassed)
    {
        return TEST_FAILED;
    }
    if (argc == 2 && stringsAreEqual(argv[1], "-test"))
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
