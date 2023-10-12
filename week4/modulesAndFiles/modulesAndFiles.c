#include "quicksort.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define NAME_OF_FILE "modulesAndFiles.txt"
#define TEST_FILE_1 "test1.txt"
#define TEST_FILE_2 "test2.txt"
#define TEST_FILE_3 "test3.txt"
#define TEST_FAILED -1
#define READ_ERROR 1
#define RAND_RANGE 20000

void printArray(const int* const array, const size_t sizeOfArray)
{
    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        printf("%d ", array[i]);
    }
}

int* readArrayFromFile(const char* const nameOfFile, int* const sizeOfArray)
{
    FILE* inputFile = NULL;
    int errorCode = fopen_s(&inputFile, nameOfFile, "r");
    if (errorCode != 0)
    {
        return NULL;
    }
    if (!feof(inputFile))
    {
        fscanf_s(inputFile, "%d", sizeOfArray);
    }
    int* array = (int*)calloc(*sizeOfArray, sizeof(int));
    if (array == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < *sizeOfArray && !feof(inputFile); ++i)
    {
        fscanf_s(inputFile, "%d", &array[i]);
    }
    fclose(inputFile);

    return array;
}

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

int* createTestArray(const size_t sizeOfArray)
{
    int* array = (int*)calloc(sizeOfArray, sizeof(int));
    if (array == NULL)
    {
        return NULL;
    }
    srand(time(NULL));
    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        array[i] = rand() % RAND_RANGE - RAND_RANGE / 2;
    }
    return array;
}

bool arraysAreEqual(const int* const array1, const int* const array2, const size_t sizeOfArray)
{
    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        if (array1[i] != array2[i])
        {
            return false;
        }
    }
    return true;
}

bool arrayIsSorted(const int* const array, const size_t sizeOfArray)
{
    for (size_t i = 1; i < sizeOfArray; ++i)
    {
        if (array[i - 1] > array[i])
        {
            return false;
        }
    }
    return true;
}

bool testForReadArrayFromFileSupport(const char* const testFile, const int* const expectedArray, const int expectedSize)
{
    int sizeOfArray = 0;
    int* array = readArrayFromFile(testFile, &sizeOfArray);
    if (array == NULL || sizeOfArray != expectedSize)
    {
        return false;
    }
    bool equal = arraysAreEqual(array, expectedArray, sizeOfArray);
    free(array);
    return equal;
}

char* testForReadArrayFromFile()
{
    int expectedArray1[15] = { 999, 0, -100, 4, 0, 2, 42, 999, 0, 4, 4, 4, -999, 100, 0 };
    bool testOneIsPassed = testForReadArrayFromFileSupport(TEST_FILE_1, expectedArray1, 15);
    if (!testOneIsPassed)
    {
        return "Test one has failed";
    }

    int expectedArray2[6] = { 0, 0, 0, 0, 0, 0 };
    bool testTwoIsPassed = testForReadArrayFromFileSupport(TEST_FILE_2, expectedArray2, 6);
    if (!testTwoIsPassed)
    {
        return "Test two has failed";
    }

    int expectedArray3[4] = { 1, 2, 3, 4 };
    bool testThreeIsPassed = testForReadArrayFromFileSupport(TEST_FILE_3, expectedArray3, 4);
    if (!testThreeIsPassed)
    {
        return "Test three has failed";
    }

    return "All tests are passed";
}

bool testForQuicksortSupport(int* const array, const int* const expectedArray, const size_t sizeOfArray)
{
    quicksort(array, 0, sizeOfArray);
    return arraysAreEqual(array, expectedArray, sizeOfArray);
}

char* testForQuicksort()
{
    int array1[20] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10 };
    int expectedArray1[20] = { -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6 ,7, 8, 9 };
    bool testOneIsPassed = testForQuicksortSupport(array1, expectedArray1, 20);
    if (!testOneIsPassed)
    {
        return "Test one has failed";
    }

    int array2[] = { 0 };
    int expectedArray2[] = { 0 };
    bool testTwoIsPassed = testForQuicksortSupport(array2, expectedArray2, 0);
    if (!testTwoIsPassed)
    {
        return "Test two has failed";
    }

    int array3[10] = { 2, 2, 2, 2, 2, 4, 4, 4, 4, 4 };
    int expectedArray3[10] = { 2, 2, 2, 2, 2, 4, 4, 4, 4, 4 };
    bool testThreeIsPassed = testForQuicksortSupport(array3, expectedArray3, 10);
    if (!testThreeIsPassed)
    {
        return "Test three has failed";
    }

    const size_t sizeOfTestArray = 10000;
    int* testArray = createTestArray(sizeOfTestArray);
    if (testArray == NULL)
    {
        return "Bad allocation";
    }
    quicksort(testArray, 0, sizeOfTestArray);
    bool testFourIsPassed = arrayIsSorted(testArray, sizeOfTestArray);
    free(testArray);
    if (!testFourIsPassed)
    {
        return "Test four has failed";
    }

    return "All tests are passed";
}

char* testForFindMostCommonElement()
{
    int array1[5] = { 2, 2, 2, 2, 2 };
    int mostCommonElement = findMostCommonElement(array1, 5);
    bool testOneIsPassed = mostCommonElement == 2;
    if (!testOneIsPassed)
    {
        return "Test one has failed";
    }

    int array2[6] = { 1, 2, 3, 4, 5, 6 };
    mostCommonElement = findMostCommonElement(array2, 6);
    bool testTwoIsPassed = mostCommonElement == 1;
    if (!testTwoIsPassed)
    {
        return "Test two has failed";
    }

    int array3[] = { NULL };
    mostCommonElement = findMostCommonElement(array3, 0);
    bool testThreeIsPassed = mostCommonElement == NULL;
    if (!testThreeIsPassed)
    {
        return "Test three has failed";
    }

    int array4[7] = { -1, -1, -1, 3, 3, 3, 3 };
    mostCommonElement = findMostCommonElement(array4, 7);
    bool testFourIsPassed = mostCommonElement == 3;
    if (!testFourIsPassed)
    {
        return "Test four has failed";
    }

    return "All tests are passed";
}

bool stringsAreEqual(const char* const string1, const char* const string2)
{
    const size_t size1 = strlen(string1);
    const size_t size2 = strlen(string2);
    if (size1 != size2)
    {
        return false;
    }
    for (size_t i = 0; i < size1; ++i)
    {
        if (string1[i] != string2[i])
        {
            return false;
        }
    }
    return true;
}

char* stringSum(const char* const string1, const char* const string2)
{
    const size_t size1 = strlen(string1);
    const size_t size2 = strlen(string2);
    char* newString = (char*)calloc(size1 + size2 + 1, sizeof(char));
    if (newString == NULL)
    {
        return newString;
    }
    for (size_t i = 0; i < size1; ++i)
    {
        newString[i] = string1[i];
    }

    for (size_t i = 0; i < size2; ++i)
    {
        newString[size1 + i] = string2[i];
    }
    return newString;
}

char* test()
{
    char* test1 = testForReadArrayFromFile();
    if (!stringsAreEqual(test1, "All tests are passed"))
    {
        char* output = stringSum(test1, " in testForReadArrayFromFile");
        return output;
    }

    char* test2 = testForQuicksort();
    if (!stringsAreEqual(test2, "All tests are passed"))
    {
        char* output = stringSum(test2, " in testForQuicksort");
        return output;
    }

    char* test3 = testForFindMostCommonElement();
    if (!stringsAreEqual(test3, "All tests are passed"))
    {
        char* output = stringSum(test3, " in testForFindMostCommonElement");
        return output;
    }

    return "All tests are passed";
}

int main()
{
    char* testOutput = test();
    if (!stringsAreEqual(testOutput, "All tests are passed"))
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
