#pragma once
#include <stdio.h>

// быстрая сортировка, реализованная рекурсивно. принимает массив и границы сортировки:
// нижняя граница включительно, верхняя не включительно
void quicksort(int* const array, const size_t start, const size_t end);
