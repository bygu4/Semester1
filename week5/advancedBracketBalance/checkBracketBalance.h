#pragma once
#include <stdbool.h>

// проверяет баланс скобок в переданной строке. Передает по указателю код ошибки
bool checkBracketBalance(const char* const string, bool* const errorOccured);
