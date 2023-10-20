#include "convertToPostfixForm.h"
#include "str.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    const bool allTestsArePassed = test();
    if (!allTestsArePassed)
    {
        return TEST_FAILED;
    }
    printf("Enter an ariphmetic expression: ");
    char* inputString = getString('\n');
    if (inputString == NULL)
    {
        printf("An error occured\n");
        return BAD_ALLOCATION;
    }

    int errorCode = SUCCESS;
    char* output = convertToPostfixForm(inputString, &errorCode);
    free(inputString);
    if (errorCode != SUCCESS)
    {
        free(output);
        printf("An error occured\n");
        return errorCode;
    }
    printf("Expression in postfix form: %s\n", output);
    free(output);
}
