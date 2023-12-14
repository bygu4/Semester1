#include "console.h"
#include "getSubstringFirstEntry.h"
#include "str.h"
#include <stdlib.h>

int console(void)
{
    char* fileData = NULL;
    int errorCode = readFile(&fileData, NAME_OF_FILE);
    if (errorCode != SUCCESS)
    {
        printf(errorCode == FILE_NOT_FOUND ? "File not found\n" : "An error occured\n");
        return errorCode;
    }
    printf("Enter a substring to find: ");
    char* inputString = getString('\n');
    if (inputString == NULL)
    {
        printf("An error occured\n");
        free(fileData);
        return BAD_ALLOCATION;
    }
    bool substringIsFound = false;
    size_t firstEntryIndex = getSubstringFirstEntry(inputString, fileData, &substringIsFound);
    free(fileData);
    free(inputString);
    if (substringIsFound)
    {
        printf("Index of first entry: %zu\n", firstEntryIndex);
    }
    else
    {
        printf("Substring not found\n");
    }
    return SUCCESS;
}
