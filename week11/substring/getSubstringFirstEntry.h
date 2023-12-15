#pragma once

#include <stdio.h>
#include <stdbool.h>

// получить индекс первого вхождения подстроки
// записывает по указателю наличие подстроки и наличие ошибки
size_t getSubstringFirstEntry(const char* const substring, const char* const string,
    const size_t lengthOfString, bool* const found, bool* const errorOccured);
