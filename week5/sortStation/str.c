#include "str.h"
#include <stdlib.h>
#include <stdio.h>

char* getString(const char breakPoint)
{
    size_t sizeOfBuffer = sizeof(char);
    char* string = (char*)malloc(sizeOfBuffer);
    if (string == NULL)
    {
        return NULL;
    }
    char character = getchar();
    size_t i = 0;
    while (character != breakPoint)
    {
        string[i] = character;
        ++i;
        if (i * sizeof(char) >= sizeOfBuffer)
        {
            sizeOfBuffer *= 2;
            string = (char*)realloc(string, sizeOfBuffer);
            if (string == NULL)
            {
                return NULL;
            }
        }
        character = getchar();
    }
    string[i] = '\0';
    return string;
}

int addCharToString(char** const string, const char character, const size_t lengthOfString)
{
    *string = (char*)realloc(*string, lengthOfString + 2);
    if (*string == NULL)
    {
        return BAD_ALLOCATION;
    }
    (*string)[lengthOfString] = character;
    (*string)[lengthOfString + 1] = '\0';
    return SUCCESS;
}

bool stringsAreEqual(const char* const string1, const char* const string2)
{
    for (size_t i = 0; string1[i] != '\0' || string2[i] != '\0'; ++i)
    {
        if (string1[i] != string2[i])
        {
            return false;
        }
    }
    return true;
}
