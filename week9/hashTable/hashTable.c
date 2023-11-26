#include "hashTable.h"
#include "list.h"
#include <stdlib.h>
#include <math.h>

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
    List* buckets[NUMBER_OF_BUCKETS];
};

HashTable* createHashTable(void)
{
    return (HashTable*)calloc(1, sizeof(HashTable));
}

bool add(HashTable* const table, const char* const key)
{
    size_t index = hash(key) % NUMBER_OF_BUCKETS;
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
    for (size_t i = 0; i < NUMBER_OF_BUCKETS; ++i)
    {
        printList(table->buckets[i]);
    }
}

void freeHashTable(HashTable** const table)
{
    for (size_t i = 0; i < NUMBER_OF_BUCKETS; ++i)
    {
        freeList(&(*table)->buckets[i]);
    }
    free(*table);
    *table = NULL;
}

double getLoadFactor(const HashTable* const table)
{
    size_t numberOfElements = 0;
    for (size_t i = 0; i < NUMBER_OF_BUCKETS; ++i)
    {
        numberOfElements += size(table->buckets[i]);
    }
    return (double)numberOfElements / NUMBER_OF_BUCKETS;
}

size_t getMaxLength(const HashTable* const table)
{
    size_t maxLength = 0;
    for (size_t i = 0; i < NUMBER_OF_BUCKETS; ++i)
    {
        maxLength = max(maxLength, size(table->buckets[i]));
    }
    return maxLength;
}

double getAverageLength(const HashTable* const table)
{
    size_t sum = 0;
    size_t numberOfLists = 0;
    for (size_t i = 0; i < NUMBER_OF_BUCKETS; ++i)
    {
        if (table->buckets[i] != NULL)
        {
            sum += size(table->buckets[i]);
            ++numberOfLists;
        }
    }
    return (double)sum / numberOfLists;
}
