#pragma once
#include "str.h"

#define SUCCESS 0
#define BAD_ALLOCATION 1

// преобразует выражение из инфиксной формы в постфиксную. Записывает по указателю код ошибки
String* convertToPostfixForm(const String* const string, int* const errorCode);
