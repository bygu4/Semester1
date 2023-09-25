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

int partition(int* array, const int start, const int end, bool* isSorted)
{
    int pointer = start + 1;
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
    if (sizeOfArray <= 1)
    {
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

int createTestArray(int* array, const int sizeOfArray)
{
    if (array == NULL)
    {
        return 1;
    }
    for (int i = 0; i < sizeOfArray; ++i)
    {
        array[i] = rand() % 20000 - 10000;
    }
    return 0;
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

bool testOneIsPassed()
{
    int array1[6] = { 1, 2, 3, 4, 5, 6 };
    int array2[6] = { 1, 2, 3, 4, 5, 5 };
    return !arraysAreEqual(array1, array2, 6);
}

bool testTwoIsPassed()
{
    int array1[6] = { 10, 9, 8, 7, 6, 5 };
    int array2[6] = { 10, 9, 8, 7, 6, 5 };
    return arraysAreEqual(array1, array2, 6);
}

bool testThreeIsPassed()
{
    int array[6] = { 1, 1, 1, 1, 1, 1 };
    return arrayIsSorted(array, 6);
}

bool testFourIsPassed()
{
    int array[9] = { 1, 2, 3, 1, 2, 3, 1, 2, 3 };
    return !arrayIsSorted(array, 9);
}

bool testFiveIsPassed()
{
    int array[10] = { 5, 6, 1, 2, 3, 4, 5, 6, 7, 8 };
    int expectedArray[10] = { 5, 1, 2, 3, 4, 5, 6, 6, 7, 8 };
    bool isSorted = true;
    int pointer = partition(array, 0, 10, &isSorted);
    return pointer == 6 && !isSorted && arraysAreEqual(array, expectedArray, 10);
}

bool testSixIsPassed()
{
    int array[5] = { 1, 1, 1, 1, 1 };
    int expectedArray[5] = { 1, 1, 1, 1, 1 };
    bool isSorted = true;
    int pointer = partition(array, 0, 5, &isSorted);
    return pointer == 4 && isSorted && arraysAreEqual(array, expectedArray, 5);
}

bool testSevenIsPassed()
{
    int array[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    int expectedArray[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int errorCode = quicksort(array, 0, 10);
    return errorCode == 0 && arraysAreEqual(array, expectedArray, 10);
}

bool testEightIsPassed()
{
    int array[5] = { 8, 8, 8, 8, 8 };
    int expectedArray[5] = { 8, 8, 8, 8, 8 };
    int errorCode = quicksort(array, 0, 5);
    return errorCode == 0 && arraysAreEqual(array, expectedArray, 5);
}

bool testNineIsPassed()
{
    int array[] = { NULL };
    int expectedArray[] = { NULL };
    int errorCode = quicksort(array, 0, 0);
    return errorCode == 0 && arraysAreEqual(array, expectedArray, 0);
}

bool testTenIsPassed(const int sizeOfArray)
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

bool testElevenIsPassed()
{
    int array[5] = { 2, 2, 2, 2, 2 };
    int mostCommonElement = findMostCommonElement(array, 5);
    return mostCommonElement == 2;
}

bool testTwelveIsPassed()
{
    int array[6] = { 1, 2, 3, 4, 5, 6 };
    int mostCommonElement = findMostCommonElement(array, 6);
    return mostCommonElement == 1;
}

bool testThirteenIsPassed()
{
    int array[] = { NULL };
    int mostCommonElement = findMostCommonElement(array, 0);
    return mostCommonElement == NULL;
}

bool testFourteenIsPassed()
{
    int array[7] = { 1, 1, 1, -1, -1, -1, -1 };
    int mostCommonElement = findMostCommonElement(array, 7);
    return mostCommonElement == -1;
}

bool allTestsArePassed()
{
    return testOneIsPassed() && testTwoIsPassed() && testThreeIsPassed() && testFourIsPassed()
        && testFiveIsPassed() && testSixIsPassed() && testSevenIsPassed() && testEightIsPassed()
        && testNineIsPassed() && testTenIsPassed(10000) && testElevenIsPassed()
        && testTwelveIsPassed() && testThirteenIsPassed() && testFourteenIsPassed();
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