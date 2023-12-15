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
        while (string[i] != substring[prefixLength] && prefixLength > 0)
        {
            prefixLength = prefixArray[prefixLength - 1];
        }
        prefixArray[i] = string[i] == substring[prefixLength] ? prefixLength + 1 : 0;
    }
    return prefixArray;
}

// Кнут-Моррис-Пратт
size_t getSubstringFirstEntry(const char* const substring, const char* const string, 
    const size_t lengthOfSubstring, const size_t lengthOfString, bool* const found, bool* const errorOccured)
{
    size_t* prefixArray = makePrefixArray(substring, string, lengthOfString);
    if (prefixArray == NULL)
    {
        *errorOccured = true;
        return 0;
    }
    size_t result = 0;
    size_t stringIndex = 0;
    for (size_t i = 0;; ++i)
    {
        if (i == lengthOfSubstring)
        {
            *found = true;
            result = i - lengthOfString;
            break;
        }
        if (string[stringIndex] == '\0')
        {
            *found = false;
            break;
        }
        while (stringIndex > 0 && string[stringIndex] != substring[i])
        {
            stringIndex = prefixArray[stringIndex - 1];
        }
        if (string[stringIndex] == substring[i])
        {
            ++stringIndex;
        }
    }
    free(prefixArray);
    *errorOccured = false;
    return result;
}
