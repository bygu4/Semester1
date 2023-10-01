#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int* generateArray(const int sizeOfArray)
{
    int* array = (int*)calloc(sizeOfArray, sizeof(int));
    if (array == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < sizeOfArray; ++i)
    {
        array[i] = rand() % 2000 - 1000;
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

bool allTestsForPartitionArePassed()
{
    int array1[10] = { 5, 6, 1, 2, 3, 4, 7, 8, 9, 10 };
    int expectedArray1[10] = { 5, 1, 2, 3, 4, 6, 7, 8, 9, 10 };
    bool isSorted = true;
    int pointer = partition(array1, 0, 10, &isSorted);
    bool testOneIsPassed = pointer == 5 && !isSorted && arraysAreEqual(array1, expectedArray1, 10);

    int array2[5] = { 1, 1, 1, 1, 1 };
    int expectedArray2[5] = { 1, 1, 1, 1, 1 };
    isSorted = true;
    pointer = partition(array2, 0, 5, &isSorted);
    bool testTwoIsPassed = pointer == 4 && isSorted && arraysAreEqual(array2, expectedArray2, 5);

    int array3[5] = { 15, 0, 0, 0, 0 };
    int expectedArray3[5] = { 0, 0, 0, 0, 15 };
    isSorted = true;
    pointer = partition(array3, 0, 5, &isSorted);
    bool testThreeIsPassed = pointer == 4 && !isSorted && arraysAreEqual(array3, expectedArray3, 5);

    return testOneIsPassed && testTwoIsPassed && testThreeIsPassed;
}

bool testForQuicksort(int* array, const int* expectedArray, const int sizeOfArray)
{
    int errorCode = quicksort(array, 0, sizeOfArray);
    return errorCode == 0 && arraysAreEqual(array, expectedArray, sizeOfArray);
}

bool allTestsForQuicksortArePassed()
{
    int array1[20] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10 };
    int expectedArray1[20] = { -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6 ,7, 8, 9 };
    bool testOneIsPassed = testForQuicksort(array1, expectedArray1, 20);

    int array2[] = { 0 };
    int expectedArray2[] = { 0 };
    bool testTwoIsPassed = testForQuicksort(array2, expectedArray2, 0);

    int array3[10] = { 2, 2, 2, 2, 2, 4, 4, 4, 4, 4 };
    int expectedArray3[10] = { 2, 2, 2, 2, 2, 4, 4, 4, 4, 4 };
    bool testThreeIsPassed = testForQuicksort(array3, expectedArray3, 10);

    int sizeOfTestArray = 10000;
    int* testArray = generateArray(sizeOfTestArray);
    if (testArray == NULL)
    {
        return false;
    }
    int errorCode = quicksort(testArray, 0, sizeOfTestArray);
    bool testFourIsPassed = errorCode == 0 && arrayIsSorted(testArray, sizeOfTestArray);
    free(testArray);

    return testOneIsPassed && testTwoIsPassed && testThreeIsPassed && testFourIsPassed;
}

bool allTestsForSearchArePassed()
{
    int array1[7] = { 0, 0, 0, 0, 0, 0, 1 };
    bool testOneIsPassed = search(array1, 7, 1);

    int array2[5] = { 9, 9, 9, 9, 9 };
    bool testTwoIsPassed = !search(array2, 5, 10);

    int array3[8] = { 1, 1, 2, 2, 3, 3, 4, 4 };
    bool testThreeIsPassed = search(array3, 8, 1);

    int array4[] = { 0 };
    bool testFourIsPassed = !search(array4, 0, 42);

    return testOneIsPassed && testTwoIsPassed && testThreeIsPassed && testFourIsPassed;
}

bool allTestsArePassed()
{
    return allTestsForPartitionArePassed() && allTestsForQuicksortArePassed()
        && allTestsForSearchArePassed();
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
    int* generatedArray = generateArray(sizeOfArray);
    if (generatedArray == NULL)
    {
        printf("\nAn error occured");
        return -1;
    }
    printArray(generatedArray, sizeOfArray);
    printf("\n\n");

    int amountOfNumbers = 0;
    printf("Enter an amount of numbers k: ");
    scanf_s("%d", &amountOfNumbers);

    int errorCode = quicksort(generatedArray, 0, sizeOfArray);
    if (errorCode != 0)
    {
        printf("\nAn error occured");
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