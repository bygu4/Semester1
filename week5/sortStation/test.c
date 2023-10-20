#include "test.h"
#include "convertToPostfixForm.h"
#include "str.h"
#include <stdio.h>
#include <stdlib.h>

static bool testForStringsIsPassed(void)
{
    bool testOneIsPassed = stringsAreEqual("", "");
    if (!testOneIsPassed)
    {
        printf("Test 1 has failed in test for strings\n");
        return false;
    }

    bool testTwoIsPassed = !stringsAreEqual("abc", "abcd");
    if (!testTwoIsPassed)
    {
        printf("Test 2 has failed in test for strings\n");
        return false;
    }

    bool testThreeIsPassed = !stringsAreEqual("qwerty", "qwerti");
    if (!testThreeIsPassed)
    {
        printf("Test 3 has failed in test for strings\n");
        return false;
    }

    char* string = NULL;
    int errorCode = addCharToString(&string, 'a', 0);
    bool testFourIsPassed = errorCode == SUCCESS && stringsAreEqual(string, "a");
    if (!testFourIsPassed)
    {
        free(string);
        printf("Test 4 has failed in test for strings\n");
        return false;
    }

    errorCode = addCharToString(&string, 'b', 1);
    bool testFiveIsPassed = errorCode == SUCCESS && stringsAreEqual(string, "ab");
    free(string);
    if (!testFiveIsPassed)
    {
        printf("Test 5 has failed in test for strings\n");
        return false;
    }

    return true;
}

static bool testForConversToPostfixFormIsPassed(void)
{
    int errorCode = -1;
    char* output1 = convertToPostfixForm("(1 + 2) * 3", &errorCode);
    bool testOneIsPassed = errorCode == SUCCESS && stringsAreEqual(output1, "1 2 + 3 *");
    free(output1);
    if (!testOneIsPassed)
    {
        printf("Test 1 has failed in test for convertToPostfixForm\n");
        return false;
    }

    char* output2 = convertToPostfixForm("", &errorCode);
    bool testTwoIsPassed = errorCode == SUCCESS && stringsAreEqual(output2, "");
    free(output2);
    if (!testTwoIsPassed)
    {
        printf("Test 2 has failed in test for convertToPostfixForm\n");
        return false;
    }

    char* output3 = convertToPostfixForm("6 - 9 / 3 + 2", &errorCode);
    bool testThreeIsPassed = errorCode == SUCCESS && stringsAreEqual(output3, "6 9 3 / 2 + -");
    free(output3);
    if (!testThreeIsPassed)
    {
        printf("Test 3 has failed in test for convertToPostfixForm\n");
        return false;
    }

    char* output4 = convertToPostfixForm("(9 + 4 * 2) / (7 - 1)", &errorCode);
    bool testFourIsPassed = errorCode == SUCCESS && stringsAreEqual(output4, "9 4 2 * + 7 1 - /");
    free(output4);
    if (!testFourIsPassed)
    {
        printf("Test 4 has failed in test for convertToPostfixForm\n");
        return false;
    }

    char* output5 = convertToPostfixForm("7 + )", &errorCode);
    bool testFiveIsPassed = errorCode == SUCCESS && stringsAreEqual(output5, "7 +");
    free(output5);
    if (!testFiveIsPassed)
    {
        printf("Test 5 has failed in test for convertToPostfixForm\n");
        return false;
    }

    char* output6 = convertToPostfixForm("(abc)", &errorCode);
    bool testSixIsPassed = errorCode == SUCCESS && stringsAreEqual(output6, "");
    free(output6);
    if (!testSixIsPassed)
    {
        printf("Test 6 has failed in test for convertToPostfixForm\n");
        return false;
    }

    return true;
}

bool test(void)
{
    return testForStringsIsPassed() && testForConversToPostfixFormIsPassed();
}
