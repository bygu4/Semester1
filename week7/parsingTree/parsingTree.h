#pragma once
#include <stdio.h>
#include <stdbool.h>

#define SUCCESS 0
#define BAD_ALLOCATION 1
#define FILE_NOT_FOUND 2
#define DIVISION_BY_ZERO 3

typedef struct ParsingTree ParsingTree;

// считать файл и построить дерево разбора. Возвращает код ошибки
int buildTree(ParsingTree** const tree, const char* const nameOfFile);

// получить значение выражения, и если нужно, вывести выражение в инфиксной форме. Записывает по указателю код ошибки
int calculateTree(const ParsingTree* const tree, const bool printTree, int* const errorCode);

// освободить память, выделенную под дерево
void freeTree(ParsingTree** const tree);
