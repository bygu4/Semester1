#include "console.h"
#include "hashTable.h"
#include "str.h"
#include <stdlib.h>

static int readTextAndAdd(HashTable* const table, const char* const nameOfFile)
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

int console(void)
{
    HashTable* table = createHashTable();
    if (table == NULL)
    {
        printf("An error occured\n");
        return BAD_ALLOCATION;
    }
    int errorCode = readTextAndAdd(table, NAME_OF_FILE);
    if (errorCode != SUCCESS)
    {
        printf(errorCode == FILE_NOT_FOUND ? "File not found\n" : "An error occured\n");
        freeHashTable(&table);
        return errorCode;
    }
    printTable(table);
    printf("\n");
    printf("Load factor of table: %g\n", getLoadFactor(table));
    printf("Max length of list: %zu\n", getMaxLength(table));
    printf("Average length of list: %g\n", getAverageLength(table));
    freeHashTable(&table);
    return SUCCESS;
}
