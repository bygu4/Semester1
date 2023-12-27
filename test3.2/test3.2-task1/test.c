#include "test.h"
#include "sortMatrix.h"
#include <stdio.h>

static void printFailedTest(const size_t numberOfTest)
{
    printf("Test %zu has failed\n", numberOfTest);
}

static bool rowsAreEqual(const int* const row1, const int* const row2, const size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
        if (row1[i] != row2[i])
        {
            return false;
        }
    }
    return true;
}

static bool matricesAreEqual(const int** const matrix1, const int** const matrix2, 
    const size_t rows, const size_t columns)
{
    for (size_t i = 0; i < rows; ++i)
    {
        if (!rowsAreEqual(matrix1[i], matrix2[i], columns))
        {
            return false;
        }
    }
    return true;
}

static void freeTable(int*** const table, const size_t rows)
{
    for (size_t i = 0; i < rows; ++i)
    {
        free((*table)[i]);
    }
    free(*table);
    *table = NULL;
}

static int** createDynamicTable(const int staticTable[], const size_t rows, const size_t columns)
{
    int** table = (int**)malloc(rows * sizeof(int*));
    if (table == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < rows; ++i)
    {
        table[i] = (int*)malloc(columns * sizeof(int));
        if (table[i] == NULL)
        {
            freeTable(&table, i);
            return NULL;
        }
        for (size_t j = 0; j < columns; ++j)
        {
            table[i][j] = staticTable[i * columns + j];
        }
    }
    return table;
}

static bool testCase(const int staticTable[], const int expectedTable[],
    const size_t rows, const size_t columns, const size_t numberOfTest)
{
    int** matrix = createDynamicTable(staticTable, rows, columns);
    int** expectedMatrix = createDynamicTable(expectedTable, rows, columns);
    if (matrix == NULL || expectedMatrix == NULL)
    {
        freeTable(&matrix, rows);
        freeTable(&expectedMatrix, rows);
        printf("Failed to create dynamic table\n");
        return false;
    }
    sortMatrix(matrix, rows, columns);
    bool testPassed = matricesAreEqual(matrix, expectedMatrix, rows, columns);
    if (!testPassed)
    {
        printFailedTest(numberOfTest);
    }
    freeTable(&matrix, rows);
    freeTable(&expectedMatrix, rows);
    return testPassed;
}

bool test(void)
{
    int matrix1[3][4] = { { 4, 3, 2, 1 },
                          { 5, 6, 7, 8 },
                          { -1, -1, -1, -1 } };
    int expectedMatrix1[3][4] = { { 1, 2, 3, 4 },
                                  { 8, 7, 6, 5 },
                                  { -1, -1, -1, -1 } };

    int* matrix2[5] = { NULL, NULL, NULL, NULL, NULL };

    int matrix3[3][3] = { { 1, 2, 3 },
                          { 3, 2, 1 },
                          { 6, 5, 4 } };

    int matrix4[5][1] = { { 8 }, { 7 }, { 6 }, { 5 }, { 4 } };

    int** matrix5 = NULL;

    return testCase(matrix1, expectedMatrix1, 3, 4, 1) &&
        testCase(matrix2, matrix2, 5, 0, 2) &&
        testCase(matrix3, matrix3, 3, 3, 3) && 
        testCase(matrix4, matrix4, 5, 1, 4) && 
        testCase(matrix5, matrix5, 0, 0, 5);
}
