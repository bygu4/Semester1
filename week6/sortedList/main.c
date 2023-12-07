#include "console.h"
#include "test.h"
#include <stdio.h>

int main(const unsigned int argc, const char argv[])
{
    const bool allTestsArePassed = test();
    if (!allTestsArePassed)
    {
        return TEST_FAILED;
    }
    if (argc == 2 && argv[1] == 't')
    {
        return SUCCESS;
    }
    SortedList* list = createList();
    if (list == NULL)
    {
        return BAD_ALLOCATION;
    }

    printf("Commands:\n0: quit\n1: add an item to list\n");
    printf("2: delete an item from list\n3: print list\n\n");

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
