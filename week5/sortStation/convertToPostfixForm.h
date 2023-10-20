#pragma once

#define SUCCESS 0
#define BAD_ALLOCATION 1

// преобразует выражение из инфиксной формы в постфиксную. Записывает по указателю код ошибки
char* convertToPostfixForm(const char* const string, int* const errorCode);
