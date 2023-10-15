#include "test.h"
#include "files.h"
#include "str.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define TEST_FILE_1 "test1.txt"
#define TEST_FILE_2 "test2.txt"
#define TEST_FILE_3 "test3.txt"
#define TEST_FILE_4 "test4.txt"

static bool testForStringsAreEqualIsPassed(int* const errorCode)
{
    bool testOneIsPassed = stringsAreEqual("", "");
    if (!testOneIsPassed)
    {
        *errorCode = 1;
        return false;
    }

    bool testTwoIsPassed = !stringsAreEqual("1234", "12345");
    if (!testTwoIsPassed)
    {
        *errorCode = 2;
        return false;
    }

    bool testThreeIsPassed = !stringsAreEqual("abcdef", "ABCDEF");
    if (!testThreeIsPassed)
    {
        *errorCode = 3;
        return false;
    }

    bool testFourIsPassed = stringsAreEqual("qwerty", "qwerty");
    if (!testFourIsPassed)
    {
        *errorCode = 4;
        return false;
    }

    return true;
}

static bool testForStringMulIsPassed(int* const errorCode)
{
    char* testString1 = stringMul("qwerty", 2);
    bool testOneIsPassed = testString1 != NULL && stringsAreEqual(testString1, "qwertyqwerty");
    free(testString1);
    if (!testOneIsPassed)
    {
        *errorCode = 1;
        return false;
    }

    char* testString2 = stringMul("a", 5);
    bool testTwoIsPassed = testString2 != NULL && stringsAreEqual(testString2, "aaaaa");
    free(testString2);
    if (!testTwoIsPassed)
    {
        *errorCode = 2;
        return false;
    }

    char* testString3 = stringMul("", 100);
    bool testThreeIsPassed = testString3 != NULL && stringsAreEqual(testString3, "");
    free(testString3);
    if (!testThreeIsPassed)
    {
        *errorCode = 3;
        return false;
    }

    char* testString4 = stringMul("123456", 0);
    bool testFourIsPassed = testString4 != NULL && stringsAreEqual(testString4, "");
    free(testString4);
    if (!testFourIsPassed)
    {
        *errorCode = 4;
        return false;
    }

    return true;
}

static bool testForFgetStringIsPassed(int* const errorCode)
{
    FILE* file = NULL;
    int openErrorCode = fopen_s(&file, TEST_FILE_1, "r");
    if (openErrorCode != SUCCESS)
    {
        *errorCode = -1;
        return false;
    }

    char* testString1 = fgetString(file, ':', 0);
    bool testOneIsPassed = testString1 == NULL;
    if (!testOneIsPassed)
    {
        fclose(file);
        *errorCode = 1;
        return false;
    }

    char* testString2 = fgetString(file, ':', 1);
    bool testTwoIsPassed = testString2 != NULL && stringsAreEqual(testString2, "abcdef");
    free(testString2);
    if (!testTwoIsPassed)
    {
        fclose(file);
        *errorCode = 2;
        return false;
    }

    char* testString3 = fgetString(file, '\n', 2);
    bool testThreeIsPassed = testString3 != NULL && stringsAreEqual(testString3, "1234567");
    free(testString3);
    if (!testThreeIsPassed)
    {
        fclose(file);
        *errorCode = 3;
        return false;
    }

    char* testString4 = fgetString(file, '\n', 3);
    bool testFourIsPassed = testString4 != NULL && stringsAreEqual(testString4, "");
    free(testString4);
    if (!testFourIsPassed)
    {
        fclose(file);
        *errorCode = 4;
        return false;
    }

    char* testString5 = fgetString(file, '.', 4);
    bool testFiveIsPassed = testString5 != NULL && stringsAreEqual(testString5, "aaaaaaa\nbbbbbbb");
    free(testString5);
    fclose(file);
    if (!testFiveIsPassed)
    {
        *errorCode = 5;
        return false;
    }

    return true;
}

static bool testForAddIsPassed(int* const errorCode)
{
    Phonebook phonebook = { .notes = NULL, .numberOfNotes = 0 };
    phonebook.notes = malloc(sizeof(Note) * 10);
    if (phonebook.notes == NULL)
    {
        *errorCode = -1;
        return false;
    }

    int errorCode1 = addNote(&phonebook, "abababa", "99");
    Note note1 = phonebook.notes[0];
    bool testOneIsPassed = errorCode1 == SUCCESS &&
        stringsAreEqual(note1.name, "abababa") && stringsAreEqual(note1.number, "99");
    if (!testOneIsPassed)
    {
        *errorCode = 1;
        freePhonebook(&phonebook);
        return false;
    }

    int errorCode2 = addNote(&phonebook, "", "");
    Note note2 = phonebook.notes[1];
    bool testTwoIsPassed = errorCode2 == SUCCESS &&
        stringsAreEqual(note2.name, "") && stringsAreEqual(note2.number, "");
    if (!testTwoIsPassed)
    {
        *errorCode = 2;
        freePhonebook(&phonebook);
        return false;
    }

    char* name3 = stringMul("abc", 100);
    char* number3 = stringMul("8", 100);
    if (name3 == NULL || number3 == NULL)
    {
        free(name3);
        free(number3);
        freePhonebook(&phonebook);
        *errorCode = -2;
        return false;
    }
    int errorCode3 = addNote(&phonebook, name3, number3);
    Note note3 = phonebook.notes[2];
    bool testThreeIsPassed = errorCode3 == SUCCESS && phonebook.numberOfNotes == 3 &&
        stringsAreEqual(note3.number, number3) && stringsAreEqual(note3.name, name3);
    free(name3);
    free(number3);
    freePhonebook(&phonebook);
    if (!testThreeIsPassed)
    {
        *errorCode = 3;
        return false;
    }

    return true;
}

static bool testForFindIsPassed(int* const errorCode)
{
    Phonebook phonebook = { .notes = NULL, .numberOfNotes = 0 };
    int readErrorCode = readNotesFromFile(&phonebook, TEST_FILE_4);
    if (readErrorCode != SUCCESS)
    {
        freePhonebook(&phonebook);
        *errorCode = -1;
        return false;
    }

    char* test1 = findNumberByName(&phonebook, "sasha");
    bool testOneIsPassed = stringsAreEqual(test1, "89001112233");
    if (!testOneIsPassed)
    {
        freePhonebook(&phonebook);
        *errorCode = 1;
        return false;
    }

    char* test2 = findNameByNumber(&phonebook, "World");
    bool testTwoIsPassed = stringsAreEqual(test2, "Hello");
    if (!testTwoIsPassed)
    {
        freePhonebook(&phonebook);
        *errorCode = 2;
        return false;
    }

    char* test3 = findNumberByName(&phonebook, "17");
    bool testThreeIsPassed = stringsAreEqual(test3, "03");
    if (!testThreeIsPassed)
    {
        freePhonebook(&phonebook);
        *errorCode = 3;
        return false;
    }

    char* test4 = findNameByNumber(&phonebook, "babab");
    bool testFourIsPassed = stringsAreEqual(test4, "ababa");
    if (!testFourIsPassed)
    {
        freePhonebook(&phonebook);
        *errorCode = 4;
        return false;
    }

    char* test5 = findNumberByName(&phonebook, "Matmex");
    bool testFiveIsPassed = test5 == NULL;
    if (!testFiveIsPassed)
    {
        freePhonebook(&phonebook);
        *errorCode = 5;
        return false;
    }

    char* test6 = findNameByNumber(&phonebook, "123456789");
    bool testSixIsPassed = test6 == NULL;
    freePhonebook(&phonebook);
    if (!testSixIsPassed)
    {
        *errorCode = 6;
        return false;
    }

    return true;
}

static bool testForFiles(int* const errorCode)
{
    Phonebook phonebook = { .notes = NULL, .numberOfNotes = 0 };
    int readErrorCode = readNotesFromFile(&phonebook, TEST_FILE_2);
    if (readErrorCode != SUCCESS)
    {
        freePhonebook(&phonebook);
        *errorCode = -1;
        return false;
    }

    Note note1 = phonebook.notes[0];
    bool testOneIsPassed = stringsAreEqual(note1.name, "sasha")
        && stringsAreEqual(note1.number, "+1234567890");
    if (!testOneIsPassed)
    {
        freePhonebook(&phonebook);
        *errorCode = 1;
        return false;
    }

    Note note2 = phonebook.notes[1];
    bool testTwoIsPassed = stringsAreEqual(note2.name, "")
        && stringsAreEqual(note2.number, "");
    if (!testTwoIsPassed)
    {
        freePhonebook(&phonebook);
        *errorCode = 2;
        return false;
    }

    Note note3 = phonebook.notes[2];
    char* name3 = stringMul("abc", 10);
    char* number3 = stringMul("123456789", 5);
    if (name3 == NULL || number3 == NULL)
    {
        free(name3);
        free(number3);
        freePhonebook(&phonebook);
        *errorCode = -2;
        return false;
    }
    bool testThreeIsPassed = stringsAreEqual(note3.name, name3)
        && stringsAreEqual(note3.number, number3);
    free(name3);
    free(number3);
    if (!testThreeIsPassed)
    {
        freePhonebook(&phonebook);
        *errorCode = 3;
        return false;
    }

    int saveErrorCode = saveNotesToFile(&phonebook, TEST_FILE_2);
    bool testFourIsPassed = saveErrorCode == SUCCESS && phonebook.numberOfNotes == 3;
    freePhonebook(&phonebook);
    if (!testFourIsPassed)
    {
        *errorCode = 4;
        return false;
    }

    readErrorCode = readNotesFromFile(&phonebook, TEST_FILE_3);
    bool testFiveIsPassed = readErrorCode == INCORRECT_FORMAT;
    freePhonebook(&phonebook);
    if (!testFiveIsPassed)
    {
        *errorCode = 5;
        return false;
    }

    readErrorCode = readNotesFromFile(&phonebook, TEST_FILE_4);
    bool testSixIsPassed = readErrorCode == SUCCESS && phonebook.numberOfNotes == MAX_NOTES;
    freePhonebook(&phonebook);
    if (!testSixIsPassed)
    {
        *errorCode = 6;
        return false;
    }

    return true;
}

static bool testForStringsIsPassed(void)
{
    int errorCode = 0;
    bool testOneIsPassed = testForStringsAreEqualIsPassed(&errorCode);
    if (!testOneIsPassed)
    {
        printf("Test %d has failed in test for stringsAreEqual\n", errorCode);
        return false;
    }

    bool testTwoIsPassed = testForStringMulIsPassed(&errorCode);
    if (!testTwoIsPassed)
    {
        printf("Test %d has failed in test for stringMul\n", errorCode);
        return false;
    }

    bool testThreeIsPassed = testForFgetStringIsPassed(&errorCode);
    if (!testThreeIsPassed)
    {
        printf("Test %d has failed in test for fgetString\n", errorCode);
        return false;
    }

    return true;
}

static bool testForPhonebookIsPassed(void)
{
    int errorCode = 0;
    bool testOneIsPassed = testForAddIsPassed(&errorCode);
    if (!testOneIsPassed)
    {
        printf("Test %d has failed in test for addNote\n", errorCode);
        return false;
    }

    bool testTwoIsPassed = testForFindIsPassed(&errorCode);
    if (!testTwoIsPassed)
    {
        printf("Test %d has failed in test for find\n", errorCode);
        return false;
    }

    return true;
}

static bool testForFilesIsPassed(void)
{
    int errorCode = 0;
    bool testIsPassed = testForFiles(&errorCode);
    if (!testIsPassed)
    {
        printf("Test %d has failed in test for files\n", errorCode);
        return false;
    }
    return true;
}

bool test(void)
{
    if (!testForStringsIsPassed())
    {
        return false;
    }

    if (!testForPhonebookIsPassed())
    {
        return false;
    }

    if (!testForFilesIsPassed())
    {
        return false;
    }

    return true;
}
