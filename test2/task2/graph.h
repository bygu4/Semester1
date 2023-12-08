#pragma once

#include <stdbool.h>
#include <stdio.h>

typedef struct Graph Graph;

void freeGraph(Graph** const graph);

Graph* createGraph(const unsigned int** const incidence,
    const size_t numberOfVertices, const size_t numberOfEdges);

bool printAdjacencyComponents(Graph* const graph);
