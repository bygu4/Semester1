#pragma once

#include <stdbool.h>

typedef struct PriorityQueue PriorityQueue;

PriorityQueue* createQueue(void);

void freeQueue(PriorityQueue** const queue);

bool enqueue(PriorityQueue* const queue, const unsigned int value, const int key);

unsigned int dequeue(PriorityQueue* const queue);
