#ifndef LINKEDLIST_H
#define LINKEDLIST_H
/*
    custom linkedlist used for hashtable
    this linkedlist stores nodes that have character and (frequency or code) in them
*/

typedef union
{
    int frequency;
    char *code;
} Value;


/*
    a structure uses as linked list's node
    contains a character and either frequency of that character or code of that character
    this type is specified using a member called valueType
        0: int
        1: char *
*/
typedef struct _node
{
    char character;
    Value value;
    int valueType;
    struct _node *next;
} Node;


typedef struct _list
{
    Node *head;
} List;


// creates and returns a new empty list
List *newList();


// checks whether list is empty
int isListEmpty(List *list);


/*
    adds character to the list
    if it exists, adds one to the frequency
*/
void addIntNode(List *list, char character);


// adds character with code to the list
void addStringNode(List *list, char character, char *code);


// returns the frequency of node
int getFrequency(List *list, char character);


// returns the code of the node
char *getCode(List *list, char character);


// deletes the node with specified character
int deleteNode(List *list, char character);


// deletes whole list along with all nodes in it
void deleteList(List *list);


// prints the list
void printList(List *list);

#endif