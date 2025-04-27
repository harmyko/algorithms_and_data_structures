#include "priorityQueue.h"

// Priority queue using dynamic array of pointers to PQNode

size_t newMemorySize(size_t currentSize)
{
  int k = 8;
  size_t minSize = 16;

  if (currentSize < minSize)
    return minSize;

  size_t newSize = currentSize + k * sqrt(currentSize);

  if (newSize < currentSize) // overflow safety
    return currentSize;

  return newSize;
}

PriorityQueue *newPriorityQueue()
{
  PriorityQueue *pq = (PriorityQueue *)malloc(sizeof(PriorityQueue));
  if (!pq)
    return NULL;

  pq->size = 0;
  pq->isFull = 0;
  pq->capacity = newMemorySize(0);
  pq->nodes = (PQNode **)malloc(pq->capacity * sizeof(PQNode *));

  if (!pq->nodes)
  {
    free(pq);
    return NULL;
  }

  return pq;
}

char expandPriorityQueue(PriorityQueue *pq)
{
  size_t newSize = newMemorySize(pq->capacity);

  PQNode **newNodes = (PQNode **)realloc(pq->nodes, newSize * sizeof(PQNode *));
  if (!newNodes)
  {
    pq->isFull = 1;
    return 0;
  }

  pq->nodes = newNodes;
  pq->capacity = newSize;
  return 1;
}

size_t getQueueSize(PriorityQueue *pq)
{
  return pq->size;
}

char isEmpty(PriorityQueue *pq)
{
  return pq->size == 0;
}

char isFull(PriorityQueue *pq)
{
  return pq->isFull;
}

char enqueue(PriorityQueue *pq, dn_type data, size_t priority)
{
  if (pq->isFull)
  {
    return 0;
  }

  if (pq->size == pq->capacity)
  {
    if (!expandPriorityQueue(pq))
      return 0;
  }

  PQNode *newNode = (PQNode *)malloc(sizeof(PQNode));
  if (!newNode)
  {
    return 0;
  }

  newNode->data = data;
  newNode->priority = priority;

  size_t i = pq->size;
  while (i > 0 && pq->nodes[i - 1]->priority > priority)
  {
    pq->nodes[i] = pq->nodes[i - 1];
    i--;
  }
  pq->nodes[i] = newNode;
  pq->size++;

  return 1;
}

char dequeue(PriorityQueue *pq)
{
  if (isEmpty(pq))
  {
    return 0;
  }

  size_t lastNodeIndex = pq->size - 1;

  if (pq->nodes[lastNodeIndex]->data)
  {
    free(pq->nodes[lastNodeIndex]->data);
  }
  free(pq->nodes[lastNodeIndex]);

  pq->size--;
  pq->isFull = 0;

  return 1;
}

dn_type peek(PriorityQueue *pq)
{
  if (isEmpty(pq))
  {
    return NULL;
  }

  return pq->nodes[pq->size - 1]->data;
}

dn_type pop(PriorityQueue *pq)
{
  dn_type data = peek(pq);
  dequeue(pq);
  return data;
}

void freePriorityQueue(PriorityQueue *pq)
{
  for (size_t i = 0; i < pq->size; i++)
  {
    if (pq->nodes[i]->data)
    {
      free(pq->nodes[i]->data);
    }
    free(pq->nodes[i]);
  }

  free(pq->nodes);
  free(pq);
}

dn_type peekAt(PriorityQueue *pq, size_t index)
{
    if (index >= pq->size)
        return NULL;
    return pq->nodes[index]->data;
}

dn_type removeAt(PriorityQueue *pq, size_t index)
{
    if (index >= pq->size)
        return NULL;

    dn_type data = pq->nodes[index]->data;
    free(pq->nodes[index]);

    for (size_t i = index; i < pq->size - 1; i++)
    {
        pq->nodes[i] = pq->nodes[i + 1];
    }

    pq->size--;
    pq->isFull = 0;

    return data;
}


