#include "List.h"
#include "str.h"
#include <stdlib.h>

typedef struct {
    char* name;
    char* number;
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

bool isEmpty(const List* const list)
{
    return list == NULL || list->head == NULL;
}

size_t size(const List* const list)
{
    return list->size;
}

char* getName(const List* const list)
{
    if (isEmpty(list))
    {
        return NULL;
    }
    return list->head->name;
}

char* getNumber(const List* const list)
{
    if (isEmpty(list))
    {
        return NULL;
    }
    return list->head->number;
}

static void freeElement(ListElement** const element)
{
    free((*element)->name);
    free((*element)->number);
    free(*element);
    *element = NULL;
}

int push(List* const list, const char* const name, const char* const number)
{
    ListElement* element = malloc(sizeof(ListElement));
    if (element == NULL)
    {
        return BAD_ALLOCATION;
    }
    size_t lengthOfName = strlen(name);
    element->name = (char*)malloc(lengthOfName + 1);
    if (element->name == NULL)
    {
        freeElement(&element);
        return BAD_ALLOCATION;
    }
    int errorCode = strcpy_s(element->name, lengthOfName + 1, name);
    if (errorCode != SUCCESS)
    {
        freeElement(&element);
        return errorCode;
    }
    size_t lengthOfNumber = strlen(number);
    element->number = (char*)malloc(lengthOfNumber + 1);
    if (element->number == NULL)
    {
        freeElement(&element);
        return BAD_ALLOCATION;
    }
    errorCode = strcpy_s(element->number, lengthOfNumber + 1, number);
    if (errorCode != SUCCESS)
    {
        freeElement(&element);
        return errorCode;
    }
    element->next = NULL;
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
    return SUCCESS;
}

void pop(List* const list)
{
    if (isEmpty(list))
    {
        return;
    }
    ListElement* element = list->head;
    list->head = element->next;
    if (list->back == element)
    {
        list->back = element->next;
    }
    freeElement(&element);
    --list->size;
}

void freeList(List** const list)
{
    while (!isEmpty(*list))
    {
        pop(*list);
    }
    free(*list);
    *list = NULL;
}

void printList(const List* const list)
{
    for (ListElement* currentElement = list->head;
        currentElement != NULL; currentElement = currentElement->next)
    {
        printf("%s - %s\n", currentElement->name, currentElement->number);
    }
}

static void freeArray(char** array, const size_t sizeOfArray)
{
    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        free(array[i]);
    }
    free(array);
}

char** getList(const List* const list, int* const errorCode)
{
    size_t sizeOfList = size(list);
    char** output = (char**)malloc(sizeOfList * sizeof(char*));
    if (output == NULL)
    {
        *errorCode = BAD_ALLOCATION;
        return NULL;
    }
    size_t i = 0;
    for (ListElement* currentElement = list->head;
        currentElement != NULL; currentElement = currentElement->next)
    {
        char* data = stringSum(errorCode, 3, currentElement->name, " - ", currentElement->number);
        if (*errorCode != SUCCESS)
        {
            freeArray(output, i);
            return NULL;
        }
        output[i] = data;
        ++i;
    }
    *errorCode = SUCCESS;
    return output;
}
