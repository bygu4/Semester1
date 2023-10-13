#include "test.h"
#include "readArrayFromFile.h"
#include "quicksort.h"
#include "findMostCommonElement.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define TEST_FILE_1 "test1.txt"
#define TEST_FILE_2 "test2.txt"
#define TEST_FILE_3 "test3.txt"
#define RAND_RANGE 20000

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

bool testForReadArrayFromFile(const char* const testFile, const int* const expectedArray, const int expectedSize)
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

bool testsForReadArrayFromFileArePassed(char* const output)
{
    int expectedArray1[15] = { 999, 0, -100, 4, 0, 2, 42, 999, 0, 4, 4, 4, -999, 100, 0 };
    bool testOneIsPassed = testForReadArrayFromFile(TEST_FILE_1, expectedArray1, 15);
    if (!testOneIsPassed)
    {
        *output = "Test one has failed";
        return false;
    }

    int expectedArray2[6] = { 0, 0, 0, 0, 0, 0 };
    bool testTwoIsPassed = testForReadArrayFromFile(TEST_FILE_2, expectedArray2, 6);
    if (!testTwoIsPassed)
    {
        *output = "Test two has failed";
        return false;
    }

    int expectedArray3[4] = { 1, 2, 3, 4 };
    bool testThreeIsPassed = testForReadArrayFromFile(TEST_FILE_3, expectedArray3, 4);
    if (!testThreeIsPassed)
    {
        *output = "Test three has failed";
        return false;
    }

    return true;
}

bool testForQuicksortSupport(int* const array, const int* const expectedArray, const size_t sizeOfArray)
{
    quicksort(array, 0, sizeOfArray);
    return arraysAreEqual(array, expectedArray, sizeOfArray);
}

char* testsForQuicksortArePassed(char* const output)
{
    int array1[20] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10 };
    int expectedArray1[20] = { -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6 ,7, 8, 9 };
    bool testOneIsPassed = testForQuicksortSupport(array1, expectedArray1, 20);
    if (!testOneIsPassed)
    {
        *output = "Test one has failed";
        return false;
    }

    int array2[] = { 0 };
    int expectedArray2[] = { 0 };
    bool testTwoIsPassed = testForQuicksortSupport(array2, expectedArray2, 0);
    if (!testTwoIsPassed)
    {
        *output = "Test two has failed";
        return false;
    }

    int array3[10] = { 2, 2, 2, 2, 2, 4, 4, 4, 4, 4 };
    int expectedArray3[10] = { 2, 2, 2, 2, 2, 4, 4, 4, 4, 4 };
    bool testThreeIsPassed = testForQuicksortSupport(array3, expectedArray3, 10);
    if (!testThreeIsPassed)
    {
        *output = "Test three has failed";
        return false;
    }

    const size_t sizeOfTestArray = 10000;
    int* testArray = createTestArray(sizeOfTestArray);
    if (testArray == NULL)
    {
        *output = "Bad allocation";
        return false;
    }
    quicksort(testArray, 0, sizeOfTestArray);
    bool testFourIsPassed = arrayIsSorted(testArray, sizeOfTestArray);
    free(testArray);
    if (!testFourIsPassed)
    {
        *output = "Test four has failed";
        return false;
    }

    return true;
}

bool testForFindMostCommonElement(const int* const array, const size_t sizeOfArray, const int expectedOutput)
{
    int output = findMostCommonElement(array, sizeOfArray);
    return output == expectedOutput;
}

bool testsForFindMostCommonElementArePassed(char* const output)
{
    int array1[5] = { 2, 2, 2, 2, 2 };
    bool testOneIsPassed = testForFindMostCommonElement(array1, 5, 2);
    if (!testOneIsPassed)
    {
        *output = "Test one has failed";
        return false;
    }

    int array2[6] = { 1, 2, 3, 4, 5, 6 };
    bool testTwoIsPassed = testForFindMostCommonElement(array2, 6, 1);
    if (!testTwoIsPassed)
    {
        *output = "Test two has failed";
        return false;
    }

    int array3[] = { 0 };
    bool testThreeIsPassed = testForFindMostCommonElement(array3, 0, 0);
    if (!testThreeIsPassed)
    {
        *output = "Test three has failed";
        return false;
    }

    int array4[7] = { -1, -1, -1, 3, 3, 3, 3 };
    bool testFourIsPassed = testForFindMostCommonElement(array4, 7, 3);
    if (!testFourIsPassed)
    {
        *output = "Test four has failed";
        return false;
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
        return NULL;
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

bool test(char* const output)
{
    char* testOutput1 = NULL;
    bool testOneIsPassed = testsForReadArrayFromFileArePassed(testOutput1);
    if (!testOneIsPassed)
    {
        *output = stringSum(testOutput1, " in test for readArrayFromFile");
        return false;
    }

    char* testOutput2 = NULL;
    bool testTwoIsPassed = testsForQuicksortArePassed(testOutput2);
    if (!testTwoIsPassed)
    {
        *output = stringSum(testOutput2, " in test for quicksort");
        return false;
    }

    char* testOutput3 = NULL;
    bool testThreeIsPassed = testsForFindMostCommonElementArePassed(testOutput3);
    if (!testThreeIsPassed)
    {
        *output = stringSum(testOutput3, " in test for findMostCommonElement");
        return false;
    }

    return true;
}
