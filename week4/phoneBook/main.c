#include "phonebook.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NAME_OF_FILE "main.txt"
#define TEST_FAILED -1

int main(void)
{
    const bool allTestsArePassed = test();
    if (!allTestsArePassed)
    {
        return TEST_FAILED;
    }

    Phonebook phonebook = { .notes = NULL, .numberOfNotes = 0 };
    int errorCode = readNotesFromFile(&phonebook, NAME_OF_FILE);
    if (errorCode != SUCCESS && errorCode != FILE_NOT_FOUND)
    {
        printf("An error occured\n");
        return errorCode;
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
        if (errorCode != SUCCESS)
        {
            freePhonebook(&phonebook);
            printf("An error occured\n");
            return errorCode;
        }
    }
    freePhonebook(&phonebook);
}
