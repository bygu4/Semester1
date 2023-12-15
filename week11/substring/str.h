#pragma once
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define SUCCESS 0
#define BAD_ALLOCATION 1
#define FILE_NOT_FOUND 2

// посимвольное считывание строки из стандартного потока
char* getString(const char breakPoint, size_t* const length);

// считывание файла целиком, возвращает код ошибки
int readFile(char** const result, const char* const nameOfFile, size_t* const length);

// проверка строк на равенство
bool stringsAreEqual(const char* const string1, const char* const string2);
