#include "test.h"
#include "str.h"
#include "avlTree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

static bool addKeysToTree(AvlTree* const tree, const char** const keys, const size_t numberOfKeys)
{
    for (size_t i = 0; i < numberOfKeys; ++i)
    {
        bool errorOccured = addNode(tree, keys[i], "");
        if (errorOccured)
        {
            return true;
        }
    }
    return false;
}

static void deleteKeysFromTree(AvlTree* const tree, const char** const keys, const size_t numberOfKeys)
{
    for (size_t i = 0; i < numberOfKeys; ++i)
    {
        deleteNode(tree, keys[i]);
    }
}

static bool testCaseForAddNode(const char** const keysToAdd, const size_t numberOfKeys)
{
    AvlTree* tree = createTree();
    if (tree == NULL)
    {
        printf("Failed to create tree\n");
        return false;
    }
    bool errorOccured = addKeysToTree(tree, keysToAdd, numberOfKeys);
    if (errorOccured)
    {
        freeTree(&tree);
        return false;
    }
    for (size_t i = 0; i < numberOfKeys; ++i)
    {
        if (!findKey(tree, keysToAdd[i]))
        {
            freeTree(&tree);
            return false;
        }
    }
    freeTree(&tree);
    return true;
}

static bool testForAddNode(void)
{
    const char* const testName = "testForAddNode";

    char* keys1[20] = { "90", "2", "0", "30", "42", "55", "130", "32", "abcde", 
        "ololo", "lolol", "132", "15", "6", "3", "7", "19", "20", "eq", "qe" };
    bool testOneIsPassed = testCaseForAddNode(keys1, 20);
    if (!testOneIsPassed)
    {
        printFailedTest(1, testName);
        return false;
    }

    char* keys2[10] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };
    bool testTwoIsPassed = testCaseForAddNode(keys2, 10);
    if (!testTwoIsPassed)
    {
        printFailedTest(2, testName);
        return false;
    }

    bool testThreeIsPassed = testCaseForAddNode(NULL, 0);
    if (!testThreeIsPassed)
    {
        printFailedTest(3, testName);
        return false;
    }

    return true;
}

static bool testCaseForDeleteNode(const char** const keysToAdd, const char** const keysToDelete, 
    const size_t numberOfKeysToAdd, const size_t numberOfKeysToDelete)
{
    AvlTree* tree = createTree();
    if (tree == NULL)
    {
        printf("Failed to create tree\n");
        return false;
    }
    bool errorOccured = addKeysToTree(tree, keysToAdd, numberOfKeysToAdd);
    if (errorOccured)
    {
        freeTree(&tree);
        printf("Failed to add keys\n");
        return false;
    }
    deleteKeysFromTree(tree, keysToDelete, numberOfKeysToDelete);
    for (size_t i = 0; i < numberOfKeysToDelete; ++i)
    {
        if (findKey(tree, keysToDelete[i]))
        {
            freeTree(&tree);
            return false;
        }
    }
    freeTree(&tree);
    return true;
}

static bool testForDeleteNode(void)
{
    const char* const testName = "testForDeleteNode";

    char* keysToAdd1[20] = { "60", "0", "1", "1", "23", "23", "-100", "-20", "99", 
        "54", "42", "65", "-89", "-7", "0", "18", "-40", "100", "22", "-21" };
    char* keysToDelete1[12] = { "54", "-40", "22", "60", "1", "0", "-100", "99", "9999", "-10000", "43434", "23" };
    bool testOneIsPassed = testCaseForDeleteNode(keysToAdd1, keysToDelete1, 20, 12);
    if (!testOneIsPassed)
    {
        printFailedTest(1, testName);
        return false;
    }

    char** keysToAdd2 = NULL;
    char* keysToDelete2[6] = { "0", "1", "2", "3", "4", "5" };
    bool testTwoIsPassed = testCaseForDeleteNode(keysToAdd2, keysToDelete2, 0, 6);
    if (!testTwoIsPassed)
    {
        printFailedTest(2, testName);
        return false;
    }

    char* keysToAdd3[14] = { "-3", "-3", "-2", "-2", "-1", "-1", "0", "0", "1", "1", "2", "2", "3", "3"};
    char* keysToDelete3[7] = { "-3", "-2", "-1", "0", "1", "2", "3" };
    bool testThreeIsPassed = testCaseForDeleteNode(keysToAdd3, keysToDelete3, 14, 7);
    if (!testThreeIsPassed)
    {
        printFailedTest(3, testName);
        return false;
    }

    return true;
}

static bool testCaseForGetData(AvlTree* const tree,
    const char* key, const char* const data, const bool keyIsInTree)
{
    char* foundData = getData(tree, key);
    if (foundData == NULL)
    {
        return !keyIsInTree;
    }
    return stringsAreEqual(foundData, data);
}

static bool testForGetData(void)
{
    const char* const testName = "testForGetData";

    AvlTree* tree = createTree();
    if (tree == NULL)
    {
        printf("Failed to create tree in %s\n", testName);
        return false;
    }

    char* keys[10] = { "0", "-4", "4", "-2", "2", "-6", "6", "-3", "3", "8" };
    bool errorOccured = addKeysToTree(tree, keys, 10) || 
        addNode(tree, "0", "test1") || addNode(tree, "3", "test2") || addNode(tree, "-1", "test3");
    if (errorOccured)
    {
        freeTree(&tree);
        printf("Failed to add keys in %s\n", testName);
        return false;
    }

    bool testOneIsPassed = testCaseForGetData(tree, "0", "test1", true);
    if (!testOneIsPassed)
    {
        freeTree(&tree);
        printFailedTest(1, testName);
        return false;
    }

    bool testTwoIsPassed = testCaseForGetData(tree, "3", "test2", true);
    if (!testTwoIsPassed)
    {
        freeTree(&tree);
        printFailedTest(2, testName);
        return false;
    }

    bool testThreeIsPassed = testCaseForGetData(tree, "-1", "test3", true);
    if (!testThreeIsPassed)
    {
        freeTree(&tree);
        printFailedTest(3, testName);
        return false;
    }

    bool testFourIsPassed = testCaseForGetData(tree, "5", "test4", false);
    freeTree(&tree);
    if (!testFourIsPassed)
    {
        printFailedTest(4, testName);
        return false;
    }

    return true;
}

static bool testForBalance(const size_t numberOfKeys, const size_t numberOfSearches, const double timeLimit)
{
    AvlTree* tree = createTree();
    if (tree == NULL)
    {
        printf("Failed to create tree\n");
        return false;
    }
    srand(time(NULL));
    double start = clock() / CLOCKS_PER_SEC;
    for (size_t i = 0; i < numberOfKeys; ++i)
    {
        int number = rand() % numberOfKeys;
        char key[12] = { '\0' };
        sprintf(key, "%d", number);
        bool errorOccured = addNode(tree, key, "");
        if (errorOccured)
        {
            freeTree(&tree);
            printf("Failed to add keys\n");
            return false;
        }
        double time = clock() / CLOCKS_PER_SEC;
        if (time - start > timeLimit)
        {
            freeTree(&tree);
            printf("Test for balance has failed\n");
            return false;
        }
    }
    for (size_t i = 0; i < numberOfSearches; ++i)
    {
        int number = rand() % numberOfKeys;
        char key[12] = { '\0' };
        sprintf(key, "%d", number);
        findKey(tree, key);
        double time = clock() / CLOCKS_PER_SEC;
        if (time - start > timeLimit)
        {
            freeTree(&tree);
            printf("Test for balance has failed\n");
            return false;
        }
    }
    freeTree(&tree);
    return true;
}

static bool testForStrings(void)
{
    return testForStringsAreEqual() && testForCopyString();
}

static bool testForAvlTree(void)
{
    return testForAddNode() && testForDeleteNode() && testForGetData() && testForBalance(1000000, 1000000, 5);
}

bool test(void)
{
    return testForStrings() && testForAvlTree();
}
