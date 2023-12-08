#include "test.h"
#include "CyclicList.h"
#include <stdlib.h>

static void printFailedTest(const int numberOfTest, const char* const nameOfTest)
{
    printf("Test %d has failed in %s\n", numberOfTest, nameOfTest);
}

static bool arraysAreEqual(const size_t* const array1, const size_t* const array2, const size_t sizeOfArray)
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

static bool pushArrayToList(CycledList* const list, const size_t* const array, const size_t sizeOfArray)
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

static bool testCaseForPush(const size_t* const array, const size_t sizeOfArray)
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
    size_t* output = getList(list);
    if (output == NULL)
    {
        freeList(&list);
        return false;
    }
    bool testIsPassed = size(list) == sizeOfArray && arraysAreEqual(output, array, sizeOfArray);
    free(output);
    freeList(&list);
    return testIsPassed;
}

static bool testCaseForCyclicPop(const size_t* const array, const size_t* const expectedArray,
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
    size_t* output = getList(list);
    if (output == NULL)
    {
        freeList(&list);
        return false;
    }
    size_t expectedSize = 1;
    if (count == 0 || sizeOfArray == 0)
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
    size_t array1[10] = { 90, 89, 88, 87, 86, -4, -3, -2, -1, 0 };
    bool testOneIsPassed = testCaseForPush(array1, 10);
    if (!testOneIsPassed)
    {
        printFailedTest(1, "testForPush");
        return false;
    }

    size_t* array2 = NULL;
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
    size_t* array1 = NULL;
    size_t* expectedArray1 = NULL;
    bool testOneIsPassed = testCaseForCyclicPop(array1, expectedArray1, 2, 0);
    if (!testOneIsPassed)
    {
        printFailedTest(1, "testForCyclicPop");
        return false;
    }

    size_t array2[5] = { 10, 1, 9, 2, 8 };
    size_t expectedArray2[5] = { 10, 1, 9, 2, 8 };
    bool testTwoIsPassed = testCaseForCyclicPop(array2, expectedArray2, 0, 5);
    if (!testTwoIsPassed)
    {
        printFailedTest(2, "testForCyclicPop");
        return false;
    }

    size_t array3[7] = { 7, 7, 7, 7, 7, 7, 8 };
    size_t expectedArray3[1] = { 8 };
    bool testThreeIsPassed = testCaseForCyclicPop(array3, expectedArray3, 1, 7);
    if (!testThreeIsPassed)
    {
        printFailedTest(3, "testForCyclicPop");
        return false;
    }

    size_t array4[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    size_t expectedArray4[1] = { 3 };
    bool testFourIsPassed = testCaseForCyclicPop(array4, expectedArray4, 2, 9);
    if (!testFourIsPassed)
    {
        printFailedTest(4, "testForCyclicPop");
        return false;
    }

    size_t array5[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    size_t expectedArray5[1] = { 4 };
    bool testFiveIsPassed = testCaseForCyclicPop(array5, expectedArray5, 3, 10);
    if (!testFiveIsPassed)
    {
        printFailedTest(5, "testForCyclicPop");
        return false;
    }

    size_t array6[6] = { 1, 2, 3, 4, 5, 6 };
    size_t expectedArray6[1] = { 5 };
    bool testSixIsPassed = testCaseForCyclicPop(array6, expectedArray6, 7, 6);
    if (!testSixIsPassed)
    {
        printFailedTest(6, "testForCyclicPop");
        return false;
    }

    size_t array7[1] = { 42 };
    size_t expectedArray7[1] = { 42 };
    bool testSevenIsPassed = testCaseForCyclicPop(array7, expectedArray7, 1, 1);
    if (!testSevenIsPassed)
    {
        printFailedTest(7, "testForCyclicPop");
        return false;
    }

    return true;
}

bool test(void)
{
    return testForPush() && testForCyclicPop();
}
