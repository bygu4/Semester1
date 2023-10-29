#pragma once
#include "List.h"
#include <stdbool.h>

// сравнение элементов списка по имени
bool compareByName(const List* const list1, const List* const list2);

// сравнение элементов списка по номеру
bool compareByNumber(const List* const list1, const List* const list2);

// сортировка слиянием по переданному ключу
int mergeSort(List* const list, bool (*key)(const List* const, const List* const));
