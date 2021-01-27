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
}

int len(Array *array)
{
    return array->size;
}

Node *get(Array *array, int index)
{
    if (index < array->size && index >= 0)
        return array->elements[index];

    return NULL;
}

void set(Array *array, int index, Node *node)
{
    if (index < array->size && index >= 0)
        array->elements[index] = node;
}

void addFirst(Array *array, Node *node)
{
    if (array->size == array->capacity)
        doubleTheCapacity(array);

    array->size++;
    for (int i = array->size - 1; i > 0; i--)
        set(array, i, get(array, i - 1));

    set(array, 0, node);
}

void addLast(Array *array, Node *node)
{
    if (array->size == array->capacity)
        doubleTheCapacity(array);

    array->size++;
    set(array, array->size - 1, node);
}

void add(Array *array, int index, Node *node)
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
    for (int i = 0; i < len(array); i++)
    {
        free(get(array, i));
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
        Node *node = get(array, i);
        if (node == NULL)
            printf("node is null\n");
        printf("(%c, %i), ", node->c, node->frequency);
    }
    
    if (size != 0)
    {
        Node *node = get(array, len(array) - 1);
        printf("(%c, %i)]\n", node->c, node->frequency);
    }
    else
        printf("]\n");
}