#include "console.h"
#include "list.h"
#include "deleteOddElements.h"

static bool scanList(List* const list, const size_t sizeOfList)
{
    int number = 0;
    for (size_t i = 0; i < sizeOfList; ++i)
    {
        scanf_s("%d", &number);
        bool errorOccured = push(list, number);
        if (errorOccured)
        {
            return true;
        }
    }
    return false;
}

int console(void)
{
    List* list = createList();
    if (list == NULL)
    {
        printf("An error occured\n");
        return BAD_ALLOCATION;
    }
    size_t sizeOfList = 0;
    printf("Enter size of list: ");
    scanf_s("%zu", &sizeOfList);
    printf("Enter list: ");
    bool errorOccured = scanList(list, sizeOfList);
    if (errorOccured)
    {
        freeList(&list);
        printf("An error occured\n");
        return BAD_ALLOCATION;
    }
    printf("Array after deletion: ");
    deleteOddElements(list);
    printList(list);
    freeList(&list);
    return SUCCESS;
}
