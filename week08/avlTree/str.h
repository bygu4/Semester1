#pragma once
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

// посимвольное считывание строки из стандартного потока
char* getString(const char breakPoint);

// получение копии строки
char* copyString(const char* const source);

// проверка строк на равенство
bool stringsAreEqual(const char* const string1, const char* const string2);

// компаратор для строк. Возвращает 0, если строки равны, 1, если первая меньше второй, -1 если больше 
int compareStrings(const char* const string1, const char* const string2);
