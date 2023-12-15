#include "test.h"
#include "str.h"
#include "getSubstringFirstEntry.h"
#include <stdlib.h>

#define TEST_FILE_1 "testFiles/testFile1.txt"
#define TEST_FILE_2 "testFiles/testFile2.txt"
#define TEST_FILE_3 "testFiles/testFile3.txt"

void printFailedTest(const size_t numberOfTest)
{
    printf("Test %zu has failed\n", numberOfTest);
}

static bool testCase(const char* const nameOfFile, const char* const stringToFind, 
    const bool stringIsInFile, const size_t expectedOutput, const size_t numberOfTest)
{
    char* fileData = NULL;
    size_t lengthOfFile = 0;
    int errorCode = readFile(&fileData, nameOfFile, &lengthOfFile);
    if (errorCode != SUCCESS)
    {
        printf(errorCode == FILE_NOT_FOUND ? "File not found\n" : "Failed to read file\n");
        return false;
    }
    bool stringFound = false;
    bool errorOccured = false;
    size_t firstEntryIndex = getSubstringFirstEntry(stringToFind, fileData, 
        lengthOfFile, &stringFound, &errorOccured);
    free(fileData);
    bool testPassed = !errorOccured && (stringFound && stringIsInFile) ? 
        (firstEntryIndex == expectedOutput) : (stringFound == stringIsInFile);
    if (!testPassed)
    {
        printFailedTest(numberOfTest);
    }
    return testPassed;
}

bool test(void)
{
    return testCase(TEST_FILE_1, "", true, 0, 1) &&
        testCase(TEST_FILE_1, "a", false, 0, 2) &&
        testCase(TEST_FILE_2, "hot", true, 18, 3) &&
        testCase(TEST_FILE_2, "tea", false, 0, 4) &&
        testCase(TEST_FILE_3, "aba", true, 11, 5) &&
        testCase(TEST_FILE_3, "aaaaa", false, 0, 6);
}
