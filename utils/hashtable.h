#ifndef HASHTABLE_H
#define HASHTABLE_H
/*
    this file implements a type of hash table which stores (character, frequency)
    when a overlap is happened, linkedlist is used
*/

#include "linkedlist.h"
#define HASH_ARRAY_SIZE 25


typedef struct _hashtable
{
    List **array;
    int size;
} HashTable;


// creates and returns a new hash table
HashTable *newHashTable();


// returns true if hash table contains character
int contain(HashTable *hashTable, char character);

/* 
    adds the character to the hash table
    if the character exists, adds one to the frequency
*/
void addCharToIntItem(HashTable *hashTable, char character);


// adds (character, string) pair to the hash table
void addCharToStringItem(HashTable *hashTable, char character, char *string);


// deletes the item with key = character
int deleteItem(HashTable *hashTabe, char character);


// prints the hash table
void printHashTable(HashTable *hashTable);


// deletes the whole hash table
void deleteHashTable(HashTable *hashTable);


// returns the value(frequency) of the character
int getIntValue(HashTable *hashTable, char character);


// returns the value(code) of the character
char *getStringValue(HashTable *hashTable, char character);

#endif