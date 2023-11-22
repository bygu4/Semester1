#pragma once
#include <stdbool.h>
#include <stdio.h>

typedef struct List List;

// создать пустой список
List* createList(void);

// проверка на пустоту списка
bool isEmpty(const List* const list);

// добавление в конец списка
bool push(List* const list, const int value);

// удалить элемент следующий за текущим
void deleteElement(List* const list);

// смена текущего элемента на следующий за ним
void switchCurrent(List* const list);

// установить текущий элемент в начало списка
void setCurrent(List* const list);

// получить список в виде массива
int* getValues(const List* const list);

// освободить память, выделенную под список
void freeList(List** const list);

// возвращает true, если текущий элемент равен NULL, иначе false
bool currentIsNull(const List* const list);

// вывести список в консоль
void printList(const List* const list);

// получить размер списка
size_t size(const List* const list);
