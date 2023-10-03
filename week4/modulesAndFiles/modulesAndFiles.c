#include "quicksort.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define NAME_OF_FILE "modulesAndFiles.txt"
#define TEST_FILE "test.txt"

int* readFile(const char* nameOfFile, const int sizeOfArray)
{
    FILE* inputFile = NULL;
    int errorCode = fopen_s(&inputFile, nameOfFile, "r");
    if (errorCode != 0)
    {
        return NULL;
    }
    int* array = (int*)calloc(sizeOfArray, sizeof(int));
    if (array == NULL)
    {
        return NULL;
    }
    int i = 0;
    while (!feof(inputFile) && i < sizeOfArray)
    {
        fscanf_s(inputFile, "%d", &array[i]);
        ++i;
    }
    fclose(inputFile);

    return array;
}

int findMostCommonElement(const int* array, const int sizeOfArray)
{
    int mostCommonElement = NULL;
    int maxNumberOfEntries = 0;
    int previousElement = NULL;
    int count = 0;
    for (int i = 0; i < sizeOfArray; ++i)
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

int* createTestArray(const int sizeOfArray)
{
    int* array = (int*)calloc(sizeOfArray, sizeof(int));
    if (array == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < sizeOfArray; ++i)
    {
        array[i] = rand() % 20000 - 10000;
    }
    return array;
}

bool arraysAreEqual(const int* array1, const int* array2, const int sizeOfArray)
{
    for (int i = 0; i < sizeOfArray; ++i)
    {
        if (array1[i] != array2[i])
        {
            return false;
        }
    }
    return true;
}

bool arrayIsSorted(const int* array, const int sizeOfArray)
{
    for (int i = 1; i < sizeOfArray; ++i)
    {
        if (array[i - 1] > array[i])
        {
            return false;
        }
    }
    return true;
}

bool testForReadFileIsPassed()
{
    int* array = readFile(TEST_FILE, 15);
    if (array == NULL)
    {
        return false;
    }
    int expectedArray[15] = { 999, 0, -100, 4, 0, 2, 42, 999, 0, 4, 4, 4, -999, 100, 0 };
    bool equal = arraysAreEqual(array, expectedArray, 15);
    free(array);
    return equal;
}

bool testForQuicksort(int* array, const int* expectedArray, const int sizeOfArray)
{
    int errorCode = quicksort(array, 0, sizeOfArray);
    return errorCode == 0 && arraysAreEqual(array, expectedArray, sizeOfArray);
}

bool allTestsForQuicksortArePassed()
{
    int array1[20] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10 };
    int expectedArray1[20] = { -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6 ,7, 8, 9 };
    bool testOneIsPassed = testForQuicksort(array1, expectedArray1, 20);

    int array2[] = { 0 };
    int expectedArray2[] = { 0 };
    bool testTwoIsPassed = testForQuicksort(array2, expectedArray2, 0);

    int array3[10] = { 2, 2, 2, 2, 2, 4, 4, 4, 4, 4 };
    int expectedArray3[10] = { 2, 2, 2, 2, 2, 4, 4, 4, 4, 4 };
    bool testThreeIsPassed = testForQuicksort(array3, expectedArray3, 10);

    int sizeOfTestArray = 10000;
    int* testArray = createTestArray(sizeOfTestArray);
    if (testArray == NULL)
    {
        return false;
    }
    int errorCode = quicksort(testArray, 0, sizeOfTestArray);
    bool testFourIsPassed = errorCode == 0 && arrayIsSorted(testArray, sizeOfTestArray);
    free(testArray);

    return testOneIsPassed && testTwoIsPassed && testThreeIsPassed && testFourIsPassed;
}

bool allTestsForMostCommonElementArePassed()
{
    int array1[5] = { 2, 2, 2, 2, 2 };
    int mostCommonElement = findMostCommonElement(array1, 5);
    bool testOneIsPassed = mostCommonElement == 2;

    int array2[6] = { 1, 2, 3, 4, 5, 6 };
    mostCommonElement = findMostCommonElement(array2, 6);
    bool testTwoIsPassed = mostCommonElement == 1;

    int array3[] = { NULL };
    mostCommonElement = findMostCommonElement(array3, 0);
    bool testThreeIsPassed = mostCommonElement == NULL;

    int array4[7] = { -1, -1, -1, 3, 3, 3, 3 };
    mostCommonElement = findMostCommonElement(array4, 7);
    bool testFourIsPassed = mostCommonElement == 3;

    return testOneIsPassed && testTwoIsPassed && testThreeIsPassed && testFourIsPassed;
}

bool allTestsArePassed()
{
    return testForReadFileIsPassed() && allTestsForQuicksortArePassed()
        && allTestsForMostCommonElementArePassed();
}

int main()
{
    if (!allTestsArePassed())
    {
        printf("An error occured");
        return -1;
    }

    int sizeOfArray = 0;
    printf("Enter a size of array: ");
    scanf_s("%d", &sizeOfArray);

    int* inputArray = readFile(NAME_OF_FILE, sizeOfArray);
    if (inputArray == NULL)
    {
        printf("An error occured");
        return -1;
    }

    int errorCode = quicksort(inputArray, 0, sizeOfArray);
    if (errorCode != 0)
    {
        printf("An error occured");
        return -1;
    }

    int mostCommonElement = findMostCommonElement(inputArray, sizeOfArray);
    printf("\nThe most common element in array: %d", mostCommonElement);
    free(inputArray);
}