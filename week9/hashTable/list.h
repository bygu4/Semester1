#pragma once
#include <stdbool.h>
#include <stdio.h>

typedef struct List List;

// создание пустого списка
List* createList(void);

// получение размера списка
size_t size(const List* const list);

// добавление в конец списка, если не найдено данной строки. Возвращает наличие ошибки при выделении памяти
bool push(List* const list, const char* const data);

// вывести данные в консоль
void printList(const List* const list);

// освободить память, выделенную под список
void freeList(List** const list);
