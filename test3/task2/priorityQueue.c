#include "priorityQueue.h"
#include <stdlib.h>

typedef struct {
    unsigned int value;
    int key;
    struct QueueNode* next;
} QueueNode;

struct PriorityQueue {
    QueueNode* head;
    QueueNode* back;
    size_t size;
};

PriorityQueue* createQueue(void)
{
    return (PriorityQueue*)calloc(1, sizeof(PriorityQueue));
}

static bool isEmpty(const PriorityQueue* const queue)
{
    return queue->head == NULL;
}

static QueueNode* createNode(const unsigned int value, const int key)
{
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    if (node == NULL)
    {
        return NULL;
    }
    node->value = value;
    node->key = key;
    node->next = NULL;
    return node;
}

bool enqueue(PriorityQueue* const queue, const unsigned int value, const int key)
{
    QueueNode* newNode = createNode(value, key);
    if (newNode == NULL)
    {
        return true;
    }
    QueueNode* previous = NULL;
    QueueNode* current = queue->head;
    for (; current != NULL && current->key >= newNode->key; current = current->next)
    {
        previous = current;
    }

    if (previous != NULL)
    {
        previous->next = newNode;
    }
    else
    {
        queue->head = newNode;
    }
    if (current != NULL)
    {
        newNode->next = current;
    }
    else
    {
        queue->back = newNode;
    }
    ++queue->size;
    return false;
}

unsigned int dequeue(PriorityQueue* const queue)
{
    if (isEmpty(queue))
    {
        return -1;
    }
    QueueNode* node = queue->head;
    queue->head = node->next;
    unsigned int value = node->value;
    free(node);
    --queue->size;
    return value;
}

void freeQueue(PriorityQueue** const queue)
{
    while ((*queue)->size > 0)
    {
        dequeue(*queue);
    }
    free(*queue);
    *queue = NULL;
}
