#include "test.h"
#include "distribute.h"

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

static bool testCase(const char* const nameOfFile, const unsigned int states[32][32],
    const size_t sizeOfState[32])
{
    Graph* graph = NULL;
    int errorCode = createGraph(&graph, nameOfFile);
    if (errorCode != SUCCESS)
    {
        printf(errorCode == FILE_NOT_FOUND ? "File not found\n" : "Failed to create graph\n");
        return false;
    }
    distribute(graph);
    bool testIsPassed = checkStates(graph, states, sizeOfState);
    freeGraph(&graph);
    return testIsPassed;
}

bool test(void)
{
    bool testOneIsPassed = testCase(TEST_FILE_1, NULL, NULL);
    if (!testOneIsPassed)
    {
        printFailedTest(1);
        return false;
    }

    bool testTwoIsPassed = testCase(TEST_FILE_2, NULL, NULL);
    if (!testTwoIsPassed)
    {
        printFailedTest(2);
        return false;
    }

    unsigned int states3[32][32] = { { 1 }, { 2 }, { 3 }, { 4 } };
    size_t sizeOfState3[32] = { 1, 1, 1, 1 };
    bool testThreeIsPassed = testCase(TEST_FILE_3, states3, sizeOfState3);
    if (!testThreeIsPassed)
    {
        printFailedTest(3);
        return false;
    }

    unsigned int states4[32][32] = { { 1, 2, 3 } };
    size_t sizeOfState4[32] = { 3 };
    bool testFourIsPassed = testCase(TEST_FILE_4, states4, sizeOfState4);
    if (!testFourIsPassed)
    {
        printFailedTest(4);
        return false;
    }

    unsigned int states5[32][32] = { { 1 }, { 2, 3, 5, 6, 4 } };
    size_t sizeOfState5[32] = { 1, 5 };
    bool testFiveIsPassed = testCase(TEST_FILE_5, states5, sizeOfState5);
    if (!testFiveIsPassed)
    {
        printFailedTest(5);
        return false;
    }

    unsigned int states6[32][32] = { { 2, 4, 5, 1, 3 }, { 6, 8, 7, 9, 10 }, { 12, 13, 11 } };
    size_t sizeOfState6[32] = { 5, 5, 3 };
    bool testSixIsPassed = testCase(TEST_FILE_6, states6, sizeOfState6);
    if (!testSixIsPassed)
    {
        printFailedTest(6);
        return false;
    }
    
    return true;
}
