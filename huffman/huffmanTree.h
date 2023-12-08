#pragma once
#include <stdbool.h>

typedef struct {
    size_t size[256];
    bool code[256][256];
} CodeTable;

typedef struct Tree Tree;

size_t getCount(const Tree* const tree);

Tree* makeLeaf(const char value, const size_t count);

Tree* makeTree(Tree** const tree1, Tree** const tree2);

CodeTable* createCodeTable(const Tree* const tree);
