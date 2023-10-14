#pragma once
#include <stdbool.h>

// сравнение строк посимвольно
bool stringsAreEqual(const char* const string1, const char* const string2);

// умножение строки на число
char* stringMul(const char* const string, const int multiplier);
