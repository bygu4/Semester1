#pragma once
#include "List.h"
#include <stdio.h>

#define INCORRECT_FORMAT 3

// считать данные из файла и записать в список. Возвращает код ошибки
int readListFromFile(List* const list, const char* const nameOfFile);
