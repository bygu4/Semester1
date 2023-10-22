#include "str.h"
#include <stdlib.h>
#include <stdio.h>

void freeString(String** const string)
{
    if (*string != NULL)
    {
        free((*string)->data);
        free(*string);
        *string = NULL;
    }
}

String* createString(const char* const data)
{
    String* string = malloc(sizeof(String));
    if (string == NULL)
    {
        return NULL;
    }
    string->length = strlen(data);
    string->capacity = string->length + 1;
    string->data = (char*)malloc(string->capacity);
    if (string->data == NULL)
    {
        freeString(&string);
        return NULL;
    }
    int errorCode = strcpy_s(string->data, string->capacity, data);
    if (errorCode != SUCCESS)
    {
        freeString(&string);
        return NULL;
    }
    return string;
}

String* getString(const char breakPoint)
{
    String* string = createString("");
    if (string == NULL)
    {
        return NULL;
    }
    char character = getchar();
    size_t i = 0;
    while (character != breakPoint)
    {
        string->data[i++] = character;
        if (i * sizeof(char) >= string->capacity)
        {
            string->capacity *= 2;
            string->data = (char*)realloc(string->data, string->capacity);
            if (string->data == NULL)
            {
                freeString(&string);
                return NULL;
            }
        }
        character = getchar();
    }
    string->data[i] = '\0';
    string->length = i;
    return string;
}

int addCharToString(String* const string, const char character)
{
    if (string->length + 1 >= string->capacity)
    {
        string->capacity *= 2;
        string->data = (char*)realloc(string->data, string->capacity);
    }
    if (string->data == NULL)
    {
        return BAD_ALLOCATION;
    }
    ++string->length;
    string->data[string->length - 1] = character;
    string->data[string->length] = '\0';
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
