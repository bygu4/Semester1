#pragma once
#include <stdio.h>
#include <stdbool.h>

#define NUMBER_OF_BUCKETS 256

typedef struct HashTable HashTable;

// создать пустую таблицу
HashTable* createHashTable(void);

// освободить память, выделенную под таблицу
void freeHashTable(HashTable** const table);

// добавить элемент в таблицу, возвращает наличие ошибки при выделении памяти
bool add(HashTable* const table, const char* const key);

// вывести данные в консоль
void printTable(const HashTable* const table);

// посчитать коэффициент заполненности таблицы
double getLoadFactor(const HashTable* const table);

// получить максимальную длину списка
size_t getMaxLength(const HashTable* const table);

// посчитать среднюю длину списка
double getAverageLength(const HashTable* const table);

// получить число вхождений по ключу
unsigned int getNumberOfEntries(const HashTable* const table, const char* const key);
