#pragma once
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

// посимвольно считать строку из стандартного потока
char* getString(const char breakPoint);

// получить копию строки
char* copyString(const char* const source);

// проверка строк на равенство
bool stringsAreEqual(const char* const string1, const char* const string2);
