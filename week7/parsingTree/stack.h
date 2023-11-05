#pragma once
#include <stdbool.h>

// стек char'ов
typedef struct Stack Stack;

// создание пустого стека
Stack* createStack(void);

// проверка на пустоту стека
bool isEmpty(const Stack* const stack);

// получение значения из головы стека
char top(const Stack* const stack);

// добавление в стек, возвращает наличие ошибки при выделении памяти
bool push(Stack* const stack, const char value);

// удаление из стека
void pop(Stack* const stack);

// освобождение памяти, выделенной под стек
void freeStack(Stack** const stack);
