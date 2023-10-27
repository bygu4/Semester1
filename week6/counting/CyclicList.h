#pragma once
#include <stdbool.h>
#include <stdio.h>

typedef struct CycledList CycledList;

// создание пустого списка
CycledList* createList(void);

// проверка на пустоту списка
bool isEmpty(const CycledList* const list);

// получение длины списка
size_t size(const CycledList* const list);

// добавление элемента в конец списка. Возвращает наличие ошибки при выделении памяти
bool push(CycledList* const list, const size_t value);

// циклическое удаление каждого n-го элемента пока не останется n - 1 элемент
void cyclicPop(CycledList* const list, const size_t count);

// освобождение памяти, выделенной под список
void freeList(CycledList** const list);

// вывод списка в консоль
void printList(const CycledList* const list);

// получение списка в виде массива
size_t* getList(const CycledList* const list);
