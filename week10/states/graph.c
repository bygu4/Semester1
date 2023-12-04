#include "graph.h"
#include "list.h"
#include <stdlib.h>

struct Graph {
    size_t numberOfCities;
    size_t numberOfCapitals;
    List** adjacency;
    List** states;
    unsigned int* occupation;
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
}

void freeGraph(Graph** const graph)
{
    freeTable(&(*graph)->adjacency, (*graph)->numberOfCities);
    freeTable(&(*graph)->states, (*graph)->numberOfCapitals);
    free((*graph)->occupation);
    free(*graph);
    *graph = NULL;
}

static bool createAdjacencyTable(Graph* const graph, FILE* const stream)
{
    graph->numberOfCities = 0;
    size_t numberOfRoads = 0;
    fscanf_s(stream, "%zu", &graph->numberOfCities);
    fscanf_s(stream, "%zu", &numberOfRoads);

    graph->adjacency = (List**)malloc(graph->numberOfCities * sizeof(List*));
    bool errorOccured = initTable(&graph->adjacency, graph->numberOfCities);
    if (errorOccured)
    {
        return true;
    }
    for (size_t i = 0; i < numberOfRoads; ++i)
    {
        unsigned int city1 = 0, city2 = 0, distance = 0;
        fscanf_s(stream, "%u %u %u", &city1, &city2, &distance);
        bool errorOccured = push(graph->adjacency[city1 - 1], city2, distance) || 
            push(graph->adjacency[city2 - 1], city1, distance);
        if (errorOccured)
        {
            return true;
        }
    }
    return false;
}

static bool setCapitals(Graph* const graph, FILE* const stream)
{
    graph->numberOfCapitals = 0;
    fscanf_s(stream, "%zu", &graph->numberOfCapitals);

    graph->states = (List**)malloc(graph->numberOfCapitals * sizeof(List*));
    graph->occupation = (unsigned int*)calloc(graph->numberOfCities, sizeof(unsigned int));
    bool errorOccured = initTable(&graph->states, graph->numberOfCapitals) || graph->occupation == NULL;
    if (errorOccured)
    {
        return true;
    }
    for (size_t i = 0; i < graph->numberOfCapitals; ++i)
    {
        unsigned int capital = 0;
        fscanf_s(stream, "%u", &capital);
        bool errorOccured = push(graph->states[i], capital, 0);
        if (errorOccured)
        {
            return true;
        }
        graph->occupation[capital - 1] = (unsigned int)i + 1;
    }
    return false;
}

int createGraph(Graph** const graph, const char* const nameOfFile)
{
    FILE* inputFile = NULL;
    int errorCode = fopen_s(&inputFile, nameOfFile, "r");
    if (errorCode != SUCCESS)
    {
        return errorCode;
    }
    *graph = (Graph*)malloc(sizeof(Graph));
    if (*graph == NULL)
    {
        fclose(inputFile);
        return BAD_ALLOCATION;
    }
    bool errorOccured = createAdjacencyTable(*graph, inputFile) || setCapitals(*graph, inputFile);
    fclose(inputFile);
    if (errorOccured)
    {
        freeGraph(graph);
        return BAD_ALLOCATION;
    }
    return SUCCESS;
}

bool occupy(Graph* const graph, const unsigned int numberOfState, bool* const occupied)
{
    unsigned int minDistance = UINT_MAX;
    unsigned int closestCity = 0;
    List* state = graph->states[numberOfState - 1];
    for (size_t i = 0; i < listSize(state); ++i)
    {
        List* neighbors = graph->adjacency[city(state, i) - 1];
        for (size_t j = 0; j < listSize(neighbors); ++j)
        {
            if (graph->occupation[city(neighbors, j) - 1] == 0)
            {
                unsigned int currentDistance = distance(neighbors, j);
                closestCity = currentDistance <= minDistance ? city(neighbors, j) : closestCity;
                minDistance = min(minDistance, currentDistance);
            }
        }
    }
    if (closestCity == 0)
    {
        *occupied = false;
        return false;
    }
    graph->occupation[closestCity - 1] = numberOfState;
    *occupied = true;
    return push(state, closestCity, 0);
}

void printStates(const Graph* const graph)
{
    for (size_t i = 0; i < graph->numberOfCapitals; ++i)
    {
        printf("\nState %zu", i + 1);
        printf("\nCities: ");
        printList(graph->states[i]);
        printf("\n");
    }
}

size_t numberOfCities(const Graph* const graph)
{
    return graph->numberOfCities;
}

size_t numberOfCapitals(const Graph* const graph)
{
    return graph->numberOfCapitals;
}

bool checkStates(const Graph* const graph, const unsigned int* const* const states, 
    const size_t* const sizeOfState, const size_t numberOfStates)
{
    if (numberOfCapitals(graph) != numberOfStates)
    {
        return false;
    }
    for (size_t i = 0; i < numberOfStates; ++i)
    {
        if (!arrayIsEqual(graph->states[i], states[i], sizeOfState[i]))
        {
            return false;
        }
    }
    return true;
}
