#include "readArrayFromFile.h"
#include "quicksort.h"
#include "findMostCommonElement.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NAME_OF_FILE "modulesAndFiles.txt"
#define TEST_FAILED -1
#define SUCCESS 0
#define READ_ERROR 1

void printArray(const int* const array, const size_t sizeOfArray)
{
    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        printf("%d ", array[i]);
    }
}

int main(const unsigned int argc, const char argv[])
{
    bool allTestsArePassed = test();
    if (!allTestsArePassed)
    {
        return TEST_FAILED;
    }
    if (argc == 2 && argv[1] == 't')
    {
        return SUCCESS;
    }

    int sizeOfArray = 0;
    int* inputArray = readArrayFromFile(NAME_OF_FILE, &sizeOfArray);
    if (inputArray == NULL)
    {
        printf("An error occured\n");
        return READ_ERROR;
    }
    printArray(inputArray, sizeOfArray);

    quicksort(inputArray, 0, sizeOfArray);
    int mostCommonElement = findMostCommonElement(inputArray, sizeOfArray);
    printf("\nThe most common element in array: %d\n", mostCommonElement);
    free(inputArray);
    return SUCCESS;
}
