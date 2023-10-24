#include "convertToPostfixForm.h"
#include "stack.h"
#include "str.h"
#include <stdlib.h>
#include <ctype.h>

static int addToOutput(String* string, const char character)
{
    int errorCode = SUCCESS;
    errorCode = addCharToString(string, character);
    if (errorCode != SUCCESS)
    {
        return BAD_ALLOCATION;
    }
    errorCode = addCharToString(string, ' ');
    if (errorCode != SUCCESS)
    {
        return BAD_ALLOCATION;
    }
    return SUCCESS;
}

String* convertToPostfixForm(const String* const string, int* const errorCode)
{
    StackNode* head = NULL;
    String* output = createString("");
    if (output == NULL)
    {
        *errorCode = BAD_ALLOCATION;
        return NULL;
    }
    for (size_t i = 0; string->data[i] != '\0'; ++i)
    {
        char character = string->data[i];
        if (isdigit(character))
        {
            *errorCode = addToOutput(output, character);
            if (*errorCode != SUCCESS)
            {
                return output;
            }
        }
        else if (character == '*' || character == '/' || character == '(')
        {
            bool errorOccured = push(&head, character);
            if (errorOccured)
            {
                *errorCode = BAD_ALLOCATION;
                return output;
            }
        }
        else if (character == '+' || character == '-')
        {
            while (head != NULL && (head->value == '*' || head->value == '/'))
            {
                *errorCode = addToOutput(output, head->value);
                if (*errorCode != SUCCESS)
                {
                    return output;
                }
                pop(&head);
            }
            bool errorOccured = push(&head, character);
            if (errorOccured)
            {
                *errorCode = BAD_ALLOCATION;
                return output;
            }
        }
        else if (character == ')')
        {
            while (head != NULL && head->value != '(')
            {
                *errorCode = addToOutput(output, head->value);
                if (*errorCode != SUCCESS)
                {
                    return output;
                }
                pop(&head);
            }
            pop(&head);
        }
    }
    while (head != NULL)
    {
        if (head->value == '(')
        {
            pop(&head);
            continue;
        }
        *errorCode = addToOutput(output, head->value);
        if (*errorCode != SUCCESS)
        {
            return output;
        }
        pop(&head);
    }
    if (output->length > 0)
    {
        output->data[output->length - 1] = '\0';
        --output->length;
    }
    freeStack(&head);
    *errorCode = SUCCESS;
    return output;
}
