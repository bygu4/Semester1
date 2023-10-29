#include "str.h"
#include <stdlib.h>
#include <stdarg.h>

typedef struct {
    char* data;
    size_t length;
    size_t capacity;
} String;

static String* createString(void)
{
    String* string = malloc(sizeof(String));
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

static int addCharToString(String* string, const char character)
{
    if (string->capacity <= string->length + 1)
    {
        string->capacity *= 2;
        string->data = (char*)realloc(string->data, string->capacity);
        if (string->data == NULL)
        {
            free(string);
            return BAD_ALLOCATION;
        }
    }
    ++string->length;
    string->data[string->length - 1] = character;
    string->data[string->length] = '\0';
    return SUCCESS;
}

char* stringSum(int* const errorCode, const size_t numberOfSources, ...)
{
    String* sum = createString();
    if (sum == NULL)
    {
        *errorCode = BAD_ALLOCATION;
        return NULL;
    }
    va_list sources;
    va_start(sources, numberOfSources);
    for (size_t i = 0; i < numberOfSources; ++i)
    {
        const char* const source = va_arg(sources, const char* const);
        char character = source[0];
        for (size_t i = 1; character != '\0'; ++i)
        {
            *errorCode = addCharToString(sum, character);
            if (*errorCode != SUCCESS)
            {
                return NULL;
            }
            character = source[i];
        }
    }
    va_end(sources);
    char* output = (char*)malloc(sum->length + 1);
    if (output == NULL)
    {
        *errorCode = BAD_ALLOCATION;
        return NULL;
    }
    *errorCode = strcpy_s(output, sum->length + 1, sum->data);
    freeString(&sum);
    if (*errorCode != SUCCESS)
    {
        free(output);
        return NULL;
    }
    *errorCode = SUCCESS;
    return output;
}

char* fgetString(FILE* const inputFile, const char breakPoint, int* const errorCode)
{
    String* string = createString();
    if (string == NULL)
    {
        *errorCode = BAD_ALLOCATION;
        return NULL;
    }
    char character = fgetc(inputFile);
    while (character != breakPoint && !feof(inputFile))
    {
        *errorCode = addCharToString(string, character);
        if (*errorCode != SUCCESS)
        {
            return NULL;
        }
        character = fgetc(inputFile);
    }
    char* output = (char*)malloc(string->length + 1);
    if (output == NULL)
    {
        *errorCode = BAD_ALLOCATION;
        return NULL;
    }
    *errorCode = strcpy_s(output, string->length + 1, string->data);
    freeString(&string);
    if (*errorCode != SUCCESS)
    {
        free(output);
        return NULL;
    }
    *errorCode = SUCCESS;
    return output;
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

bool compareStrings(const char* const string1, const char* const string2)
{
    for (size_t i = 0; string1[i] != '\0' || string2[i] != '\0'; ++i)
    {
        if (string1[i] < string2[i])
        {
            return true;
        }
        if (string1[i] > string2[i])
        {
            return false;
        }
    }
    return true;
}
