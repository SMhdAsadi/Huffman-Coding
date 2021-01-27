#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct _node
{
    char *key;
    int value;
    struct _node *next;
} Node;

typedef struct _list
{
    Node *head;
} List;


Node *newNode(char *key, int value)
{
    Node *node = malloc(sizeof(Node));
    node->key = key;
    node->value = value;
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

void addNode(List *list, char *key, int value)
{
    Node *node = newNode(key, value);

    if (isEmpty(list))
    {
        list->head = node;
    }
    else
    {
        node->next = list->head;
        list->head = node;
    }
}

int deleteNode(List *list, char *key)
{
    if (isEmpty(list))
    {
        return 0;
    }

    Node *node = list->head;

    // if it is first item
    if (list->head->key == key)
    {
        Node *firstNode = list->head;
        list->head = firstNode->next;
        free(firstNode);
        return 1;
    }

    // if it is not first item
    while(node->next != NULL)
    {
        if (strcmp(node->next->key, key) == 0)
        {
            Node *deletedNode = node->next;
            node->next = deletedNode->next;
            free(deletedNode);
            return 1;            
        }
        node = node->next;
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
            printf("(%s, %i), ", node->key, node->value);
            node = node->next;
        }
        printf("(%s, %i)]\n", node->key, node->value);
    }
    else
    {
        printf(" ]\n");
    }
}