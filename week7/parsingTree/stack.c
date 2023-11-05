#include "stack.h"
#include <stdlib.h>

typedef struct {
    char value;
    struct StackNode* next;
} StackNode;

struct Stack {
    StackNode* head;
};

Stack* createStack(void)
{
    return (Stack*)calloc(1, sizeof(Stack));
}

bool isEmpty(const Stack* const stack)
{
    return stack->head == NULL;
}

char top(const Stack* const stack)
{
    return stack->head->value;
}

bool push(Stack* const stack, const char value)
{
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL)
    {
        return true;
    }
    newNode->value = value;
    newNode->next = stack->head;
    stack->head = newNode;
    return false;
}

void pop(Stack* const stack)
{
    if (isEmpty(stack))
    {
        return;
    }
    StackNode* head = stack->head;
    stack->head = head->next;
    free(head);
}

void freeStack(Stack** const stack)
{
    while (!isEmpty(*stack))
    {
        pop(*stack);
    }
    free(*stack);
    *stack = NULL;
}
