#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

// получение целого числа из потока. Записывает по указателю наличие ошибки при выделении памяти
int getInt(FILE* const stream, bool* const errorOccured);
