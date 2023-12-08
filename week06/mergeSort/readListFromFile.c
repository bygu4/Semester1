#include "readListFromFile.h"
#include "List.h"
#include "str.h"
#include <stdlib.h>

static int readLineAndPush(FILE* const inputFile, List* const list)
{
    int errorCode = 0;
    char* name = fgetString(inputFile, ' ', &errorCode);
    if (errorCode != SUCCESS)
    {
        return errorCode;
    }
    if (feof(inputFile))
    {
        size_t length = strlen(name);
        free(name);
        if (length != 0)
        {
            return INCORRECT_FORMAT;
        }
        return SUCCESS;
    }
    char buffer1 = fgetc(inputFile);
    char buffer2 = fgetc(inputFile);
    if (buffer1 != '-' || buffer2 != ' ')
    {
        free(name);
        return INCORRECT_FORMAT;
    }
    char* number = fgetString(inputFile, '\n', &errorCode);
    if (errorCode != SUCCESS)
    {
        free(name);
        return errorCode;
    }
    errorCode = push(list, name, number);
    free(name);
    free(number);
    return errorCode;
}

int readListFromFile(List* const list, const char* const nameOfFile)
{
    FILE* inputFile = NULL;
    int errorCode = fopen_s(&inputFile, nameOfFile, "r");
    if (errorCode != SUCCESS)
    {
        return errorCode;
    }
    while (!feof(inputFile))
    {
        errorCode = readLineAndPush(inputFile, list);
        if (errorCode != SUCCESS)
        {
            break;
        }
    }
    fclose(inputFile);
    return errorCode;
}
