#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define SUCCESS 0
#define BAD_ALLOCATION 1
#define LIST_IS_EMPTY 2
#define ELEMENT_NOT_IN_LIST 3

typedef struct SortedList SortedList;

// создание пустого списка
SortedList* createList(void);

// добавление в список с сохранением порядка. Возвращает наличие ошибки при выделении памяти
bool push(SortedList* const list, const int value);

// удаление элемента из списка. Возвращает код ошибки
int pop(SortedList* const list, const int value);

// проверка на пустоту списка
bool isEmpty(const SortedList* const list);

// получение длины списка
size_t size(const SortedList* const list);

// вывод списка в консоль
void printList(const SortedList* const list);

// получение списка в виде массива
int* getList(const SortedList* const list);

// освобождение памяти, выделенной под массив
void freeList(SortedList** const list);
