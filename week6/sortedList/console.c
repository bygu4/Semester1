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
    int inputNumber = 0;
    printf("Enter a number: ");
    scanf_s("%d", &inputNumber);
    int errorCode = pop(list, inputNumber);
    if (errorCode == ELEMENT_NOT_IN_LIST)
    {
        printf("Element not in list\n");
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
