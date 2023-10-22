#include "test.h"
#include "convertToPostfixForm.h"
#include "str.h"
#include <stdio.h>
#include <stdlib.h>

static void printFailedTest(const int testNumber, const char* const testName)
{
    printf("Test %d has failed in %s\n", testNumber, testName);
}

static bool testForStringsAreEqual(void)
{
    bool testOneIsPassed = stringsAreEqual("", "");
    if (!testOneIsPassed)
    {
        printFailedTest(1, "testForStringsAreEqual");
        return false;
    }

    bool testTwoIsPassed = !stringsAreEqual("abc", "abcd");
    if (!testTwoIsPassed)
    {
        printFailedTest(2, "testForStringsAreEqual");
        return false;
    }

    bool testThreeIsPassed = !stringsAreEqual("qwerty", "qwerti");
    if (!testThreeIsPassed)
    {
        printFailedTest(3, "testForStringsAreEqual");
        return false;
    }

    return true;
}

static bool testCaseCreateString(const char* const data, const size_t length)
{
    String* string = createString(data);
    if (string == NULL)
    {
        return false;
    }
    bool testIsPassed = string->length == length && string->capacity == length + 1 && stringsAreEqual(string->data, data);
    freeString(&string);
    return testIsPassed;
}

static bool testForCreateString(void)
{
    bool testOneIsPassed = testCaseCreateString("", 0);
    if (!testOneIsPassed)
    {
        printFailedTest(1, "testForCreateString");
    }

    bool testTwoIsPassed = testCaseCreateString("qwertyuiop", 10);
    if (!testTwoIsPassed)
    {
        printFailedTest(2, "testForCreateString");
    }

    bool testThreeIsPassed = testCaseCreateString("a b \0 c d", 4);
    if (!testThreeIsPassed)
    {
        printFailedTest(3, "testForCreateString");
    }

    return true;
}

static bool testCaseAddCharToString(const char* const input, const char addition, const char* const sum)
{
    String* string = createString(input);
    if (string == NULL)
    {
        return false;
    }
    int errorCode = addCharToString(string, addition);
    bool testIsPassed = errorCode == SUCCESS && stringsAreEqual(string->data, sum);
    freeString(&string);
    return testIsPassed;
}

static bool testForAddCharToString(void)
{
    bool testOneIsPassed = testCaseAddCharToString("", 'a', "a");
    if (!testOneIsPassed)
    {
        printFailedTest(1, "testForAddCharToString");
        return false;
    }

    bool testTwoIsPassed = testCaseAddCharToString("12345", '6', "123456");
    if (!testTwoIsPassed)
    {
        printFailedTest(2, "testForAddCharToString");
        return false;
    }

    bool testThreeIsPassed = testCaseAddCharToString("abc", '\0', "abc");
    if (!testThreeIsPassed)
    {
        printFailedTest(3, "testForAddCharToString");
        return false;
    }

    return true;
}

static bool testCaseConvertToPostfixForm(const char* const infixString, const char* const postfixString)
{
    String* input = createString(infixString);
    if (input == NULL)
    {
        return false;
    }
    int errorCode = -1;
    String* output = convertToPostfixForm(input, &errorCode);
    freeString(&input);
    bool testIsPassed = errorCode == SUCCESS && stringsAreEqual(output->data, postfixString);
    freeString(&output);
    return testIsPassed;
}

static bool testForConvertToPostfixForm(void)
{
    bool testOneIsPassed = testCaseConvertToPostfixForm("(1 + 2) * 3", "1 2 + 3 *");
    if (!testOneIsPassed)
    {
        printFailedTest(1, "testForConvertToPostfixForm");
        return false;
    }

    bool testTwoIsPassed = testCaseConvertToPostfixForm("", "");
    if (!testTwoIsPassed)
    {
        printFailedTest(2, "testForConvertToPostfixForm");
        return false;
    }

    bool testThreeIsPassed = testCaseConvertToPostfixForm("6 - 9 / 3 + 2", "6 9 3 / 2 + -");
    if (!testThreeIsPassed)
    {
        printFailedTest(3, "testForConvertToPostfixForm");
        return false;
    }

    bool testFourIsPassed = testCaseConvertToPostfixForm("(9 + 4 * 2) / (7 - 1)", "9 4 2 * + 7 1 - /");
    if (!testFourIsPassed)
    {
        printFailedTest(4, "testForConvertToPostfixForm");
        return false;
    }

    bool testFiveIsPassed = testCaseConvertToPostfixForm("7 + )", "7 +");
    if (!testFiveIsPassed)
    {
        printFailedTest(5, "testForConvertToPostfixForm");
        return false;
    }

    bool testSixIsPassed = testCaseConvertToPostfixForm("(abc)", "");
    if (!testSixIsPassed)
    {
        printFailedTest(6, "testForConvertToPostfixForm");
        return false;
    }

    return true;
}

static bool testForStrings(void)
{
    return testForStringsAreEqual() && testForCreateString() && testForAddCharToString();
}

bool test(void)
{
    return testForStrings() && testForConvertToPostfixForm();
}
