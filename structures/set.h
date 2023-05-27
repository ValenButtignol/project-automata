#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../constants.h"

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct SetOfMarkableSets {
    Node* set;
    int marked;
    struct SetOfMarkableSets* next;
} SetOfMarkableSets;

typedef struct Array {
    int a[MAX_ARRAY];
    int length;
} Array;

Node* createNode(int data);

void insertElement(Node** head, int data);

int containsElement(Node* head, int data);

int areEqual(Node* set1, Node* set2);

void displaySet(Node* head);

void freeSet(Node* head);

void insertSetOfMarkableSets(SetOfMarkableSets** head, Node* set);

int containsSet(SetOfMarkableSets* setOfMarkableSets, Node* set);

void markSet(SetOfMarkableSets* setOfMarkableSets, Node* set);

int isMarked(SetOfMarkableSets* setOfMarkableSets, Node* set);

Node* getUnmarkedSet(SetOfMarkableSets* setOfMarkableSets);

int getSetIndex(SetOfMarkableSets* setOfMarkableSets, Node* set);

void freeSetOfMarkableSets(SetOfMarkableSets* setOfMarkableSets);

Array stringToArray(char string[]);