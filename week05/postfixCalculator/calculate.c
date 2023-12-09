#include "calculate.h"
#include "stack.h"
#include <stdlib.h>
#include <ctype.h>

static int pushResultOfOperation(StackNode** const head, const char operator)
{
    int argument2 = (*head)->value;
    pop(head);
    int argument1 = (*head)->value;
    pop(head);
    int result = 0;
    switch (operator)
    {
    case '+':
        result = argument1 + argument2;
        break;
    case '-':
        result = argument1 - argument2;
        break;
    case '*':
        result = argument1 * argument2;
        break;
    case '/':
        if (argument2 == 0)
        {
            return DIVISION_BY_ZERO;
        }
        result = argument1 / argument2;
        break;
    }
    bool errorOccured = false;
    errorOccured = push(head, result);
    if (errorOccured)
    {
        return BAD_ALLOCATION;
    }
    return SUCCESS;
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
            if (errorOccured)
            {
                *errorCode = BAD_ALLOCATION;
                return 0;
            }
        }
        else if (character == '+' || character == '-' || character == '*' || character == '/')
        {
            if (numbers == NULL || numbers->next == NULL)
            {
                *errorCode = BAD_INPUT;
                return 0;
            }
            *errorCode = pushResultOfOperation(&numbers, character);
            if (*errorCode != SUCCESS)
            {
                return 0;
            }
        }
    }
    if (numbers == NULL)
    {
        return 0;
    }
    int result = numbers->value;
    freeStack(&numbers);
    *errorCode = SUCCESS;
    return result;
}
