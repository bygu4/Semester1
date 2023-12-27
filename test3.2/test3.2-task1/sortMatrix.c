#include <stdlib.h>

static void swapElements(int* const element1, int* const element2)
{
    int temp = *element1;
    *element1 = *element2;
    *element2 = temp;
}

static void swapColumns(int** const matrix, const size_t column1, const size_t column2, const size_t rows)
{
    for (size_t i = 0; i < rows; ++i)
    {
        swapElements(&matrix[i][column1], &matrix[i][column2]);
    }
}

void sortMatrix(int** const matrix, const size_t rows, const size_t columns)
{
    for (size_t i = 0; i < columns; ++i)
    {
        for (size_t j = 1; j < columns; ++j)
        {
            if (matrix[0][j - 1] > matrix[0][j])
            {
                swapColumns(matrix, j - 1, j, rows);
            }
        }
    }
}
