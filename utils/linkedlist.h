/*
    custom linkedlist used for hashtable
    this linkedlist stores nodes that have name and age in them
*/

typedef struct _node
{
    char *key;
    int value;
    struct _node *next;
} Node;

typedef struct _list
{
    Node *head;
} List;


List *newList();
int isEmpty(List *list);
void addNode(List *list, char *key, int value);
int deleteNode(List *list, char *key);
void deleteList(List *list);
void printList(List *list);
