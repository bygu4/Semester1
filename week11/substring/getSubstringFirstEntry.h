#pragma once

#include <stdio.h>
#include <stdbool.h>

// получить индекс первого вхождения подстроки. Записывает по указателю наличие подстроки
size_t getSubstringFirstEntry(const char* const substring, const char* const string, bool* const found);
