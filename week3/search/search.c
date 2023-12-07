#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define RAND_RANGE 2000
#define TEST_FAILED -1
#define SUCCESS 0
#define BAD_ALLOCATION 1

int* generateArray(const size_t sizeOfArray)
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

void printArray(const int* const array, const size_t sizeOfArray)
{
    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        printf("%d ", array[i]);
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

bool search(const int* const array, const size_t sizeOfArray, const int numberToFind)
{
    size_t leftBorder = 0;
    size_t rightBorder = sizeOfArray;
    while (rightBorder > leftBorder)
    {
        size_t medianIndex = (leftBorder + rightBorder) / 2;
        int medianNumber = array[medianIndex];
        if (medianNumber == numberToFind)
        {
            return true;
        }
        if (medianNumber > numberToFind)
        {
            rightBorder = medianIndex;
        }
        else
        {
            leftBorder = medianIndex + 1;
        }
    }
    return false;
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
    int* testArray = generateArray(sizeOfTestArray);
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

bool testsForSearchArePassed(int* const errorCode)
{
    int array1[7] = { 0, 0, 0, 0, 0, 0, 1 };
    bool testOneIsPassed = search(array1, 7, 1);
    if (!testOneIsPassed)
    {
        *errorCode = 1;
        return false;
    }

    int array2[5] = { 9, 9, 9, 9, 9 };
    bool testTwoIsPassed = !search(array2, 5, 10);
    if (!testTwoIsPassed)
    {
        *errorCode = 2;
        return false;
    }

    int array3[8] = { 1, 1, 2, 2, 3, 3, 4, 4 };
    bool testThreeIsPassed = search(array3, 8, 1);
    if (!testThreeIsPassed)
    {
        *errorCode = 3;
        return false;
    }

    int array4[] = { 0 };
    bool testFourIsPassed = !search(array4, 0, 42);
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

    bool testThreeIsPassed = testsForSearchArePassed(&errorCode);
    if (!testThreeIsPassed)
    {
        printf("Test %d has failed in testForSearch", errorCode);
        return false;
    }

    return true;
}

static bool stringsAreEqual(const char* const string1, const char* const string2)
{
    for (size_t i = 0; string1[i] != '\0' || string2[i] != '\0'; ++i)
    {
        if (string1[i] != string2[i])
        {
            return false;
        }
    }
    return true;
}

int main(const unsigned int argc, const char* const argv[])
{
    const bool allTestsArePassed = test();
    if (!allTestsArePassed)
    {
        return TEST_FAILED;
    }
    if (argc == 2 && stringsAreEqual(argv[1], "-test"))
    {
        return SUCCESS;
    }

    int sizeOfArray = 0;
    printf("Enter a size of array n: ");
    scanf_s("%d", &sizeOfArray);
    int* generatedArray = generateArray(sizeOfArray);
    if (generatedArray == NULL)
    {
        printf("An error occured");
        return BAD_ALLOCATION;
    }
    printArray(generatedArray, sizeOfArray);
    printf("\n\n");

    int amountOfNumbers = 0;
    printf("Enter an amount of numbers k: ");
    scanf_s("%d", &amountOfNumbers);

    quicksort(generatedArray, 0, sizeOfArray);
    srand(time(NULL));
    for (int i = 0; i < amountOfNumbers; ++i)
    {
        int number = rand() % RAND_RANGE - RAND_RANGE / 2;
        bool numberIsInArray = search(generatedArray, sizeOfArray, number);
        if (numberIsInArray)
        {
            printf("!!! Number %d is in array !!!\n", number);
        }
        else
        {
            printf("Number %d is not in array\n", number);
        }
    }
    free(generatedArray);
    return SUCCESS;
}
