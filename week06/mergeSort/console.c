#include "console.h"
#include "readListFromFile.h"
#include "mergeSort.h"

int console(void)
{
    List* list = createList();
    if (list == NULL)
    {
        printf("An error occured\n");
        return BAD_ALLOCATION;
    }
    int errorCode = readListFromFile(list, NAME_OF_FILE);
    if (errorCode != SUCCESS)
    {
        printf("An error occured\n");
        freeList(&list);
        return errorCode;
    }
    printf("1: Sort list by name\n2: Sort list by number\n\n");
    bool errorOccured = false;
    int command = 0;
    while (true)
    {
        scanf_s("%d", &command);
        switch (command)
        {
        case 1:
            errorOccured = mergeSort(list, compareByName);
            break;
        case 2:
            errorOccured = mergeSort(list, compareByNumber);
            break;
        default:
            printf("Unknown command\n\n");
            continue;
        }
        break;
    }
    if (errorOccured)
    {
        printf("An error occured\n");
        freeList(&list);
        return BAD_ALLOCATION;
    }
    printList(list);
    freeList(&list);
    return SUCCESS;
}
