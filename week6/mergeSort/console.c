#include "console.h"
#include "readListFromFile.h"
#include "mergeSort.h"

int console(void)
{
    List* list = createList();
    if (list == NULL)
    {
        return BAD_ALLOCATION;
    }
    int errorCode = readListFromFile(list, NAME_OF_FILE);
    if (errorCode != SUCCESS)
    {
        freeList(&list);
        return errorCode;
    }
    printf("1: Sort list by name\n2: Sort list by number\n\n");
    int command = 0;
    while (true)
    {
        scanf_s("%d", &command);
        switch (command)
        {
        case 1:
            errorCode = mergeSort(list, compareByName);
            break;
        case 2:
            errorCode = mergeSort(list, compareByNumber);
            break;
        default:
            printf("Unknown command\n\n");
            continue;
        }
        break;
    }
    if (errorCode == SUCCESS)
    {
        printList(list);
    }
    freeList(&list);
    return errorCode;
}
