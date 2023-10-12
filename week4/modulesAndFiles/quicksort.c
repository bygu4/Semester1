#include "quicksort.h"
#include <stdlib.h>
#include <stdbool.h>

void swap(int* const number1, int* const number2)
{
    int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

size_t partition(int* const array, const size_t start, const size_t end, bool* const isSorted)
{
    size_t pointer = start + 1;
    while (array[pointer - 1] == array[pointer] && pointer + 1 < end)
    {
        ++pointer;
    }
    if (array[pointer - 1] > array[pointer])
    {
        *isSorted = false;
        --pointer;
    }
    int pivot = array[pointer];

    for (size_t i = pointer; i < end; ++i)
    {
        if (array[i] < pivot)
        {
            swap(&array[i], &array[pointer]);
            *isSorted = false;
            ++pointer;
        }
        if (isSorted && array[i - 1] > array[i])
        {
            *isSorted = false;
        }
    }
    return pointer;
}

void quicksort(int* const array, const size_t start, const size_t end)
{
    const size_t sizeOfArray = end - start;
    if (sizeOfArray <= 1)
    {
        return;
    }

    bool isSorted = true;
    size_t pointer = partition(array, start, end, &isSorted);

    if (isSorted)
    {
        return;
    }
    quicksort(array, start, pointer);
    quicksort(array, pointer, end);
}
