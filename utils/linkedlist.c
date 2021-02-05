#include "linkedlist.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>


Node *newIntNode(char character, int frequency)
{
    Node *node = malloc(sizeof(Node));
    node->character = character;
    node->value.frequency = frequency;
    node->valueType = 0;
    node->next = NULL;

    return node;
}

Node *newStringNode(char character, char *code)
{
    Node *node = malloc(sizeof(Node));
    node->character = character;
    node->value.code = code;
    node->valueType = 1;
    node->next = NULL;

    return node;
}

List *newList()
{
    List *list = malloc(sizeof(List));
    list->head = NULL;

    return list;
}

int isListEmpty(List *list)
{
    return list->head == NULL;
}

void addIntNode(List *list, char character)
{
    if (isListEmpty(list))
        list->head = newIntNode(character, 1);
    else
    {
        Node *currentNode = list->head;
        while (currentNode != NULL)
        {
            if (currentNode->character == character)
            {
                currentNode->value.frequency++;
                return;
            }
            currentNode = currentNode->next;
        }
        Node *new_node = newIntNode(character, 1);

        new_node->next = list->head;
        list->head = new_node;
    }
}

void addStringNode(List *list, char character, char *code)
{
    if (isListEmpty(list))
        list->head = newStringNode(character, code);
    else
    {
        Node *node = newStringNode(character, code);
        node->next = list->head;
        list->head = node;
    }
}

int getFrequency(List *list, char character)
{
    if (isListEmpty(list))
        return -1;

    Node *currentNode = list->head;
    while (currentNode != NULL)
    {
        if (currentNode->character == character)
            return currentNode->value.frequency;
        
        currentNode = currentNode->next;
    }

    return -1;
}

char *getCode(List *list, char character)
{
    if (isListEmpty(list))
        return NULL;
    
    Node *currentNode = list->head;
    while (currentNode != NULL)
    {
        if (character == currentNode->character)
            return currentNode->value.code;

        currentNode = currentNode->next;
    }

    return NULL;
}

int deleteNode(List *list, char character)
{
    if (isListEmpty(list))
        return 0;

    Node *currentNode = list->head;

    // if it is first item
    if (list->head->character == character)
    {
        Node *firstNode = list->head;
        list->head = firstNode->next;
        if (firstNode->valueType == 1)
            free(&firstNode->value.code);
        free(firstNode);
        return 1;
    }

    // if it is not first item
    while(currentNode->next != NULL)
    {
        if (currentNode->next->character == character)
        {
            Node *deletedNode = currentNode->next;
            currentNode->next = deletedNode->next;
            free(deletedNode);
            return 1;            
        }
        currentNode = currentNode->next;
    }

    return 0;
}

void deleteNodes(Node *node)
{
    if (node != NULL)
    {
        deleteNodes(node->next);
        if (node->valueType == 1)
            free(node->value.code);
            
        free(node);
    }
}

void deleteList(List *list)
{
    deleteNodes(list->head);
    free(list);
}

void printList(List *list)
{
    printf("[");

    Node *node = list->head;

    if (!isListEmpty(list))
    {
        while (node->next != NULL)
        {
            if (node->valueType == 0) // frequency
                printf("(%c, %i), ", node->character, node->value.frequency);
            else // code
                printf("(%c, %s), ", node->character, node->value.code);
            node = node->next;
        }
        if (node->valueType == 0) // frequency
            printf("(%c, %i)]\n", node->character, node->value.frequency);
        else // code
            printf("(%c, %s)]\n", node->character, node->value.code);
    }
    else
        printf(" ]\n");
}