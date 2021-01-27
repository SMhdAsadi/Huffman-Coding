#include "linkedlist.h"

#define HASH_ARRAY_SIZE 5

typedef struct _hashtable
{
    List *array[HASH_ARRAY_SIZE];
    int size;
} HashTable;

HashTable *newHashTable();
void addItem(HashTable *hashTable, char *key, int value);
int deleteItem(HashTable *hashTabe, char *key);
void print(HashTable *hashTable);
void deleteHashTable(HashTable *hashTable);
int getValue(HashTable *hashTable, char *key);
