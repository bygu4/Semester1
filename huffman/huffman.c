#include "huffman.h"
#include "huffmanTree.h"
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_CHARACTERS 256
#define NAME_OF_FILE "main.txt"

static void swap(const Tree** tree1, const Tree** tree2)
{
    Tree* temp = *tree1;
    *tree1 = *tree2;
    *tree2 = temp;
}

static void insertionSortStep(const Tree** const array, const size_t index)
{
    for (size_t i = index; i >= 1 && getCount(array[i - 1]) < getCount(array[i]); --i)
    {
        swap(&array[i - 1], &array[i]);
    }
}

static void insertionSort(const Tree** const array, const size_t sizeOfArray)
{
    for (size_t i = 1; i < sizeOfArray; ++i)
    {
        insertionSortStep(array, i);
    }
}

static size_t getLength(const char* const string, const CodeTable* const table)
{
    size_t result = 0;
    for (size_t i = 0; string[i] != '\0'; ++i)
    {
        result += table->size[(unsigned char)string[i]];
    }
    return result + 1;
}

static char* getCompression(const char* const string, const CodeTable* const table, const size_t length)
{
    char* result = (char*)malloc(sizeof(char) * length);
    size_t index = 0;
    for (size_t i = 0; string[i] != '\0'; ++i)
    {
        bool* code = table->code[(unsigned char)string[i]];
        size_t size = table->size[(unsigned char)string[i]];
        for (size_t j = 0; j < size; ++j)
        {
            result[index] = code[j] ? '1' : '0';
            ++index;
        }
    }
    result[index] = '\0';
    return result;
}

static void putInBytes(FILE* const stream, const bool* const code, const size_t length)
{
    char byte = 0;
    int count = 0;
    for (size_t i = 0; i < length; ++i)
    {
        if (count == 8)
        {
            fputc(byte, stream);
            byte = 0;
            count = 0;
        }
        ++count;
        byte += code[i] * (1 << (7 - count));
    }
    fputc(byte, stream);
}

static void writeTable(const CodeTable* const table, const char* const nameOfFile)
{
    FILE* file = NULL;
    int errorCode = fopen_s(&file, nameOfFile, "w");
    if (errorCode != 0)
    {
        return;
    }
    for (size_t i = 0; i < NUMBER_OF_CHARACTERS; ++i)
    {
        fputc((char)i, file);
        putInBytes(file, table->code[i], table->size[i]);
    }
    fclose(file);
}

char* compress(const char* const string, size_t* const resultSize)
{
    size_t* charCount = (size_t*)calloc(NUMBER_OF_CHARACTERS, sizeof(size_t));
    if (charCount == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; string[i] != '\0'; ++i)
    {
        unsigned char character = string[i];
        ++charCount[character];
    }
    Tree** treeArray = (Tree**)calloc(NUMBER_OF_CHARACTERS, sizeof(Tree*));
    if (treeArray == NULL)
    {
        free(charCount);
        return NULL;
    }
    for (size_t i = 0; i < NUMBER_OF_CHARACTERS; ++i)
    {
        size_t count = charCount[i];
        if (count != 0)
        {
            treeArray[i] = makeLeaf((unsigned char)i, charCount[i]);
            if (treeArray[i] == NULL)
            {
                free(charCount);
                free(treeArray);
                return NULL;
            }
        }
    }
    insertionSort(treeArray, NUMBER_OF_CHARACTERS);
    for (size_t i = NUMBER_OF_CHARACTERS - 1; i > 0; --i)
    {
        if (treeArray[i] == NULL)
        {
            continue;
        }
        treeArray[i] = makeTree(&treeArray[i], &treeArray[i - 1]);
        insertionSortStep(treeArray, i);
    }
    CodeTable* table = createCodeTable(treeArray[0]);
    writeTable(table, NAME_OF_FILE);
    *resultSize = getLength(string, table);
    return getCompression(string, table, *resultSize);
}
