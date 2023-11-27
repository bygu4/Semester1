#pragma once
#include <stdbool.h>
#include <stdio.h>

typedef struct List List;

// создание пустого списка
List* createList(void);

// освободить пам€ть, выделенную под список
void freeList(List** const list);

// получение размера списка
size_t size(const List* const list);

// добавление в конец списка, если не найдено данной строки. ¬озвращает наличие ошибки при выделении пам€ти
bool push(List* const list, const char* const key);

// вывести данные в консоль
void printList(const List* const list);

// получить число вхождений по ключу
unsigned int numberOfEntries(const List* const list, const char* const key);
