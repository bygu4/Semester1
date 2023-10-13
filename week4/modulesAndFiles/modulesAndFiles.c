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
#define READ_ERROR 1

void printArray(const int* const array, const size_t sizeOfArray)
{
    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        printf("%d ", array[i]);
    }
}

int main()
{
    char* testOutput = NULL;
    bool allTestsArePassed = test(testOutput);
    if (!allTestsArePassed)
    {
        printf("%s", testOutput);
        free(testOutput);
        return TEST_FAILED;
    }

    int sizeOfArray = 0;
    int* inputArray = readArrayFromFile(NAME_OF_FILE, &sizeOfArray);
    if (inputArray == NULL)
    {
        printf("An error occured");
        return READ_ERROR;
    }
    printArray(inputArray, sizeOfArray);

    quicksort(inputArray, 0, sizeOfArray);
    int mostCommonElement = findMostCommonElement(inputArray, sizeOfArray);
    printf("\nThe most common element in array: %d", mostCommonElement);
    free(inputArray);
}
