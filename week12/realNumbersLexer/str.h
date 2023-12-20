#pragma once

#include <stdbool.h>

// посимвольное считывание строки из стандартного потока
char* getString(const char breakPoint);

// проверка строк на равенство
bool stringsAreEqual(const char* const string1, const char* const string2);
