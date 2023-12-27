#include "test.h"
#include "sort.h"
#include <stdio.h>
#include <stdlib.h>

static void printFailedTest(const size_t numberOfTest)
{
    printf("Test %zu has failed\n", numberOfTest);
}

static bool arrayIsSorted(const int* const array, const size_t lengthOfArray)
{
    for (size_t i = 1; i < lengthOfArray; ++i)
    {
        if (array[i - 1] > array[i])
        {
            return false;
        }
    }
    return true;
}

static bool testCase(int* const array, const size_t lengthOfArray, const size_t numberOfTest)
{
    bool errorOccured = sort(array, lengthOfArray);
    bool testPassed = !errorOccured && arrayIsSorted(array, lengthOfArray);
    if (!testPassed)
    {
        printFailedTest(numberOfTest);
    }
    return testPassed;
}

bool test(void)
{
    int array1[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int array2[10] = { 5, 4, 3, 2, 1, 0, -1, -2, -3, -4 };
    int array3[10] = { 1, 1, 2, 2, 3, 3, 4, 4, 5, 5 };
    int array4[10] = { 7, 7, 7, 7, 6, 6, 6, 6, 5, 5 };
    int* array5 = NULL;

    return testCase(array1, 10, 1) &&
        testCase(array2, 10, 2) &&
        testCase(array3, 10, 3) &&
        testCase(array4, 10, 4) &&
        testCase(array5, 0, 5);
}
