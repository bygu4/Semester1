#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SUCCESS 0
#define BAD_ALLOCATION 1

#define NAME_OF_FILE "task3.txt"
#define TEST_FILE "test.txt"

void readStringAndCount(FILE* const file, int* const characters)
{
    char character = fgetc(file);
    while (character != '\n' && !feof(file))
    {
        ++characters[(size_t)character + 128];
        character = fgetc(file);
    }
}

int* countNumberOfEntriesForEveryCharacter(const char* const nameOfFile, int* const errorCode)
{
    FILE* file = NULL;
    *errorCode = fopen_s(&file, nameOfFile, "r");
    if (*errorCode != SUCCESS)
    {
        return NULL;
    }
    int* characters = (int*)calloc(256, sizeof(int));
    if (characters == NULL)
    {
        *errorCode = BAD_ALLOCATION;
        return NULL;
    }
    while (!feof(file))
    {
        readStringAndCount(file, characters);
    }
    fclose(file);
    *errorCode = SUCCESS;
    return characters;
}

void printResult(const int* const result)
{
    for (size_t i = 0; i < 256; ++i)
    {
        char character = (char)i - 128;
        int numberOfEntries = result[i];
        if (numberOfEntries != 0)
        {
            printf("%c: %d\n", character, numberOfEntries);
        }
    }
}

int main(void)
{
    int errorCode = -1;
    int* result = countNumberOfEntriesForEveryCharacter(NAME_OF_FILE, &errorCode);
    if (errorCode != SUCCESS)
    {
        printf("An error occured\n");
        return errorCode;
    }
    printResult(result);
    free(result);
    return SUCCESS;
}
