#include "test.h"
#include "str.h"
#include "SearchTree.h"
#include <stdio.h>
#include <stdlib.h>

static void printFailedTest(const size_t numberOfTest, const char* const nameOfTest)
{
    printf("Test %zu has failed in %s\n", numberOfTest, nameOfTest);
}

static bool testForStringsAreEqual(void)
{
    if (!stringsAreEqual("", ""))
    {
        printFailedTest(1, "testForStringsAreEqual");
        return false;
    }

    if (!stringsAreEqual("qwerty", "qwerty"))
    {
        printFailedTest(2, "testForStringsAreEqual");
        return false;
    }

    if (stringsAreEqual("abcd", "abc"))
    {
        printFailedTest(3, "testForStringsAreEqual");
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
    if (!testCaseForCopyString(""))
    {
        printFailedTest(1, "testForCopyString");
        return false;
    }

    if (!testCaseForCopyString("ABCDEF"))
    {
        printFailedTest(2, "testForCopyString");
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

static bool testCaseForAddNode(const int* const keysToAdd, const int* const expectedTree,
    const size_t numberOfKeys, const size_t sizeOfTree)
{
    SearchTree* tree = createTree();
    if (tree == NULL)
    {
        printf("Failed to create tree\n");
        return false;
    }
    bool errorOccured = addKeysToTree(tree, keysToAdd, numberOfKeys);
    bool testIsPassed = !errorOccured && checkTreeByPreorder(tree, expectedTree, sizeOfTree);
    freeTree(&tree);
    return testIsPassed;
}

static bool testForAddNode(void)
{
    int keys1[10] = { 8,
                  5,      10,
               2,    6, 9,   11,
            1,    3,            15 };

    bool testOneIsPassed = testCaseForAddNode(keys1, keys1, 10, 10);
    if (!testOneIsPassed)
    {
        printFailedTest(1, "testForAddNode");
        return false;
    }

    int* keys2 = NULL;
    bool testTwoIsPassed = testCaseForAddNode(keys2, keys2, 0, 0);
    if (!testTwoIsPassed)
    {
        printFailedTest(2, "testForAddNode");
        return false;
    }

    int keys3[8] = { 1, 1, 2, 2, 3, 3, 4, 4 };
    int tree3[4] = { 1, 2, 3, 4 };
    bool testThreeIsPassed = testCaseForAddNode(keys3, tree3, 8, 4);
    if (!testThreeIsPassed)
    {
        printFailedTest(3, "testForAddNode");
        return false;
    }

    return true;
}

static bool testCaseForDeleteNode(const int* const keysToAdd, const int* const keysToDelete,
    const int* const expectedTree, const size_t numberOfKeysToAdd, const size_t numberOfKeysToDelete,
    const size_t sizeOfTree)
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
        freeTree(&tree);
        return false;
    }
    deleteKeysFromTree(tree, keysToDelete, numberOfKeysToDelete);
    bool testIsPassed = checkTreeByPreorder(tree, expectedTree, sizeOfTree);
    freeTree(&tree);
    return testIsPassed;
}

static bool testForDeleteNode(void)
{
    int keysToAdd1[15] = { 8,
                      5,       12,
                  3,    7,  10,    14,
              -1,  4,  6,     11,      80,
                 0,                 45,   82 };

    int keysToDelete1[6] = { 0, 45, 80, 3, 12, 8 };

    int expectedTree1[9] = { 7,
                          5,     11,
                       4,   6, 10,  14,
                    -1,                82 };

    bool testOneIsPassed = testCaseForDeleteNode(keysToAdd1, keysToDelete1, expectedTree1, 14, 6, 8);
    if (!testOneIsPassed)
    {
        printFailedTest(1, "testForDeleteNode");
        return false;
    }

    int* keysToAdd2 = NULL;
    int keysToDelete2[5] = { 1, 2, 3, 4, 5 };
    bool testTwoIsPassed = testCaseForDeleteNode(keysToAdd2, keysToDelete2, NULL, 0, 5, 0);
    if (!testTwoIsPassed)
    {
        printFailedTest(2, "testForDeleteNode");
        return false;
    }

    int keysToAdd3[7] = { 0, 2, 1, 3, -2, -1, -3 };
    int keysToDelete3[14] = { -3, -3, -2, -2, -1, -1, 0, 0, 1, 1, 2, 2, 3, 3 };
    bool testThreeIsPassed = testCaseForDeleteNode(keysToAdd3, keysToDelete3, NULL, 7, 14, 0);
    if (!testThreeIsPassed)
    {
        printFailedTest(3, "testForDeleteNode");
        return false;
    }

    return true;
}

static bool testCaseForFindKeyAndGetData(SearchTree* const tree,
    const int key, const char* const data, const bool keyIsInTree)
{
    bool keyFound = findKey(tree, key);
    if (keyFound != keyIsInTree)
    {
        return false;
    }
    char* foundData = getData(tree, key);
    if (foundData == NULL)
    {
        return !keyIsInTree;
    }
    return stringsAreEqual(foundData, data);
}

static bool testForFindKeyAndGetData(void)
{
    SearchTree* tree = createTree();
    if (tree == NULL)
    {
        printf("Failed to create tree in testForFindKeyAndGetData\n");
        return false;
    }

    int keys[10] = { 0, -4, 4, -2, 2, -6, 6, -3, 3, 8 };
    bool errorOccured = addKeysToTree(tree, keys, 10);
    if (errorOccured)
    {
        freeTree(&tree);
        printf("Failed to add keys in testForFindKeyAndGetData\n");
        return false;
    }
    addNode(tree, 0, "test1");
    addNode(tree, 3, "test2");
    addNode(tree, -1, "test3");

    bool testOneIsPassed = testCaseForFindKeyAndGetData(tree, 0, "test1", true);
    if (!testOneIsPassed)
    {
        freeTree(&tree);
        printFailedTest(1, "testForFindKeyAndGetData");
        return false;
    }

    bool testTwoIsPassed = testCaseForFindKeyAndGetData(tree, 3, "test2", true);
    if (!testTwoIsPassed)
    {
        freeTree(&tree);
        printFailedTest(2, "testForFindKeyAndGetData");
        return false;
    }

    bool testThreeIsPassed = testCaseForFindKeyAndGetData(tree, -1, "test3", true);
    if (!testThreeIsPassed)
    {
        freeTree(&tree);
        printFailedTest(3, "testForFindKeyAndGetData");
        return false;
    }

    bool testFourIsPassed = testCaseForFindKeyAndGetData(tree, 5, "test4", false);
    freeTree(&tree);
    if (!testFourIsPassed)
    {
        printFailedTest(4, "testForFindKeyAndGetData");
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
    return testForAddNode() && testForDeleteNode() && testForFindKeyAndGetData();
}

bool test(void)
{
    return testForStrings() && testForSearchTree();
}
