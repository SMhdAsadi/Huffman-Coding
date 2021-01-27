#ifndef HEAP_H
#define HEAP_H
#include "dynamic_array.h"

#define DEFAULT_HEAP_SIZE 10

typedef enum {MIN_HEAP, MAX_HEAP} HeapType;

typedef struct
{
    Array *array;
    HeapType type;
} Heap;

/*
    creates new heap with specified type
    type: MIN_HEAP, MAX_HEAP
*/
Heap *newHeap(HeapType type);
void insert(Heap *heap, Node *node);
Node *deleteRoot(Heap *heap);
void printHeap(Heap *heap);
void deleteHeap(Heap *heap);

#endif