#include "test.h"
#include "str.h"
#include "readFileAndAdd.h"
#include <stdlib.h>
#include <time.h>

#define STR_TEST_1 "testFiles/strTest1.txt"
#define STR_TEST_2 "testFiles/strTest2.txt"
#define HT_TEST_1 "testFiles/htTest1.txt"
#define HT_TEST_2 "testFiles/htTest2.txt"

static void printFailedTest(const size_t numberOfTest, const char* const nameOfTest)
{
    printf("Test %zu has failed in %s\n", numberOfTest, nameOfTest);
}

static bool testForStringsAreEqual(void)
{
    const char* const testName = "testForStringsAreEqual";

    if (!stringsAreEqual("", ""))
    {
        printFailedTest(1, testName);
        return false;
    }

    if (!stringsAreEqual("qwerty", "qwerty"))
    {
        printFailedTest(2, testName);
        return false;
    }

    if (stringsAreEqual("abcd", "abc"))
    {
        printFailedTest(3, testName);
        return false;
    }

    return true;
}

static bool testCaseForCopyString(const char* const string)
{
    char* copy = copyString(string);
    bool testIsPassed = copy != NULL && stringsAreEqual(copy, string);
    free(copy);
    return testIsPassed;
}

static bool testForCopyString(void)
{
    const char* const testName = "testForCopyString";

    if (!testCaseForCopyString(""))
    {
        printFailedTest(1, testName);
        return false;
    }

    if (!testCaseForCopyString("ABCDEF"))
    {
        printFailedTest(2, testName);
        return false;
    }

    return true;
}

static bool testCaseForGetWord(const char* const nameOfFile, 
    const char** const expectedOutput, const size_t numberOfWords)
{
    FILE* testFile = NULL;
    int errorCode = fopen_s(&testFile, nameOfFile, "r");
    if (errorCode != SUCCESS)
    {
        printf("Failed to open file\n");
        return false;
    }
    bool testIsPassed = true;
    size_t i = 0;
    for (; i < numberOfWords && !feof(testFile); ++i)
    {
        char* word = getWord(testFile);
        testIsPassed = word != NULL && stringsAreEqual(word, expectedOutput[i]);
        free(word);
        if (!testIsPassed)
        {
            break;
        }
    }
    fclose(testFile);
    return testIsPassed && i == numberOfWords;
}

static bool testForGetWord(void)
{
    const char* const testName = "testForGetWord";

    char* output1[5] = { "aaaaa", "bbbb", "ccc", "dd", "1" };
    bool testOneIsPassed = testCaseForGetWord(STR_TEST_1, output1, 5);
    if (!testOneIsPassed)
    {
        printFailedTest(1, testName);
        return false;
    }

    char* output2[1] = { "" };
    bool testTwoIsPassed = testCaseForGetWord(STR_TEST_2, output2, 1);
    if (!testTwoIsPassed)
    {
        printFailedTest(2, testName);
        return false;
    }

    return true;
}

static bool testCaseForHashTable(const char* const nameOfFile, const char** const keys, 
    const unsigned int* const entries, const size_t numberOfKeys, const size_t numberOfBuckets)
{
    HashTable* table = createHashTable(numberOfBuckets);
    if (table == NULL)
    {
        printf("Failed to create table\n");
        return false;
    }
    int errorCode = readFileAndAdd(table, nameOfFile);
    if (errorCode != SUCCESS)
    {
        printf("Failed to read file\n");
        freeHashTable(&table);
        return false;
    }
    bool testIsPassed = true;
    for (size_t i = 0; i < numberOfKeys; ++i)
    {
        testIsPassed = getNumberOfEntries(table, keys[i]) == entries[i];
        if (!testIsPassed)
        {
            break;
        }
    }
    freeHashTable(&table);
    return testIsPassed;
}

static char* getRandomKey(const size_t randLimit)
{
    int number = rand() % randLimit;
    char key[12] = { '\0' };
    sprintf_s(key, 12, "%d", number);
    return key;
}

static bool loadTest(const size_t numberOfKeys, const size_t numberOfSearches, 
    const size_t numberOfBuckets, const double timeLimit)
{
    HashTable* table = createHashTable(numberOfBuckets);
    if (table == NULL)
    {
        printf("Failed to create table\n");
        return false;
    }
    srand(time(NULL));
    double start = clock() / CLOCKS_PER_SEC;
    for (size_t i = 0; i < numberOfKeys; ++i)
    {
        char* key = getRandomKey(numberOfKeys);
        bool errorOccured = add(table, key);
        double time = clock() / CLOCKS_PER_SEC;
        if (errorOccured || time - start > timeLimit)
        {
            if (errorOccured)
            {
                printf("Failed to add keys\n");
            }
            freeHashTable(&table);
            return false;
        }
    }
    for (size_t i = 0; i < numberOfSearches; ++i)
    {
        char* key = getRandomKey(numberOfKeys);
        getNumberOfEntries(table, key);
        double time = clock() / CLOCKS_PER_SEC;
        if (time - start > timeLimit)
        {
            freeHashTable(&table);
            return false;
        }
    }
    freeHashTable(&table);
    return true;
}

static bool testForHashTable(void)
{
    const char* const testName = "testForHashTable";

    char* keys1[23] = { "Hey,", "Jude,", "don't", "make", "it", "bad",
        "Take", "a", "sad", "song", "and", "better",
        "Remember", "to", "let", "her", "into", "your", "heart",
        "Then", "you", "can", "start" };
    unsigned int entries1[23] = { 1, 1, 1, 3, 3, 1, 1, 
        1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    bool testOneIsPassed = testCaseForHashTable(HT_TEST_1, keys1, entries1, 23, 5);
    if (!testOneIsPassed)
    {
        printFailedTest(1, testName);
        return false;
    }

    char* keys2[4] = { "a", "b", "c", "e"};
    unsigned int entries2[4] = { 7, 3, 4, 0 };
    bool testTwoIsPassed = testCaseForHashTable(HT_TEST_2, keys2, entries2, 4, 1);
    if (!testTwoIsPassed)
    {
        printFailedTest(2, testName);
        return false;
    }

    bool testThreeIsPassed = loadTest(1000000, 1000000, 2048, 5);
    if (!testThreeIsPassed)
    {
        printFailedTest(3, testName);
        return false;
    }

    return true;
}

static bool testForStrings(void)
{
    return testForStringsAreEqual() && testForCopyString() && testForGetWord();
}

bool test(void)
{
    return testForStrings() && testForHashTable();
}
