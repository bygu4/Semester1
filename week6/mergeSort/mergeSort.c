#include "mergeSort.h"
#include "str.h"

bool compareByName(const List* const list1, const List* const list2)
{
    char* name1 = getName(list1);
    char* name2 = getName(list2);
    return compareStrings(name1, name2);
}

bool compareByNumber(const List* const list1, const List* const list2)
{
    char* number1 = getNumber(list1);
    char* number2 = getNumber(list2);
    return compareStrings(number1, number2);
}

static int moveFirstElementToList(List* const destination, List* const source)
{
    char* name = getName(source);
    char* number = getNumber(source);
    int errorCode = push(destination, name, number);
    pop(source);
    return errorCode;
}

static int splitList(List* const list, List** const leftHalf, List** const rightHalf)
{
    *leftHalf = createList();
    *rightHalf = createList();
    if (*leftHalf == NULL || *rightHalf == NULL)
    {
        return BAD_ALLOCATION;
    }
    int errorCode = 0;
    size_t sizeOfList = size(list);
    for (size_t i = 0; i < sizeOfList; ++i)
    {
        if (i < sizeOfList / 2)
        {
            errorCode = moveFirstElementToList(*leftHalf, list);
        }
        else
        {
            errorCode = moveFirstElementToList(*rightHalf, list);
        }
        if (errorCode != SUCCESS)
        {
            return errorCode;
        }
    }
    return SUCCESS;
}

static int merge(List* const list, List* leftList, List* rightList, 
    bool (*key)(const List* const, const List* const))
{
    int errorCode = 0;
    while (!isEmpty(leftList) && !isEmpty(rightList))
    {
        if (key(leftList, rightList))
        {
            errorCode = moveFirstElementToList(list, leftList);
        }
        else
        {
            errorCode = moveFirstElementToList(list, rightList);
        }
        if (errorCode != SUCCESS)
        {
            return errorCode;
        }
    }
    while (!isEmpty(leftList))
    {
        errorCode = moveFirstElementToList(list, leftList);
        if (errorCode != SUCCESS)
        {
            return errorCode;
        }
    }
    while (!isEmpty(rightList))
    {
        errorCode = moveFirstElementToList(list, rightList);
        if (errorCode != SUCCESS)
        {
            return errorCode;
        }
    }
    return SUCCESS;
}

int mergeSort(List* const list, bool (*key)(const List* const, const List* const))
{
    if (size(list) <= 1)
    {
        return SUCCESS;
    }
    List* leftList = NULL;
    List* rightList = NULL;
    int errorCode = splitList(list, &leftList, &rightList);
    if (errorCode != SUCCESS)
    {
        freeList(&leftList);
        freeList(&rightList);
        return errorCode;
    }
    errorCode = mergeSort(leftList, key);
    if (errorCode != SUCCESS)
    {
        freeList(&leftList);
        freeList(&rightList);
        return errorCode;
    }
    errorCode = mergeSort(rightList, key);
    if (errorCode != SUCCESS)
    {
        freeList(&leftList);
        freeList(&rightList);
        return errorCode;
    }
    errorCode = merge(list, leftList, rightList, key);
    freeList(&leftList);
    freeList(&rightList);
    return errorCode;
}
