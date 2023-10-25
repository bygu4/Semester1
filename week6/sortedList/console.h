#pragma once
#include "SortedList.h"
#include <stdbool.h>

// считать число из стандартного потока и добавить в список
bool pushConsole(SortedList* const list);

// считать число из стандартного потока и удалить из списка
void popConsole(SortedList* const list);

// вывести список в консоль
void printListConsole(const SortedList* const list);
