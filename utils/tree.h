#ifndef TREE_H
#define TREE_H

typedef struct _node
{
    char c;
    int frequency;
    struct _node *left, *right;
} TNode;

TNode *newNode(char c, int frequency);
TNode *newEmptyNode();

#endif