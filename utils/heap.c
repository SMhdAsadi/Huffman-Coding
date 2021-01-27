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
    if (left < size && (
                        heap->type == MAX_HEAP && get(heap->array, left) > get(heap->array, extremum_index) ||
                        heap->type == MIN_HEAP && get(heap->array, left) < get(heap->array, extremum_index)
                        )
    )
    {
        extremum_index = left;
    }

    if (right < size && (
                        heap->type == MAX_HEAP && get(heap->array, right) > get(heap->array, extremum_index) ||
                        heap->type == MIN_HEAP && get(heap->array, right) < get(heap->array, extremum_index)
                        )
    )
    {
        extremum_index = right;
    }

    if (extremum_index != index)
    {
        swap(heap->array, extremum_index, index);
        heapify(heap, extremum_index);
    }
}

void insert(Heap *heap, int data)
{
    addLast(heap->array, data);

    for (int i = len(heap->array); i >= 0; i--)
    {
        heapify(heap, i);
    }
}

int deleteRoot(Heap *heap)
{
    int size = len(heap->array);

    if (size == 0)
        return -1;

    int data = get(heap->array, 0);
    swap(heap->array, 0, size - 1);
    deleteLast(heap->array);

    for (int i = size / 2 - 1; i >= 0; i--)
    {
        heapify(heap, i);
    }

    return data;
}

void printHeap(Heap *heap)
{
    int size = len(heap->array);
    printf("Heap [");
    for (int i = 0; i < size - 1; i++)
    {
        printf("%i, ", get(heap->array, i));
    }

    if (size != 0)
    {
        printf("%i]\n", get(heap->array, size - 1));
    }
    else
    {
        printf("]\n");
    }   
}

void deleteHeap(Heap *heap)
{
    deleteArray(heap->array);
    free(heap);
}