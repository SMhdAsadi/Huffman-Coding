#include "tree.h"
#include <malloc.h>

TNode *newNode(char c, int frequency)
{
    TNode *node = malloc(sizeof(TNode));
    node->c = c;
    node->frequency = frequency;
    node->left = node->right = NULL;

    return node;
}

TNode *newEmptyNode()
{
    TNode *node = calloc(1, sizeof(TNode));
    node->left = node->right = NULL;

    return node;
}
