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

static bool splitList(List* const list, List** const leftHalf, List** const rightHalf)
{
    *leftHalf = createList();
    *rightHalf = createList();
    if (*leftHalf == NULL || *rightHalf == NULL)
    {
        return true;
    }
    size_t sizeOfList = size(list);
    for (size_t i = 0; i < sizeOfList; ++i)
    {
        if (i < sizeOfList / 2)
        {
            replaceFirstElement(*leftHalf, list);
        }
        else
        {
            replaceFirstElement(*rightHalf, list);
        }
    }
    return false;
}

static void merge(List* const list, List* leftList, List* rightList, 
    bool (*key)(const List* const, const List* const))
{
    while (!isEmpty(leftList) && !isEmpty(rightList))
    {
        if (key(leftList, rightList))
        {
            replaceFirstElement(list, leftList);
        }
        else
        {
            replaceFirstElement(list, rightList);
        }
    }
    while (!isEmpty(leftList))
    {
        replaceFirstElement(list, leftList);
    }
    while (!isEmpty(rightList))
    {
        replaceFirstElement(list, rightList);
    }
}

static bool freeLists(List* list1, List* list2, bool errorCode)
{
    freeList(&list1);
    freeList(&list2);
    return errorCode;
}

bool mergeSort(List* const list, bool (*key)(const List* const, const List* const))
{
    if (size(list) <= 1)
    {
        return false;
    }
    List* leftList = NULL;
    List* rightList = NULL;
    bool errorOccured = splitList(list, &leftList, &rightList);
    if (errorOccured)
    {
        return freeLists(leftList, rightList, true);
    }
    errorOccured = mergeSort(leftList, key);
    if (errorOccured)
    {
        return freeLists(leftList, rightList, true);
    }
    errorOccured = mergeSort(rightList, key);
    if (errorOccured)
    {
        return freeLists(leftList, rightList, true);
    }
    merge(list, leftList, rightList, key);
    return freeLists(leftList, rightList, false);
}
