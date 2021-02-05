#include "huffman_tree.h"
#include <malloc.h>
#include <stdio.h>

TNode *newTNode(char c, int frequency)
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

TNode *addHuffmanNode(TNode *a, TNode *b)
{
    TNode *internalNode = newEmptyNode();
    internalNode->frequency = a->frequency + b->frequency;
    internalNode->left = a;
    internalNode->right = b;

    return internalNode;
}

void deleteHuffmanTree(TNode *root)
{
    if (root != NULL)
    {
        deleteHuffmanTree(root->left);
        deleteHuffmanTree(root->right);
        free(root);
    }
}

void printHuffmanTree(TNode *root)
{
    if (root != NULL)
    {
        printHuffmanTree(root->left);
        printf("(%c, %i), ", root->c, root->frequency);
        printHuffmanTree(root->right);
    }
}