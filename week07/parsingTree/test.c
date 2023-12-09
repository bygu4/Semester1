#include "test.h"
#include "parsingTree.h"

#define TEST_FILE_FOR_PARSING_TREE_1 "testFiles/testForParsingTree1.txt"
#define TEST_FILE_FOR_PARSING_TREE_2 "testFiles/testForParsingTree2.txt"
#define TEST_FILE_FOR_PARSING_TREE_3 "testFiles/testForParsingTree3.txt"
#define TEST_FILE_FOR_PARSING_TREE_4 "testFiles/testForParsingTree4.txt"
#define TEST_FILE_FOR_PARSING_TREE_5 "testFiles/testForParsingTree5.txt"

static void printFailedTest(const size_t numberOfTest, const char* const nameOfTest)
{
    printf("Test %zu has failed in %s\n", numberOfTest, nameOfTest);
}

static bool testCaseForParsingTree(const char* const nameOfFile, 
    const int expectedOutput, const int expectedCode)
{
    ParsingTree* tree = NULL;
    int errorCode = buildTree(&tree, nameOfFile);
    if (errorCode != SUCCESS)
    {
        if (errorCode == FILE_NOT_FOUND)
        {
            printf("File not found\n");
        }
        return false;
    }
    const int output = calculateTree(tree, false, &errorCode);
    freeTree(&tree);
    if (errorCode != SUCCESS)
    {
        return errorCode == expectedCode;
    }
    return output == expectedOutput;
}

bool test(void)
{
    const char* const testName = "testForParsingTree";

    const bool testOneIsPassed = testCaseForParsingTree(TEST_FILE_FOR_PARSING_TREE_1, 0, SUCCESS);
    if (!testOneIsPassed)
    {
        printFailedTest(1, testName);
        return false;
    }

    const bool testTwoIsPassed = testCaseForParsingTree(TEST_FILE_FOR_PARSING_TREE_2, 123, SUCCESS);
    if (!testTwoIsPassed)
    {
        printFailedTest(2, testName);
        return false;
    }

    const bool testThreeIsPassed = testCaseForParsingTree(TEST_FILE_FOR_PARSING_TREE_3, 35, SUCCESS);
    if (!testThreeIsPassed)
    {
        printFailedTest(3, testName);
        return false;
    }

    const bool testFourIsPassed = testCaseForParsingTree(TEST_FILE_FOR_PARSING_TREE_4, 360, SUCCESS);
    if (!testFourIsPassed)
    {
        printFailedTest(4, testName);
        return false;
    }

    const bool testFiveIsPassed = testCaseForParsingTree(TEST_FILE_FOR_PARSING_TREE_5, 0, DIVISION_BY_ZERO);
    if (!testFiveIsPassed)
    {
        printFailedTest(5, testName);
        return false;
    }

    return true;
}
