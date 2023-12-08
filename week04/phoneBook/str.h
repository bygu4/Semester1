#pragma once
#include <stdbool.h>
#include <stdio.h>

// сравнение строк посимвольно
bool stringsAreEqual(const char* const string1, const char* const string2);

// умножение строки на число
char* stringMul(const char* const string, const unsigned int multiplier);

// посимвольное считывание строки произвольной длины из файла
char* fgetString(FILE* const file, const char breakPoint, const size_t initialSizeOfBuffer);

// посимвольное считывание строки произвольной длины из консоли
char* getString(const char breakPoint, const size_t initialSizeOfBuffer);
