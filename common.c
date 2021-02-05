#include "common.h"

#ifndef NULL
#define NULL ((void *)0)
#endif

char *decToBinary(int n) 
{ 
    int binaryNum[32]; 

    int i = 0; 
    while (n > 0) 
    { 
        binaryNum[i] = n % 2; 
        n = n / 2; 
        i++; 
    } 
  
    char *output = malloc(sizeof(char) * (i + 1));

    for (int j = i - 1, k = 0; j >= 0; j--, k++) 
        output[k] = binaryNum[j] == 1 ? '1' : '0';

    output[i] = '\0';
    return output;
}

char *getCanonicalCode(TNode *node, int isFirstNode, char *lastCode, int lastCodeLength)
{
    char *canonical = NULL;
    if (isFirstNode)
    {
        canonical = malloc(sizeof(char) * (node->frequency + 1));
        sprintf(canonical, "%*c", node->frequency, '0');
    }
    else
    {
        int canonicalIntCode = (int)strtol(lastCode, NULL, 2);
        canonicalIntCode += 0b1;
        canonicalIntCode <<= node->frequency - lastCodeLength;

        char *binaryForm = decToBinary(canonicalIntCode);
        canonical = malloc(sizeof(char) * (strlen(binaryForm) + 1));
        sprintf(canonical, "%s", binaryForm);
        free(binaryForm);
    }
    return canonical;
}

void initializeCanonicalHash(HashTable *canonical, Array *codeLengthArray)
{
    int size = len(codeLengthArray);
    if (size == 0)
        return;

    TNode *firstNode = get(codeLengthArray, 0);
    char *canonicalCode = getCanonicalCode(firstNode, 1, "", 0);
    addCharToStringItem(canonical, firstNode->c, canonicalCode);

    for (int i = 1; i < size; i++)
    {
        TNode *node = get(codeLengthArray, i);
        canonicalCode = getCanonicalCode(node, 0, canonicalCode, get(codeLengthArray, i - 1)->frequency);
        addCharToStringItem(canonical, node->c, canonicalCode);
    }
}