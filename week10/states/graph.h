#pragma once
#include <stdbool.h>
#include <stdio.h>

#define SUCCESS 0
#define BAD_ALLOCATION 1
#define FILE_NOT_FOUND 2

typedef struct Graph Graph;

// считать данные из файла и создать соответствующий граф. Возвращает код ошибки
int createGraph(Graph** const graph, const char* const nameOfFile);

// освободить память, выделенную под граф
void freeGraph(Graph** const graph);

// присоединить ближайший незанятый город к данному государству. Возвращает наличие ошибки при выделении памяти
bool occupy(Graph* const graph, const unsigned int numberOfState, bool* const occupied);

// вывести в консоль номера государств со списком городов
void printStates(const Graph* const graph);

// получить число городов
size_t numberOfCities(const Graph* const graph);

// получить число столиц
size_t numberOfCapitals(const Graph* const graph);

// проверить списки городов каждого государства
bool checkStates(const Graph* const graph, const unsigned int* const* const states,
    const size_t* const sizeOfState, const size_t numberOfStates);
