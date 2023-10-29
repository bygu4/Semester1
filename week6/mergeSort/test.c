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

static bool arraysAreEqual(const char** const array1, const char** const array2,
    const size_t sizeOfArray)
{
    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        if (!stringsAreEqual(array1[i], array2[i]))
        {
            return false;
        }
    }
    return true;
}

static bool testCaseForReadListFromFile(const char* const nameOfFile,
    const char** const expectedArray, const size_t sizeOfArray, const int expectedCode)
{
    List* list = createList();
    if (list == NULL)
    {
        printf("Failed to create list\n");
        return false;
    }
    int errorCode = readListFromFile(list, nameOfFile);
    if (errorCode != expectedCode)
    {
        freeList(&list);
        return false;
    }
    char** array = getListData(list, &errorCode);
    bool testIsPassed = errorCode == SUCCESS && size(list) == sizeOfArray && 
        arraysAreEqual(array, expectedArray, sizeOfArray);
    freeListData(&array, sizeOfArray);
    freeList(&list);
    return testIsPassed;
}

static bool testForReadListFromFile(void)
{
    char** expectedArray1 = NULL;
    bool testOneIsPassed = testCaseForReadListFromFile(TEST_FILE_1, expectedArray1, 0, INCORRECT_FORMAT);
    if (!testOneIsPassed)
    {
        printFailedTest(1, "testForReadListFromFile");
        return false;
    }

    char** expectedArray2 = NULL;
    bool testTwoIsPassed = testCaseForReadListFromFile(TEST_FILE_2, expectedArray2, 0, SUCCESS);
    if (!testTwoIsPassed)
    {
        printFailedTest(2, "testForReadListFromFile");
        return false;
    }

    char* expectedArray3[7] = { "cd - gg", "cc - gg", "ab - cc",
                                "aa - dd", "bb - aa", "ac - dd", "ee - aa" };
    bool testThreeIsPassed = testCaseForReadListFromFile(TEST_FILE_3, expectedArray3, 7, SUCCESS);
    if (!testThreeIsPassed)
    {
        printFailedTest(3, "testForReadListFromFile");
        return false;
    }

    return true;
}

static bool testCaseForMergeSort(const char* const nameOfFile,
    const char** const expectedArray, const size_t sizeOfArray, 
    bool (*key)(const List* const, const List* const))
{
    List* list = createList();
    if (list == NULL)
    {
        printf("Failed to create list\n");
        return false;
    }
    int errorCode = readListFromFile(list, nameOfFile);
    if (errorCode != SUCCESS)
    {
        freeList(&list);
        return false;
    }
    errorCode = mergeSort(list, key);
    if (errorCode != SUCCESS)
    {
        freeList(&list);
        return false;
    }
    char** array = getListData(list, &errorCode);
    bool testIsPassed = errorCode == SUCCESS && size(list) == sizeOfArray &&
        arraysAreEqual(array, expectedArray, sizeOfArray);
    freeListData(&array, sizeOfArray);
    freeList(&list);
    return testIsPassed;
}

static bool testForMergeSort(void)
{
    char** expectedArray1 = NULL;
    bool testOneIsPassed = testCaseForMergeSort(TEST_FILE_2, expectedArray1, 0, compareByName);
    if (!testOneIsPassed)
    {
        printFailedTest(1, "testForMergeSort");
        return false;
    }

    char** expectedArray2 = NULL;
    bool testTwoIsPassed = testCaseForMergeSort(TEST_FILE_2, expectedArray2, 0, compareByNumber);
    if (!testTwoIsPassed)
    {
        printFailedTest(2, "testForMergeSort");
        return false;
    }

    char* expectedArray3[7] = { "aa - dd", "ab - cc", "ac - dd",
                                "bb - aa", "cc - gg", "cd - gg", "ee - aa" };
    bool testThreeIsPassed = testCaseForMergeSort(TEST_FILE_3, expectedArray3, 7, compareByName);
    if (!testThreeIsPassed)
    {
        printFailedTest(3, "testForMergeSort");
        return false;
    }

    char* expectedArray4[7] = { "bb - aa", "ee - aa", "ab - cc",
                                "aa - dd", "ac - dd", "cd - gg", "cc - gg" };
    bool testFourIsPassed = testCaseForMergeSort(TEST_FILE_3, expectedArray4, 7, compareByNumber);
    if (!testFourIsPassed)
    {
        printFailedTest(4, "testForMergeSort");
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
    return testForStrings() && testForReadListFromFile() && testForMergeSort();
}
