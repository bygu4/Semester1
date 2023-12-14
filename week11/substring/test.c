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
    const bool stringIsInFile, const size_t expectedOutput, const size_t numeberOfTest)
{
    char* fileData = NULL;
    int errorCode = readFile(&fileData, nameOfFile);
    if (errorCode != SUCCESS)
    {
        printf(errorCode == FILE_NOT_FOUND ? "File not found\n" : "Failed to read file\n");
        return false;
    }
    bool stringFound = false;
    size_t firstEntryIndex = getSubstringFirstEntry(stringToFind, fileData, &stringFound);
    free(fileData);
    bool testPassed = stringFound && stringIsInFile ? 
        firstEntryIndex == expectedOutput : stringFound == stringIsInFile;
    if (!testPassed)
    {
        printFailedTest(numeberOfTest);
    }
    return testPassed;
}

bool test(void)
{
    return testCase(TEST_FILE_1, "", true, 0, 1) &&
        testCase(TEST_FILE_1, "a", false, 0, 2) &&
        testCase(TEST_FILE_2, "hot", true, 18, 3) &&
        testCase(TEST_FILE_2, "tea", false, 0, 4) &&
        testCase(TEST_FILE_3, "aaaa", true, 10, 5) &&
        testCase(TEST_FILE_3, "aaaaa", false, 0, 6);
}
