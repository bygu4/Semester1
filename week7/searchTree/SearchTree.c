#include "searchTree.h"
#include "str.h"
#include <stdlib.h>

typedef struct {
    char* data;
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

static Node* getNode(const SearchTree* const tree, int const key, Node** const parent)
{
    Node* currentNode = tree->root;
    while (currentNode != NULL && currentNode->key != key)
    {
        if (parent != NULL)
        {
            *parent = currentNode;
        }
        if (key < currentNode->key)
        {
            currentNode = currentNode->leftChild;
        }
        else
        {
            currentNode = currentNode->rightChild;
        }
    }
    return currentNode;
}

bool addNode(SearchTree* const tree, const int key, const char* const data)
{
    Node* parent = NULL;
    Node* node = getNode(tree, key, &parent);
    if (node == NULL)
    {
        node = (Node*)malloc(sizeof(Node));
        if (node == NULL)
        {
            return true;
        }
        node->key = key;
        node->leftChild = NULL;
        node->rightChild = NULL;
        if (parent == NULL)
        {
            tree->root = node;
        }
        else
        {
            if (node->key < parent->key)
            {
                parent->leftChild = node;
            }
            else
            {
                parent->rightChild = node;
            }
        }
    }
    else
    {
        free(node->data);
    }
    node->data = copyString(data);
    if (node->data == NULL)
    {
        return true;
    }
    return false;
}

char* getData(const SearchTree* const tree, const int key)
{
    Node* node = getNode(tree, key, NULL);
    if (node == NULL)
    {
        return NULL;
    }
    return node->data;
}

bool findKey(const SearchTree* const tree, const int key)
{
    Node* node = getNode(tree, key, NULL);
    return node != NULL;
}

static Node* getLeftMostChild(const Node* const node, Node** const parent)
{
    if (node == NULL)
    {
        return NULL;
    }
    Node* currentNode = node;
    while (currentNode->leftChild != NULL)
    {
        *parent = currentNode;
        currentNode = currentNode->leftChild;
    }
    return currentNode;
}

static Node* getRightMostChild(const Node* const node, Node** const parent)
{
    if (node == NULL)
    {
        return NULL;
    }
    Node* currentNode = node;
    while (currentNode->rightChild != NULL)
    {
        *parent = currentNode;
        currentNode = currentNode->rightChild;
    }
    return currentNode;
}

static Node* getClosestChild(const Node* const node, Node** const parent)
{
    Node* leftParent = NULL;
    Node* closestLeft = getRightMostChild(node->leftChild, &leftParent);
    Node* rightParent = NULL;
    Node* closestRight = getLeftMostChild(node->rightChild, &rightParent);
    if (closestLeft == NULL && closestRight == NULL)
    {
        return NULL;
    }
    if (closestLeft == NULL)
    {
        *parent = rightParent;
        return closestRight;
    }
    if (closestRight == NULL)
    {
        *parent = leftParent;
        return closestLeft;
    }
    const unsigned int leftDifference = abs(closestLeft->key - node->key);
    const unsigned int rightDifference = abs(closestRight->key - node->key);
    if (leftDifference < rightDifference)
    {
        *parent = leftParent;
        return closestLeft;
    }
    else
    {
        *parent = rightParent;
        return closestRight;
    }
}

static void freeNode(Node** const node)
{
    free((*node)->data);
    free(*node);
    *node = NULL;
}

bool deleteNode(SearchTree* const tree, int const key)
{
    Node* parent = NULL;
    Node* node = getNode(tree, key, &parent);
    if (node == NULL)
    {
        return false;
    }
    Node* closestChildParent = NULL;
    Node* closestChild = getClosestChild(node, &closestChildParent);
    if (closestChild != NULL)
    {
        if (closestChild == node->leftChild || closestChild == node->rightChild)
        {
            if (closestChild->key < node->key)
            {
                closestChild->rightChild = node->rightChild;
            }
            else
            {
                closestChild->leftChild = node->leftChild;
            }
        }
        else
        {
            if (closestChild->key < node->key)
            {
                closestChildParent->rightChild = closestChild->leftChild;
            }
            else
            {
                closestChildParent->leftChild = closestChild->rightChild;
            }
            closestChild->leftChild = node->leftChild;
            closestChild->rightChild = node->rightChild;
        }
    }
    if (parent == NULL)
    {
        tree->root = closestChild;
    }
    else
    {
        if (node->key < parent->key)
        {
            parent->leftChild = closestChild;
        }
        else
        {
            parent->rightChild = closestChild;
        }
    }
    freeNode(&node);
    return true;
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
    freeNode(&node);
}

void freeTree(SearchTree** const tree)
{
    freeTreeRecursion((*tree)->root);
    free(*tree);
    *tree = NULL;
}
