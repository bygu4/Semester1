#include "console.h"
#include "graph.h"
#include <stdlib.h>

static void freeTable(unsigned int*** const table, const size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
        free((*table)[i]);
    }
    free(*table);
    *table = NULL;
}

static unsigned int** scanTable(const size_t rows, const size_t columns)
{
    unsigned int** table = (unsigned int**)malloc(rows * sizeof(unsigned int*));
    if (table == NULL)
    {
        return NULL;
    }
    for (size_t i = 0; i < rows; ++i)
    {
        table[i] = (unsigned int**)malloc(columns * sizeof(unsigned int));
        if (table[i] == NULL)
        {
            freeTable(&table, i);
            return NULL;
        }
        for (size_t j = 0; j < columns; ++j)
        {
            scanf_s("%u", &table[i][j]);
        }
    }
    return table;
}

int console(void)
{
    size_t rows = 0, columns = 0;
    scanf_s("%zu %zu", &rows, &columns);
    unsigned int** table = scanTable(rows, columns);
    if (table == NULL)
    {
        return BAD_ALLOCATION;
    }
    Graph* graph = createGraph(table, columns, rows);
    if (graph == NULL)
    {
        return BAD_ALLOCATION;
    }
    bool errorOccured = printAdjacencyComponents(graph);
    return errorOccured ? BAD_ALLOCATION : SUCCESS;
}
