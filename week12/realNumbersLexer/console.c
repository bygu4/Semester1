#include "console.h"
#include "isRealNumber.h"
#include "str.h"
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define BAD_ALLOCATION 1

int console(void)
{
    printf("Input a character sequence: ");
    char* inputString = getString('\n');
    if (inputString == NULL)
    {
        printf("An error occured\n");
        return BAD_ALLOCATION;
    }
    if (isRealNumber(inputString))
    {
        printf("This is a real number\n");
    }
    else
    {
        printf("This is not a real number\n");
    }
    free(inputString);
    return SUCCESS;
}
