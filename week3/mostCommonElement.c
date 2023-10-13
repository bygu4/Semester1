#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define TEST_FAILED -1
#define BAD_ALLOCATION 1
#define RAND_RANGE 20000

void scanArray(int* const array, const size_t sizeOfArray)
{
    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        scanf_s("%d", &array[i]);
    }
}

void swap(int* const number1, int* const number2)
{
    int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

size_t partition(int* const array, const size_t start, const size_t end, bool* const isSorted)
{
    size_t pointer = start + 1;
    while (array[pointer - 1] == array[pointer] && pointer + 1 < end)
    {
        ++pointer;
    }
    if (array[pointer - 1] > array[pointer])
    {
        *isSorted = false;
        --pointer;
    }
    int pivot = array[pointer];

    for (size_t i = pointer; i < end; ++i)
    {
        if (array[i] < pivot)
        {
            swap(&array[i], &array[pointer]);
            *isSorted = false;
            ++pointer;
        }
        if (isSorted && array[i - 1] > array[i])
        {
            *isSorted = false;
        }
    }
    return pointer;
}

void quicksort(int* const array, const size_t start, const size_t end)
{
    const size_t sizeOfArray = end - start;
    if (sizeOfArray <= 1)
    {
        return;
    }

    bool isSorted = true;
    size_t pointer = partition(array, start, end, &isSorted);

    if (isSorted)
    {
        return;
    }
    quicksort(array, start, pointer);
    quicksort(array, pointer, end);
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

bool testForPartition(int* const array, const int* const expectedArray,
    const size_t expectedPointer, const size_t sizeOfArray)
{
    bool isSorted = arrayIsSorted(array, sizeOfArray);
    bool isSortedResponse = true;
    size_t pointer = partition(array, 0, sizeOfArray, &isSortedResponse);
    return pointer == expectedPointer && isSorted == isSortedResponse &&
        arraysAreEqual(array, expectedArray, sizeOfArray);
}

bool testsForPartitionArePassed(int* const errorCode)
{
    int array1[10] = { 5, 6, 1, 2, 3, 4, 7, 8, 9, 10 };
    int expectedArray1[10] = { 5, 1, 2, 3, 4, 6, 7, 8, 9, 10 };
    bool testOneIsPassed = testForPartition(array1, expectedArray1, 5, 10);
    if (!testOneIsPassed)
    {
        *errorCode = 1;
        return false;
    }

    int array2[5] = { 1, 1, 1, 1, 1 };
    int expectedArray2[5] = { 1, 1, 1, 1, 1 };
    bool testTwoIsPassed = testForPartition(array2, expectedArray2, 4, 5);
    if (!testTwoIsPassed)
    {
        *errorCode = 2;
        return false;
    }

    int array3[5] = { 15, 0, 0, 0, 0 };
    int expectedArray3[5] = { 0, 0, 0, 0, 15 };
    bool testThreeIsPassed = testForPartition(array3, expectedArray3, 4, 5);
    if (!testThreeIsPassed)
    {
        *errorCode = 3;
        return false;
    }

    return true;
}

bool testForQuicksort(int* const array, const int* const expectedArray, const size_t sizeOfArray)
{
    quicksort(array, 0, sizeOfArray);
    return arraysAreEqual(array, expectedArray, sizeOfArray);
}

bool testsForQuicksortArePassed(int* const errorCode)
{
    int array1[20] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10 };
    int expectedArray1[20] = { -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6 ,7, 8, 9 };
    bool testOneIsPassed = testForQuicksort(array1, expectedArray1, 20);
    if (!testOneIsPassed)
    {
        *errorCode = 1;
        return false;
    }

    int array2[] = { 0 };
    int expectedArray2[] = { 0 };
    bool testTwoIsPassed = testForQuicksort(array2, expectedArray2, 0);
    if (!testTwoIsPassed)
    {
        *errorCode = 2;
        return false;
    }

    int array3[10] = { 2, 2, 2, 2, 2, 4, 4, 4, 4, 4 };
    int expectedArray3[10] = { 2, 2, 2, 2, 2, 4, 4, 4, 4, 4 };
    bool testThreeIsPassed = testForQuicksort(array3, expectedArray3, 10);
    if (!testThreeIsPassed)
    {
        *errorCode = 3;
        return false;
    }

    const size_t sizeOfTestArray = 10000;
    int* testArray = createTestArray(sizeOfTestArray);
    if (testArray == NULL)
    {
        *errorCode = 4;
        return false;
    }
    quicksort(testArray, 0, sizeOfTestArray);
    bool testFourIsPassed = arrayIsSorted(testArray, sizeOfTestArray);
    free(testArray);
    if (!testFourIsPassed)
    {
        *errorCode = 4;
        return false;
    }

    return true;
}

bool testForFindMostCommonElement(const int* const array, const size_t sizeOfArray, const int expectedOutput)
{
    int output = findMostCommonElement(array, sizeOfArray);
    return output == expectedOutput;
}

bool testsForFindMostCommonElementArePassed(int* const errorCode)
{
    int array1[5] = { 2, 2, 2, 2, 2 };
    bool testOneIsPassed = testForFindMostCommonElement(array1, 5, 2);
    if (!testOneIsPassed)
    {
        *errorCode = 1;
        return false;
    }

    int array2[6] = { 1, 2, 3, 4, 5, 6 };
    bool testTwoIsPassed = testForFindMostCommonElement(array2, 6, 1);
    if (!testTwoIsPassed)
    {
        *errorCode = 2;
        return false;
    }

    int array3[] = { 0 };
    bool testThreeIsPassed = testForFindMostCommonElement(array3, 0, 0);
    if (!testThreeIsPassed)
    {
        *errorCode = 3;
        return false;
    }

    int array4[7] = { -1, -1, -1, 3, 3, 3, 3 };
    bool testFourIsPassed = testForFindMostCommonElement(array4, 7, 3);
    if (!testFourIsPassed)
    {
        *errorCode = 4;
        return false;
    }

    return true;
}

bool test(void)
{
    int errorCode = 0;
    bool testOneIsPassed = testsForPartitionArePassed(&errorCode);
    if (!testOneIsPassed)
    {
        printf("Test %d has failed in test for partition", errorCode);
        return false;
    }

    bool testTwoIsPassed = testsForQuicksortArePassed(&errorCode);
    if (!testTwoIsPassed)
    {
        printf("Test %d has failed in test for quicksort", errorCode);
        return false;
    }

    bool testThreeIsPassed = testsForFindMostCommonElementArePassed(&errorCode);
    if (!testThreeIsPassed)
    {
        printf("Test %d has failed in test for findMostCommonElement", errorCode);
        return false;
    }

    return true;
}

int main(void)
{
    bool allTestsArePassed = test();
    if (!allTestsArePassed)
    {
        return TEST_FAILED;
    }

    int sizeOfArray = 0;
    printf("Enter a size of array: ");
    scanf_s("%d", &sizeOfArray);
    int* inputArray = (int*)calloc(sizeOfArray, sizeof(int));
    if (inputArray == NULL)
    {
        printf("An error occured");
        return BAD_ALLOCATION;
    }
    printf("Enter an array: ");
    scanArray(inputArray, sizeOfArray);

    quicksort(inputArray, 0, sizeOfArray);

    int mostCommonElement = findMostCommonElement(inputArray, sizeOfArray);
    printf("\nThe most common element in array: %d", mostCommonElement);
    free(inputArray);
}
