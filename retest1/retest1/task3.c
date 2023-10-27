#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SUCCESS 0
#define TEST_FAILED -1
#define BAD_ALLOCATION 1

#define NUMBER_OF_CHARACTERS 256

#define NAME_OF_FILE "task3.txt"
#define TEST_FILE "test.txt"

void readStringAndCount(FILE* const file, int* const characters)
{
    char character = fgetc(file);
    while (character != '\n' && !feof(file))
    {
        ++characters[(size_t)character + NUMBER_OF_CHARACTERS / 2];
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
    int* characters = (int*)calloc(NUMBER_OF_CHARACTERS, sizeof(int));
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
    for (size_t i = 0; i < NUMBER_OF_CHARACTERS; ++i)
    {
        char character = (char)i - NUMBER_OF_CHARACTERS / 2;
        int numberOfEntries = result[i];
        if (numberOfEntries != 0)
        {
            if (character == ' ')
            {
                printf("Space: %d\n", numberOfEntries);
            }
            else
            {
                printf("%c: %d\n", character, numberOfEntries);
            }
        }
    }
}

bool arraysAreEqual(const int* const array1, const int* const array2, const size_t sizeOfArray)
{
    for (size_t i = 0; i < sizeOfArray; ++i)
    {
        if (array1[i] != array2[i])
        {
            return false;
        }
    }
    return true;
}

bool testCase(const char* const nameOfFile, int* expectedArray)
{
    int errorCode = -1;
    int* result = countNumberOfEntriesForEveryCharacter(nameOfFile, &errorCode);
    bool testIsPassed = errorCode == SUCCESS && arraysAreEqual(result, expectedArray, NUMBER_OF_CHARACTERS);
    free(result);
    free(expectedArray);
    return testIsPassed;
}

bool test(void)
{
    int* expectedArray = (int*)calloc(NUMBER_OF_CHARACTERS, sizeof(int));
    expectedArray[(size_t)'8' + NUMBER_OF_CHARACTERS / 2] = 8;
    expectedArray[(size_t)'7' + NUMBER_OF_CHARACTERS / 2] = 7;
    expectedArray[(size_t)'a' + NUMBER_OF_CHARACTERS / 2] = 2;
    expectedArray[(size_t)'b' + NUMBER_OF_CHARACTERS / 2] = 3;
    expectedArray[(size_t)'c' + NUMBER_OF_CHARACTERS / 2] = 1;
    expectedArray[(size_t)' ' + NUMBER_OF_CHARACTERS / 2] = 2;
    expectedArray[(size_t)'#' + NUMBER_OF_CHARACTERS / 2] = 2;
    bool testOneIsPassed = testCase(TEST_FILE, expectedArray);
    if (!testOneIsPassed)
    {
        printf("Test 1 has failed\n");
        return false;
    }
}

int main(void)
{
    const bool allTestsArePassed = test();
    if (!allTestsArePassed)
    {
        return TEST_FAILED;
    }
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
