#include "getString.h"
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
