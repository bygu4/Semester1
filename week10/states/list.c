#include "list.h"
#include <stdlib.h>

typedef struct {
    unsigned int city;
    unsigned int distance;
    struct ListElement* next;
} ListElement;

struct List {
    ListElement* head;
    ListElement* back;
    ListElement* current;
    size_t index;
    size_t size;
};

static ListElement* head(const List* const list)
{
    return list != NULL ? list->head : NULL;
}

List* createList(void)
{
    return (List*)calloc(1, sizeof(List));
}

void freeList(List** const list)
{
    for (ListElement* current = head(*list); current != NULL;)
    {
        ListElement* next = current->next;
        free(current);
        current = next;
    }
    free(*list);
    *list = NULL;
}

static ListElement* createElement(const unsigned int city, const unsigned int distance)
{
    ListElement* element = (ListElement*)malloc(sizeof(ListElement));
    if (element == NULL)
    {
        return NULL;
    }
    element->city = city;
    element->distance = distance;
    element->next = NULL;
    return element;
}

bool push(List* const list, const unsigned int city, const unsigned int distance)
{
    if (list == NULL)
    {
        return true;
    }
    ListElement* element = createElement(city, distance);
    if (element == NULL)
    {
        return true;
    }
    if (list->head == NULL)
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

static void setCurrent(List* const list)
{
    list->current = list->head;
    list->index = 0;
}

static ListElement* getElement(List* const list, const size_t index)
{
    if (index < list->index)
    {
        setCurrent(list);
    }
    for (ListElement** current = &list->current; *current != NULL; *current = (*current)->next)
    {
        if (list->index == index)
        {
            return *current;
        }
        ++list->index;
    }
    return NULL;
}

unsigned int city(List* const list, const size_t index)
{
    ListElement* element = getElement(list, index);
    return element != NULL ? element->city : 0;
}

unsigned int distance(List* const list, const size_t index)
{
    ListElement* element = getElement(list, index);
    return element != NULL ? element->distance : 0;
}

size_t size(const List* const list)
{
    return list->size;
}

void printList(const List* const list)
{
    for (ListElement* current = head(list); current != NULL; current = current->next)
    {
        printf("%u ", current->city);
    }
}

bool arrayIsEqual(const List* const list, const unsigned int array[32], const size_t length)
{
    if (size(list) != length)
    {
        return false;
    }
    size_t i = 0;
    for (ListElement* current = head(list); current != NULL; current = current->next)
    {
        if (current->city != array[i])
        {
            return false;
        }
        ++i;
    }
    return true;
}
