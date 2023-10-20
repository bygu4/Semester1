#include "convertToPostfixForm.h"
#include "stack.h"
#include "str.h"
#include <stdlib.h>
#include <ctype.h>

static int addToOutput(char** const string, const char character, size_t* const lengthOfString)
{
    int errorCode = SUCCESS;
    errorCode = addCharToString(string, character, *lengthOfString);
    if (errorCode != SUCCESS)
    {
        return BAD_ALLOCATION;
    }
    errorCode = addCharToString(string, ' ', *lengthOfString + 1);
    if (errorCode != SUCCESS)
    {
        return BAD_ALLOCATION;
    }
    *lengthOfString += 2;
    return SUCCESS;
}

char* convertToPostfixForm(const char* const string, int* const errorCode)
{
    StackNode* head = NULL;
    char* output = (char*)malloc(sizeof(char));
    output[0] = '\0';
    size_t lengthOfOutput = 0;
    for (size_t i = 0; string[i] != '\0'; ++i)
    {
        char character = string[i];
        if (isdigit(character))
        {
            *errorCode = addToOutput(&output, character, &lengthOfOutput);
            if (*errorCode != SUCCESS)
            {
                return NULL;
            }
        }
        if (character == '*' || character == '/' || character == '(')
        {
            bool errorOccured = push(&head, character);
            if (errorOccured)
            {
                *errorCode = BAD_ALLOCATION;
                return NULL;
            }
        }
        if (character == '+' || character == '-')
        {
            while (head != NULL && (head->value == '*' || head->value == '/'))
            {
                *errorCode = addToOutput(&output, head->value, &lengthOfOutput);
                if (*errorCode != SUCCESS)
                {
                    return NULL;
                }
                pop(&head);
            }
            bool errorOccured = push(&head, character);
            if (errorOccured)
            {
                *errorCode = BAD_ALLOCATION;
                return NULL;
            }
        }
        if (character == ')')
        {
            while (head != NULL && head->value != '(')
            {
                *errorCode = addToOutput(&output, head->value, &lengthOfOutput);
                if (*errorCode != SUCCESS)
                {
                    return NULL;
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
        *errorCode = addToOutput(&output, head->value, &lengthOfOutput);
        if (*errorCode != SUCCESS)
        {
            return NULL;
        }
        pop(&head);
    }
    if (lengthOfOutput > 0)
    {
        output[lengthOfOutput - 1] = '\0';
    }
    freeStack(&head);
    return output;
}
