#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE_OF_BUFFER 64
#define MAX_NOTES 100
#define NAME_OF_FILE "phoneBook.txt"
#define TEST_FILE_1 "test1.txt"
#define TEST_FILE_2 "test2.txt"
#define TEST_FILE_3 "test3.txt"

typedef struct {
    char* name;
    char* number;
} Note;

typedef struct {
    Note* notes;
    int numberOfNotes;
} Phonebook;

void freePhonebook(Phonebook* phonebook)
{
    Note* notes = phonebook->notes;
    int* numberOfNotes = &phonebook->numberOfNotes;
    for (int i = 0; i < *numberOfNotes; ++i)
    {
        Note note = notes[i];
        free(note.name);
        free(note.number);
    }
    free(notes);
    *numberOfNotes = 0;
}

int addNoteSupport(Phonebook* phonebook, const char* name, const char* number)
{
    Note note = { "", "" };
    size_t sizeOfName = strlen(name) + 1;
    size_t sizeOfNumber = strlen(number) + 1;
    note.name = calloc(sizeOfName, sizeof(char));
    note.number = calloc(sizeOfNumber, sizeof(char));
    if (note.name == NULL || note.number == NULL)
    {
        free(note.name);
        free(note.number);
        return 1;
    }
    int errorCode1 = strcpy_s(note.name, sizeOfName, name);
    int errorCode2 = strcpy_s(note.number, sizeOfNumber, number);
    if (errorCode1 != 0 || errorCode2 != 0)
    {
        free(note.name);
        free(note.number);
        return 1;
    }
    int* numberOfNotes = &phonebook->numberOfNotes;
    int index = *numberOfNotes;
    phonebook->notes[index] = note;
    ++* numberOfNotes;
    return 0;
}

int readNotesFromFile(Phonebook* phonebook, const char* nameOfFile)
{
    phonebook->notes = malloc(sizeof(Note) * MAX_NOTES);
    if (phonebook->notes == NULL)
    {
        return 1;
    }
    FILE* inputFile = NULL;
    int errorCode = fopen_s(&inputFile, nameOfFile, "r");
    if (errorCode == 2)
    {
        return 0;
    }
    if (errorCode != 0)
    {
        free(phonebook->notes);
        return 1;
    }
    int* numberOfNotes = &phonebook->numberOfNotes;
    while (!feof(inputFile) && *numberOfNotes < MAX_NOTES)
    {
        char name[SIZE_OF_BUFFER] = { '\0' };
        fscanf_s(inputFile, "%[^ ]", name, SIZE_OF_BUFFER - 1);
        if (strlen(name) == 0)
        {
            break;
        }
        fseek(inputFile, 1, SEEK_CUR);
        char number[SIZE_OF_BUFFER] = { '\0' };
        fscanf_s(inputFile, "%[^\n]", number, SIZE_OF_BUFFER - 1);
        fseek(inputFile, 2, SEEK_CUR);

        errorCode = addNoteSupport(phonebook, name, number);
        if (errorCode != 0)
        {
            fclose(inputFile);
            freePhonebook(phonebook);
            return 1;
        }
    }
    fclose(inputFile);
    return 0;
}

int addNote(Phonebook* phonebook)
{
    int* numberOfNotes = &phonebook->numberOfNotes;
    if (*numberOfNotes >= MAX_NOTES)
    {
        printf("Cannot add any more notes\n");
        return 0;
    }
    char name[SIZE_OF_BUFFER] = { '\0' };
    printf("Enter name: ");
    scanf_s("%s", name, SIZE_OF_BUFFER - 1);
    char number[SIZE_OF_BUFFER] = { '\0' };
    printf("Enter number: ");
    scanf_s("%s", number, SIZE_OF_BUFFER - 1);

    int errorCode = addNoteSupport(phonebook, name, number);
    if (errorCode != 0)
    {
        return 1;
    }
    printf("Note added\n");
    return 0;
}

void printAllNotes(const Phonebook* phonebook)
{
    int numberOfNotes = phonebook->numberOfNotes;
    if (numberOfNotes == 0)
    {
        printf("No notes yet\n");
    }
    for (int i = 0; i < numberOfNotes; ++i)
    {
        Note note = phonebook->notes[i];
        printf("%d) %s - %s\n", i + 1, note.name, note.number);
    }
}

bool stringsAreEqual(const char* string1, const char* string2)
{
    size_t lengthOfString1 = strlen(string1);
    size_t lengthOfString2 = strlen(string2);
    if (lengthOfString1 != lengthOfString2)
    {
        return false;
    }
    for (int i = 0; i < lengthOfString1; ++i)
    {
        if (string1[i] != string2[i])
        {
            return false;
        }
    }
    return true;
}

char* findNumberByNameSupport(const Phonebook* phonebook, const char* nameToFind)
{
    Note* notes = phonebook->notes;
    int numberOfNotes = phonebook->numberOfNotes;
    for (int i = 0; i < numberOfNotes; ++i)
    {
        Note note = notes[i];
        if (stringsAreEqual(note.name, nameToFind))
        {
            return note.number;
        }
    }
    return NULL;
}

void findNumberByName(const Phonebook* phonebook)
{
    char nameToFind[SIZE_OF_BUFFER] = { '\0' };
    printf("Enter a name: ");
    scanf_s("%s", nameToFind, SIZE_OF_BUFFER - 1);
    char* foundNumber = findNumberByNameSupport(phonebook, nameToFind);
    if (foundNumber == NULL)
    {
        printf("Name not found\n");
        return;
    }
    printf("%s\n", foundNumber);
}

char* findNameByNumberSupport(const Phonebook* phonebook, const char* numberToFind)
{
    Note* notes = phonebook->notes;
    int numberOfNotes = phonebook->numberOfNotes;
    for (int i = 0; i < numberOfNotes; ++i)
    {
        Note note = notes[i];
        if (stringsAreEqual(note.number, numberToFind))
        {
            return note.name;
        }
    }
    return NULL;
}

void findNameByNumber(const Phonebook* phonebook)
{
    char numberToFind[SIZE_OF_BUFFER] = { '\0' };
    printf("Enter a number: ");
    scanf_s("%s", numberToFind, SIZE_OF_BUFFER - 1);
    char* foundName = findNameByNumberSupport(phonebook, numberToFind);
    if (foundName == NULL)
    {
        printf("Number not found\n");
        return;
    }
    printf("%s\n", foundName);
}

int saveNotesToFileSupport(const Phonebook* phonebook, const char* nameOfFile)
{
    FILE* outputFile = NULL;
    int errorCode = fopen_s(&outputFile, nameOfFile, "w");
    if (errorCode != 0)
    {
        return 1;
    }
    Note* notes = phonebook->notes;
    int numberOfNotes = phonebook->numberOfNotes;
    for (int i = 0; i < numberOfNotes; ++i)
    {
        Note note = notes[i];
        fprintf(outputFile, "%s %s\n", note.name, note.number);
    }
    fclose(outputFile);
    return 0;
}

int saveNotesToFile(const Phonebook* phonebook, const char* nameOfFile)
{
    int errorCode = saveNotesToFileSupport(phonebook, nameOfFile);
    if (errorCode != 0)
    {
        return 1;
    }
    printf("Notes saved\n");
    return 0;
}

char* stringMul(const char* string, const int multiplier)
{
    size_t lengthOfOriginalString = strlen(string);
    char* newString = (char*)calloc(lengthOfOriginalString * multiplier + 1, sizeof(char));
    if (newString == NULL)
    {
        return NULL;
    }
    int j = 0;
    for (int i = 0; i < lengthOfOriginalString * multiplier; ++i)
    {
        newString[i] = string[j];
        ++j;
        if (j >= lengthOfOriginalString)
        {
            j = 0;
        }
    }
    return newString;
}

bool testForAddIsPassed()
{
    Phonebook phonebook = { .notes = NULL, .numberOfNotes = 0 };
    int errorCode = readNotesFromFile(&phonebook, TEST_FILE_1);
    if (errorCode != 0)
    {
        return false;
    }
    int errorCode1 = addNoteSupport(&phonebook, "abababa", "99");
    Note note1 = phonebook.notes[0];
    bool testOneIsPassed = errorCode1 == 0 && stringsAreEqual(note1.name, "abababa")
        && stringsAreEqual(note1.number, "99");

    int errorCode2 = addNoteSupport(&phonebook, "", "");
    Note note2 = phonebook.notes[1];
    bool testTwoIsPassed = errorCode2 == 0 && stringsAreEqual(note2.name, "")
        && stringsAreEqual(note2.number, "");

    char* name3 = stringMul("abc", 21);
    char* number3 = stringMul("8", 63);
    if (name3 == NULL || number3 == NULL)
    {
        free(name3);
        free(number3);
        freePhonebook(&phonebook);
        return false;
    }
    int errorCode3 = addNoteSupport(&phonebook, name3, number3);
    Note note3 = phonebook.notes[2];
    bool testThreeIsPassed = errorCode3 == 0 && stringsAreEqual(note3.name, name3)
        && stringsAreEqual(note3.number, number3) && phonebook.numberOfNotes == 3;
    free(name3);
    free(number3);

    freePhonebook(&phonebook);
    return testOneIsPassed && testTwoIsPassed && testThreeIsPassed;
}

bool testForReadAndSaveIsPassed()
{
    Phonebook phonebook = { .notes = NULL, .numberOfNotes = 0 };
    int errorCode = readNotesFromFile(&phonebook, TEST_FILE_2);
    if (errorCode != 0)
    {
        return false;
    }
    Note note1 = phonebook.notes[0];
    bool testOneIsPassed = stringsAreEqual(note1.name, "sasha")
        && stringsAreEqual(note1.number, "+1234567890");

    Note note2 = phonebook.notes[1];
    bool testTwoIsPassed = stringsAreEqual(note2.name, "masha")
        && stringsAreEqual(note2.number, "89000000000");

    Note note3 = phonebook.notes[2];
    bool testThreeIsPassed = stringsAreEqual(note3.name, "pasha")
        && stringsAreEqual(note3.number, "8(999)1112233");

    errorCode = saveNotesToFileSupport(&phonebook, TEST_FILE_2);
    bool testFourIsPassed = errorCode == 0 && phonebook.numberOfNotes == 3;

    freePhonebook(&phonebook);
    return testOneIsPassed && testTwoIsPassed && testThreeIsPassed && testFourIsPassed;
}

bool testForFindIsPassed()
{
    Phonebook phonebook = { .notes = NULL, .numberOfNotes = 0 };
    int errorCode = readNotesFromFile(&phonebook, TEST_FILE_3);
    if (errorCode != 0)
    {
        return false;
    }
    char* test1 = findNumberByNameSupport(&phonebook, "sasha");
    bool testOneIsPassed = stringsAreEqual(test1, "89001112233");

    char* test2 = findNameByNumberSupport(&phonebook, "World");
    bool testTwoIsPassed = stringsAreEqual(test2, "Hello");

    char* test3 = findNumberByNameSupport(&phonebook, "17");
    bool testThreeIsPassed = stringsAreEqual(test3, "03");

    char* test4 = findNameByNumberSupport(&phonebook, "babab");
    bool testFourIsPassed = stringsAreEqual(test4, "ababa");

    char* test5 = findNumberByNameSupport(&phonebook, "Matmex");
    bool testFiveIsPassed = test5 == NULL && phonebook.numberOfNotes == 100;

    char* test6 = findNameByNumberSupport(&phonebook, "123456789");
    bool testSixIsPassed = test6 == NULL;

    freePhonebook(&phonebook);
    return testOneIsPassed && testTwoIsPassed && testThreeIsPassed
        && testFourIsPassed && testFiveIsPassed && testSixIsPassed;
}

bool allTestsArePassed()
{
    return testForAddIsPassed() && testForReadAndSaveIsPassed() && testForFindIsPassed();
}

int main()
{
    if (!allTestsArePassed())
    {
        printf("An error occured");
        return -1;
    }
    Phonebook phonebook = { .notes = NULL, .numberOfNotes = 0 };
    int errorCode = readNotesFromFile(&phonebook, NAME_OF_FILE);
    if (errorCode != 0)
    {
        printf("An error occured");
        return -1;
    }
    printf("Command list:\n0: exit\n1: add note to phonebook\n2: print all notes\n");
    printf("3: find a number by name\n4: find a name by number\n5: save all notes to file\n");
    int command = -1;
    while (command != 0)
    {
        printf("\nEnter a command: ");
        scanf_s("%d", &command);
        switch (command)
        {
        case 0:
            break;
        case 1:
            errorCode = addNote(&phonebook);
            break;
        case 2:
            printAllNotes(&phonebook);
            break;
        case 3:
            findNumberByName(&phonebook);
            break;
        case 4:
            findNameByNumber(&phonebook);
            break;
        case 5:
            errorCode = saveNotesToFile(&phonebook, NAME_OF_FILE);
            break;
        default:
            printf("Unknown command\n");
        }
        if (errorCode != 0)
        {
            freePhonebook(&phonebook);
            printf("An error occured");
            return -1;
        }
    }
    freePhonebook(&phonebook);
}