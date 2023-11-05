#include "test.h"
#include "getInt.h"
#include "parsingTree.h"

static void printFailedTest(const size_t numberOfTest, const char* const nameOfTest)
{
    printf("Test %zu has failed in %s\n", numberOfTest, nameOfTest);
}

static bool testCaseForGetInt(FILE* const stream, const int expectedOutput)
{
    bool errorOccured = false;
    const int output = getInt(stream, &errorOccured);
    bool testIsPassed = !errorOccured && output == expectedOutput;
    return testIsPassed;
}

static bool testForGetInt(void)
{
    const char* const testName = "testForGetInt";

    FILE* testFile = NULL;
    int errorCode = fopen_s(&testFile, TEST_FILE_FOR_GET_INT, "r");
    if (errorCode != SUCCESS)
    {
        printf("Failed to open file in %s\n", testName);
        return false;
    }

    bool testIsPassed = true;
    const int expectation[6] = { 99, 0, 1, 6556, 100, 123456789 };
    for (size_t i = 1; !feof(testFile);)
    {
        char character = fgetc(testFile);
        if (isdigit(character))
        {
            ungetc(character, testFile);
            testIsPassed = testCaseForGetInt(testFile, expectation[i - 1]);
            if (!testIsPassed)
            {
                printFailedTest(i, testName);
                break;
            }
            ++i;
        }
    }
    fclose(testFile);
    return testIsPassed;
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
    bool testIsPassed = output == expectedOutput;
    return testIsPassed;
}

static bool testForParsingTree(void)
{
    const char* const testName = "testForParsingTree";

    bool testOneIsPassed = testCaseForParsingTree(TEST_FILE_FOR_PARSING_TREE_1, 0, SUCCESS);
    if (!testOneIsPassed)
    {
        printFailedTest(1, testName);
        return false;
    }

    bool testTwoIsPassed = testCaseForParsingTree(TEST_FILE_FOR_PARSING_TREE_2, 12, SUCCESS);
    if (!testTwoIsPassed)
    {
        printFailedTest(2, testName);
        return false;
    }

    bool testThreeIsPassed = testCaseForParsingTree(TEST_FILE_FOR_PARSING_TREE_3, 5, SUCCESS);
    if (!testThreeIsPassed)
    {
        printFailedTest(3, testName);
        return false;
    }

    bool testFourIsPassed = testCaseForParsingTree(TEST_FILE_FOR_PARSING_TREE_4, 6, SUCCESS);
    if (!testFourIsPassed)
    {
        printFailedTest(4, testName);
        return false;
    }

    bool testFiveIsPassed = testCaseForParsingTree(TEST_FILE_FOR_PARSING_TREE_5, 0, DIVISION_BY_ZERO);
    if (!testFiveIsPassed)
    {
        printFailedTest(5, testName);
        return false;
    }

    return true;
}

bool test(void)
{
    return testForGetInt() && testForParsingTree();
}
