#pragma once

#include <stdbool.h>
#include <stdlib.h>

typedef struct SearchTree SearchTree;

// создание пустого дерева
SearchTree* createTree(void);

// добавление элемента в дерево поиска. Возвращает наличие ошибки при выделении памяти
bool addNode(SearchTree* const tree, const int key);

// очистить память, выделенную под дерево
void freeTree(SearchTree** const tree);

// перезаписать массив ключами дерева симметричным обходом
void rewriteArray(const SearchTree* const tree, int** const array, const size_t lengthOfArray);
