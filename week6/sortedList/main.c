#include "console.h"
#include "test.h"
#include <stdio.h>

#define TEST_FAILED -1

int main(void)
{
    const bool allTestsArePassed = test();
    if (!allTestsArePassed)
    {
        return TEST_FAILED;
    }
    SortedList* list = createList();
    if (list == NULL)
    {
        return BAD_ALLOCATION;
    }
    bool errorOccured = false;
    int command = -1;
    while (command != 0)
    {
        printf("Enter a command: ");
        scanf_s("%d", &command);
        switch (command)
        {
        case 0:
            continue;
        case 1:
            errorOccured = pushConsole(list);
            break;
        case 2:
            popConsole(list);
            break;
        case 3:
            printListConsole(list);
            break;
        }
        printf("\n");
        if (errorOccured)
        {
            freeList(&list);
            return BAD_ALLOCATION;
        }
    }
    freeList(&list);
    return SUCCESS;
}
