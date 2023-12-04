#pragma once
#include <stdbool.h>
#include <stdio.h>

typedef struct List List;

// создание пустого списка
List* createList(void);

// освобождение памяти, выделенной под список
void freeList(List** const list);

// добавление в конец списка. Возвращает наличие ошибки при выделении памяти
bool push(List* const list, const unsigned int city, const unsigned int distance);

// получение номера города по индексу
unsigned int city(List* const list, const size_t index);

// получение длины дороги по индексу
unsigned int distance(List* const list, const size_t index);

// получение размера списка
size_t listSize(const List* const list);

// вывести в консоль номера городов
void printList(const List* const list);

// сравнить массив с номерами городов из списка
bool arrayIsEqual(List* const list, const unsigned int* const array, const size_t length);
