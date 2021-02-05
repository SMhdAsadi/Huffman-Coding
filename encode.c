#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/hashtable.h"
#include "utils/heap.h"
#include "common.h"

void initializeFrequencyHashTable(HashTable *hashTable, char *string);
void initializeHeap(Heap *heap, HashTable *hashTable);
TNode *initializeHuffmanTree(TNode *tree, Heap *heap);
void initializeCodeHashTable(HashTable *hashTable, TNode *node, char *codeTillNow);
void initializeCodeLengthArray(Array *codeLengthArray, HashTable *codeHash);
void initializeCanonicalHash(HashTable *canonical, Array *codeLengthArray);
void writeHeaderToFile(Array *codeLength);
void writeCodeToFile(char *string, HashTable *canonicalHash);

int main()
{
    HashTable *frequencyHash = newHashTable();
    HashTable *codeHash = newHashTable();
    Heap *heap = newHeap(MIN_HEAP);
    TNode *huffmanTree = NULL;
    Array *codeLengthArray = newArray(10);
    HashTable *canonicalCodeHash = newHashTable();
    char *string = "aaaaaaaaaabcccccccccccccccddddddd";

    initializeFrequencyHashTable(frequencyHash, string);
    initializeHeap(heap, frequencyHash);
    huffmanTree = initializeHuffmanTree(huffmanTree, heap);

    char *emptyString = malloc(sizeof(char));
    strcpy(emptyString, "");
    initializeCodeHashTable(codeHash, huffmanTree, emptyString);

    initializeCodeLengthArray(codeLengthArray, codeHash);
    initializeCanonicalHash(canonicalCodeHash, codeLengthArray);

    printHashTable(canonicalCodeHash);
    writeHeaderToFile(codeLengthArray);
    writeCodeToFile(string, canonicalCodeHash);


    deleteHashTable(frequencyHash);
    deleteHeap(heap);
    deleteHuffmanTree(huffmanTree);
    deleteHashTable(codeHash);
    deleteArray(codeLengthArray);
    deleteHashTable(canonicalCodeHash);

    return 0;
}

void initializeFrequencyHashTable(HashTable *hashTable, char *string)
{
    for (int i = 0; *(string + i); i++)
        addCharToIntItem(hashTable, *(string + i));
}

void initializeHeap(Heap *heap, HashTable *hashTable)
{
    List *currentList = NULL;
    Node *currentNode = NULL;
    for (int i = 0; i < HASH_ARRAY_SIZE; i++)
    {
        currentList = hashTable->array[i];
        currentNode = currentList->head;

        while (currentNode != NULL)
        {
            insert(heap, newTNode(currentNode->character, currentNode->value.frequency));
            currentNode = currentNode->next;
        }
    }
}

TNode *initializeHuffmanTree(TNode *tree, Heap *heap)
{
    TNode *a = NULL, *b = NULL;
    while (len(heap->array) > 1)
    {
        a = deleteRoot(heap);
        b = deleteRoot(heap);
        tree = addHuffmanNode(a, b);

        insert(heap, tree);
    }

    return tree;
}

char *append(char *first, char *second)
{
    char *third = malloc(strlen(first) + strlen(second) + 1);
    strcpy(third, first);
    strcat(third, second);

    return third;    
}

void initializeCodeHashTable(HashTable *hashTable, TNode *node, char *codeTillNow)
{
    if (node != NULL)
    {
        if (node->left == NULL && node->right == NULL)
        {
            addCharToStringItem(hashTable, node->c, codeTillNow);
            return;
        }

        char *before = codeTillNow;
        initializeCodeHashTable(hashTable, node->left, append(codeTillNow, "0"));
        initializeCodeHashTable(hashTable, node->right, append(codeTillNow, "1"));
        free(before);
    }
}

void sort(Array *codeLengthArray)
{
    const int size = len(codeLengthArray);
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            TNode *first = get(codeLengthArray, i);
            TNode *second = get(codeLengthArray, j);

            if (first->frequency > second->frequency || (first->frequency == second->frequency && first->c > second->c))
                swap(codeLengthArray, i, j);
        }
    }
}

void initializeCodeLengthArray(Array *codeLengthArray, HashTable *codeHash)
{
    for (int i = 0; i < HASH_ARRAY_SIZE; i++)
    {
        List *currentList = codeHash->array[i];
        Node *currentNode = currentList->head;

        while (currentNode != NULL)
        {
            addLast(codeLengthArray, newTNode(currentNode->character, (int)strlen(currentNode->value.code)));
            currentNode = currentNode->next;
        }
    }

    sort(codeLengthArray);
}

void writeHeaderToFile(Array *codeLength)
{
    FILE *file = fopen("save.dat", "wb");

    int numberOfCodes = len(codeLength);
    fwrite(&numberOfCodes, sizeof(int), 1, file);

    for (int i = 0; i < numberOfCodes; i++)
    {
        TNode *node = get(codeLength, i);
        fwrite(&node->c, sizeof(char), 1, file);
        fwrite(&node->frequency, sizeof(int), 1, file);
    }

    fclose(file);
}

void writeCodeToFile(char *string, HashTable *canonicalHash)
{
    FILE *file = fopen("save.dat", "ab");

    for (int i = 0; *(string + i); i++)
    {
        char *code = getStringValue(canonicalHash, *(string + 1));
        fwrite(code, sizeof(char), strlen(code), file);
    }

    fclose(file);
}