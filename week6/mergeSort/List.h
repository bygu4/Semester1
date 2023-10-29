#pragma once
#include <stdbool.h>
#include <stdio.h>

#define SUCCESS 0
#define BAD_ALLOCATION 1

typedef struct List List;

// создание пустого списка
List* createList(void);

// проверка на пустоту списка
bool isEmpty(const List* const list);

// получение размера списка
size_t size(const List* const list);

// получение имени из начала списка
char* getName(const List* const list);

// получение номера из начала списка
char* getNumber(const List* const list);

// добавление в конец списка, возвращает код ошибки
int push(List* const list, const char* const name, const char* const number);

// удаление из начала списка
void pop(List* const list);

// освобождение памяти, выделенной под список
void freeList(List** const list);

// вывод данных в консоль
void printList(const List* const list);

// получение списка в виде массива строк. Записывает по указателю код ошибки
char** getList(const List* const list, int* const errorCode);
