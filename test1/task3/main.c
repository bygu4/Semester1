#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NAME_OF_FILE "main.txt"
#define TEST_FILE_1 "testFiles/testfile1.txt"
#define TEST_FILE_2 "testFiles/testfile2.txt"
#define TEST_FILE_3 "testFiles/testfile3.txt"

enum errorCodes {
    testFailed = -1,
    success = 0,
    badAllocation = 1,
    fileNotFound = 2
};

typedef struct {
    char* data;
    size_t length;
    size_t capacity;
} String;

static String* createString(void)
{
    String* string = (String*)malloc(sizeof(String));
    if (string == NULL)
    {
        return NULL;
    }
    string->length = 0;
    string->capacity = 1;
    string->data = (char*)calloc(string->capacity, sizeof(char));
    if (string->data == NULL)
    {
        free(string);
        return NULL;
    }
    return string;
}

static void freeString(String** const string)
{
    free((*string)->data);
    free(*string);
    *string = NULL;
}

static bool addCharToString(String* string, const char character)
{
    if (string->capacity <= string->length + 1)
    {
        string->capacity *= 2;
        string->data = (char*)realloc(string->data, string->capacity);
        if (string->data == NULL)
        {
            return true;
        }
    }
    ++string->length;
    string->data[string->length - 1] = character;
    string->data[string->length] = '\0';
    return false;
}

static void swap(char** const string1, char** const string2)
{
    char* temp = *string1;
    *string1 = *string2;
    *string2 = temp;
}

static char* fgetString(FILE* const stream, const char breakPoint)
{
    String* string = createString();
    if (string == NULL)
    {
        return NULL;
    }
    char previous = '\0';
    char current = fgetc(stream);
    while (!feof(stream) && current != breakPoint)
    {
        bool errorOccured = (current != previous) ? addCharToString(string, current) : false;
        if (errorOccured)
        {
            free(string);
            return NULL;
        }
        previous = current;
        current = fgetc(stream);
    }
    char* output = NULL;
    swap(&output, &string->data);
    freeString(&string);
    return output;
}

static int readFile(char** const result, const char* const nameOfFile)
{
    FILE* inputFile = NULL;
    int errorCode = fopen_s(&inputFile, nameOfFile, "r");
    if (errorCode != success)
    {
        return errorCode;
    }
    *result = fgetString(inputFile, EOF);
    fclose(inputFile);
    return *result != NULL ? success : badAllocation;
}

static bool stringsAreEqual(const char* const string1, const char* const string2)
{
    for (size_t i = 0; string1[i] != '\0' || string2[i] != '\0'; ++i)
    {
        if (string1[i] != string2[i])
        {
            return false;
        }
    }
    return true;
}

static void printFailedTest(const size_t numberOfTest)
{
    printf("Test %zu has failed\n", numberOfTest);
}

static bool testCase(const char* const nameOfFile, const char* const expectedOutput, const size_t numberOfTest)
{
    char* output = NULL;
    int errorCode = readFile(&output, nameOfFile);
    bool testIsPassed = (errorCode == success) && stringsAreEqual(output, expectedOutput);
    free(output);
    if (!testIsPassed)
    {
        if (errorCode == fileNotFound)
        {
            printf("File not found\n");
        }
        printFailedTest(numberOfTest);
    }
    return testIsPassed;
}

static bool testIsPassed(void)
{
    return testCase(TEST_FILE_1, "", 1) &&
        testCase(TEST_FILE_2, "ba\ncdc", 2) &&
        testCase(TEST_FILE_3, "abcd abcd", 3);
}

int main(const size_t argc, const char* const argv)
{
    if (!testIsPassed())
    {
        return testFailed;
    }
    if (argc == 2 && stringsAreEqual(argv[1], "-test"))
    {
        return success;
    }
    char* fileData = NULL;
    int errorCode = readFile(&fileData, NAME_OF_FILE);
    if (errorCode != success)
    {
        printf(errorCode == fileNotFound ? "File not found\n" : "An error occured\n");
        return errorCode;
    }
    printf("File data without sequences:\n");
    printf("%s\n", fileData);
    free(fileData);
    return success;
}
