#include "test.h"
#include "distribute.h"
#include <stdlib.h>

#define TEST_FILE_1 "testFiles/test1.txt"
#define TEST_FILE_2 "testFiles/test2.txt"
#define TEST_FILE_3 "testFiles/test3.txt"
#define TEST_FILE_4 "testFiles/test4.txt"
#define TEST_FILE_5 "testFiles/test5.txt"
#define TEST_FILE_6 "testFiles/test6.txt"

static void printFailedTest(const size_t numberOfTest)
{
    printf("Test %zu has failed\n", numberOfTest);
}

static void freeTable(unsigned int*** const table, const size_t rows)
{
    for (size_t i = 0; i < rows; ++i)
    {
        free((*table)[i]);
    }
    free(*table);
    *table = NULL;
}

static unsigned int** makeTable(const unsigned int staticTable[],
    const size_t* const lengths, const size_t rows, const size_t columns)
{
    unsigned int** table = (unsigned int**)malloc(rows * sizeof(unsigned int*));
    if (table == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < rows; ++i)
    {
        table[i] = (unsigned int*)malloc(lengths[i] * sizeof(unsigned int));
        if (table[i] == NULL)
        {
            freeTable(&table, i);
            return NULL;
        }
        for (size_t j = 0; j < lengths[i]; ++j)
        {
            table[i][j] = staticTable[i * columns + j];
        }
    }
    return table;
}

static bool testCase(const char* const nameOfFile, const unsigned int staticStates[],
    const size_t* const sizeOfState, const size_t numberOfStates, const size_t maxCities)
{
    unsigned int** states = makeTable(staticStates, sizeOfState, numberOfStates, maxCities);
    if (states == NULL)
    {
        printf("Failed to create table\n");
        return false;
    }
    Graph* graph = NULL;
    int errorCode = createGraph(&graph, nameOfFile);
    if (errorCode != SUCCESS)
    {
        printf(errorCode == FILE_NOT_FOUND ? "File not found\n" : "Failed to create graph\n");
        freeTable(&states, numberOfStates);
        return false;
    }
    distribute(graph);
    bool testIsPassed = checkStates(graph, states, sizeOfState, numberOfStates);
    freeGraph(&graph);
    freeTable(&states, numberOfStates);
    return testIsPassed;
}

bool test(void)
{
    bool testOneIsPassed = testCase(TEST_FILE_1, NULL, NULL, 0, 0);
    if (!testOneIsPassed)
    {
        printFailedTest(1);
        return false;
    }

    bool testTwoIsPassed = testCase(TEST_FILE_2, NULL, NULL, 0, 0);
    if (!testTwoIsPassed)
    {
        printFailedTest(2);
        return false;
    }

    unsigned int states3[4][1] = { { 1 }, { 2 }, { 3 }, { 4 } };
    size_t sizeOfState3[4] = { 1, 1, 1, 1 };
    bool testThreeIsPassed = testCase(TEST_FILE_3, states3, sizeOfState3, 4, 1);
    if (!testThreeIsPassed)
    {
        printFailedTest(3);
        return false;
    }

    unsigned int states4[1][3] = { { 1, 2, 3 } };
    size_t sizeOfState4[1] = { 3 };
    bool testFourIsPassed = testCase(TEST_FILE_4, states4, sizeOfState4, 1, 3);
    if (!testFourIsPassed)
    {
        printFailedTest(4);
        return false;
    }

    unsigned int states5[2][5] = { { 1 }, { 2, 3, 5, 6, 4 } };
    size_t sizeOfState5[2] = { 1, 5 };
    bool testFiveIsPassed = testCase(TEST_FILE_5, states5, sizeOfState5, 2, 5);
    if (!testFiveIsPassed)
    {
        printFailedTest(5);
        return false;
    }

    unsigned int states6[3][5] = { { 2, 4, 5, 1, 3 }, { 6, 8, 7, 9, 10 }, { 12, 13, 11 } };
    size_t sizeOfState6[3] = { 5, 5, 3 };
    bool testSixIsPassed = testCase(TEST_FILE_6, states6, sizeOfState6, 3, 5);
    if (!testSixIsPassed)
    {
        printFailedTest(6);
        return false;
    }
    
    return true;
}
