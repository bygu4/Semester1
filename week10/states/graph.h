#pragma once
#include <stdbool.h>
#include <stdio.h>

#define SUCCESS 0
#define BAD_ALLOCATION 1
#define FILE_NOT_FOUND 2

typedef struct Graph Graph;

// считать данные из файла и создать соответствующий граф. ¬озвращает код ошибки
int createGraph(Graph** const graph, const char* const nameOfFile);

// освободить пам€ть, выделенную под граф
void freeGraph(Graph** const graph);

// присоединить ближайший незан€тый город к данному государству. ¬озвращает наличие ошибки при выделении пам€ти
bool occupy(Graph* const graph, const unsigned int numberOfState, bool* const occupied);

// вывести в консоль номера государств со списком городов
void printStates(const Graph* const graph);

// получить число городов
size_t numberOfCities(const Graph* const graph);

// получить число столиц
size_t numberOfCapitals(const Graph* const graph);

// проверить списки городов каждого государства
bool checkStates(const Graph* const graph, const unsigned int** const expectedStates, 
    const size_t* const lengths);
