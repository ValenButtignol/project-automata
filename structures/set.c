#include "set.h"

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to insert an element into the set in order
void insertElement(Node** head, int data) {
    Node* newNode = createNode(data);

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
}

// Function to display the elements of the set
void displaySet(Node* head) {
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

// Function to free the memory allocated for the set
void freeSet(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

void insertSetOfMarkableSets(SetOfMarkableSets** head, Node* set){
    SetOfMarkableSets* newNode = (SetOfMarkableSets*)malloc(sizeof(SetOfMarkableSets));
    if (newNode == NULL) {
        exit(1);
    }
    newNode->set = set;
    newNode->marked = 0;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        SetOfMarkableSets* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

int isMarked(SetOfMarkableSets* setOfMarkableSets, Node* set) {
    SetOfMarkableSets* current = setOfMarkableSets;
    while (current != NULL) {
        if (areEqual(current->set, set)) {
            return current->marked;
        }
        current = current->next;
    }
    return -1;
}

int areEqual(Node* set1, Node* set2) {
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

void markSet(SetOfMarkableSets* setOfMarkableSets, Node* set) {
    SetOfMarkableSets* current = setOfMarkableSets;
    while (current != NULL) {
        if (areEqual(current->set, set)) {
            current->marked = 1;
            return;
        }
        current = current->next;
    }
}

Node* getUnmarkedSet(SetOfMarkableSets* setOfMarkableSets) {
    SetOfMarkableSets* current = setOfMarkableSets;
    while (current != NULL) {
        if (current->marked == 0) {
            return current->set;
        }
        current = current->next;
    }
    return NULL;
}

int getSetIndex(SetOfMarkableSets* setOfMarkableSets, Node* set) {
    SetOfMarkableSets* current = setOfMarkableSets;
    int index = 0;
    while (current != NULL) {
        if (areEqual(current->set, set)) {
            return index;
        }
        index++;
        current = current->next;
    }
    return -1;
}

int containsSet(SetOfMarkableSets* setOfMarkableSets, Node* set) {
    SetOfMarkableSets* current = setOfMarkableSets;
    while (current != NULL) {
        if (areEqual(current->set, set)) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

int containsElement(Node* set, int element) {
    Node* current = set;
    while (current != NULL) {
        if (current->data == element) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void freeSetOfMarkableSets(SetOfMarkableSets* setOfMarkableSets) {
    SetOfMarkableSets* current = setOfMarkableSets;
    while (current != NULL) {
        SetOfMarkableSets* temp = current;
        current = current->next;
        freeSet(temp->set);
        free(temp);
    }
}

Array stringToArray(char string[]){
    Array result;
    int length = strlen(string);
    for (int i = 0; i < length; i++){
        char stringNumber[2];
        stringNumber[0] = string[i];
        stringNumber[1] = '\0';
        result.a[i] = atoi(stringNumber);
        result.length++;
    }
    return result;
}