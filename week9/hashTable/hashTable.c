#include "hashTable.h"
#include "list.h"
#include <stdlib.h>

#define PRIME_BASE 757
#define PRIME_MOD 1000000001

static size_t hash(const char* const key)
{
    size_t result = 0;
    for (size_t i = 0; key[i] != '\0'; ++i)
    {
        result = result * PRIME_BASE + (size_t)key[i];
        result %= PRIME_MOD;
    }
    return result;
}

struct HashTable {
    size_t numberOfBuckets;
    List** buckets;
};

HashTable* createHashTable(const size_t numberOfBuckets)
{
    if (numberOfBuckets == 0)
    {
        return NULL;
    }
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (table == NULL)
    {
        return NULL;
    }
    table->numberOfBuckets = numberOfBuckets;
    table->buckets = (List**)calloc(numberOfBuckets, sizeof(List*));
    if (table->buckets == NULL)
    {
        free(table);
        return NULL;
    }
    return table;
}

void freeHashTable(HashTable** const table)
{
    for (size_t i = 0; i < (*table)->numberOfBuckets; ++i)
    {
        freeList(&(*table)->buckets[i]);
    }
    free((*table)->buckets);
    free(*table);
    *table = NULL;
}

bool add(HashTable* const table, const char* const key)
{
    size_t index = hash(key) % table->numberOfBuckets;
    if (table->buckets[index] == NULL)
    {
        table->buckets[index] = createList();
        if (table->buckets[index] == NULL)
        {
            return true;
        }
    }
    return push(table->buckets[index], key);
}

void printTable(const HashTable* const table)
{
    for (size_t i = 0; i < table->numberOfBuckets; ++i)
    {
        printList(table->buckets[i]);
    }
}

double getLoadFactor(const HashTable* const table)
{
    size_t numberOfElements = 0;
    for (size_t i = 0; i < table->numberOfBuckets; ++i)
    {
        numberOfElements += size(table->buckets[i]);
    }
    return (double)numberOfElements / table->numberOfBuckets;
}

size_t getMaxLength(const HashTable* const table)
{
    size_t maxLength = 0;
    for (size_t i = 0; i < table->numberOfBuckets; ++i)
    {
        maxLength = max(maxLength, size(table->buckets[i]));
    }
    return maxLength;
}

double getAverageLength(const HashTable* const table)
{
    size_t sum = 0;
    size_t numberOfLists = 0;
    for (size_t i = 0; i < table->numberOfBuckets; ++i)
    {
        if (table->buckets[i] != NULL)
        {
            sum += size(table->buckets[i]);
            ++numberOfLists;
        }
    }
    return (double)sum / numberOfLists;
}

unsigned int getNumberOfEntries(const HashTable* const table, const char* const key)
{
    size_t index = hash(key) % table->numberOfBuckets;
    return numberOfEntries(table->buckets[index], key);
}
