#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#include "tree.h"


/*
    a dynamic array that stores node in it
*/
typedef struct _dynamic_array
{
    Node **elements;
    int size;
    int capacity;
} Array;


// creates a new dynamic array with initial capacity
Array *newArray(int capacity);


// returns a pointer to node from that index in dynamic array
Node *get(Array *array, int index);


/*
    puts the node in that index in the array
    caution: if there is a node in that index already, free it manually first
*/
void set(Array *array, int index, Node *node);


// adds node to start of the array
void addFirst(Array *array, Node *node);


// adds the node to end of the arra
void addLast(Array *array, Node *node);


/*
    adds the node to that index of the array
    if index is not valid, does nothing
    accepts index from 0 to array size - 1
*/
void add(Array *array, int index, Node *node);


/*
    deletes the first item of the array
    returns 0 if there was an Error
    returns 1 if deleted successfully
*/
int deleteFirst(Array *array);


/*
    deletes the last item of the array
    returns 0 if there was an Error
    returns 1 if deleted successfully
*/
int deleteLast(Array *array);


/*
    deletes the item at that index of the array
    returns 0 if there was an Error
    returns 1 if deleted successfully
*/
int delete(Array *array, int index);


// returns the size of the array
int len(Array *array);


/*
    swaps the indexes in the array
    returns 1 if successful otherwise 0
*/
int swap(Array *array, int index1, int index2);


// prints the array
void printArray(Array *array);


// delets the entire array along with all nodes
void deleteArray(Array *array);

#endif