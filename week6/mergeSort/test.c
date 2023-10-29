#include "test.h"
#include "str.h"
#include "readListFromFile.h"
#include "mergeSort.h"
#include <stdlib.h>

static void printFailedTest(const int numberOfTest, const char* const nameOfTest)
{
    printf("Test %d has failed in %s\n", numberOfTest, nameOfTest);
}

static bool testForCompareStrings(void)
{
    bool testOneIsPassed = compareStrings("aaabbbccc", "aaabbbccc");
    if (!testOneIsPassed)
    {
        printFailedTest(1, "testForCompareStrings");
        return false;
    }

    bool testTwoIsPassed = compareStrings("12345", "23456");
    if (!testTwoIsPassed)
    {
        printFailedTest(2, "testForCompareStrings");
        return false;
    }

    bool testThreeIsPassed = !compareStrings("zzzzz", "zzzzx");
    if (!testThreeIsPassed)
    {
        printFailedTest(3, "testForCompareStrings");
        return false;
    }

    return true;
}

static bool testForStringSum(void)
{
    int errorCode = -1;
    char* sum1 = stringSum(&errorCode, 5, "a", "b", "c", "d", "e");
    bool testOneIsPassed = errorCode == SUCCESS && stringsAreEqual(sum1, "abcde");
    free(sum1);
    if (!testOneIsPassed)
    {
        printFailedTest(1, "testForStringSum");
        return false;
    }

    char* sum2 = stringSum(&errorCode, 2, "", "");
    bool testTwoIsPassed = errorCode == SUCCESS && stringsAreEqual(sum2, "");
    free(sum2);
    if (!testTwoIsPassed)
    {
        printFailedTest(2, "testForStringSum");
        return false;
    }

    char* sum3 = stringSum(&errorCode, 1, "QWERTY");
    bool testThreeIsPassed = errorCode == SUCCESS && stringsAreEqual(sum3, "QWERTY");
    free(sum3);
    if (!testThreeIsPassed)
    {
        printFailedTest(3, "testForStringSum");
        return false;
    }

    char* sum4 = stringSum(&errorCode, 3, "1", "22", "333");
    bool testFourIsPassed = errorCode == SUCCESS && stringsAreEqual(sum4, "122333");
    free(sum4);
    if (!testFourIsPassed)
    {
        printFailedTest(4, "testForStringSum");
        return false;
    }

    return true;
}

static bool testForFgetString(void)
{
    FILE* testFile = NULL;
    int errorCode = fopen_s(&testFile, TEST_FILE_1, "r");
    if (errorCode != SUCCESS)
    {
        return false;
    }
    char* testString1 = fgetString(testFile, ':', &errorCode);
    bool testOneIsPassed = errorCode == SUCCESS && stringsAreEqual(testString1, "qwerty");
    free(testString1);
    if (!testOneIsPassed)
    {
        fclose(testFile);
        printFailedTest(1, "testForFgetString");
        return false;
    }

    char* testString2 = fgetString(testFile, ' ', &errorCode);
    bool testTwoIsPassed = errorCode == SUCCESS && stringsAreEqual(testString2, "uiop");
    free(testString2);
    if (!testTwoIsPassed)
    {
        fclose(testFile);
        printFailedTest(2, "testForFgetString");
        return false;
    }

    char* testString3 = fgetString(testFile, '\n', &errorCode);
    bool testThreeIsPassed = errorCode == SUCCESS && stringsAreEqual(testString3, "{}");
    free(testString3);
    if (!testThreeIsPassed)
    {
        fclose(testFile);
        printFailedTest(3, "testForFgetString");
        return false;
    }

    char* testString4 = fgetString(testFile, '^', &errorCode);
    bool testFourIsPassed = errorCode == SUCCESS && stringsAreEqual(testString4, "123 45\n");
    fclose(testFile);
    free(testString4);
    if (!testFourIsPassed)
    {
        printFailedTest(4, "testForFgetString");
        return false;
    }

    return true;
}

static bool testForStrings(void)
{
    return testForCompareStrings() && testForStringSum() && testForFgetString();
}

bool test(void)
{
    return testForStrings();
}
