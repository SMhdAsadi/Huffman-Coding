#ifndef COMMON_H
#define COMMON_H

#include "utils/hashtable.h"
#include "utils/dynamic_array.h"
#include "utils/huffman_tree.h"

void initializeCanonicalHash(HashTable *canonical, Array *codeLengthArray);
void appendZeroToEnd(char *string, int amount);

#endif