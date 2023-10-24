#include "console.h"
#include <stdio.h>

bool pushConsole(SortedList* const list)
{
    int inputNumber = 0;
    printf("Enter a number: ");
    scanf_s("%d", &inputNumber);
    bool errorOccured = push(list, inputNumber);
    if (!errorOccured)
    {
        printf("Added\n");
    }
    return errorOccured;
}

void popConsole(SortedList* const list)
{
    if (isEmpty(list))
    {
        printf("List is empty\n");
        return;
    }
    unsigned int inputIndex = 0;
    printf("Enter an index: ");
    scanf_s("%d", &inputIndex);
    int errorCode = pop(list, inputIndex);
    if (errorCode == INDEX_OUT_OF_RANGE)
    {
        printf("Index out of range\n");
        return;
    }
    printf("Deleted\n");
}

void printListConsole(const SortedList* const list)
{
    if (isEmpty(list))
    {
        printf("List is empty\n");
        return;
    }
    printf("List: ");
    printList(list);
    printf("\n");
}
