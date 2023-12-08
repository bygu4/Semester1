#include "list.h"
#include <stdlib.h>

typedef struct {
    int value;
    struct ListElement* next;
} ListElement;

struct List {
    ListElement* head;
    ListElement* back;
    ListElement* current;
    size_t size;
};

List* createList(void)
{
    return (List*)calloc(1, sizeof(List));
}

bool isEmpty(const List* const list)
{
    return list->head == NULL;
}

bool push(List* const list, const int value)
{
    ListElement* element = (ListElement*)malloc(sizeof(ListElement));
    if (element == NULL)
    {
        return true;
    }
    element->value = value;
    element->next = NULL;
    if (isEmpty(list))
    {
        list->head = element;
        list->current = element;
    }
    else
    {
        list->back->next = element;
    }
    list->back = element;
    ++list->size;
    return false;
}

static void freeElement(ListElement** const element)
{
    free(*element);
    *element = NULL;
}

void deleteElement(List* const list)
{
    if (list->current == NULL || list->current->next == NULL)
    {
        return;
    }
    ListElement* elementToDelete = list->current->next;
    list->current->next = elementToDelete->next;
    if (elementToDelete == list->back)
    {
        list->back = elementToDelete->next;
    }
    --list->size;
    freeElement(&elementToDelete);
}

void switchCurrent(List* const list)
{
    if (list->current != NULL)
    {
        list->current = list->current->next;
    }
}

void setCurrent(List* const list)
{
    list->current = list->head;
}

int* getValues(const List* const list)
{
    int* array = (int*)malloc(sizeof(int) * list->size);
    if (array == NULL)
    {
        return NULL;
    }
    size_t i = 0;
    for (const ListElement* element = list->head; element != NULL; element = element->next)
    {
        array[i] = element->value;
        ++i;
    }
    return array;
}

void freeList(List** const list)
{
    setCurrent(*list);
    while ((*list)->size > 1)
    {
        deleteElement(*list);
    }
    free((*list)->current);
    free(*list);
    *list = NULL;
}

bool currentIsNull(const List* const list)
{
    return list->current == NULL;
}

void printList(const List* const list)
{
    for (const ListElement* element = list->head; element != NULL; element = element->next)
    {
        printf("%d ", element->value);
    }
}

size_t size(const List* const list)
{
    return list->size;
}
