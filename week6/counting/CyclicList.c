#include "CyclicList.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    size_t value;
    struct ListElement* next;
} ListElement;

struct CycledList {
    ListElement* head;
    ListElement* back;
    size_t size;
};

CycledList* createList(void)
{
    return (CycledList*)calloc(1, sizeof(CycledList));
}

bool isEmpty(const CycledList* const list)
{
    return list->head == NULL;
}

size_t size(const CycledList* const list)
{
    return list->size;
}

bool push(CycledList* const list, const size_t value)
{
    ListElement* element = malloc(sizeof(ListElement));
    if (element == NULL)
    {
        return true;
    }
    element->value = value;
    if (isEmpty(list))
    {
        list->head = element;
    }
    else
    {
        list->back->next = element;
    }
    list->back = element;
    element->next = list->head;
    ++list->size;
    return false;
}

static void pop(CycledList* const list,  ListElement* element, ListElement* const previousElement)
{
    if (list->head == list->back)
    {
        list->head = NULL;
        list->back = NULL;
        free(element);
        --list->size;
        return;
    }
    previousElement->next = element->next;
    if (element == list->head)
    {
        list->head = element->next;
    }
    if (element == list->back)
    {
        list->back = previousElement;
    }
    free(element);
    --list->size;
}

void cyclicPop(CycledList* const list, const size_t count)
{
    if (count == 0)
    {
        return;
    }
    ListElement* currentElement = list->head;
    ListElement* previousElement = list->back;
    size_t i = 1;
    while (size(list) > 1)
    {
        if (i == count)
        {
            pop(list, currentElement, previousElement);
            currentElement = previousElement->next;
            i = 1;
        }
        else
        {
            previousElement = currentElement;
            currentElement = currentElement->next;
            ++i;
        }
    }
}

void freeList(CycledList** const list)
{
    while (!isEmpty(*list))
    {
        pop(*list, (*list)->head, (*list)->back);
    }
    free(*list);
    *list = NULL;
}

void printList(const CycledList* const list)
{
    size_t sizeOfList = size(list);
    ListElement* currentElement = list->head;
    for (size_t i = 0; i < sizeOfList; ++i)
    {
        printf("%zu ", currentElement->value);
        currentElement = currentElement->next;
    }
}

size_t* getList(const CycledList* const list)
{
    size_t sizeOfList = size(list);
    size_t* array = (size_t*)malloc(sizeOfList * sizeof(size_t));
    if (array == NULL)
    {
        return NULL;
    }
    ListElement* currentElement = list->head;
    for (size_t i = 0; i < sizeOfList; ++i)
    {
        array[i] = currentElement->value;
        currentElement = currentElement->next;
    }
    return array;
}
