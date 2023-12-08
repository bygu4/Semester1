#include "readArrayFromFile.h"
#include "quicksort.h"
#include "findMostCommonElement.h"
#include "test.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define NAME_OF_FILE "modulesAndFiles.txt"
#define TEST_FAILED -1
#define SUCCESS 0
#define READ_ERROR 1

static void printArray(const int* const array, const size_t sizeOfArray)
{
    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        printf("%d ", array[i]);
    }
}

static bool stringsAreEqual(const char* const string1, const char* const string2)
{
    for (size_t i = 0; string1[i] != '\0' || string2[i] != '\0'; ++i)
    {
        if (string1[i] != string2[i])
        {
            return false;
        }
    }
    return true;
}

int main(const unsigned int argc, const char* const argv[])
{
    bool allTestsArePassed = test();
    if (!allTestsArePassed)
    {
        return TEST_FAILED;
    }
    if (argc == 2 && stringsAreEqual(argv[1], "-test"))
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
