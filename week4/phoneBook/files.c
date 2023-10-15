#include "files.h"
#include "str.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
        char* name = fgetString(inputFile, ' ', INITIAL_SIZE_OF_BUFFER);
        if (feof(inputFile))
        {
            if (strlen(name) == 0)
            {
                free(name);
                break;
            }
            free(name);
            errorCode = INCORRECT_FORMAT;
            break;
        }
        char* number = fgetString(inputFile, '\n', INITIAL_SIZE_OF_BUFFER);
        if (name == NULL || number == NULL)
        {
            free(name);
            free(number);
            errorCode = BAD_ALLOCATION;
            break;
        }
        errorCode = addNote(phonebook, name, number);
        free(name);
        free(number);
        if (errorCode != SUCCESS)
        {
            break;
        }
    }
    fclose(inputFile);
    return errorCode;
}

int saveNotesToFile(const Phonebook* const phonebook, const char* const nameOfFile)
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
