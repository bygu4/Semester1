#pragma once
#include "hashTable.h"

#define SUCCESS 0
#define BAD_ALLOCATION 1
#define FILE_NOT_FOUND 2

// считать слова из файла и добавить в таблицу. Возвращает код ошибки
int readFileAndAdd(HashTable* const table, const char* const nameOfFile);
