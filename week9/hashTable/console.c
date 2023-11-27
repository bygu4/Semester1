#include "console.h"
#include "readFileAndAdd.h"

int console(void)
{
    HashTable* table = createHashTable();
    if (table == NULL)
    {
        printf("An error occured\n");
        return BAD_ALLOCATION;
    }
    int errorCode = readFileAndAdd(table, NAME_OF_FILE);
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
