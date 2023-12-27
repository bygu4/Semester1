#include "logic.h"
#include <stdlib.h>
#include <math.h>

static void swap(unsigned char* const number1, unsigned char* const number2)
{
    char temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

static size_t partition(unsigned char* const array, const size_t start, const size_t end, bool* const isSorted)
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
    unsigned char pivot = array[pointer];

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

static void quicksort(unsigned char* const array, const size_t start, const size_t end)
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

unsigned int permutateToGetMinimal(unsigned int number, bool* const errorOccured)
{
    unsigned int numberCopy = number;
    size_t numberOfDigits = 0;
    while (numberCopy > 0)
    {
        numberCopy /= 10;
        ++numberOfDigits;
    }
    unsigned char* digits = (unsigned char*)malloc(numberOfDigits * sizeof(unsigned char));
    if (digits == NULL)
    {
        *errorOccured = true;
        return 0;
    }
    for (size_t i = numberOfDigits; i > 0; --i)
    {
        digits[i - 1] = number % 10;
        number /= 10;
    }
    quicksort(digits, 0, numberOfDigits);
    unsigned int result = 0;
    for (size_t i = 0; i < numberOfDigits; ++i)
    {
        result += (unsigned int)digits[i] * (unsigned int)pow(10, numberOfDigits - i - 1);
    }
    free(digits);
    *errorOccured = false;
    return result;
}
