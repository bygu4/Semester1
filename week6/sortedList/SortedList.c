#include "SortedList.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct ListElement {
    int value;
    struct ListElement* next;
} ListElement;

struct SortedList {
    ListElement* head;
    ListElement* back;
    size_t size;
};

SortedList* createList(void)
{
    return (SortedList*)calloc(1, sizeof(SortedList));
}

bool push(SortedList* const list, const int value)
{
    ListElement* element = malloc(sizeof(ListElement));
    if (element == NULL)
    {
        return true;
    }
    element->value = value;
    ListElement* currentElement = list->head;
    ListElement* previousElement = NULL;
    while (currentElement != NULL && currentElement->value < value)
    {
        previousElement = currentElement;
        currentElement = currentElement->next;
    }
    if (previousElement == NULL)
    {
        list->head = element;
    }
    else
    {
        previousElement->next = element;
    }
    element->next = currentElement;
    if (element->next == NULL)
    {
        list->back = element;
    }
    ++list->size;
    return false;
}

int pop(SortedList* const list, const int value)
{
    if (list->size == 0)
    {
        return LIST_IS_EMPTY;
    }
    if (value < list->head->value || list->back->value < value)
    {
        return ELEMENT_NOT_IN_LIST;
    }
    ListElement* currentElement = list->head;
    ListElement* previousElement = NULL;
    while (currentElement != NULL && currentElement->value != value)
    {
        previousElement = currentElement;
        currentElement = currentElement->next;
    }
    if (currentElement == NULL)
    {
        return ELEMENT_NOT_IN_LIST;
    }
    ListElement* next = currentElement->next;
    free(currentElement);
    if (previousElement == NULL)
    {
        list->head = next;
    }
    else
    {
        previousElement->next = next;
    }
    if (next == NULL)
    {
        list->back = previousElement;
    }
    --list->size;
    return SUCCESS;
}

bool isEmpty(const SortedList* const list)
{
    return list->head == NULL;
}

size_t size(const SortedList* const list)
{
    return list->size;
}

void printList(const SortedList* const list)
{
    for (const ListElement* currentElement = list->head; currentElement != NULL; currentElement = currentElement->next)
    {
        printf("%d ", currentElement->value);
    }
}

int* getList(const SortedList* const list)
{
    int* array = (int*)malloc(list->size * sizeof(int));
    if (array == NULL)
    {
        return NULL;
    }
    size_t i = 0;
    for (const ListElement* currentElement = list->head; currentElement != NULL; currentElement = currentElement->next)
    {
        array[i] = currentElement->value;
        ++i;
    }
    return array;
}

void freeList(SortedList** const list)
{
    while (!isEmpty(*list))
    {
        pop(*list, (*list)->head->value);
    }
    free(*list);
    *list = NULL;
}
