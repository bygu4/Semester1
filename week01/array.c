#include <stdio.h>

void reverseSection(int* array, int start, int end)
{
    for (int i = 0; start + i < (start + end) / 2; ++i)
    {
        int temp = array[start + i];
        array[start + i] = array[end - i - 1];
        array[end - i - 1] = temp;
    }
}

int main()
{
    int lengthOfFirstSection = 0;
    int lengthOfSecondSection = 0;
    printf("Enter length m of first section: ");
    scanf_s("%d", &lengthOfFirstSection);
    printf("Enter length n of second section: ");
    scanf_s("%d", &lengthOfSecondSection);

    int inputArray[256] = { 0 };
    printf("Enter array (256 numbers max): ");
    for (int i = 0; i < lengthOfFirstSection + lengthOfSecondSection; ++i)
    {
        scanf_s("%d", &inputArray[i]);
    }

    printf("Swapping two sections...\n");
    reverseSection(inputArray, 0, lengthOfFirstSection);
    reverseSection(inputArray, lengthOfFirstSection, lengthOfFirstSection + lengthOfSecondSection);
    reverseSection(inputArray, 0, lengthOfFirstSection + lengthOfSecondSection);

    printf("Your array:");
    for (int i = 0; i < lengthOfFirstSection + lengthOfSecondSection; ++i)
    {
        printf(" %d", inputArray[i]);
    }
}