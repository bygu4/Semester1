#include "checkBracketBalance.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char bracket;
    struct StackNode* next;
} StackNode;

static bool push(StackNode** const head, const char bracket)
{
    StackNode* next = malloc(sizeof(StackNode));
    if (next == NULL)
    {
        return true;
    }
    next->bracket = bracket;
    next->next = *head;
    *head = next;
    return false;
}

static void pop(StackNode** const head)
{
    StackNode* next = (*head)->next;
    free(*head);
    *head = next;
}

static void freeStack(StackNode** const head)
{
    while (*head != NULL)
    {
        pop(head);
    }
}

static char getClosingBracket(const char bracket)
{
    switch (bracket)
    {
    case '(':
        return ')';
    case '[':
        return ']';
    case '{':
        return '}';
    default:
        return NULL;
    }
}

bool checkBracketBalance(const char* const string, bool* const errorOccured)
{
    StackNode* head = NULL;
    size_t lengthOfString = strlen(string);
    for (size_t i = 0; i < lengthOfString; ++i)
    {
        char character = string[i];
        if (character == '(' || character == '[' || character == '{')
        {
            char closingBracket = getClosingBracket(character);
            bool pushErrorOccured = push(&head, closingBracket);
            if (pushErrorOccured)
            {
                *errorOccured = true;
                freeStack(&head);
                return false;
            }
        }
        else if (head != NULL && character == head->bracket)
        {
            pop(&head);
        }
        else if ((character == ')' || character == ']' || character == '}')
            && (head == NULL || character != head->bracket))
        {
            freeStack(&head);
            return false;
        }
    }
    if (head == NULL)
    {
        return true;
    }
    freeStack(&head);
    return false;
}
