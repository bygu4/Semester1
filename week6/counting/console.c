#include "console.h"
#include "CyclicList.h"
#include <stdlib.h>

static CycledList* getNumberAndCreateList(void)
{
    int numberOfWarriors = 0;
    printf("Enter a number of warriors: ");
    scanf_s("%d", &numberOfWarriors);
    CycledList* list = createList();
    if (list == NULL)
    {
        return NULL;
    }
    bool errorOccured = false;
    for (int i = 1; i <= numberOfWarriors; ++i)
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

static void getCountAndPop(CycledList* list)
{
    unsigned int count = 0;
    printf("Enter count: ");
    scanf_s("%u", &count);
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
    printf("Remaining warriors: ");
    printList(list);
    printf("\n");
    freeList(&list);
    return false;
}
