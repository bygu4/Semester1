#include "findMostCommonElement.h"
#include <stdlib.h>
#include <string.h>

int findMostCommonElement(const int* const array, const size_t sizeOfArray)
{
    int mostCommonElement = NULL;
    int maxNumberOfEntries = 0;
    int previousElement = NULL;
    int count = 0;
    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        ++count;
        if (array[i] != previousElement)
        {
            previousElement = array[i];
            count = 1;
        }
        if (count > maxNumberOfEntries)
        {
            maxNumberOfEntries = count;
            mostCommonElement = array[i];
        }
    }
    return mostCommonElement;
}
