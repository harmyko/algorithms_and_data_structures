#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Changed the original work to make it function with void type pointers.
typedef void *dn_type;

typedef struct
{
  dn_type data;
  int priority;
} PQNode;

typedef struct
{
  PQNode **nodes;
  size_t size;
  size_t capacity;
  char isFull;
} PriorityQueue;

size_t newMemorySize(size_t currentSize);
PriorityQueue *newPriorityQueue();
char expandPriorityQueue(PriorityQueue *pq);
size_t getQueueSize(PriorityQueue *pq);
char isEmpty(PriorityQueue *pq);
char isFull(PriorityQueue *pq);
char enqueue(PriorityQueue *pq, dn_type data, size_t priority);
char dequeue(PriorityQueue *pq);
dn_type peek(PriorityQueue *pq);
dn_type pop(PriorityQueue *pq);
void freePriorityQueue(PriorityQueue *pq);

#endif
