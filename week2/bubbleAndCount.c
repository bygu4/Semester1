#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define AMOUNT_OF_POSSIBLE_NUMBERS 64001

void scanArray(short int* array, const int sizeOfArray)
{
    for (int i = 0; i < sizeOfArray; ++i)
    {
        scanf_s("%hd", &array[i]);
    }
}

void swap(short int* number1, short int* number2)
{
    short int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

void bubbleSort(short int* array, const int sizeOfArray)
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

int countSort(short int* array, const int sizeOfArray)
{
    int* arrayOfPossibleNumbers = (int*)calloc(AMOUNT_OF_POSSIBLE_NUMBERS, sizeof(int));
    if (arrayOfPossibleNumbers == NULL)
    {
        return 1;
    }
    for (int i = 0; i < sizeOfArray; ++i)
    {
        short int numberFromOriginalArray = array[i];
        ++arrayOfPossibleNumbers[numberFromOriginalArray + 32000];
    }

    int count = 0;
    short int numberForSortedArray = -32000;
    while (count < sizeOfArray && numberForSortedArray + 32000 < AMOUNT_OF_POSSIBLE_NUMBERS)
    {
        int amountOfNumbers = arrayOfPossibleNumbers[numberForSortedArray + 32000];
        for (int i = 0; i < amountOfNumbers; ++i)
        {
            array[count] = numberForSortedArray;
            ++count;
        }
        ++numberForSortedArray;
    }
    free(arrayOfPossibleNumbers);
    return 0;
}

int createTestArray(short int* array, const int sizeOfArray)
{
    if (array == NULL)
    {
        return 1;
    }
    for (int i = 0; i < sizeOfArray; ++i)
    {
        array[i] = rand() % AMOUNT_OF_POSSIBLE_NUMBERS - 32000;
    }
    return 0;
}

bool arraysAreEqual(const short int* array1, const short int* array2, const int sizeOfArray)
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

bool arrayIsSorted(const short int* array, const int sizeOfArray)
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

bool firstTestIsPassed()
{
    short int array[10] = { 32000, 0, 99, -100, 43, 1, -1, -32000, 0, 100 };
    short int expectedArray[10] = { -32000, -100, -1, 0, 0, 1, 43, 99, 100, 32000 };
    bubbleSort(array, 10);
    return arraysAreEqual(array, expectedArray, 10);
}

bool secondTestIsPassed()
{
    short int array[10] = { 32000, 0, 99, -100, 43, 1, -1, -32000, 0, 100 };
    short int expectedArray[10] = { -32000, -100, -1, 0, 0, 1, 43, 99, 100, 32000 };
    countSort(array, 10);
    return arraysAreEqual(array, expectedArray, 10);
}

bool thirdTestIsPassed()
{
    short int array[] = { NULL };
    short int expectedArray[] = { NULL };
    bubbleSort(array, 0);
    return arraysAreEqual(array, expectedArray, 0);
}

bool fourthTestIsPassed()
{
    short int array[] = { NULL };
    short int expectedArray[] = { NULL };
    countSort(array, 0);
    return arraysAreEqual(array, expectedArray, 0);
}

bool fifthTestIsPassed(const int sizeOfArray)
{
    short int* array = (short int*)calloc(sizeOfArray, sizeof(short int));
    int errorCode = createTestArray(array, sizeOfArray);
    if (errorCode != 0)
    {
        return false;
    }
    bubbleSort(array, sizeOfArray);
    bool sorted = arrayIsSorted(array, sizeOfArray);
    free(array);
    return sorted;
}

bool sixthTestIsPassed(const int sizeOfArray)
{
    short int* array = (short int*)calloc(sizeOfArray, sizeof(short int));
    int errorCode = createTestArray(array, sizeOfArray);
    if (errorCode != 0)
    {
        return false;
    }
    errorCode = countSort(array, sizeOfArray);
    bool sorted = arrayIsSorted(array, sizeOfArray);
    free(array);
    return sorted && errorCode == 0;
}

bool allTestsArePassed()
{
    return firstTestIsPassed() && secondTestIsPassed() && thirdTestIsPassed() &&
        fourthTestIsPassed() && fifthTestIsPassed(10000) && sixthTestIsPassed(10000);
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
    short int* inputArray = (short int*)calloc(sizeOfArray, sizeof(short int));
    if (inputArray == NULL)
    {
        printf("An error occured");
        return -1;
    }
    printf("Enter an array of numbers (-32000 <= n <= 32000): ");
    scanArray(inputArray, sizeOfArray);

    printf("Sorting...\n");
    countSort(inputArray, sizeOfArray);

    printf("Your array sorted:");
    for (int i = 0; i < sizeOfArray; ++i)
    {
        printf(" %hd", inputArray[i]);
    }
    free(inputArray);

    printf("\n\nTesting runtime...\n");
    short int* testArray1 = (short int*)calloc(100000, sizeof(short int));
    int errorCode = createTestArray(testArray1, 100000);
    if (errorCode != 0)
    {
        printf("An error occured");
        return -1;
    }
    double startTime = (double)clock() / CLOCKS_PER_SEC;
    bubbleSort(testArray1, 100000);
    double endTime = (double)clock() / CLOCKS_PER_SEC;
    printf("Bubble sort was completed in %g seconds\n", endTime - startTime);
    free(testArray1);

    short int* testArray2 = (short int*)calloc(100000, sizeof(short int));
    errorCode = createTestArray(testArray2, 100000);
    if (errorCode != 0)
    {
        printf("An error occured");
        return -1;
    }
    startTime = (double)clock() / CLOCKS_PER_SEC;
    errorCode = countSort(testArray2, 100000);
    endTime = (double)clock() / CLOCKS_PER_SEC;
    if (errorCode != 0)
    {
        printf("An error occured");
        return -1;
    }
    printf("Count sort was completed in %g seconds", endTime - startTime);
    free(testArray2);
}