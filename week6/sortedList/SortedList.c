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
    SortedList* list = calloc(1, sizeof(SortedList));
    return list;
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

int pop(SortedList* const list, const size_t index)
{
    if (list->size == 0)
    {
        return LIST_IS_EMPTY;
    }
    if (list->size < index + 1)
    {
        return INDEX_OUT_OF_RANGE;
    }
    ListElement* currentElement = list->head;
    ListElement* previousElement = NULL;
    size_t currentIndex = 0;
    while (currentElement != NULL && currentIndex != index)
    {
        previousElement = currentElement;
        currentElement = currentElement->next;
        ++currentIndex;
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
    ListElement* currentElement = list->head;
    while (currentElement != NULL)
    {
        printf("%d ", currentElement->value);
        currentElement = currentElement->next;
    }
}

int* getList(const SortedList* const list)
{
    int* array = (int*)malloc(list->size * sizeof(int));
    if (array == NULL)
    {
        return NULL;
    }
    ListElement* currentElement = list->head;
    size_t i = 0;
    while (currentElement != NULL)
    {
        array[i] = currentElement->value;
        currentElement = currentElement->next;
        ++i;
    }
    return array;
}

void freeList(SortedList** const list)
{
    while (!isEmpty(*list))
    {
        pop(*list, 0);
    }
    free(*list);
    *list = NULL;
}
