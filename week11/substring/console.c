#include "console.h"
#include "getSubstringFirstEntry.h"
#include "str.h"
#include <stdlib.h>

int console(void)
{
    char* fileData = NULL;
    size_t lengthOfFile = 0;
    int errorCode = readFile(&fileData, NAME_OF_FILE, &lengthOfFile);
    if (errorCode != SUCCESS)
    {
        printf(errorCode == FILE_NOT_FOUND ? "File not found\n" : "An error occured\n");
        return errorCode;
    }
    printf("Enter a substring to find: ");
    size_t lengthOfString = 0;
    char* inputString = getString('\n', &lengthOfString);
    if (inputString == NULL)
    {
        printf("An error occured\n");
        free(fileData);
        return BAD_ALLOCATION;
    }
    bool substringIsFound = false;
    bool errorOccured = false;
    size_t firstEntryIndex = getSubstringFirstEntry(inputString, fileData, 
        lengthOfFile, &substringIsFound, &errorOccured);
    free(fileData);
    free(inputString);
    if (errorOccured)
    {
        printf("An error occured\n");
        return BAD_ALLOCATION;
    }
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
