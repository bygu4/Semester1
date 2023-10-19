#pragma once

#define SUCCESS 0
#define BAD_ALLOCATION 1
#define BAD_INPUT 2

// принимает строку, содержащую выражение, возвращает результат вычисления. Записывает по указателю код ошибки
int calculate(const char* const string, int* const errorCode);
