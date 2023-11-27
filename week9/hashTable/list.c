#include "list.h"
#include "str.h"
#include <stdlib.h>

typedef struct {
    char* key;
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

static void freeElement(ListElement** const element)
{
    free((*element)->key);
    free(*element);
    *element = NULL;
}

static ListElement* head(const List* const list)
{
    return list != NULL ? list->head : NULL;
}

void freeList(List** const list)
{
    for (ListElement* current = head(*list); current != NULL;)
    {
        ListElement* next = current->next;
        freeElement(&current);
        current = next;
    }
    free(*list);
    *list = NULL;
}

size_t size(const List* const list)
{
    return list != NULL ? list->size : 0;
}

static bool isEmpty(const List* const list)
{
    return list->head == NULL;
}

static ListElement* createElement(const char* const key)
{
    ListElement* element = (ListElement*)malloc(sizeof(ListElement));
    if (element == NULL)
    {
        return NULL;
    }
    element->key = copyString(key);
    if (element->key == NULL)
    {
        free(element);
        return NULL;
    }
    element->numberOfEntries = 1;
    element->next = NULL;
    return element;
}

static ListElement* getElement(const List* const list, const char* const key)
{
    for (ListElement* current = head(list); current != NULL; current = current->next)
    {
        if (stringsAreEqual(current->key, key))
        {
            return current;
        }
    }
    return NULL;
}

bool push(List* const list, const char* const key)
{
    ListElement* element = getElement(list, key);
    if (element != NULL)
    {
        ++element->numberOfEntries;
        return false;
    }
    element = createElement(key);
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
    for (ListElement* current = head(list); current != NULL; current = current->next)
    {
        printf("%s: %d\n", current->key, current->numberOfEntries);
    }
}

unsigned int numberOfEntries(const List* const list, const char* const key)
{
    for (ListElement* current = head(list); current != NULL; current = current->next)
    {
        if (stringsAreEqual(current->key, key))
        {
            return current->numberOfEntries;
        }
    }
    return 0;
}
