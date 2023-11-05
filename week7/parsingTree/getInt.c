#include "getInt.h"
#include "stack.h"
#include <stdlib.h>
#include <math.h>

#define CHAR_TO_INT 48

int getInt(FILE* const stream, bool* const errorOccured)
{
    Stack* digits = createStack();
    if (digits == NULL)
    {
        *errorOccured = true;
        return 0;
    }
    char character = fgetc(stream);
    while (isdigit(character))
    {
        *errorOccured = push(digits, character);
        if (*errorOccured)
        {
            freeStack(&digits);
            return 0;
        }
        character = fgetc(stream);
    }
    ungetc(character, stream);
    int result = 0;
    for (unsigned int i = 0; !isEmpty(digits); ++i)
    {
        char digit = top(digits);
        pop(digits);
        result += ((int)digit - CHAR_TO_INT) * (int)pow(10, i);
    }
    free(digits);
    *errorOccured = false;
    return result;
}
