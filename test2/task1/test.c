#include "test.h"
#include "list.h"
#include "deleteOddElements.h"
#include <stdio.h>
#include <stdlib.h>

static bool arraysAreEqual(const int* const array1, const int* const array2, const size_t sizeOfArray)
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

static bool testCase(const int* const elements, const int* const expectedOutput, 
    const size_t numberOfElements, const size_t sizeOfOutput)
{
    List* list = createList();
    if (list == NULL)
    {
        return false;
    }
    for (size_t i = 0; i < numberOfElements; ++i)
    {
        bool errorOccured = push(list, elements[i]);
        if (errorOccured)
        {
            return false;
        }
    }
    deleteOddElements(list);
    int* output = getValues(list);
    bool testIsPassed = size(list) == sizeOfOutput && arraysAreEqual(output, expectedOutput, sizeOfOutput);
    freeList(&list);
    free(output);
    return testIsPassed;
}

static void printFailedTest(const size_t testNumber)
{
    printf("Test %zu has failed\n", testNumber);
}

bool test(void)
{
    int elements1[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int output1[5] = { 1, 3, 5, 7, 9 };
    bool testOneIsPassed = testCase(elements1, output1, 10, 5);
    if (!testOneIsPassed)
    {
        printFailedTest(1);
        return false;
    }

    int element2[1] = { 10 };
    int output2[1] = { 10 };
    bool testTwoIsPassed = testCase(element2, output2, 1, 1);
    if (!testTwoIsPassed)
    {
        printFailedTest(2);
        return false;
    }

    bool testThreeIsPassed = testCase(NULL, NULL, 0, 0);
    if (!testThreeIsPassed)
    {
        printFailedTest(3);
        return false;
    }

    return true;
}
