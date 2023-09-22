#include <stdio.h>

int getNumberOfNullElements(int* array, int size)
{
    int count = 0;
    for (int i = 0; i < size; ++i)
    {
        if (array[i] == 0)
        {
            ++count;
        }
    }
    return count;
}

int main()
{
    int sizeOfArray = 0;
    printf("Enter the size of array (256 max): ");
    scanf_s("%d", &sizeOfArray);

    int inputArray[256] = { 0 };
    printf("Enter your array: ");
    for (int i = 0; i < sizeOfArray; ++i)
    {
        scanf_s("%d", &inputArray[i]);
    }
    int numberOfNullElements = getNumberOfNullElements(inputArray, sizeOfArray);
    printf("Number of null elements in array: %d", numberOfNullElements);
}