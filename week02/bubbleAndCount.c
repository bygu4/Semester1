#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define SIZE_OF_TEST_ARRAY 100000
#define MAX_NUMBER 2147483647
#define MIN_NUMBER -2147483647 - 1
#define AMOUNT_OF_POSSIBLE_NUMBERS 4294967296

void scanArray(int* array, const int sizeOfArray)
{
    for (int i = 0; i < sizeOfArray; ++i)
    {
        scanf_s("%d", &array[i]);
    }
}

void swap(int* number1, int* number2)
{
    short int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

void bubbleSort(int* array, const int sizeOfArray)
{
    for (int i = 0; i < sizeOfArray - 1; ++i)
    {
        for (int j = 1; j < sizeOfArray; ++j)
        {
            if (array[j - 1] > array[j])
            {
                swap(&array[j - 1], &array[j]);
            }
        }
    }
}

int countSort(int* array, const int sizeOfArray)
{
    int minNumber = MAX_NUMBER;
    int maxNumber = MIN_NUMBER;
    for (int i = 0; i < sizeOfArray; ++i)
    {
        int number = array[i];
        minNumber = min(minNumber, number);
        maxNumber = max(maxNumber, number);
    }
    int sizeOfSupportingArray = maxNumber - minNumber + 1;
    int* supportingArray = (int*)calloc(sizeOfSupportingArray, sizeof(int));
    if (supportingArray == NULL)
    {
        return 1;
    }
    int indexDifference = minNumber;

    for (int i = 0; i < sizeOfArray; ++i)
    {
        int numberFromOriginalArray = array[i];
        ++supportingArray[numberFromOriginalArray - indexDifference];
    }

    int numberForSortedArray = minNumber;
    int count = 0;
    while (numberForSortedArray <= maxNumber && count < sizeOfArray)
    {
        int amountOfNumbers = supportingArray[numberForSortedArray - indexDifference];
        for (int i = 0; i < amountOfNumbers; ++i)
        {
            array[count] = numberForSortedArray;
            ++count;
        }
        ++numberForSortedArray;
    }
    free(supportingArray);
    return 0;
}

int* createTestArray(const int sizeOfArray)
{
    int* testArray = (int*)calloc(sizeOfArray, sizeof(int));
    if (testArray == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < sizeOfArray; ++i)
    {
        testArray[i] = rand() % AMOUNT_OF_POSSIBLE_NUMBERS + MIN_NUMBER;
    }
    return testArray;
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

bool testForBubbleSort(int* array, const int* expectedArray, const int sizeOfArray)
{
    bubbleSort(array, sizeOfArray);
    return arraysAreEqual(array, expectedArray, sizeOfArray);
}

bool testForCountSort(int* array, const int* expectedArray, const int sizeOfArray)
{
    int errorCode = countSort(array, sizeOfArray);
    return errorCode == 0 && arraysAreEqual(array, expectedArray, sizeOfArray);
}

bool allTestsForBubbleSortArePassed()
{
    int array1[20] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10 };
    int expectedArray1[20] = { -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    bool testOneIsPassed = testForBubbleSort(array1, expectedArray1, 20);

    int array2[10] = { 2, 2, 2, 2, 2, 4, 4, 4, 4, 4 };
    int expectedArray2[10] = { 2, 2, 2, 2, 2, 4, 4, 4, 4, 4 };
    bool testTwoIsPassed = testForBubbleSort(array2, expectedArray2, 10);

    int array3[] = { 0 };
    int expectedArray3[] = { 0 };
    bool testThreeIsPassed = testForBubbleSort(array3, expectedArray3, 0);

    int sizeOfTestArray = 10000;
    int* testArray = createTestArray(sizeOfTestArray);
    if (testArray == NULL)
    {
        return false;
    }
    bubbleSort(testArray, sizeOfTestArray);
    bool testFourIsPassed = arrayIsSorted(testArray, sizeOfTestArray);
    free(testArray);

    return testOneIsPassed && testTwoIsPassed && testThreeIsPassed && testFourIsPassed;
}

bool allTestsForCountSortArePassed()
{
    int array1[20] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10 };
    int expectedArray1[20] = { -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    bool testOneIsPassed = testForCountSort(array1, expectedArray1, 20);

    int array2[10] = { 2, 2, 2, 2, 2, 4, 4, 4, 4, 4 };
    int expectedArray2[10] = { 2, 2, 2, 2, 2, 4, 4, 4, 4, 4 };
    bool testTwoIsPassed = testForCountSort(array2, expectedArray2, 10);

    int array3[] = { 0 };
    int expectedArray3[] = { 0 };
    bool testThreeIsPassed = testForCountSort(array3, expectedArray3, 0);

    int sizeOfTestArray = 10000;
    int* testArray = createTestArray(sizeOfTestArray);
    if (testArray == NULL)
    {
        return false;
    }
    int errorCode = countSort(testArray, sizeOfTestArray);
    bool testFourIsPassed = errorCode == 0 && arrayIsSorted(testArray, sizeOfTestArray);
    free(testArray);

    return testOneIsPassed && testTwoIsPassed && testThreeIsPassed && testFourIsPassed;
}

bool allTestsArePassed()
{
    return allTestsForBubbleSortArePassed() && allTestsForCountSortArePassed();
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
        printf("\nAn error occured");
        return -1;
    }
    printf("Enter an array of numbers: ");
    scanArray(inputArray, sizeOfArray);

    printf("Sorting...\n");
    countSort(inputArray, sizeOfArray);

    printf("Your array sorted:");
    for (int i = 0; i < sizeOfArray; ++i)
    {
        printf(" %d", inputArray[i]);
    }
    free(inputArray);

    printf("\n\nTesting runtime...\n");
    int* testArray1 = createTestArray(SIZE_OF_TEST_ARRAY);
    if (testArray1 == NULL)
    {
        printf("\nAn error occured");
        return -1;
    }
    double startTime = (double)clock() / CLOCKS_PER_SEC;
    bubbleSort(testArray1, SIZE_OF_TEST_ARRAY);
    double endTime = (double)clock() / CLOCKS_PER_SEC;
    printf("Bubble sort was completed in %g seconds\n", endTime - startTime);
    free(testArray1);

    int* testArray2 = createTestArray(SIZE_OF_TEST_ARRAY);
    if (testArray2 == NULL)
    {
        printf("\nAn error occured");
        return -1;
    }
    startTime = (double)clock() / CLOCKS_PER_SEC;
    int errorCode = countSort(testArray2, SIZE_OF_TEST_ARRAY);
    endTime = (double)clock() / CLOCKS_PER_SEC;
    if (errorCode != 0)
    {
        printf("\nAn error occured");
        return -1;
    }
    printf("Count sort was completed in %g seconds", endTime - startTime);
    free(testArray2);
}