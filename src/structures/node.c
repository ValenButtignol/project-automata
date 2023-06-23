#include <stdlib.h>
#include <stdio.h>
#include "../../include/structures/node.h"

/**
 * This function creates a new node.
 * 
 * @param data The data of the node to be created.
 * @return The newly created node.
*/
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    newNode->size = 1;
    return newNode;
}


/**
 * This function adds a node to the end of the linked list.
 * 
 * @param head The head of the linked list.
 * @param data The data of the node to be added
*/
void addData(Node** head, int data) {
    Node* newNode = createNode(data);
    // print new Node:
    printf("Head: %d\n", (*head)->data);
    
    if (*head == NULL || data < (*head)->data) {
        newNode->next = *head;
        *head = newNode;
    } else if (data == (*head)->data) {
        free(newNode);
        return;
    } else {
        Node* current = *head;
        while (current->next != NULL && current->next->data < data) {
            current = current->next;
        }
        if (current->next != NULL && current->next->data == data) {
            free(newNode);
            return;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    (*head)->size++;
}


/**
 * This function checks if the linked list contains a node with the given data.
 * 
 * @param head The head of the linked list.
 * @param data The data to be checked.
 * @return TRUE (1) if the linked list contains the data, FALSE (0) otherwise.
*/
int containsData(Node* set, int data) {
    Node* current = set;
    while (current != NULL) {
        if (current->data == data) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}


/**
 * This function checks if two nodes are equals.
 * 
 * @param head1 The head of the first list to be compared.
 * @param head2 The head of the second list to be compared.
 * @return TRUE (1) if the nodes are equal, FALSE (0) otherwise.
*/
int areEqualNodes(Node* set1, Node* set2) {
    Node* current1 = set1;
    Node* current2 = set2;
    while (current1 != NULL && current2 != NULL) {
        if (current1->data != current2->data) {
            return 0;
        }
        current1 = current1->next;
        current2 = current2->next;
    }
    if (current1 == NULL && current2 == NULL) {
        return 1;
    } else {
        return 0;
    }
}


/**
 * This function prints all the nodes in the linked list.
 * 
 * @param head The head of the linked list.
*/
void toStringNode(Node* head) {
    if (head == NULL) {
        printf("Set is empty.\n");
        return;
    }

    Node* current = head;
    printf("Set: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

/**
 * This function frees the memory allocated for the linked list.
 * 
 * @param head The head of the linked list.
*/
void freeNode(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}