#include "console.h"
#include "CyclicList.h"
#include <stdlib.h>

static CycledList* getNumberAndCreateList(void)
{
    size_t numberOfWarriors = 0;
    printf("Enter a number of warriors: ");
    scanf_s("%zu", &numberOfWarriors);
    CycledList* list = createList();
    if (list == NULL)
    {
        return NULL;
    }
    bool errorOccured = false;
    for (size_t i = 1; i <= numberOfWarriors; ++i)
    {
        errorOccured = push(list, i);
        if (errorOccured)
        {
            freeList(&list);
            return NULL;
        }
    }
    return list;
}

static void getCountAndPop(CycledList* const list)
{
    size_t count = 0;
    printf("Enter count: ");
    scanf_s("%zu", &count);
    cyclicPop(list, count);
}

bool console(void)
{
    CycledList* list = getNumberAndCreateList();
    if (list == NULL)
    {
        return true;
    }
    getCountAndPop(list);
    printf("Remaining warrior: ");
    printList(list);
    printf("\n");
    freeList(&list);
    return false;
}
