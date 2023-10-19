#pragma once
#include <stdbool.h>

typedef struct StackNode {
    int value;
    struct StackNode* next;
} StackNode;

// добавить элемент в стек
bool push(StackNode** const head, const int value);

// удалить элемент из стека
void pop(StackNode** const head);

// освободить память, выделенную под стек
void freeStack(StackNode** const head);
