#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int* createTestArray(int sizeOfArray)
{
    int* array = (int*)malloc(sizeOfArray * 4);
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

void printArray(int* array, int sizeOfArray)
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

int sort(int* array, int sizeOfArray)
{
    if (sizeOfArray < 1)
    {
        return 0;
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
    return 1;
}

bool arraysAreEqual(int* array1, int* array2, int sizeOfArray)
{
    if (sizeof(array1) != sizeof(array2))
    {
        return false;
    }
    for (int i = 0; i < sizeOfArray; ++i)
    {
        if (array1[i] != array2[i])
        {
            return false;
        }
    }
    return true;
}

bool arrayIsSorted(int* array, int sizeOfArray, int firstElement)
{
    bool firstElementIsReached = false;
    for (int i = 0; i < sizeOfArray; ++i)
    {
        if (firstElementIsReached && array[i] < firstElement)
        {
            free(array);
            return false;
        }
        if (array[i] >= firstElement)
        {
            firstElementIsReached = true;
        }
    }
    free(array);
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

bool testFourIsPassed(int sizeOfArray)
{
    int* array = createTestArray(sizeOfArray);
    int firstElement = array[0];
    sort(array, sizeOfArray);
    return arrayIsSorted(array, sizeOfArray, firstElement);
}

bool allTestsArePassed()
{
    return testOneIsPassed() && testTwoIsPassed() && testThreeIsPassed() && testFourIsPassed(100000);
}

int main()
{
    if (!(allTestsArePassed()))
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
    printArray(testArray, sizeOfArray);

    printf("\n\nSorting...\n");
    sort(testArray, sizeOfArray);
    printArray(testArray, sizeOfArray);
    free(testArray);
}