#pragma once

#pragma once
#include <stdbool.h>

typedef struct SearchTree SearchTree;

// создание пустого дерева
SearchTree* createTree(void);

// добавление элемента в дерево по ключу. Возвращает наличие ошибки при выделении памяти
bool addNode(SearchTree* const tree, const int key, const char* const data);

// получение значения по ключу
char* getData(const SearchTree* const tree, const int key);

// проверка наличия ключа в дереве
bool findKey(const SearchTree* const tree, const int key);

// удаление элемента из дерева по ключу. Если элемент удален, возвращает true, иначе - false
bool deleteNode(SearchTree* const tree, int const key);

// освобождение памяти, выделенной под дерево
void freeTree(SearchTree** const tree);
