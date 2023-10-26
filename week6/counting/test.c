#include "test.h"
#include "CyclicList.h"
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

static bool pushArrayToList(CycledList* const list, const int* const array, const size_t sizeOfArray)
{
    bool errorOccured = false;
    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        errorOccured = push(list, array[i]);
        if (errorOccured)
        {
            return true;
        }
    }
    return false;
}

static bool testCaseForPush(const int* const array, const size_t sizeOfArray)
{
    CycledList* list = createList();
    if (list == NULL)
    {
        printf("Failed to create list\n");
        return false;
    }
    bool errorOccured = pushArrayToList(list, array, sizeOfArray);
    if (errorOccured)
    {
        freeList(&list);
        return false;
    }
    int* output = getList(list);
    bool testIsPassed = size(list) == sizeOfArray && arraysAreEqual(output, array, sizeOfArray);
    free(output);
    freeList(&list);
    return testIsPassed;
}

static bool testCaseForCyclicPop(const int* const array, const int* const expectedArray,
    const size_t count, const size_t sizeOfArray)
{
    CycledList* list = createList();
    if (list == NULL)
    {
        printf("Failed to create list\n");
        return false;
    }
    bool errorOccured = pushArrayToList(list, array, sizeOfArray);
    if (errorOccured)
    {
        free(&list);
        return false;
    }
    cyclicPop(list, count);
    int* output = getList(list);
    size_t expectedSize = count - 1;
    if (count == 0)
    {
        expectedSize = sizeOfArray;
    }
    bool testIsPassed = size(list) == expectedSize && arraysAreEqual(output, expectedArray, expectedSize);
    free(output);
    freeList(&list);
    return testIsPassed;
}

static bool testForPush(void)
{
    int array1[10] = { 90, 89, 88, 87, 86, -4, -3, -2, -1, 0 };
    bool testOneIsPassed = testCaseForPush(array1, 10);
    if (!testOneIsPassed)
    {
        printFailedTest(1, "testForPush");
        return false;
    }

    int* array2 = NULL;
    bool testTwoIsPassed = testCaseForPush(array2, 0);
    if (!testTwoIsPassed)
    {
        printFailedTest(2, "testForPush");
        return false;
    }

    return true;
}

static bool testForCyclicPop(void)
{
    int* array1 = NULL;
    int* expectedArray1 = NULL;
    bool testOneIsPassed = testCaseForCyclicPop(array1, expectedArray1, 1, 0);
    if (!testOneIsPassed)
    {
        printFailedTest(1, "testForCyclicPop");
        return false;
    }

    int array2[5] = { 10, 1, 9, 2, 8 };
    int expectedArray2[5] = { 10, 1, 9, 2, 8 };
    bool testTwoIsPassed = testCaseForCyclicPop(array2, expectedArray2, 0, 5);
    if (!testTwoIsPassed)
    {
        printFailedTest(2, "testForCyclicPop");
        return false;
    }

    int array3[7] = { 7, 7, 7, 7, 7, 7, 7 };
    int* expectedArray3 = NULL;
    bool testThreeIsPassed = testCaseForCyclicPop(array3, expectedArray3, 1, 7);
    if (!testThreeIsPassed)
    {
        printFailedTest(3, "testForCyclicPop");
        return false;
    }

    int array4[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    int expectedArray4[1] = { 3 };
    bool testFourIsPassed = testCaseForCyclicPop(array4, expectedArray4, 2, 9);
    if (!testFourIsPassed)
    {
        printFailedTest(4, "testForCyclicPop");
        return false;
    }

    int array5[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int expectedArray5[2] = { 4, 10 };
    bool testFiveIsPassed = testCaseForCyclicPop(array5, expectedArray5, 3, 10);
    if (!testFiveIsPassed)
    {
        printFailedTest(5, "testForCyclicPop");
        return false;
    }

    int array6[6] = { 1, 2, 3, 4, 5, 6 };
    int expectedArray6[5] = { 1, 2, 3, 4, 5 };
    bool testSixIsPassed = testCaseForCyclicPop(array6, expectedArray6, 6, 6);
    if (!testSixIsPassed)
    {
        printFailedTest(6, "testForCyclicPop");
        return false;
    }

    return true;
}

bool test(void)
{
    return testForPush() && testForCyclicPop();
}
