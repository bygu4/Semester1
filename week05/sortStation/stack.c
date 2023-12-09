#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

bool push(StackNode** const head, const char value)
{
    StackNode* next = malloc(sizeof(StackNode));
    if (next == NULL)
    {
        return true;
    }
    next->value = value;
    next->next = *head;
    *head = next;
    return false;
}

void pop(StackNode** const head)
{
    if (*head == NULL)
    {
        return;
    }
    StackNode* next = (*head)->next;
    free(*head);
    *head = next;
}

void freeStack(StackNode** const head)
{
    while (*head != NULL)
    {
        pop(head);
    }
}
