#ifndef STRUCTURES_NODE_H
#define STRUCTURES_NODE_H

/**
 * This struct represents a dynamic linked list of nodes.
 * 
 * @param data The data of the current node (Integer value).
 * @param next The next node of the linked list.
*/
typedef struct Node {
    int data;
    struct Node* next;
} Node;


/**
 * This function creates a new node.
 * 
 * @param data The data of the node to be created.
 * @return The newly created node.
*/
Node* createNode(int data);


/**
 * This function adds a node to the end of the linked list.
 * 
 * @param head The head of the linked list.
 * @param data The data of the node to be added
*/
void addData(Node** head, int data);


/**
 * This function checks if the linked list contains a node with the given data.
 * 
 * @param head The head of the linked list.
 * @param data The data to be checked.
 * @return TRUE (1) if the linked list contains the data, FALSE (0) otherwise.
*/
int containsData(Node* head, int data);


/**
 * This function checks if two nodes are equals.
 * 
 * @param head1 The head of the first list to be compared.
 * @param head2 The head of the second list to be compared.
 * @return TRUE (1) if the nodes are equal, FALSE (0) otherwise.
*/
int areEqualNodes(Node* head1, Node* head2);


/**
 * This function prints all the nodes in the linked list.
 * 
 * @param head The head of the linked list.
*/
void toStringNode(Node* head);


/**
 * This function frees the memory allocated for the linked list.
 * 
 * @param head The head of the linked list.
*/
void freeNode(Node* head);

#endif