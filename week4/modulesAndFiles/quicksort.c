#include "quicksort.h"
#include <stdbool.h>

void swap(int* number1, int* number2)
{
    int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

int partition(int* array, const int start, const int end, bool* isSorted)
{
    int pointer = start + 1;
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
    for (int i = pointer; i < end; ++i)
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

int quicksort(int* array, const int start, const int end)
{
    int sizeOfArray = end - start;
    if (sizeOfArray <= 1)
    {
        return 0;
    }

    bool isSorted = true;
    int pointer = partition(array, start, end, &isSorted);
    if (pointer >= end)
    {
        return 1;
    }
    if (isSorted)
    {
        return 0;
    }
    int errorCode1 = quicksort(array, start, pointer);
    int errorCode2 = quicksort(array, pointer, end);
    return errorCode1 + errorCode2;
}