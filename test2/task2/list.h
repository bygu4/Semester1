#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef struct List List;

// создание пустого списка
List* createList(void);

// освобождение памяти, выделенной под список
void freeList(List** const list);

// добавление в конец списка. Возвращает наличие ошибки при выделении памяти
bool push(List* const list, const unsigned int value);

// получение значения по индексу
unsigned int value(List* const list, const size_t index);

// получение размера списка
size_t listSize(const List* const list);

// вывести в список в консоль
void printList(const List* const list);
