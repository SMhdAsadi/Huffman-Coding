// read header from file (code length)
// read code from file (character code string)
// create canonical tree from header (e.g. a -> 110)
// parse character code string to characters
#include <stdio.h>
#include <malloc.h>
#include <string.h>

#include "utils/hashtable.h"
#include "utils/dynamic_array.h"
#include "utils/huffman_tree.h"
#include "common.h"

long int readHeader(Array *codeLength);
char *readCode(long int seekPtr, char *extra);
void initializeCanonicalTree(TNode *root, HashTable *canonicalCode);
void parseData(TNode *canonicalTree, char *string, char extra);

int main()
{
    Array *codeLength = newArray(10);
    long int seekPtr = readHeader(codeLength);

    char extra = 0;
    char *string = readCode(seekPtr, &extra);

    HashTable *canonicalCode = newHashTable();
    initializeCanonicalHash(canonicalCode, codeLength);

    printHashTable(canonicalCode);

    TNode *root = newEmptyNode();
    initializeCanonicalTree(root, canonicalCode);

    parseData(root, string, extra);

    deleteArray(codeLength);
    free(string);
    deleteHashTable(canonicalCode);

    return 0;
}

long int readHeader(Array *codeLength)
{
    FILE *file = fopen("save.dat", "rb");
    if (file == NULL)
        return -1;

    int numberOfCodes = 0;
    fread(&numberOfCodes, sizeof(int), 1, file);

    char c;
    int frequency;
    for (int i = 0; i < numberOfCodes; i++)
    {
        fread(&c, sizeof(char), 1, file);
        fread(&frequency, sizeof(int), 1, file);

        addLast(codeLength, newTNode(c, frequency));
    }
    int seekPtr = ftell(file);

    fclose(file);
    return seekPtr;
}

char *getBinaryCode(unsigned char character)
{
    char *output = malloc(sizeof(char) * 9);
    output[8] = '\0';
    for (int i = 7; i >= 0; i--)
    {
        output[i] = character % 2 ? '1' : '0';
        character /= 2;
    }

    return output;
}

char *readCode(long int seekPtr, char *extra)
{
    FILE *file = fopen("save.dat", "rb");
    if (file == NULL)
        return NULL;

    fseek(file, seekPtr, SEEK_SET);
    fread(extra, sizeof(char), 1, file);

    int currentSize = 96, i = 0;
    char *code = malloc(sizeof(char) * currentSize);
    strcpy(code, "");
    unsigned char temp;

    while (fread(&temp, sizeof(unsigned char), 1, file))
    {
        if (i == currentSize)
        {
            code = realloc(code, 2 * currentSize);
            currentSize *= 2;
        }
        char *binary = getBinaryCode(temp);
        strcat(code, binary);
        free(binary);

        i += 8;
    }

    if (currentSize != i)
        code = realloc(code, sizeof(char) * i);

    return code;
}

void addCanonicalNode(TNode *root, char character, char *code)
{
    TNode *currentTNode = root;
    for (int i = 0; *(code + i); i++)
    {
        char c = *(code + i);
        if (c == '1')
        {
            if (currentTNode->right == NULL)
                currentTNode->right = newEmptyNode();

            currentTNode = currentTNode->right;
        }
        else if (c == '0')
        {
            if (currentTNode->left == NULL)
                currentTNode->left = newEmptyNode();
            
            currentTNode = currentTNode->left;
        }
    }

    currentTNode->c = character;
}

void initializeCanonicalTree(TNode *root, HashTable *canonicalCode)
{
    for (int i = 0; i < HASH_ARRAY_SIZE; i++)
    {
        List *currentList = canonicalCode->array[i];
        Node *currentNode = currentList->head;

        while (currentNode != NULL)
        {
            char *code = currentNode->value.code;
            addCanonicalNode(root, currentNode->character, code);

            currentNode = currentNode->next;
        }
    }
}

void parseData(TNode *canonicalTree, char *string, char extra)
{
    TNode *currentTNode = canonicalTree;
    for (int i = 0; *(string + i + extra); i++)
    {
        if (*(string + i) == '1')
            currentTNode = currentTNode->right;
        else if (*(string + i) == '0')
            currentTNode = currentTNode->left;

        if (currentTNode->left == NULL && currentTNode->right == NULL)
        {
            printf("%c", currentTNode->c);
            currentTNode = canonicalTree;
        }
    }

    printf("\n");
}