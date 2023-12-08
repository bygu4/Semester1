#include "str.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

char* stringMul(const char* const string, const unsigned int multiplier)
{
    size_t lengthOfOriginalString = strlen(string);
    char* newString = (char*)malloc(lengthOfOriginalString * multiplier + 1);
    if (newString == NULL)
    {
        return NULL;
    }
    size_t j = 0;
    for (size_t i = 0; i < lengthOfOriginalString * multiplier; ++i)
    {
        newString[i] = string[j];
        ++j;
        j %= lengthOfOriginalString;
    }
    newString[lengthOfOriginalString * multiplier] = '\0';
    return newString;
}

char* fgetString(FILE* const file, const char breakPoint, const size_t initialSizeOfBuffer)
{
    if (initialSizeOfBuffer == 0)
    {
        return NULL;
    }
    size_t sizeOfBuffer = initialSizeOfBuffer;
    char* string = (char*)malloc(sizeOfBuffer);
    if (string == NULL)
    {
        return NULL;
    }
    char character = fgetc(file);
    size_t i = 0;
    while (character != breakPoint && !feof(file))
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
        character = fgetc(file);
    }
    string[i] = '\0';
    return string;
}

char* getString(const char breakPoint, const size_t initialSizeOfBuffer)
{
    char* string = fgetString(stdin, breakPoint, initialSizeOfBuffer);
    return string;
}
