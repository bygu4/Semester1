#include "userInterface.h"
#include <stdio.h>
#include <string.h>

int addNoteUI(Phonebook* const phonebook)
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

    int errorCode = addNote(phonebook, name, number);
    if (errorCode != SUCCESS)
    {
        return errorCode;
    }
    printf("Note added\n");
    return SUCCESS;
}

int saveNotesToFileUI(const Phonebook* const phonebook, const char* const nameOfFile)
{
    int errorCode = saveNotesToFile(phonebook, nameOfFile);
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

void findNumberByNameUI(const Phonebook* const phonebook)
{
    char nameToFind[SIZE_OF_BUFFER] = { '\0' };
    printf("Enter a name: ");
    scanf_s("%s", nameToFind, SIZE_OF_BUFFER - 1);
    char* foundNumber = findNumberByName(phonebook, nameToFind);
    if (foundNumber == NULL)
    {
        printf("Name not found\n");
        return;
    }
    printf("%s\n", foundNumber);
}

void findNameByNumberUI(const Phonebook* const phonebook)
{
    char numberToFind[SIZE_OF_BUFFER] = { '\0' };
    printf("Enter a number: ");
    scanf_s("%s", numberToFind, SIZE_OF_BUFFER - 1);
    char* foundName = findNameByNumber(phonebook, numberToFind);
    if (foundName == NULL)
    {
        printf("Number not found\n");
        return;
    }
    printf("%s\n", foundName);
}
