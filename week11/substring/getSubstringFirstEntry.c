#include "getSubstringFirstEntry.h"
#include <stdlib.h>

static size_t* makePrefixArray(const char* const substring, const char* const string, 
    const size_t lengthOfString)
{
    size_t* prefixArray = (size_t*)malloc((lengthOfString + 1) * sizeof(size_t));
    if (prefixArray == NULL)
    {
        return NULL;
    }
    prefixArray[0] = 0;
    for (size_t i = 1; i < lengthOfString; ++i)
    {
        size_t prefixLength = prefixArray[i - 1];
        while (prefixLength > 0 && substring[prefixLength] != string[i])
        {
            prefixLength = prefixArray[prefixLength - 1];
        }
        if (substring[prefixLength] == string[i])
        {
            ++prefixLength;
        }
        prefixArray[i] = prefixLength;
    }
    return prefixArray;
}

// Кнут-Моррис-Пратт
size_t getSubstringFirstEntry(const char* const substring, const char* const string, 
    const size_t lengthOfString, bool* const found, bool* const errorOccured)
{
    size_t* prefixArray = makePrefixArray(substring, string, lengthOfString);
    if (prefixArray == NULL)
    {
        *errorOccured = true;
        return 0;
    }
    size_t result = 0;
    size_t lengthOfPrefix = 0;
    for (size_t i = 0;; ++i)
    {
        if (substring[lengthOfPrefix] == '\0')
        {
            *found = true;
            result = i - lengthOfPrefix;
            break;
        }
        if (string[i] == '\0')
        {
            *found = false;
            break;
        }
        while (lengthOfPrefix > 0 && substring[lengthOfPrefix] != string[i])
        {
            lengthOfPrefix = prefixArray[lengthOfPrefix - 1];
        }
        if (string[i] == substring[lengthOfPrefix])
        {
            ++lengthOfPrefix;
        }
    }
    free(prefixArray);
    *errorOccured = false;
    return result;
}
