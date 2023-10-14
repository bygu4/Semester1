#include "str.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool stringsAreEqual(const char* const string1, const char* const string2)
{
    size_t lengthOfString1 = strlen(string1);
    size_t lengthOfString2 = strlen(string2);
    if (lengthOfString1 != lengthOfString2)
    {
        return false;
    }
    for (size_t i = 0; i < lengthOfString1; ++i)
    {
        if (string1[i] != string2[i])
        {
            return false;
        }
    }
    return true;
}

char* stringMul(const char* const string, const int multiplier)
{
    size_t lengthOfOriginalString = strlen(string);
    char* newString = (char*)calloc(lengthOfOriginalString * multiplier + 1, sizeof(char));
    if (newString == NULL)
    {
        return NULL;
    }
    size_t j = 0;
    for (size_t i = 0; i < lengthOfOriginalString * multiplier; ++i)
    {
        newString[i] = string[j];
        ++j;
        if (j >= lengthOfOriginalString)
        {
            j = 0;
        }
    }
    return newString;
}
