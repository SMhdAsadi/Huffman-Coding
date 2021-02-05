#ifndef COMMON_H
#define COMMON_H

#include "utils/hashtable.h"
#include "utils/dynamic_array.h"
#include "utils/huffman_tree.h"

void initializeCanonicalHash(HashTable *canonical, Array *codeLengthArray);
char *getCanonicalCode(TNode *node, int isFirstNode, char *lastCode, int lastCodeLength);
char *decToBinary(int n);

#endif