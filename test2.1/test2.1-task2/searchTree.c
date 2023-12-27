#include "searchTree.h"
#include <stdlib.h>

enum Branch
{
    leftBranch = -1,
    rightBranch = 1
};

typedef struct Node {
    int key;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

struct SearchTree {
    Node* root;
};

SearchTree* createTree(void)
{
    return (SearchTree*)calloc(1, sizeof(SearchTree));
}

static Node* makeNode(const int key)
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL)
    {
        return NULL;
    }
    node->key = key;
    node->leftChild = NULL;
    node->rightChild = NULL;
    return node;
}

static Node* getParent(const SearchTree* const tree, int const key, int* const branch)
{
    Node* parent = NULL;
    Node* currentNode = tree->root;
    while (currentNode != NULL)
    {
        parent = currentNode;
        if (key < currentNode->key)
        {
            currentNode = currentNode->leftChild;
            *branch = leftBranch;
        }
        else
        {
            currentNode = currentNode->rightChild;
            *branch = rightBranch;
        }
    }
    return parent;
}

bool addNode(SearchTree* const tree, const int key)
{
    Node* node = makeNode(key);
    if (node == NULL)
    {
        return true;
    }
    int branch = 0;
    Node* parent = getParent(tree, key, &branch);
    if (parent == NULL)
    {
        tree->root = node;
    }
    else
    {
        if (branch == leftBranch)
        {
            parent->leftChild = node;
        }
        else
        {
            parent->rightChild = node;
        }
    }
    return false;
}

static void freeTreeRecursion(Node* node)
{
    if (node == NULL)
    {
        return;
    }
    if (node->leftChild != NULL)
    {
        freeTreeRecursion(node->leftChild);
    }
    if (node->rightChild != NULL)
    {
        freeTreeRecursion(node->rightChild);
    }
    free(node);
}

void freeTree(SearchTree** const tree)
{
    freeTreeRecursion((*tree)->root);
    free(*tree);
    *tree = NULL;
}

static void rewriteArrayRecursion(const Node* const node, int** const array, 
    size_t* const index, const size_t lengthOfArray)
{
    if (node == NULL || *index >= lengthOfArray)
    {
        return;
    }
    rewriteArrayRecursion(node->leftChild, array, index, lengthOfArray);
    (*array)[*index] = node->key;
    ++*index;
    rewriteArrayRecursion(node->rightChild, array, index, lengthOfArray);
}

void rewriteArray(const SearchTree* const tree, int** const array, const size_t lengthOfArray)
{
    size_t index = 0;
    rewriteArrayRecursion(tree->root, array, &index, lengthOfArray);
}
