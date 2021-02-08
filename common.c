#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void increment(char *binaryString)
{
    int size = strlen(binaryString);
    for (int i = size - 1; i >= 0; i--)
    {
        char c = binaryString[i];
        if (c == '0')
        {
            binaryString[i] = '1';
            return;
        }

        if (c == '1')
            binaryString[i] = '0';
    }

    binaryString = realloc(binaryString, sizeof(char) * (size + 2));
    size++;

    binaryString[0] = '1';
    for (int i = 1; i < size; i++)
        binaryString[i] = '0';
    binaryString[size] = '\0';
}

void appendZeroToEnd(char *string, int amount)
{
    if (amount <= 0)
        return;

    int size = strlen(string);
    string = realloc(string, size + amount + 1);
    size += amount;

    string[size] = '\0';
    for (int i = size - 1; i >= size - amount; i--)
        string[i] = '0';
}

char *getCanonicalCode(TNode *node, int isFirstNode, char *lastCode, int lastCodeLength)
{
    char *canonical = NULL;
    if (isFirstNode)
    {
        canonical = malloc(sizeof(char) * (node->frequency + 1));
        sprintf(canonical, "%0*i", node->frequency, 0);
    }
    else
    {
        canonical = malloc(lastCodeLength + 1);
        strcpy(canonical, lastCode);
        increment(canonical);
        appendZeroToEnd(canonical, node->frequency - lastCodeLength);
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