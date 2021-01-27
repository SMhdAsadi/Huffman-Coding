#include "tree.h"
#include <malloc.h>

Node *newNode(char c, int frequency)
{
    Node *node = malloc(sizeof(Node));
    node->c = c;
    node->frequency = frequency;
    node->left = node->right = NULL;

    return node;
}

Node *newEmptyNode()
{
    Node *node = calloc(1, sizeof(Node));
    node->left = node->right = NULL;

    return node;
}
