#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

typedef struct _tnode
{
    char c;
    int frequency;
    struct _tnode *left, *right;
} TNode;

TNode *newTNode(char c, int frequency);
TNode *newEmptyNode();
TNode *addHuffmanNode(TNode *a, TNode *b);
void deleteHuffmanTree(TNode *root);
void printHuffmanTree(TNode *root);

#endif