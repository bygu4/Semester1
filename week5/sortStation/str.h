#pragma once
#include <string.h>
#include <stdbool.h>

#define SUCCESS 0
#define BAD_ALLOCATION 1

// считать посимвольно строку произвольной длины из консоли
char* getString(const char breakPoint);

// добавить символ к строке. Возвращает код ошибки
int addCharToString(char** const string, const char character, const size_t lengthOfString);

// проверить строки на равенство
bool stringsAreEqual(const char* const string1, const char* const string2);
