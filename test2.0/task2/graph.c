#include "graph.h"
#include "list.h"
#include <stdlib.h>

struct Graph {
    size_t numberOfVertices;
    List** adjacency;
};

static bool initTable(List*** const table, const size_t length)
{
    if (*table == NULL)
    {
        return true;
    }
    for (size_t i = 0; i < length; ++i)
    {
        (*table)[i] = createList();
        if ((*table)[i] == NULL)
        {
            return true;
        }
    }
    return false;
}

static void freeTable(List*** const table, const size_t length)
{
    for (size_t i = 0; i < length; ++i)
    {
        freeList(&(*table)[i]);
    }
    free(*table);
    *table = NULL;
}

static bool createAdjacencyTable(Graph* const graph, const unsigned int** const incidence,
    const size_t numberOfVertices, const size_t numberOfEdges)
{
    bool errorOccured = initTable(graph->adjacency, numberOfVertices);
    if (errorOccured)
    {
        freeGraph(&graph);
        return NULL;
    }
    for (size_t i = 0; i < numberOfVertices; ++i)
    {
        unsigned int vertex1 = 0;
        unsigned int vertex2 = 0;
        for (size_t j = 0; j < numberOfEdges; ++j)
        {
            if (incidence[j][i] != 0)
            {
                if (vertex1 == 0)
                {
                    vertex1 = i + 1;
                }
                else
                {
                    vertex2 = i + 1;
                }
            }
            if (vertex1 != 0 && vertex2 != 0)
            {
                errorOccured = push(vertex1, vertex2) || push(vertex2, vertex1);
                if (errorOccured)
                {
                    return true;
                }
                break;
            }
        }
    }
    return false;
}

void freeGraph(Graph** const graph)
{
    freeTable(&(*graph)->adjacency, (*graph)->numberOfVertices);
    free(*graph);
    *graph = NULL;
}

Graph* createGraph(const unsigned int** const incidence, 
    const size_t numberOfVertices, const size_t numberOfEdges)
{
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    if (graph == NULL)
    {
        return NULL;
    }
    graph->numberOfVertices = numberOfVertices;
    bool errorOccured = createAdjacencyTable(graph, incidence, numberOfVertices, numberOfEdges);
    if (errorOccured)
    {
        freeGraph(&graph);
        return NULL;
    }
    return graph;
}

static void printAdjacencyComponentsRecursion(Graph* const graph, const unsigned int vertexIndex, bool** const checked)
{
    for (size_t i = 0; i < listSize(graph->adjacency[vertexIndex]); ++i)
    {
        if (!(*checked)[i])
        {
            printf(" %u", value(graph->adjacency[vertexIndex], i));
            *checked[i] = true;
            printAdjacencyComponentsRecursion(graph, value(graph->adjacency[vertexIndex], i) - 1, checked);
        }
    }
}

bool printAdjacencyComponents(Graph* const graph)
{
    bool* checked = (bool*)calloc(graph->numberOfVertices, sizeof(bool));
    if (checked == NULL)
    {
        return true;
    }
    unsigned int componentNumber = 1;
    for (size_t i = 0; i < graph->numberOfVertices; ++i)
    {
        if (!checked[i])
        {
            printf("Adgacency component %u:", componentNumber);
            printAdjacencyComponentsRecursion(graph, i, checked);
            ++componentNumber;
        }
    }
    free(checked);
    return false;
}
