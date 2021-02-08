#include "hashtable.h"
#include <stdio.h>
#include <string.h>
#include <malloc.h>


int hashFunction(char key)
{
    return key % HASH_ARRAY_SIZE;
}


HashTable *newHashTable()
{
    HashTable *hashTable = malloc(sizeof(HashTable));

    hashTable->array = calloc(HASH_ARRAY_SIZE, sizeof(hashTable->array[0]));
    for (int i = 0; i < HASH_ARRAY_SIZE; i++)
        hashTable->array[i] = newList();
    
    hashTable->size = 0;

    return hashTable;
}

void addCharToIntItem(HashTable *hashTable, char character)
{
    int index = hashFunction(character);
    addIntNode(hashTable->array[index], character);
    hashTable->size++;
}

void addCharToStringItem(HashTable *hashTable, char character, char *string)
{
    int index = hashFunction(character);
    addStringNode(hashTable->array[index], character, string);
    hashTable->size++;
}

int deleteItem(HashTable *hashTabe, char character)
{
    int index = hashFunction(character);
    int deletedSuccessfully = deleteNode(hashTabe->array[index], character);

    if (deletedSuccessfully)
        hashTabe->size--;

    return deletedSuccessfully;
}

int getIntValue(HashTable *hashTable, char character)
{
    int index = hashFunction(character);
    
    List *list = hashTable->array[index];
    if (isListEmpty(list))
        return -1;
    
    Node *node = list->head;
    while (node != NULL)
    {
        if (node->character == character)
            return node->value.frequency;

        node = node->next;
    }

    return -1;
}

char *getStringValue(HashTable *hashTable, char character)
{
    int index = hashFunction(character);

    List *list = hashTable->array[index];
    if (isListEmpty(list))
        return NULL;

    Node *node = list->head;
    while (node != NULL)
    {
        if (node->character == character)
            return node->value.code;

        node = node->next;
    }

    return NULL;
}

void printHashTable(HashTable *hashTable)
{
    printf("Hash Table:\n");
    for (int i = 0; i < HASH_ARRAY_SIZE; i++)
    {
        printf("\t");
        printList(hashTable->array[i]);
    }
}

void deleteHashTable(HashTable *hashTable)
{
    for (int i = 0; i < HASH_ARRAY_SIZE; i++)
        deleteList(hashTable->array[i]);

    free(hashTable->array);
    free(hashTable);
}