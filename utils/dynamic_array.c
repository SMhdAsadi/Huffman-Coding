#include "dynamic_array.h"
#include <stdio.h>
#include <malloc.h>

Array *newArray(int capacity)
{
    Array *array = malloc(sizeof(Array));
    array->size = 0;
    array->capacity = capacity;
    array->elements = calloc(capacity, sizeof(array->elements[0]));

    for (int i = 0; i < capacity; i++)
        array->elements[i] = NULL;

    return array;
}

void doubleTheCapacity(Array *array)
{
    int newCapacity = array->capacity * 2 * sizeof(array->elements[0]);
    array->elements = realloc(array->elements, newCapacity);
    array->capacity = array->capacity * 2;
}

int len(Array *array)
{
    return array->size;
}

int swap(Array *array, int index1, int index2)
{
    if (index1 < 0 || index1 > len(array) - 1)
        return 0;

    if (index2 < 0 || index2 > len(array) - 1)
        return 0;

    if (index1 == index2)
        return 1;

    TNode *first = get(array, index1);
    TNode *second = get(array, index2);
    set(array, index1, second);
    set(array, index2, first);
    return 1;
}

TNode *get(Array *array, int index)
{
    if (index < array->size && index >= 0)
        return array->elements[index];

    return NULL;
}

void set(Array *array, int index, TNode *node)
{
    if (index < array->size && index >= 0)
        array->elements[index] = node;
}

void addFirst(Array *array, TNode *node)
{
    if (array->size == array->capacity)
        doubleTheCapacity(array);

    array->size++;
    for (int i = array->size - 1; i > 0; i--)
        set(array, i, get(array, i - 1));

    set(array, 0, node);
}

void addLast(Array *array, TNode *node)
{
    if (array->size == array->capacity)
        doubleTheCapacity(array);

    array->size++;
    set(array, array->size - 1, node);
}

void add(Array *array, int index, TNode *node)
{
    int size = len(array);
    if (index >= 0 && index <= size)
    {
        if (index == size)
            addLast(array, node);
        else if (index == 0)
            addFirst(array, node);
        else
        {
            if (size == array->capacity)
                doubleTheCapacity(array);
            
            array->size++;
            for (int i = array->size - 1; i > index; i--)
                set(array, i, get(array, i - 1));
            
            set(array, index, node);
        }
    }
}

int deleteFirst(Array *array)
{
    if (len(array) > 0)
    {
        free(get(array, 0));
        for (int i = 0; i < len(array) - 1; i++)
            set(array, i, get(array, i + 1));

        array->size--;
        return 1;
    }
    return 0;
}

int deleteLast(Array *array)
{
    if (len(array) > 0)
    {
        free(get(array, len(array) - 1));
        array->size--;
        return 1;
    }

    return 0;
}

int delete(Array *array, int index)
{
    if (index < 0 && index >= len(array))
        return 0;

    free(get(array, index));
    for (int i = index; i < len(array) - 1; i++)
        set(array, i, get(array, i + 1));

    array->size--;
    return 1;
}

void deleteElements(Array *array)
{
    int size = len(array);
    for (int i = 0; i < size; i++)
    {
        TNode *node = get(array, i);
        if (node != 0)
            free(node);
    }
}

void deleteArray(Array *array)
{
    deleteElements(array);
    free(array->elements);
    free(array);
}

void printArray(Array *array)
{
    int size = len(array);
    printf("[");
    for (int i = 0; i < size - 1; i++)
    {
        TNode *node = get(array, i);
        if (node == NULL)
            printf("node is null\n");
        printf("(%c, %i), ", node->c, node->frequency);
    }
    
    if (size != 0)
    {
        TNode *node = get(array, len(array) - 1);
        printf("(%c, %i)]\n", node->c, node->frequency);
    }
    else
        printf("]\n");
}