#include "heap.h"
#include <stdio.h>
#include <malloc.h>


Heap *newHeap(HeapType type)
{
    Heap *heap = malloc(sizeof(Heap));
    heap->array = newArray(DEFAULT_HEAP_SIZE);
    heap->type = type;

    return heap;
}

void heapify(Heap *heap, int index)
{
    int size = len(heap->array);

    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    int extremum_index = index;
    if (left < size)
    {
        if (heap->type == MAX_HEAP)
        {
            if (get(heap->array, left)->frequency > get(heap->array, extremum_index)->frequency)
                extremum_index = left;
        }
        else if (get(heap->array, left)->frequency < get(heap->array, extremum_index)->frequency)
            extremum_index = left;
    }

    if (right < size)
    {
        if (heap->type == MAX_HEAP)
        {
            if (get(heap->array, right)->frequency > get(heap->array, extremum_index)->frequency)
                extremum_index = right;
        }
        else if (get(heap->array, right)->frequency < get(heap->array, extremum_index)->frequency)
            extremum_index = right;
    }

    if (extremum_index != index)
    {
        swap(heap->array, extremum_index, index);
        heapify(heap, extremum_index);
    }
}

void insert(Heap *heap, Node *node)
{
    addLast(heap->array, node);

    for (int i = len(heap->array); i >= 0; i--)
    {
        heapify(heap, i);
    }
}

Node *deleteRoot(Heap *heap)
{
    int size = len(heap->array);

    if (size == 0)
        return NULL;

    Node *node = get(heap->array, 0);
    Node *copy = newNode(node->c, node->frequency);
    copy->left = node->left;
    copy->right = node->right;
    
    swap(heap->array, 0, size - 1);
    deleteLast(heap->array);

    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(heap, i);

    return copy;
}

void printHeap(Heap *heap)
{
    int size = len(heap->array);
    printf("Heap ");
    printArray(heap->array);
}

void deleteHeap(Heap *heap)
{
    deleteArray(heap->array);
    free(heap);
}