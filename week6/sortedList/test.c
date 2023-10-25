#include "test.h"
#include "SortedList.h"
#include <stdio.h>
#include <stdlib.h>

static void printFailedTest(const int numberOfTest, const char* const nameOfTest)
{
    printf("Test %d has failed in %s\n", numberOfTest, nameOfTest);
}

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

static bool testCaseForPush(const int* const inputArray, const int* const expectedArray, const size_t sizeOfArray)
{
    SortedList* list = createList();
    if (list == NULL)
    {
        printf("Failed to create list\n");
        return false;
    }
    bool errorOccured = false;
    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        errorOccured = push(list, inputArray[i]);
        if (errorOccured)
        {
            freeList(&list);
            return false;
        }
    }
    int* array = getList(list);
    bool testIsPassed = size(list) == sizeOfArray && arraysAreEqual(array, expectedArray, sizeOfArray);
    free(array);
    freeList(&list);
    return testIsPassed;
}

static bool testCaseForPop(const int* const inputArray, const size_t* const indexesToPop, const int* const expectedArray,
    const size_t sizeOfInputArray, const size_t sizeOfIndexArray, const int expectedErrorCode)
{
    SortedList* list = createList();
    if (list == NULL)
    {
        printf("Failed to create list\n");
        return false;
    }
    bool errorOccured = false;
    for (size_t i = 0; i < sizeOfInputArray; ++i)
    {
        errorOccured = push(list, inputArray[i]);
        if (errorOccured)
        {
            freeList(&list);
            return false;
        }
    }
    int errorCode = -1;
    for (size_t i = 0; i < sizeOfIndexArray; ++i)
    {
        errorCode = pop(list, indexesToPop[i]);
        if (errorCode != SUCCESS)
        {
            freeList(&list);
            return errorCode == expectedErrorCode;
        }
    }
    int* array = getList(list);
    size_t expectedSize = sizeOfInputArray - sizeOfIndexArray;
    bool testIsPassed = size(list) == expectedSize && arraysAreEqual(array, expectedArray, expectedSize);
    free(array);
    freeList(&list);
    return testIsPassed;
}

static bool testForPush(void)
{
    int array1[] = { 0 };
    int expectedArray1[] = { 0 };
    bool testOneIsPassed = testCaseForPush(array1, expectedArray1, 0);
    if (!testOneIsPassed)
    {
        printFailedTest(1, "testForPush");
        return false;
    }

    int array2[2] = { 2, -1 };
    int expectedArray2[2] = { -1, 2 };
    bool testTwoIsPassed = testCaseForPush(array2, expectedArray2, 2);
    if (!testTwoIsPassed)
    {
        printFailedTest(2, "testForPush");
        return false;
    }

    int array3[13] = { 99, 7, 5, -100, 4, 2, 5, 2, 1, -1, -2, -1, 0 };
    int expectedArray3[13] = { -100, -2, -1, -1, 0, 1, 2, 2, 4, 5, 5, 7, 99 };
    bool testThreeIsPassed = testCaseForPush(array3, expectedArray3, 13);
    if (!testThreeIsPassed)
    {
        printFailedTest(3, "testForPush");
        return false;
    }

    return true;
}

static bool testForPop(void)
{
    int array1[] = { 0 };
    size_t indexesToPop1[1] = { 1 };
    int expectedArray1[] = { 0 };
    bool testOneIsPassed = testCaseForPop(array1, indexesToPop1, expectedArray1, 0, 0, LIST_IS_EMPTY);
    if (!testOneIsPassed)
    {
        printFailedTest(1, "testForPop");
        return false;
    }

    int array2[1] = { 4 };
    size_t indexesToPop2[1] = { 1 };
    int expectedArray2[1] = { 4 };
    bool testTwoIsPassed = testCaseForPop(array2, indexesToPop2, expectedArray2, 1, 1, INDEX_OUT_OF_RANGE);
    if (!testTwoIsPassed)
    {
        printFailedTest(2, "testForPop");
        return false;
    }

    int array3[2] = { 5, 6 };
    size_t indexesToPop3[2] = { 1, 0 };
    int expectedArray3[] = { 0 };
    bool testThreeIsPassed = testCaseForPop(array3, indexesToPop3, expectedArray3, 2, 2, SUCCESS);
    if (!testThreeIsPassed)
    {
        printFailedTest(3, "testForPop");
        return false;
    }

    int array4[10] = { -10, -9, -1, 0, 4, 5, 8, 9, 10, 11 };
    size_t indexesToPop4[6] = {9, 0, 7, 0, 2, 2};
    int expectedArray4[4] = { -1, 0, 8, 9 };
    bool testFourIsPassed = testCaseForPop(array4, indexesToPop4, expectedArray4, 10, 6, SUCCESS);
    if (!testFourIsPassed)
    {
        printFailedTest(4, "testForPop");
        return false;
    }

    return true;
}

bool test(void)
{
    return testForPush() && testForPop();
}
