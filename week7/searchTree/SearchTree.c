#include "SearchTree.h"
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
    unsigned int leftDifference = abs(closestLeft->key - node->key);
    unsigned int rightDifference = abs(closestRight->key - node->key);
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

typedef struct {
    Node* value;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* head;
    QueueNode* back;
} Queue;

static Queue* createQueue(void)
{
    return (Queue*)calloc(1, sizeof(Queue));
}

static Node* head(const Queue* const queue)
{
    if (queue->head == NULL)
    {
        return NULL;
    }
    return queue->head->value;
}

static bool enqueue(Queue* const queue, Node* value)
{
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    if (node == NULL)
    {
        return true;
    }
    node->value = value;
    node->next = NULL;
    if (queue->head == NULL)
    {
        queue->head = node;
    }
    else
    {
        queue->back->next = node;
    }
    queue->back = node;
    return false;
}

static void dequeue(Queue* const queue)
{
    if (queue->head == NULL)
    {
        return;
    }
    QueueNode* node = queue->head;
    queue->head = queue->head->next;
    if (queue->head == NULL)
    {
        queue->back = NULL;
    }
    free(node);
}

static void freeQueue(Queue** const queue)
{
    while ((*queue)->head != NULL)
    {
        dequeue(*queue);
    }
    free(*queue);
    *queue = NULL;
}

bool checkTreeByPreorder(const SearchTree* const tree, const int* const keys, const size_t numberOfKeys)
{
    Queue* queue = createQueue();
    if (queue == NULL)
    {
        return false;
    }
    bool errorOccured = false;
    Node* currentNode = tree->root;
    for (size_t i = 0; i < numberOfKeys; ++i)
    {
        if (currentNode == NULL || currentNode->key != keys[i])
        {
            freeQueue(&queue);
            return false;
        }
        if (currentNode->leftChild != NULL)
        {
            errorOccured = enqueue(queue, currentNode->leftChild);
            if (errorOccured)
            {
                freeQueue(&queue);
                return false;
            }
        }
        if (currentNode->rightChild != NULL)
        {
            errorOccured = enqueue(queue, currentNode->rightChild);
            if (errorOccured)
            {
                freeQueue(&queue);
                return false;
            }
        }
        currentNode = head(queue);
        dequeue(queue);
    }
    bool correct = currentNode == NULL;
    freeQueue(&queue);
    return correct;
}
