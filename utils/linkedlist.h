#ifndef LINKEDLIST_H
#define LINKEDLIST_H
/*
    custom linkedlist used for hashtable
    this linkedlist stores nodes that have character and frequency in them
*/


typedef struct _node
{
    char character;
    int frequency;
    struct _node *next;
} Node;


typedef struct _list
{
    Node *head;
} List;


// creates and returns a new empty list
List *newList();


// checks whether list is empty
int isEmpty(List *list);


/*
    adds character to the list
    if it exists, adds one to the frequency
*/
void addNode(List *list, char character);


// deletes the node with specified character
int deleteNode(List *list, char character);


// deletes whole list along with all nodes in it
void deleteList(List *list);


// prints the list
void printList(List *list);

#endif