#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int generateArray(int* array, const int sizeOfArray)
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
    const int sizeOfArray = end - start;
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

bool search(const int* array, const int sizeOfArray, const int numberToFind)
{
    int leftBorder = 0;
    int rightBorder = sizeOfArray;
    while (rightBorder > leftBorder)
    {
        int medianIndex = (leftBorder + rightBorder) / 2;
        int medianNumber = array[medianIndex];
        if (medianNumber == numberToFind)
        {
            return true;
        }
        if (medianNumber > numberToFind)
        {
            rightBorder = medianIndex;
        }
        if (medianNumber < numberToFind)
        {
            leftBorder = medianIndex + 1;
        }
    }
    return false;
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
    int array2[6] = { 1, 2, 3, 4, 5, 0 };
    return !arraysAreEqual(array1, array2, 6);
}

bool testTwoIsPassed()
{
    int array[6] = { 1, 1, 1, 2, 2, 2 };
    return arrayIsSorted(array, 6);
}

bool testThreeIsPassed()
{
    int array[6] = { 9, 8, 7, 6, 1, 2 };
    return !arrayIsSorted(array, 6);
}

bool testFourIsPassed()
{
    int array[8] = { 5, 6, 1, 2, 3, 4, 7, 8 };
    int expectedArray[8] = { 5, 1, 2, 3, 4, 6, 7, 8 };
    bool isSorted = true;
    int pointer = partition(array, 0, 8, &isSorted);
    return arraysAreEqual(array, expectedArray, 8) && pointer == 5 && !isSorted;
}

bool testFiveIsPassed()
{
    int array[5] = { 1, 1, 1, 1, 1 };
    int expectedArray[5] = { 1, 1, 1, 1, 1 };
    bool isSorted = true;
    int pointer = partition(array, 0, 5, &isSorted);
    return arraysAreEqual(array, expectedArray, 5) && pointer == 4 && !isSorted;
}

bool testSixIsPassed()
{
    int array[10] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    int expectedArray[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int errorCode = quicksort(array, 0, 10);
    return errorCode == 0 && arraysAreEqual(array, expectedArray, 10);
}

bool testSevenIsPassed()
{
    int array[] = { NULL };
    int expectedArray[] = { NULL };
    int errorCode = quicksort(array, 0, 0);
    return errorCode == 0 && arraysAreEqual(array, expectedArray, 0);
}

bool testEightIsPassed()
{
    int array[6] = { 2, 2, 2, 2, 2, 2 };
    int expectedArray[6] = { 2, 2, 2, 2, 2, 2 };
    int errorCode = quicksort(array, 0, 6);
    return errorCode == 0 && arraysAreEqual(array, expectedArray, 6);
}

bool testNineIsPassed(const int sizeOfArray)
{
    int* array = (int*)calloc(sizeOfArray, sizeof(int));
    int errorCode = generateArray(array, sizeOfArray);
    if (errorCode != 0)
    {
        return false;
    }
    errorCode = quicksort(array, 0, sizeOfArray);
    bool sorted = arrayIsSorted(array, sizeOfArray);
    free(array);
    return sorted && errorCode == 0;
}

bool testTenIsPassed()
{
    int array[7] = { 0, 0, 0, 0, 0, 0, 1 };
    return search(array, 7, 1);
}

bool testElevenIsPassed()
{
    int array[5] = { 9, 9, 9, 9, 9 };
    return !search(array, 5, 10);
}

bool testTwelveIsPassed()
{
    int array[8] = { 1, 1, 2, 2, 3, 3, 4, 4 };
    return search(array, 8, 1);
}

bool allTestsArePassed()
{
    return testOneIsPassed() && testTwoIsPassed() && testThreeIsPassed() && testFourIsPassed &&
        testFiveIsPassed && testSixIsPassed() && testSevenIsPassed() && testEightIsPassed() &&
        testNineIsPassed(10000) && testTenIsPassed() && testElevenIsPassed() && testTwelveIsPassed();
}

int main()
{
    if (!allTestsArePassed())
    {
        printf("An error occured");
        return -1;
    }

    int sizeOfArray = 0;
    printf("Enter a size of array n: ");
    scanf_s("%d", &sizeOfArray);
    int* generatedArray = (int*)calloc(sizeOfArray, sizeof(int));
    int  errorCode = generateArray(generatedArray, sizeOfArray);
    if (errorCode != 0)
    {
        printf("An error occured");
        return -1;
    }
    printArray(generatedArray, sizeOfArray);
    printf("\n\n");

    int amountOfNumbers = 0;
    printf("Enter an amount of numbers k: ");
    scanf_s("%d", &amountOfNumbers);

    errorCode = quicksort(generatedArray, 0, sizeOfArray);
    if (errorCode != 0)
    {
        printf("An error occured");
        return -1;
    }

    for (int i = 0; i < amountOfNumbers; ++i)
    {
        int number = rand() % 2000 - 1000;
        bool numberIsInArray = search(generatedArray, sizeOfArray, number);
        printf(numberIsInArray ? "!!! Number %d is in array !!!\n" : "Number %d is not in array\n", number);
    }
    free(generatedArray);
}