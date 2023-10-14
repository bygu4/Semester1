#include "test.h"
#include "phonebook.h"
#include "str.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define TEST_FILE_1 "test1.txt"
#define TEST_FILE_2 "test2.txt"
#define TEST_FILE_3 "test3.txt"

static bool testForAddIsPassed(int* const errorCode)
{
    Phonebook phonebook = { .notes = NULL, .numberOfNotes = 0 };
    int readErrorCode = readNotesFromFile(&phonebook, TEST_FILE_1);
    if (readErrorCode != SUCCESS)
    {
        *errorCode = -1;
        freePhonebook(&phonebook);
        return false;
    }

    int errorCode1 = addNoteSupport(&phonebook, "abababa", "99");
    Note note1 = phonebook.notes[0];
    bool testOneIsPassed = errorCode1 == 0 && stringsAreEqual(note1.name, "abababa")
        && stringsAreEqual(note1.number, "99");
    if (!testOneIsPassed)
    {
        *errorCode = 1;
        freePhonebook(&phonebook);
        return false;
    }

    int errorCode2 = addNoteSupport(&phonebook, "", "");
    Note note2 = phonebook.notes[1];
    bool testTwoIsPassed = errorCode2 == 0 && stringsAreEqual(note2.name, "")
        && stringsAreEqual(note2.number, "");
    if (!testTwoIsPassed)
    {
        *errorCode = 2;
        return false;
    }

    char* name3 = stringMul("abc", 21);
    char* number3 = stringMul("8", 63);
    if (name3 == NULL || number3 == NULL)
    {
        free(name3);
        free(number3);
        freePhonebook(&phonebook);
        *errorCode = -1;
        return false;
    }
    int errorCode3 = addNoteSupport(&phonebook, name3, number3);
    Note note3 = phonebook.notes[2];
    bool testThreeIsPassed = errorCode3 == 0 && stringsAreEqual(note3.name, name3)
        && stringsAreEqual(note3.number, number3) && phonebook.numberOfNotes == 3;
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

static bool testForReadAndSaveIsPassed(int* const errorCode)
{
    Phonebook phonebook = { .notes = NULL, .numberOfNotes = 0 };
    int readErrorCode = readNotesFromFile(&phonebook, TEST_FILE_2);
    if (readErrorCode != SUCCESS)
    {
        *errorCode = -1;
        freePhonebook(&phonebook);
        return false;
    }

    Note note1 = phonebook.notes[0];
    bool testOneIsPassed = stringsAreEqual(note1.name, "sasha")
        && stringsAreEqual(note1.number, "+1234567890");
    if (!testOneIsPassed)
    {
        *errorCode = 1;
        freePhonebook(&phonebook);
        return false;
    }

    Note note2 = phonebook.notes[1];
    bool testTwoIsPassed = stringsAreEqual(note2.name, "masha")
        && stringsAreEqual(note2.number, "89000000000");
    if (!testTwoIsPassed)
    {
        *errorCode = 2;
        freePhonebook(&phonebook);
        return false;
    }

    Note note3 = phonebook.notes[2];
    bool testThreeIsPassed = stringsAreEqual(note3.name, "pasha")
        && stringsAreEqual(note3.number, "8(999)1112233");
    if (!testThreeIsPassed)
    {
        *errorCode = 3;
        freePhonebook(&phonebook);
        return false;
    }

    int saveErrorCode = saveNotesToFileSupport(&phonebook, TEST_FILE_2);
    bool testFourIsPassed = saveErrorCode == 0 && phonebook.numberOfNotes == 3;
    freePhonebook(&phonebook);
    if (!testFourIsPassed)
    {
        *errorCode = 4;
        return false;
    }

    return true;
}

static bool testForFindIsPassed(int* const errorCode)
{
    Phonebook phonebook = { .notes = NULL, .numberOfNotes = 0 };
    int readErrorCode = readNotesFromFile(&phonebook, TEST_FILE_3);
    if (readErrorCode != SUCCESS)
    {
        *errorCode = -1;
        freePhonebook(&phonebook);
        return false;
    }

    char* test1 = findNumberByNameSupport(&phonebook, "sasha");
    bool testOneIsPassed = stringsAreEqual(test1, "89001112233");
    if (!testOneIsPassed)
    {
        *errorCode = 1;
        freePhonebook(&phonebook);
        return false;
    }

    char* test2 = findNameByNumberSupport(&phonebook, "World");
    bool testTwoIsPassed = stringsAreEqual(test2, "Hello");
    if (!testTwoIsPassed)
    {
        *errorCode = 2;
        freePhonebook(&phonebook);
        return false;
    }

    char* test3 = findNumberByNameSupport(&phonebook, "17");
    bool testThreeIsPassed = stringsAreEqual(test3, "03");
    if (!testThreeIsPassed)
    {
        *errorCode = 3;
        freePhonebook(&phonebook);
        return false;
    }

    char* test4 = findNameByNumberSupport(&phonebook, "babab");
    bool testFourIsPassed = stringsAreEqual(test4, "ababa");
    if (!testFourIsPassed)
    {
        *errorCode = 4;
        freePhonebook(&phonebook);
        return false;
    }

    char* test5 = findNumberByNameSupport(&phonebook, "Matmex");
    bool testFiveIsPassed = test5 == NULL && phonebook.numberOfNotes == 100;
    if (!testFiveIsPassed)
    {
        *errorCode = 5;
        freePhonebook(&phonebook);
        return false;
    }

    char* test6 = findNameByNumberSupport(&phonebook, "123456789");
    bool testSixIsPassed = test6 == NULL;
    freePhonebook(&phonebook);
    if (!testSixIsPassed)
    {
        *errorCode = 6;
        return false;
    }

    return true;
}

bool test(void)
{
    int errorCode = 0;
    bool testOneIsPassed = testForAddIsPassed(&errorCode);
    if (!testOneIsPassed)
    {
        printf("Test %d has failed in test for add\n", errorCode);
        return false;
    }

    bool testTwoIsPassed = testForReadAndSaveIsPassed(&errorCode);
    if (!testTwoIsPassed)
    {
        printf("Test %d has failed in test read and save\n", errorCode);
        return false;
    }

    bool testThreeIsPassed = testForFindIsPassed(&errorCode);
    if (!testThreeIsPassed)
    {
        printf("Test %d has failed in test for find\n", errorCode);
        return false;
    }
}
