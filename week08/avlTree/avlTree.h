#pragma once

#pragma once
#include <stdbool.h>

typedef struct AvlTree AvlTree;

// создание пустого дерева
AvlTree* createTree(void);

// добавление элемента в дерево по ключу. Возвращает наличие ошибки при выделении памяти
bool addNode(AvlTree* const tree, const char* const key, const char* const data);

// получение значения по ключу
char* getData(const AvlTree* const tree, const char* const key);

// проверка наличия ключа в дереве
bool findKey(const AvlTree* const tree, const char* const key);

// удаление элемента из дерева по ключу. Если элемент удален, возвращает true, иначе - false
bool deleteNode(AvlTree* const tree, const char* const key);

// освобождение памяти, выделенной под дерево
void freeTree(AvlTree** const tree);
