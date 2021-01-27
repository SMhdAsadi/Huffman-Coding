/*
    this file implements a type of hash table which stores [name: age] 
    when a overlap is happened, linkedlist is used
*/

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "linkedlist.h"

#define HASH_ARRAY_SIZE 5

typedef struct _hashtable
{
    List *array[HASH_ARRAY_SIZE];
    int size;
} HashTable;


int hashFunction(char *key)
{
    if (strlen(key) == 0)
    {
        return -1;
    }

    return *key % HASH_ARRAY_SIZE;
}

HashTable *newHashTable()
{
    HashTable *hashTable = malloc(sizeof(HashTable));
    for (int i = 0; i < HASH_ARRAY_SIZE; i++)
    {
        hashTable->array[i] = newList();
    }
    hashTable->size = 0;

    return hashTable;
}

void addItem(HashTable *hashTable, char *key, int value)
{
    int index = hashFunction(key);
    addNode(hashTable->array[index], key, value);
    hashTable->size++;
}

int deleteItem(HashTable *hashTabe, char *key)
{
    int index = hashFunction(key);
    int status = deleteNode(hashTabe->array[index], key);
    hashTabe->size--;

    return status;
}

int getValue(HashTable *hashTable, char *key)
{
    int index = hashFunction(key);
    
    List *list = hashTable->array[index];
    if (isEmpty(list))
    {
        return -1;
    }
    
    Node *node = list->head;
    while (node != NULL)
    {
        if (strcmp(node->key, key) == 0)
        {
            return node->value;
        }
        node = node->next;
    }

    return -1;
}

void print(HashTable *hashTable)
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
    {
        deleteList(hashTable->array[i]);
    }

    free(hashTable);
}