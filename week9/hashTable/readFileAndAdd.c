#include "readFileAndAdd.h"
#include "str.h"
#include <stdlib.h>

int readFileAndAdd(HashTable* const table, const char* const nameOfFile)
{
    FILE* inputFile = NULL;
    int errorCode = fopen_s(&inputFile, nameOfFile, "r");
    if (errorCode != SUCCESS)
    {
        return errorCode;
    }
    bool errorOccured = false;
    while (!feof(inputFile))
    {
        char* word = getWord(inputFile);
        if (!stringsAreEqual(word, ""))
        {
            errorOccured = add(table, word);
        }
        free(word);
        if (errorOccured)
        {
            break;
        }
    }
    fclose(inputFile);
    return errorOccured ? BAD_ALLOCATION : SUCCESS;
}
