#include "calculate.h"
#include "stack.h"
#include <stdlib.h>
#include <ctype.h>

static bool pushResultOfOperation(StackNode** const numbers, const char operator)
{
    int argument2 = (*numbers)->value;
    pop(numbers);
    int argument1 = (*numbers)->value;
    pop(numbers);
    bool errorOccured = false;
    switch (operator)
    {
    case '+':
        errorOccured = push(numbers, argument1 + argument2);
        break;
    case '-':
        errorOccured = push(numbers, argument1 - argument2);
        break;
    case '/':
        errorOccured = push(numbers, argument1 / argument2);
        break;
    case '*':
        errorOccured = push(numbers, argument1 * argument2);
        break;
    }
    return errorOccured;
}

int calculate(const char* const string, int* const errorCode)
{
    StackNode* numbers = NULL;
    bool errorOccured = false;
    for (size_t i = 0; string[i] != '\0'; ++i)
    {
        char character = string[i];
        if (isdigit(character))
        {
            errorOccured = push(&numbers, (int)character - 48);
        }
        else if (character == '+' || character == '-' || character == '/')
        {
            if (numbers == NULL || numbers->next == NULL)
            {
                *errorCode = BAD_INPUT;
                return 0;
            }
            errorOccured = pushResultOfOperation(&numbers, character);
        }
        if (errorOccured)
        {
            *errorCode = BAD_ALLOCATION;
            return 0;
        }
    }
    if (numbers == NULL)
    {
        return 0;
    }
    while (numbers->next != NULL)
    {
        errorOccured = pushResultOfOperation(&numbers, '*');
        if (errorOccured)
        {
            *errorCode = BAD_ALLOCATION;
            return 0;
        }
    }
    int result = numbers->value;
    freeStack(&numbers);
    *errorCode = SUCCESS;
    return result;
}
