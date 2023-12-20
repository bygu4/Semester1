#include "console.h"
#include "str.h"
#include "isAccepted.h"
#include <stdlib.h>
#include <stdio.h>

#define SUCCESS 0
#define BAC_ALLOCATION 1

int console(void)
{
    printf("Input a character sequence: ");
    char* inputString = getString('\n');
    if (inputString == NULL)
    {
        printf("An error occured\n");
        return BAC_ALLOCATION;
    }
    if (isAccepted(inputString))
    {
        printf("Sequence is accepted\n");
    }
    else
    {
        printf("Sequence is not accepted\n");
    }
    free(inputString);
    return SUCCESS;
}
