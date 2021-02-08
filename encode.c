#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/hashtable.h"
#include "utils/heap.h"
#include "common.h"

#define FILE_NAME "test.txt"

char *readText();
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
    char *string = readText();
    if (string == NULL)
    {
        printf("Cannot find text file.\n");
        exit(EXIT_FAILURE);
    }

    initializeFrequencyHashTable(frequencyHash, string);
    initializeHeap(heap, frequencyHash);
    huffmanTree = initializeHuffmanTree(huffmanTree, heap);

    char *emptyString = malloc(sizeof(char));
    strcpy(emptyString, "");
    initializeCodeHashTable(codeHash, huffmanTree, emptyString);

    initializeCodeLengthArray(codeLengthArray, codeHash);
    initializeCanonicalHash(canonicalCodeHash, codeLengthArray);

    writeHeaderToFile(codeLengthArray);
    writeCodeToFile(string, canonicalCodeHash);

    free(string);
    deleteHashTable(frequencyHash);
    deleteHeap(heap);
    deleteHuffmanTree(huffmanTree);
    deleteHashTable(codeHash);
    deleteArray(codeLengthArray);
    deleteHashTable(canonicalCodeHash);

    return 0;
}

char *readText()
{
    char *buffer = 0;
    long length;
    FILE *file = fopen(FILE_NAME, "rb");

    if (file)
    {
        fseek(file, 0, SEEK_END);
        length = ftell (file);
        fseek(file, 0, SEEK_SET);
        buffer = malloc(length + 1);
        if (buffer)
            fread(buffer, 1, length, file);

        buffer[length] = '\0';
        fclose(file);
    }

    if (buffer)
        return buffer;
    else
        return NULL;

    // FILE *file = fopen("a.txt", "r");
    // if (file == NULL)
    //     return NULL;

    // int currentSize = 10, i = 0;
    // char *string = malloc(sizeof(char) * currentSize), c = ' ';
    // while ((c = getc(file)) != EOF)    
    // {
    //     if (currentSize == i)
    //     {
    //         string = realloc(string, 2 * currentSize);
    //         currentSize *= 2;
    //     }
    //     string[i] = c;
    //     i++;
    // }

    // if (i != currentSize)
    //     string = realloc(string, i * sizeof(char));

    // return string;
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
            TNode *newNode = newTNode(currentNode->character, currentNode->value.frequency);
            insert(heap, newNode);

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

char *getBuffer(char *string, HashTable *canonicalHash)
{
    int outputCapacity = 50, outputSize = 0;
    char *output = malloc(sizeof(char) * outputCapacity);
    strcpy(output, "");

    for (int i = 0; *(string + i); i++)
    {
        char *code = getStringValue(canonicalHash, *(string + i));
        int codeSize = strlen(code);
        while (outputCapacity <= outputSize + codeSize)
        {
            output = realloc(output, 2 * outputCapacity);
            outputCapacity *= 2;
        }
        strcat(output + outputSize, code);
        outputSize += codeSize;
    }

    return output;
}

unsigned char getCharCode(char *string)
{
    unsigned char output = 0;
    int order = 1;
    for (int i = 7; i >= 0; i--)
    {
        if (*(string + i) == '1')
            output += order;

        order *= 2;
    }

    return output;
}

void writeCodeToFile(char *string, HashTable *canonicalHash)
{
    char *buffer = getBuffer(string, canonicalHash);
    FILE *file = fopen("save.dat", "ab");
    
    int length = strlen(buffer);
    int remainder = length % 8;
    if (remainder != 0)
    {
        char extra = (char)(8 - remainder);
        appendZeroToEnd(buffer, extra);
        fwrite(&extra, sizeof(char), 1, file);
    }

    int i = 0;
    char byte[9];
    for (int i = 0; i < length + (8 - remainder); i += 8)
    {
        strncpy(byte, buffer + i, 8);
        unsigned char code = getCharCode(byte);
        fwrite(&code, sizeof(unsigned char), 1, file);
    }
    // while (sscanf(buffer + (i * 8), "%.8s", byte) == 1)
    // {
    //     printf("here we go byte is %s\n", byte);
    //     unsigned char code = getCharCode(byte);
    //     fwrite(&code, sizeof(unsigned char), 1, file);
    //     i++;
    // }

    free(buffer);
    fclose(file);
}