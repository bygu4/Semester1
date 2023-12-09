#include "console.h"
#include "str.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int addNoteConsole(Phonebook* const phonebook)
{
    size_t* numberOfNotes = &phonebook->numberOfNotes;
    if (*numberOfNotes >= MAX_NOTES)
    {
        printf("Cannot add any more notes\n");
        return SUCCESS;
    }
    printf("Enter name: ");
    char* name = getString('\n', INITIAL_SIZE_OF_BUFFER);
    printf("Enter number: ");
    char* number = getString('\n', INITIAL_SIZE_OF_BUFFER);
    if (name == NULL || number == NULL)
    {
        free(name);
        free(number);
        return BAD_ALLOCATION;
    }
    int errorCode = addNote(phonebook, name, number);
    free(name);
    free(number);
    if (errorCode != SUCCESS)
    {
        return errorCode;
    }
    printf("Note added\n");
    return SUCCESS;
}

int saveNotesToFileConsole(const Phonebook* const phonebook, const char* const nameOfFile)
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
        return;
    }
    for (size_t i = 0; i < numberOfNotes; ++i)
    {
        Note note = phonebook->notes[i];
        printf("%d) %s - %s\n", (int)i + 1, note.name, note.number);
    }
}

int findNumberByNameConsole(const Phonebook* const phonebook)
{
    printf("Enter a name: ");
    char* nameToFind = getString('\n', INITIAL_SIZE_OF_BUFFER);
    if (nameToFind == NULL)
    {
        return BAD_ALLOCATION;
    }
    char* foundNumber = findNumberByName(phonebook, nameToFind);
    free(nameToFind);
    if (foundNumber == NULL)
    {
        printf("Name not found\n");
        return SUCCESS;
    }
    printf("%s\n", foundNumber);
    return SUCCESS;
}

int findNameByNumberConsole(const Phonebook* const phonebook)
{
    printf("Enter a number: ");
    char* numberToFind = getString('\n', INITIAL_SIZE_OF_BUFFER);
    if (numberToFind == NULL)
    {
        return BAD_ALLOCATION;
    }
    char* foundName = findNameByNumber(phonebook, numberToFind);
    free(numberToFind);
    if (foundName == NULL)
    {
        printf("Number not found\n");
        return SUCCESS;
    }
    printf("%s\n", foundName);
    return SUCCESS;
}
