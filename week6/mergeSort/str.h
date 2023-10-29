#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SUCCESS 0
#define BAD_ALLOCATION 1

// конкатенация строк. Записывает по указателю код ошибки
char* stringSum(int* const errorCode, const size_t numberOfSources, ...);

// считывание строки из файла. Записывает по указателю код ошибки
char* fgetString(FILE* const inputFile, const char breakPoint, int* const errorCode);

// проверка строк на равенство
bool stringsAreEqual(const char* const string1, const char* const string2);

// сравнение строк. Возвращает false, если первая строка больше второй, иначе true
bool compareStrings(const char* const string1, const char* const string2);
