#ifndef HASHTABLE_H
#define HASHTABLE_H
/*
    this file implements a type of hash table which stores (character, frequency)
    when a overlap is happened, linkedlist is used
*/

#include "linkedlist.h"
#define HASH_ARRAY_SIZE 15


typedef struct _hashtable
{
    List *array[HASH_ARRAY_SIZE];
    int size;
} HashTable;


// creates and returns a new hash table
HashTable *newHashTable();


/* 
    adds the character to the hash table
    if the character exists, adds one to the frequency
*/
void addItem(HashTable *hashTable, char character);


// deletes the item with key = character
int deleteItem(HashTable *hashTabe, char character);


// prints the hash table
void printHashTable(HashTable *hashTable);


// deletes the whole hash table
void deleteHashTable(HashTable *hashTable);


// returns the value(frequency) of the character
int getValue(HashTable *hashTable, char character);

#endif