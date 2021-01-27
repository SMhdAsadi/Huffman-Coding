#ifndef HEAP_H
#define HEAP_H
#include "dynamic_array.h"

#define DEFAULT_HEAP_SIZE 10

typedef enum _heap_type {MIN_HEAP, MAX_HEAP} HeapType;

typedef struct _heap
{
    Array *array;
    HeapType type;
} Heap;

/*
    creates new heap with specified type
    type: MIN_HEAP, MAX_HEAP
*/
Heap *newHeap(HeapType type);
void insert(Heap *heap, int data);
int deleteRoot(Heap *heap);
void printHeap(Heap *heap);
void deleteHeap(Heap *heap);

#endif