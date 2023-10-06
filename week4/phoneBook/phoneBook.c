#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NAME_OF_FILE "phoneBook.txt"

typedef struct {
    char* name;
    char* number;
} Note;

typedef struct {
    Note* notes;
    int numberOfNotes;
} Phonebook;

int readNotesFromFile(Phonebook* phonebook, const char* nameOfFile)
{
    phonebook->notes = malloc(sizeof(Note) * 100);
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
        return 1;
    }
    int* numberOfNotes = &phonebook->numberOfNotes;
    while (!feof(inputFile) && *numberOfNotes < 100)
    {
        Note note = { "", "" };
        char name[64] = { '\0' };
        fscanf_s(inputFile, "%[^ ]", name, 63);
        fseek(inputFile, 1, SEEK_CUR);
        if (strlen(name) == 0)
        {
            break;
        }
        char number[64] = { '\0' };
        fscanf_s(inputFile, "%[^\n]", number, 63);
        fseek(inputFile, 2, SEEK_CUR);

        int size = sizeof(char) * 64;
        note.name = malloc(size);
        note.number = malloc(size);
        if (note.name == NULL || note.number == NULL)
        {
            fclose(inputFile);
            return 1;
        }
        errorCode = strcpy_s(note.name, size, name);
        errorCode += strcpy_s(note.number, size, number);
        if (errorCode != 0)
        {
            fclose(inputFile);
            return 1;
        }
        phonebook->notes[*numberOfNotes] = note;
        ++* numberOfNotes;
    }
    fclose(inputFile);
    return 0;
}

int addNote(Phonebook* phonebook)
{
    int* numberOfNotes = &phonebook->numberOfNotes;
    if (*numberOfNotes >= 100)
    {
        printf("Cannot add any more notes\n");
        return 0;
    }
    Note note = { "", "" };
    char name[64] = { '\0' };
    printf("Enter name: ");
    scanf_s("%s", name, 63);
    char number[64] = { '\0' };
    printf("Enter number: ");
    scanf_s("%s", number, 63);

    int size = sizeof(char) * 64;
    note.name = malloc(size);
    note.number = malloc(size);
    if (note.name == NULL || note.number == NULL)
    {
        return 1;
    }
    int errorCode = strcpy_s(note.name, size, name);
    errorCode += strcpy_s(note.number, size, number);
    if (errorCode != 0)
    {
        return 1;
    }
    int index = *numberOfNotes;
    phonebook->notes[index] = note;
    ++* numberOfNotes;
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

bool stringsAreEqual(char* string1, char* string2)
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

void findNumberByName(const Phonebook* phonebook)
{
    char nameToFind[64] = { '\0' };
    printf("Enter a name: ");
    scanf_s("%s", nameToFind, 63);
    Note* notes = phonebook->notes;
    int numberOfNotes = phonebook->numberOfNotes;
    for (int i = 0; i < numberOfNotes; ++i)
    {
        Note note = notes[i];
        if (stringsAreEqual(note.name, nameToFind))
        {
            printf("%s\n", note.number);
            return;
        }
    }
    printf("Name not found\n");
}

void findNameByNumber(const Phonebook* phonebook)
{
    char numberToFind[64] = { '\0' };
    printf("Enter a number: ");
    scanf_s("%s", numberToFind, 63);
    Note* notes = phonebook->notes;
    int numberOfNotes = phonebook->numberOfNotes;
    for (int i = 0; i < numberOfNotes; ++i)
    {
        Note note = notes[i];
        if (stringsAreEqual(note.number, numberToFind))
        {
            printf("%s\n", note.name);
            return;
        }
    }
    printf("Number not found\n");
}

int saveNotesToFile(const Phonebook* phonebook, const char* nameOfFile)
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
    printf("Notes saved\n");
    fclose(outputFile);
    return 0;
}

int main()
{
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
            printf("Unknown command");
        }
        if (errorCode != 0)
        {
            free(phonebook.notes);
            return -1;
        }
    }
    free(phonebook.notes);
}