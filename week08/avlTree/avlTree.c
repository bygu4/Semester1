#include "avlTree.h"
#include "str.h"
#include <stdlib.h>

typedef struct {
    char* key;
    char* data;
    int balance;
    struct Node* leftChild;
    struct Node* rightChild;
} Node;

struct AvlTree {
    Node* root;
};

AvlTree* createTree(void)
{
    return (AvlTree*)calloc(1, sizeof(AvlTree));
}

static Node* rotateLeft(Node* const current)
{
    Node* pivot = current->rightChild;
    current->rightChild = pivot->leftChild;
    pivot->leftChild = current;
    current->balance = pivot->balance == 0 ? 1 : 0;
    pivot->balance = pivot->balance == 0 ? -1 : 0;
    return pivot;
}

static Node* rotateRight(Node* const current)
{
    Node* pivot = current->leftChild;
    current->leftChild = pivot->rightChild;
    pivot->rightChild = current;
    current->balance = pivot->balance == 0 ? -1 : 0;
    pivot->balance = pivot->balance == 0 ? 1 : 0;
    return pivot;
}

static Node* bigRotate(Node* const left, Node* const bottom, Node* const right)
{
    left->rightChild = bottom->leftChild;
    right->leftChild = bottom->rightChild;
    bottom->leftChild = left;
    bottom->rightChild = right;
    bottom->balance = 0;
    return bottom;
}

static Node* bigRotateLeft(Node* const current)
{
    Node* pivot = current->rightChild;
    Node* bottom = pivot->leftChild;
    switch (bottom->balance)
    {
    case 0:
        current->balance = 0;
        pivot->balance = 0;
        break;
    case -1:
        current->balance = 1;
        pivot->balance = 0;
        break;
    case 1:
        current->balance = 0;
        pivot->balance = -1;
        break;
    }
    return bigRotate(current, bottom, pivot);
}

static Node* bigRotateRight(Node* const current)
{
    Node* pivot = current->leftChild;
    Node* bottom = pivot->rightChild;
    switch (bottom->balance)
    {
    case 0:
        current->balance = 0;
        pivot->balance = 0;
        break;
    case -1:
        current->balance = 0;
        pivot->balance = 1;
        break;
    case 1:
        current->balance = -1;
        pivot->balance = 0;
        break;
    }
    return bigRotate(pivot, bottom, current);
}

static int balance(const Node* const node)
{
    return node != NULL ? node->balance : 0;
}

static Node* balanceTree(Node* const node)
{
    if (balance(node) == 2)
    {
        if (balance(node->rightChild) >= 0)
        {
            return rotateLeft(node);
        }
        return bigRotateLeft(node);
    }
    else if (balance(node) == -2)
    {
        if (balance(node->leftChild) <= 0)
        {
            return rotateRight(node);
        }
        return bigRotateRight(node);
    }
    return node;
}

static void freeNode(Node** const node)
{
    free((*node)->key);
    free((*node)->data);
    free(*node);
    *node = NULL;
}

static Node* makeNode(const char* const key, const char* const data)
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL)
    {
        return NULL;
    }
    node->leftChild = NULL;
    node->rightChild = NULL;
    node->balance = 0;
    node->key = copyString(key);
    node->data = copyString(data);
    if (node->key == NULL || node->data == NULL)
    {
        freeNode(&node);
        return NULL;
    }
    return node;
}

static Node* insert(Node* node, const char* const key, const char* const data, bool* const changeBalance)
{
    if (node == NULL)
    {
        *changeBalance = true;
        return makeNode(key, data);
    }
    const int comparison = compareStrings(node->key, key);
    if (comparison == -1)
    {
        Node* child = insert(node->leftChild, key, data, changeBalance);
        if (child == NULL)
        {
            return NULL;
        }
        node->leftChild = child;
        if (*changeBalance)
        {
            --node->balance;
        }
    }
    else if (comparison == 1)
    {
        Node* child = insert(node->rightChild, key, data, changeBalance); 
        if (child == NULL)
        {
            return NULL;
        }
        node->rightChild = child;
        if (*changeBalance)
        {
            ++node->balance;
        }
    }
    else
    {
        free(node->data);
        node->data = copyString(data);
        if (node->data == NULL)
        {
            return NULL;
        }
    }
    node = balanceTree(node);
    if (node->balance == 0)
    {
        *changeBalance = false;
    }
    return node;
}

bool addNode(AvlTree* const tree, const char* key, const char* const data)
{
    bool changeBalance = false;
    Node* newRoot = insert(tree->root, key, data, &changeBalance);
    if (newRoot == NULL)
    {
        return true;
    }
    tree->root = newRoot;
    return false;
}

static Node* getNode(const Node* const node, const char* const key)
{
    if (node == NULL)
    {
        return NULL;
    }
    const int comparison = compareStrings(node->key, key);
    if (comparison == 0)
    {
        return node;
    }
    return comparison < 0 ? getNode(node->leftChild, key) : getNode(node->rightChild, key);
}

char* getData(const AvlTree* const tree, const char* const key)
{
    Node* node = getNode(tree->root, key);
    return node != NULL ? node->data : NULL;
}

bool findKey(const AvlTree* const tree, const char* const key)
{
    Node* node = getNode(tree->root, key);
    return node != NULL;
}

static Node* removeClosestChild(Node* node, Node** const closestChild, bool* const changeBalance)
{
    if (node->leftChild == NULL)
    {
        *closestChild = node;
        *changeBalance = true;
        return node->rightChild;
    }
    node->leftChild = removeClosestChild(node->leftChild, closestChild, changeBalance);
    if (*changeBalance)
    {
        ++node->balance;
    }
    node = balanceTree(node);
    if (node->balance != 0)
    {
        *changeBalance = false;
    }
    return node;
}

static Node* deletion(Node* node, bool* const changeBalance)
{
    if (node->leftChild == NULL || node->rightChild == NULL)
    {
        *changeBalance = true;
    }
    Node* closestChild = node->leftChild;
    if (node->rightChild == NULL)
    {
        freeNode(&node);
        return closestChild;
    }
    Node* child = removeClosestChild(node->rightChild, &closestChild, changeBalance);
    closestChild->rightChild = child;
    closestChild->leftChild = node->leftChild;
    closestChild->balance = node->balance;
    if (*changeBalance)
    {
        --closestChild->balance;
    }
    freeNode(&node);
    return closestChild;
}

static Node* deleteNodeRecursion(Node* node, const char* const key, bool* const deleted, bool* const changeBalance)
{
    if (node == NULL)
    {
        return NULL;
    }
    const int comparison = compareStrings(node->key, key);
    if (comparison == -1)
    {
        node->leftChild = deleteNodeRecursion(node->leftChild, key, deleted, changeBalance);
        if (*changeBalance)
        {
            ++node->balance;
        }
    }
    else if (comparison == 1)
    {
        node->rightChild = deleteNodeRecursion(node->rightChild, key, deleted, changeBalance);
        if (*changeBalance)
        {
            --node->balance;
        }
    }
    else
    {
        *deleted = true;
        node = deletion(node, changeBalance);
    }
    node = balanceTree(node);
    if (balance(node) != 0)
    {
        *changeBalance = false;
    }
    return node;
}

bool deleteNode(AvlTree* const tree, const char* const key)
{
    bool deleted = false;
    bool changeBalance = false;
    tree->root = deleteNodeRecursion(tree->root, key, &deleted, &changeBalance);
    return deleted;
}

static void freeTreeRecursion(Node* node)
{
    if (node == NULL)
    {
        return;
    }
    freeTreeRecursion(node->leftChild);
    freeTreeRecursion(node->rightChild);
    freeNode(&node);
}

void freeTree(AvlTree** const tree)
{
    freeTreeRecursion((*tree)->root);
    free(*tree);
    *tree = NULL;
}
