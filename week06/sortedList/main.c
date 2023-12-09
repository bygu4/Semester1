#include "console.h"
#include "test.h"
#include <stdio.h>

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
