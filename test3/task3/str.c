#include "str.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* data;
    size_t length;
    size_t capacity;
} String;

static String* createString(void)
{
    String* string = (String*)malloc(sizeof(String));
    if (string == NULL)
    {
        return NULL;
    }
    string->length = 0;
    string->capacity = 1;
    string->data = (char*)calloc(string->capacity, sizeof(char));
    if (string->data == NULL)
    {
        free(string);
        return NULL;
    }
    return string;
}

static void freeString(String** const string)
{
    free((*string)->data);
    free(*string);
    *string = NULL;
}

static bool addCharToString(String* const string, const char character)
{
    if (string->capacity <= string->length + 1)
    {
        string->capacity *= 2;
        string->data = (char*)realloc(string->data, string->capacity);
        if (string->data == NULL)
        {
            return true;
        }
    }
    ++string->length;
    string->data[string->length - 1] = character;
    string->data[string->length] = '\0';
    return false;
}

static char* fgetString(FILE* const stream, const char breakPoint)
{
    String* string = createString();
    if (string == NULL)
    {
        return NULL;
    }
    char character = fgetc(stream);
    while (!feof(stream) && character != breakPoint)
    {
        bool errorOccured = addCharToString(string, character);
        if (errorOccured)
        {
            freeString(&string);
            return NULL;
        }
        character = fgetc(stream);
    }
    char* output = string->data;
    string->data = NULL;
    freeString(&string);
    return output;
}

char* getString(const char breakPoint)
{
    return fgetString(stdin, breakPoint);
}

bool stringsAreEqual(const char* const string1, const char* const string2)
{
    return strcmp(string1, string2) == 0;
}
