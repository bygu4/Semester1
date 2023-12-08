#include "huffmanTree.h"
#include <stdlib.h>
#include <memory.h>

typedef struct {
    char value;
    size_t count;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

struct Tree {
    Node* root;
};

size_t getCount(const Tree* const tree)
{
    return tree != NULL ? tree->root->count : 0;
}

Tree* makeLeaf(const char value, const size_t count)
{
    Node* leaf = (Node*)calloc(1, sizeof(Node));
    if (leaf == NULL)
    {
        return NULL;
    }
    leaf->value = value;
    leaf->count = count;
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    if (tree == NULL)
    {
        free(leaf);
        return NULL;
    }
    tree->root = leaf;
    return tree;
}

static void freeNodeWithDescendants(Node* node)
{
    if (node == NULL)
    {
        return;
    }
    freeNodeWithDescendants(node->leftChild);
    freeNodeWithDescendants(node->rightChild);
    free(node);
}

static void freeTree(Tree** const tree)
{
    freeNodeWithDescendants((*tree)->root);
    free(*tree);
    *tree = NULL;
}

Tree* makeTree(Tree** const tree1, Tree** const tree2)
{
    const size_t count = getCount(*tree1) + getCount(*tree2);
    Tree* parentTree = makeLeaf(0, count);
    if (parentTree == NULL)
    {
        return NULL;
    }
    parentTree->root->leftChild = (*tree1)->root;
    parentTree->root->rightChild = (*tree2)->root;
    free(*tree1);
    free(*tree2);
    *tree1 = NULL;
    *tree2 = NULL;
    return parentTree;
}

static void makeCode(const size_t position, bool code[256], const Node* const node, CodeTable* const codeTable)
{
    if (node->leftChild == NULL)
    {
        (codeTable->size)[node->value] = position;
        memcpy_s((codeTable->code)[node->value], 256 * sizeof(bool), code, 256 * sizeof(bool));
        return;
    }
    code[position] = 0;
    makeCode(position + 1, code, node->leftChild, codeTable);
    code[position] = 1;
    makeCode(position + 1, code, node->rightChild, codeTable);
}

CodeTable* createCodeTable(const Tree* const tree)
{
    CodeTable* table = (CodeTable*)calloc(1, sizeof(CodeTable));
    if (table == NULL)
    {
        return NULL;
    }
    bool code[256] = { false };
    makeCode(0, code, tree->root, table);
    return table;
}
