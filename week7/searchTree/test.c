#include "test.h"
#include "str.h"
#include "searchTree.h"
#include <stdio.h>
#include <stdlib.h>

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

static bool addKeysToTree(SearchTree* const tree, const int* const keys, const size_t numberOfKeys)
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

static void deleteKeysFromTree(SearchTree* const tree, const int* const keys, const size_t numberOfKeys)
{
    for (size_t i = 0; i < numberOfKeys; ++i)
    {
        deleteNode(tree, keys[i]);
    }
}

static bool testCaseForAddNode(const int* const keysToAdd, const size_t numberOfKeys)
{
    SearchTree* tree = createTree();
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
        if (!findKey(tree, keysToAdd[i]))
        {
            freeTree(&tree);
            return false;
        }
    freeTree(&tree);
    return true;
}

static bool testForAddNode(void)
{
    const char* const testName = "testForAddNode";

    int keys1[20] = { 60, 54, -100, 0, 0, -1, -1, 99, -20, 42, 30, -5, 10, 12, 76, 30, 31, 1, 2, 40 };
    bool testOneIsPassed = testCaseForAddNode(keys1, 20);
    if (!testOneIsPassed)
    {
        printFailedTest(1, testName);
        return false;
    }

    int keys2[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
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

static bool testCaseForDeleteNode(const int* const keysToAdd, const int* const keysToDelete, 
    const size_t numberOfKeysToAdd, const size_t numberOfKeysToDelete)
{
    SearchTree* tree = createTree();
    if (tree == NULL)
    {
        printf("Failed to create tree\n");
        return false;
    }
    bool errorOccured = addKeysToTree(tree, keysToAdd, numberOfKeysToAdd);
    if (errorOccured)
    {
        printf("Failed to add keys\n");
        freeTree(&tree);
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

    int keysToAdd1[20] = { 60, 0, 1, 1, 23, 23, -100, -20, 99, 54, 42, 65, -89, -7, 0, 18, -40, 100, 22, -21 };
    int keysToDelete1[12] = {54, -40, 22, 60, 1, 0, -100, 99, 9999, -10000, 43434, 23};
    bool testOneIsPassed = testCaseForDeleteNode(keysToAdd1, keysToDelete1, 20, 12);
    if (!testOneIsPassed)
    {
        printFailedTest(1, testName);
        return false;
    }

    int* keysToAdd2 = NULL;
    int keysToDelete2[6] = { 0, 1, 2, 3, 4, 5 };
    bool testTwoIsPassed = testCaseForDeleteNode(keysToAdd2, keysToDelete2, 0, 6);
    if (!testTwoIsPassed)
    {
        printFailedTest(2, testName);
        return false;
    }

    int keysToAdd3[14] = { 0, 0, 2, 2, 1, 1, 3, 3, -2, -2, -1, -1, -3, -3 };
    int keysToDelete3[7] = { -3, -2, -1, 0, 1, 2, 3 };
    bool testThreeIsPassed = testCaseForDeleteNode(keysToAdd3, keysToDelete3, 14, 7);
    if (!testThreeIsPassed)
    {
        printFailedTest(3, testName);
        return false;
    }

    return true;
}

static bool testCaseForGetData(SearchTree* const tree,
    const int key, const char* const data, const bool keyIsInTree)
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

    SearchTree* tree = createTree();
    if (tree == NULL)
    {
        printf("Failed to create tree in %s\n", testName);
        return false;
    }

    int keys[10] = { 0, -4, 4, -2, 2, -6, 6, -3, 3, 8 };
    bool errorOccured = addKeysToTree(tree, keys, 10);
    if (errorOccured)
    {
        freeTree(&tree);
        printf("Failed to add keys in %s\n", testName);
        return false;
    }
    addNode(tree, 0, "test1");
    addNode(tree, 3, "test2");
    addNode(tree, -1, "test3");

    bool testOneIsPassed = testCaseForGetData(tree, 0, "test1", true);
    if (!testOneIsPassed)
    {
        freeTree(&tree);
        printFailedTest(1, testName);
        return false;
    }

    bool testTwoIsPassed = testCaseForGetData(tree, 3, "test2", true);
    if (!testTwoIsPassed)
    {
        freeTree(&tree);
        printFailedTest(2, testName);
        return false;
    }

    bool testThreeIsPassed = testCaseForGetData(tree, -1, "test3", true);
    if (!testThreeIsPassed)
    {
        freeTree(&tree);
        printFailedTest(3, testName);
        return false;
    }

    bool testFourIsPassed = testCaseForGetData(tree, 5, "test4", false);
    freeTree(&tree);
    if (!testFourIsPassed)
    {
        printFailedTest(4, testName);
        return false;
    }

    return true;
}

static bool testForStrings(void)
{
    return testForStringsAreEqual() && testForCopyString();
}

static bool testForSearchTree(void)
{
    return testForAddNode() && testForDeleteNode() && testForGetData();
}

bool test(void)
{
    return testForStrings() && testForSearchTree();
}
