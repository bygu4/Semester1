#include "test.h"
#include "priorityQueue.h"
#include <stdio.h>

static printFailedTest(const size_t numeberOfTest)
{
    printf("Test %zu has failed\n", numeberOfTest);
}

static bool testCase(const unsigned int* const valuesToEnqueue, const int* const keysToEnqueue,
    const unsigned int* dequeueExpectedValues, const size_t numberOfEnqueues, const size_t numberOfDequeues)
{
    PriorityQueue* queue = createQueue();
    if (queue == NULL)
    {
        printf("Failed to create queue\n");
        return false;
    }
    for (size_t i = 0; i < numberOfEnqueues; ++i)
    {
        bool errorOccured = enqueue(queue, valuesToEnqueue[i], keysToEnqueue[i]);
        if (errorOccured)
        {
            freeQueue(&queue);
            return false;
        }
    }
    bool testPassed = true;
    for (size_t i = 0; i < numberOfDequeues; ++i)
    {
        testPassed = dequeue(queue) == dequeueExpectedValues[i];
        if (!testPassed)
        {
            break;
        }
    }
    freeQueue(&queue);
    return testPassed;
}

bool test(void)
{
    unsigned int values1[6] = { 1, 2, 3, 4, 5, 6 };
    int keys1[6] = { 2, 4, 6, 1, 3, 5 };
    int expectedOutput1[6] = { 3, 6, 2, 5, 1, 4 };
    if (!testCase(values1, keys1, expectedOutput1, 6, 6))
    {
        printFailedTest(1);
        return false;
    }

    unsigned int values2[1] = { 10 };
    int keys2[1] = { 5 };
    int expectedOutput2[2] = { 10, -1 };
    if (!testCase(values2, keys2, expectedOutput2, 1, 2))
    {
        printFailedTest(2);
        return false;
    }

    unsigned int values3[4] = { 9, 8, 7, 6 };
    int keys3[4] = { 2, 2, 2, 2 };
    int expectedOutput3[4] = { 9, 8, 7, 6 };
    if (!testCase(values3, keys3, expectedOutput3, 4, 4))
    {
        printFailedTest(3);
        return false;
    }

    return true;
}
