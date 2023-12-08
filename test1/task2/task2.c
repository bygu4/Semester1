#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void scanArray(int* array, const int sizeOfArray)
{
    for (int i = 0; i < sizeOfArray; ++i)
    {
        scanf_s("%d", &array[i]);
    }
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

void bubbleSort(int* array, const int sizeOfArray)
{
    for (int i = 0; i < sizeOfArray - 1; i += 2)
    {
        for (int j = 2; j < sizeOfArray; j += 2)
        {
            if (array[j - 2] > array[j])
            {
                swap(&array[j - 2], &array[j]);
            }
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

bool testOneIsPassed()
{
    int array[10] = { 1, 10, 2, 9, 3, 8, 4, 7, 5, 6 };
    int expectedArray[10] = { 1, 10, 2, 9, 3, 8, 4, 7, 5, 6 };
    bubbleSort(array, 10);
    return arraysAreEqual(array, expectedArray, 10);
}

bool testTwoIsPassed()
{
    int array[] = { 0 };
    int expectedArray[] = { 0 };
    bubbleSort(array, 0);
    return arraysAreEqual(array, expectedArray, 0);
}

bool testThreeIsPassed()
{
    int array[10] = { 10, 1, 9, 2, 8, 3, 7, 4, 6, 5 };
    int expectedArray[10] = { 6, 1, 7, 2, 8, 3, 9, 4, 10, 5 };
    bubbleSort(array, 10);
    return arraysAreEqual(array, expectedArray, 10);
}

bool allTestsArePassed()
{
    return testOneIsPassed() && testTwoIsPassed() && testThreeIsPassed();
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
    printf("Enter an array: ");
    scanArray(inputArray, sizeOfArray);

    bubbleSort(inputArray, sizeOfArray);

    printArray(inputArray, sizeOfArray);
    free(inputArray);
}