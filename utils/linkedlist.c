#include "linkedlist.h"
#include <stdio.h>
#include <malloc.h>


Node *newNode(char character, int frequency)
{
    Node *node = malloc(sizeof(Node));
    node->character = character;
    node->frequency = frequency;
    node->next = NULL;

    return node;
}

List *newList()
{
    List *list = malloc(sizeof(List));
    list->head = NULL;

    return list;
}

int isEmpty(List *list)
{
    return list->head == NULL;
}

void addNode(List *list, char character)
{
    if (isEmpty(list))
        list->head = newNode(character, 1);
    else
    {
        Node *currentNode = list->head;
        while (currentNode != NULL)
        {
            if (currentNode->character == character)
            {
                currentNode->frequency++;
                return;
            }
            currentNode = currentNode->next;
        }
        Node *new_node = newNode(character, 1);

        new_node->next = list->head;
        list->head = new_node;
    }
}

int getFrequency(List *list, char character)
{
    if (isEmpty(list))
        return -1;

    Node *currentNode = list->head;
    while (currentNode != NULL)
    {
        if (currentNode->character == character)
            return currentNode->frequency;
        
        currentNode = currentNode->next;
    }

    return -1;
}

int deleteNode(List *list, char character)
{
    if (isEmpty(list))
        return 0;

    Node *currentNode = list->head;

    // if it is first item
    if (list->head->character == character)
    {
        Node *firstNode = list->head;
        list->head = firstNode->next;
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

    if (!isEmpty(list))
    {
        while (node->next != NULL)
        {
            printf("(%c, %i), ", node->character, node->frequency);
            node = node->next;
        }
        printf("(%c, %i)]\n", node->character, node->frequency);
    }
    else
        printf(" ]\n");
}