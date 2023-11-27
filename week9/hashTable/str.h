#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// получить копию строки
char* copyString(const char* const source);

// считать слово из файла
char* getWord(FILE* const stream);

// проверка строк на равенство
bool stringsAreEqual(const char* const string1, const char* const string2);
