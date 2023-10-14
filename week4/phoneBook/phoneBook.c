#include "phonebook.h"
#include "str.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static void freeNote(Note* const note)
{
    free(note->name);
    free(note->number);
}

void freePhonebook(Phonebook* const phonebook)
{
    Note* notes = phonebook->notes;
    size_t* numberOfNotes = &phonebook->numberOfNotes;
    for (size_t i = 0; i < *numberOfNotes; ++i)
    {
        Note note = notes[i];
        freeNote(&note);
    }
    free(notes);
    *numberOfNotes = 0;
}

int addNoteSupport(Phonebook* const phonebook, const char* const name, const char* const number)
{
    if (phonebook->numberOfNotes >= MAX_NOTES)
    {
        return TOO_MUCH_NOTES;
    }
    Note note = { NULL, NULL };
    size_t sizeOfName = strlen(name) + 1;
    size_t sizeOfNumber = strlen(number) + 1;
    note.name = calloc(sizeOfName, sizeof(char));
    note.number = calloc(sizeOfNumber, sizeof(char));
    if (note.name == NULL || note.number == NULL)
    {
        freeNote(&note);
        return BAD_ALLOCATION;
    }
    int errorCode1 = strcpy_s(note.name, sizeOfName, name);
    int errorCode2 = strcpy_s(note.number, sizeOfNumber, number);
    if (errorCode1 != 0 || errorCode2 != 0)
    {
        freeNote(&note);
        return BAD_ALLOCATION;
    }
    size_t* numberOfNotes = &phonebook->numberOfNotes;
    size_t index = *numberOfNotes;
    phonebook->notes[index] = note;
    ++* numberOfNotes;
    return SUCCESS;
}

int addNote(Phonebook* const phonebook)
{
    size_t* numberOfNotes = &phonebook->numberOfNotes;
    if (*numberOfNotes >= MAX_NOTES)
    {
        printf("Cannot add any more notes\n");
        return SUCCESS;
    }
    char name[SIZE_OF_BUFFER] = { '\0' };
    printf("Enter name: ");
    scanf_s("%s", name, SIZE_OF_BUFFER - 1);
    char number[SIZE_OF_BUFFER] = { '\0' };
    printf("Enter number: ");
    scanf_s("%s", number, SIZE_OF_BUFFER - 1);

    int errorCode = addNoteSupport(phonebook, name, number);
    if (errorCode != SUCCESS)
    {
        return errorCode;
    }
    printf("Note added\n");
    return SUCCESS;
}

int readNotesFromFile(Phonebook* const phonebook, const char* const nameOfFile)
{
    phonebook->notes = malloc(sizeof(Note) * MAX_NOTES);
    if (phonebook->notes == NULL)
    {
        return BAD_ALLOCATION;
    }
    FILE* inputFile = NULL;
    int errorCode = fopen_s(&inputFile, nameOfFile, "r");
    if (errorCode == FILE_NOT_FOUND)
    {
        return FILE_NOT_FOUND;
    }
    if (errorCode != SUCCESS)
    {
        free(phonebook->notes);
        return errorCode;
    }
    size_t* numberOfNotes = &phonebook->numberOfNotes;
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
        if (errorCode != SUCCESS)
        {
            fclose(inputFile);
            freePhonebook(phonebook);
            return errorCode;
        }
    }
    fclose(inputFile);
    return SUCCESS;
}

int saveNotesToFileSupport(const Phonebook* const phonebook, const char* const nameOfFile)
{
    FILE* outputFile = NULL;
    int errorCode = fopen_s(&outputFile, nameOfFile, "w");
    if (errorCode != SUCCESS)
    {
        return errorCode;
    }
    Note* notes = phonebook->notes;
    size_t numberOfNotes = phonebook->numberOfNotes;
    for (size_t i = 0; i < numberOfNotes; ++i)
    {
        Note note = notes[i];
        fprintf(outputFile, "%s %s\n", note.name, note.number);
    }
    fclose(outputFile);
    return SUCCESS;
}

int saveNotesToFile(const Phonebook* const phonebook, const char* const nameOfFile)
{
    int errorCode = saveNotesToFileSupport(phonebook, nameOfFile);
    if (errorCode != 0)
    {
        return errorCode;
    }
    printf("Notes saved\n");
    return SUCCESS;
}

void printAllNotes(const Phonebook* const phonebook)
{
    size_t numberOfNotes = phonebook->numberOfNotes;
    if (numberOfNotes == 0)
    {
        printf("No notes yet\n");
    }
    for (size_t i = 0; i < numberOfNotes; ++i)
    {
        Note note = phonebook->notes[i];
        printf("%d) %s - %s\n", (int)i + 1, note.name, note.number);
    }
}

char* findNumberByNameSupport(const Phonebook* const phonebook, const char* const nameToFind)
{
    Note* notes = phonebook->notes;
    size_t numberOfNotes = phonebook->numberOfNotes;
    for (size_t i = 0; i < numberOfNotes; ++i)
    {
        Note note = notes[i];
        if (stringsAreEqual(note.name, nameToFind))
        {
            return note.number;
        }
    }
    return NULL;
}

void findNumberByName(const Phonebook* const phonebook)
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

char* findNameByNumberSupport(const Phonebook* const phonebook, const char* const numberToFind)
{
    Note* notes = phonebook->notes;
    size_t numberOfNotes = phonebook->numberOfNotes;
    for (size_t i = 0; i < numberOfNotes; ++i)
    {
        Note note = notes[i];
        if (stringsAreEqual(note.number, numberToFind))
        {
            return note.name;
        }
    }
    return NULL;
}

void findNameByNumber(const Phonebook* const phonebook)
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
