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


// checks whether heap is empty
int isHeapEmpty(Heap *heap);


// inserts the node into the heap
void insert(Heap *heap, TNode *node);


// deletes first item in heap and returns it
TNode *deleteRoot(Heap *heap);


// prints the heap
void printHeap(Heap *heap);


// deletes the whole heap
void deleteHeap(Heap *heap);

#endif