#include "readArrayFromFile.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int* readArrayFromFile(const char* const nameOfFile, int* const sizeOfArray)
{
    FILE* inputFile = NULL;
    int errorCode = fopen_s(&inputFile, nameOfFile, "r");
    if (errorCode != 0)
    {
        return NULL;
    }
    if (!feof(inputFile))
    {
        fscanf_s(inputFile, "%d", sizeOfArray);
    }
    int* array = (int*)calloc(*sizeOfArray, sizeof(int));
    if (array == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < *sizeOfArray && !feof(inputFile); ++i)
    {
        fscanf_s(inputFile, "%d", &array[i]);
    }
    fclose(inputFile);

    return array;
}
