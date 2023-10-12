#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int* createTestArray(const int sizeOfArray)
{
    int* array = (int*)calloc(sizeOfArray, sizeof(int));
    if (array == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < sizeOfArray; ++i)
    {
        array[i] = rand() % 1000;
    }
    return array;
}

void printArray(const int* array, const int sizeOfArray)
{
    for (int i = 0; i < sizeOfArray; ++i)
    {
        printf("%d ", array[i]);
    }
}

void swap(int* number1, int* number2)
{
    int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

void sort(int* array, const int sizeOfArray)
{
    if (sizeOfArray <= 1)
    {
        return;
    }
    int firstElement = array[0];
    int count = 0;
    for (int i = 1; i < sizeOfArray; ++i)
    {
        if (array[i] < firstElement)
        {
            swap(&array[count], &array[i]);
            ++count;
        }
    }
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

bool arrayIsSorted(const int* array, const int sizeOfArray, const int firstElement)
{
    bool firstElementIsReached = false;
    for (int i = 0; i < sizeOfArray; ++i)
    {
        if (firstElementIsReached && array[i] < firstElement)
        {
            return false;
        }
        if (array[i] >= firstElement)
        {
            firstElementIsReached = true;
        }
    }
    return true;
}

bool testOneIsPassed()
{
    int array[10] = { 14, 0, 0, 99, 355, 64, 8, 2, 1, -1 };
    int expectedArray[10] = { 0, 0, 8, 2, 1, -1, 14, 99, 355, 64 };
    sort(array, 10);
    return arraysAreEqual(array, expectedArray, 10);
}

bool testTwoIsPassed()
{
    int array[] = { NULL };
    int expectedArray[] = { NULL };
    sort(array, 0);
    return arraysAreEqual(array, expectedArray, 0);
}

bool testThreeIsPassed()
{
    int array[10] = { 42, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int expectedArray[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 42 };
    sort(array, 10);
    return arraysAreEqual(array, expectedArray, 10);
}

bool testFourIsPassed(const int sizeOfArray)
{
    int* array = createTestArray(sizeOfArray);
    if (array == NULL)
    {
        return false;
    }
    int firstElement = array[0];
    sort(array, sizeOfArray);
    bool sorted = arrayIsSorted(array, sizeOfArray, firstElement);
    free(array);
    return sorted;
}

bool allTestsArePassed()
{
    return testOneIsPassed() && testTwoIsPassed() && testThreeIsPassed() && testFourIsPassed(100000);
}

int main()
{
    if (!allTestsArePassed())
    {
        printf("An error occured");
        return -1;
    }
    int sizeOfArray = -1;
    while (sizeOfArray < 0)
    {
        printf("Enter a size of array: ");
        scanf_s("%d", &sizeOfArray);
    }
    printf("Creating array...\n");
    int* testArray = createTestArray(sizeOfArray);
    if (testArray == NULL)
    {
        printf("An error occured");
        return -1;
    }
    printArray(testArray, sizeOfArray);

    printf("\n\nSorting...\n");
    sort(testArray, sizeOfArray);
    printArray(testArray, sizeOfArray);
    free(testArray);
}