#ifndef TREE_H
#define TREE_H

typedef struct _node
{
    char c;
    int frequency;
    struct _node *left, *right;
} Node;

Node *newNode(char c, int frequency);
Node *newEmptyNode();

#endif