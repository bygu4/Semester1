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

int addNote(Phonebook* const phonebook, const char* const name, const char* const number)
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
        return COPY_ERROR;
    }
    size_t* numberOfNotes = &phonebook->numberOfNotes;
    size_t index = *numberOfNotes;
    phonebook->notes[index] = note;
    ++* numberOfNotes;
    return SUCCESS;
}

char* findNumberByName(const Phonebook* const phonebook, const char* const nameToFind)
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

char* findNameByNumber(const Phonebook* const phonebook, const char* const numberToFind)
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
