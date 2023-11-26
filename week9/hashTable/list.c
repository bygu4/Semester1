#include "list.h"
#include "str.h"
#include <stdlib.h>

typedef struct {
    char* data;
    unsigned int numberOfEntries;
    struct ListElement* next;
} ListElement;

struct List {
    ListElement* head;
    ListElement* back;
    size_t size;
};

List* createList(void)
{
    return (List*)calloc(1, sizeof(List));
}

size_t size(const List* const list)
{
    return list != NULL ? list->size : 0;
}

static bool isEmpty(const List* const list)
{
    return list->head == NULL;
}

static ListElement* createElement(const char* const data)
{
    ListElement* element = (ListElement*)malloc(sizeof(ListElement));
    if (element == NULL)
    {
        return NULL;
    }
    element->data = copyString(data);
    if (element->data == NULL)
    {
        free(element);
        return NULL;
    }
    element->numberOfEntries = 1;
    element->next = NULL;
    return element;
}

static ListElement* getElement(const List* const list, const char* const data)
{
    for (ListElement* current = list->head; current != NULL; current = current->next)
    {
        if (stringsAreEqual(current->data, data))
        {
            return current;
        }
    }
    return NULL;
}

bool push(List* const list, const char* const data)
{
    ListElement* element = getElement(list, data);
    if (element != NULL)
    {
        ++element->numberOfEntries;
        return false;
    }
    element = createElement(data);
    if (element == NULL)
    {
        return true;
    }
    if (isEmpty(list))
    {
        list->head = element;
    }
    else
    {
        list->back->next = element;
    }
    list->back = element;
    ++list->size;
    return false;
}

void printList(const List* const list)
{
    if (list == NULL)
    {
        return;
    }
    for (ListElement* current = list->head; current != NULL; current = current->next)
    {
        printf("%s: %d\n", current->data, current->numberOfEntries);
    }
}

static void freeElement(ListElement** const element)
{
    free((*element)->data);
    free(*element);
    *element = NULL;
}

void freeList(List** const list)
{
    if (*list == NULL)
    {
        return;
    }
    for (ListElement* current = (*list)->head; current != NULL;)
    {
        ListElement* next = current->next;
        freeElement(&current);
        current = next;
    }
    free(*list);
    *list = NULL;
}
