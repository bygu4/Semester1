#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

void scanArray(int* array, const int sizeOfArray)
{
    for (int i = 0; i < sizeOfArray; ++i)
    {
        scanf_s("%d", &array[i]);
    }
}

void swap(int* number1, int* number2)
{
    int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

void insertionSort(int* array, const int start, const int end)
{
    for (int i = start + 1; i < end; ++i)
    {
        int j = i;
        while (array[j - 1] > array[j] && j > start)
        {
            swap(&array[j - 1], &array[j]);
            --j;
        }
    }
}

int partition(int* array, const int start, const int end, bool* isSorted)
{
    int pointer = start + 1;
    while (array[pointer - 1] == array[pointer] && pointer < end - 1)
    {
        ++pointer;
    }
    if (array[pointer - 1] > array[pointer])
    {
        *isSorted = false;
        --pointer;
    }
    int pivot = array[pointer];

    for (int i = pointer; i < end; ++i)
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

int quicksort(int* array, const int start, const int end)
{
    int sizeOfArray = end - start;
    if (sizeOfArray < 10)
    {
        insertionSort(array, start, end);
        return 0;
    }

    bool isSorted = true;
    int pointer = partition(array, start, end, &isSorted);
    if (pointer >= end)
    {
        return 1;
    }
    if (isSorted)
    {
        return 0;
    }
    int errorCode1 = quicksort(array, start, pointer);
    int errorCode2 = quicksort(array, pointer, end);
    return errorCode1 + errorCode2;
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

int createTestArray(int* array, const int sizeOfArray)
{
    if (array == NULL)
    {
        return 1;
    }
    for (int i = 0; i < sizeOfArray; ++i)
    {
        array[i] = rand() % 2000 - 1000;
    }
    return 0;
}

bool testOneIsPassed()
{
    int array1[4] = { 1, 2, 3, 4 };
    int array2[4] = { 1, 2, 3, 5 };
    return !arraysAreEqual(array1, array2, 4);
}

bool testTwoIsPassed()
{
    int array1[6] = { 5, 6, 7, 8, 9, 10 };
    int array2[6] = { 5, 6, 7, 8 ,9, 10 };
    return arraysAreEqual(array1, array2, 6);
}

bool testThreeIsPassed()
{
    int array[6] = { 1, 1, 1, 2, 3, 4 };
    return arrayIsSorted(array, 6);
}

bool testFourIsPassed()
{
    int array[6] = { 1, 3, 2, 2, 3, 4 };
    return !arrayIsSorted(array, 6);
}

bool testFiveIsPassed()
{
    int array[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    int expectedArray[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    insertionSort(array, 0, 10);
    return arraysAreEqual(array, expectedArray, 10);
}

bool testSixIsPassed()
{
    int array[] = { NULL };
    int expectedArray[] = { NULL };
    insertionSort(array, 0, 0);
    return arraysAreEqual(array, expectedArray, 0);
}

bool testSevenIsPassed()
{
    int array[10] = { 5, 6, 1, 2, 3, 4, 7, 8, 9, 10 };
    int expectedArray[10] = { 5, 1, 2, 3, 4, 6, 7, 8, 9, 10 };
    bool isSorted = true;
    int pointer = partition(array, 0, 10, &isSorted);
    return !isSorted && pointer == 5 && arraysAreEqual(array, expectedArray, 10);
}

bool testEightIsPassed()
{
    int array[5] = { 1, 1, 1, 1, 1 };
    int expectedArray[5] = { 1, 1, 1, 1, 1 };
    bool isSorted = true;
    int pointer = partition(array, 0, 5, &isSorted);
    return isSorted && pointer == 4 && arraysAreEqual(array, expectedArray, 5);
}

bool testNineIsPassed()
{
    int array[12] = { 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    int expectedArray[12] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    int errorCode = quicksort(array, 0, 12);
    return errorCode == 0 && arraysAreEqual(array, expectedArray, 12);
}

bool testTenIsPassed()
{
    int array[12] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int expectedArray[12] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    int errorCode = quicksort(array, 0, 12);
    return errorCode == 0 && arraysAreEqual(array, expectedArray, 12);
}

bool testElevenIsPassed()
{
    int array[] = { NULL };
    int expectedArray[] = { NULL };
    int errorCode = quicksort(array, 0, 0);
    return errorCode == 0 && arraysAreEqual(array, expectedArray, 0);
}

bool testTwelveIsPassed(const int sizeOfArray)
{
    int* array = (int*)calloc(sizeOfArray, sizeof(int));
    int errorCode = createTestArray(array, sizeOfArray);
    if (errorCode != 0)
    {
        return false;
    }
    errorCode = quicksort(array, 0, sizeOfArray);
    bool sorted = arrayIsSorted(array, sizeOfArray);
    free(array);
    return errorCode == 0 && sorted;
}

bool allTestsArePassed()
{
    return testOneIsPassed() && testTwoIsPassed() && testThreeIsPassed() && testFourIsPassed()
        && testFiveIsPassed() && testSixIsPassed() && testSevenIsPassed() && testEightIsPassed()
        && testNineIsPassed() && testTenIsPassed() && testElevenIsPassed() && testTwelveIsPassed(10000);
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
    int* inputArray = (int*)calloc(sizeOfArray, sizeof(int));
    if (inputArray == NULL)
    {
        printf("An error occured");
        return -1;
    }
    printf("Enter an array: ");
    scanArray(inputArray, sizeOfArray);

    printf("\nSorting...\n\n");
    int errorCode = quicksort(inputArray, 0, sizeOfArray);
    if (errorCode != 0)
    {
        printf("An error occured");
        return -1;
    }

    printf("Sorted array:");
    for (int i = 0; i < sizeOfArray; ++i)
    {
        printf(" %d", inputArray[i]);
    }
    free(inputArray);
}