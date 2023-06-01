#include <stdlib.h>
#include "../../include/structures/set_of_markable_sets.h"
#include "../../include/structures/node.h"

/**
 * This function adds a new markable set.
 * 
 * @param setOfMarkableSets The set of markable sets.
 * @param set The new markable set.
*/
void addSet(SetOfMarkableSets** head, Node* set){
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

/**
 * This function checks if a markable set is in the set of markable sets.
 * 
 * @param setOfMarkableSets The set of markable sets.
 * @param set The markable set to check if exists.
 * @return TRUE (1) if the markable set exists, FALSE (0) otherwise.
*/
int containsSet(SetOfMarkableSets* setOfMarkableSets, Node* set) {
    SetOfMarkableSets* current = setOfMarkableSets;
    while (current != NULL) {
        if (areEqualNodes(current->set, set)) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}


/**
 * This function checks if a markable set is in the set of markable sets.
 * 
 * @param setOfMarkableSets The set of markable sets.
 * @param set The markable set to check if exists.
 * @return TRUE (1) if the markable set exists, FALSE (0) otherwise.
*/
int isMarked(SetOfMarkableSets* setOfMarkableSets, Node* set) {
    SetOfMarkableSets* current = setOfMarkableSets;
    while (current != NULL) {
        if (areEqualNodes(current->set, set)) {
            return current->marked;
        }
        current = current->next;
    }
    return -1;
}


/**
 * This function marks a set contained in the set of markable sets.
 * 
 * @param setOfMarkableSets The set of markable sets.
 * @param set The markable set to mark.
*/
void markSet(SetOfMarkableSets* setOfMarkableSets, Node* set) {
    SetOfMarkableSets* current = setOfMarkableSets;
    while (current != NULL) {
        if (areEqualNodes(current->set, set)) {
            current->marked = 1;
            return;
        }
        current = current->next;
    }
}


/**
 * This function returns the first unmarked set in the set of markable sets.
 * 
 * @param setOfMarkableSets The set of markable sets.
 * @return The first unmarked set or NULL if there is no such set.
*/
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


/**
 * This function returns the index of a particular markable set in the set of markable sets.
 * 
 * @param setOfMarkableSets The set of markable sets.
 * @param set The markable set to return.
 * @return The index of the markable set or -1 if the markable set is not in the set of markable sets.
*/
int getSetIndex(SetOfMarkableSets* setOfMarkableSets, Node* set) {
    SetOfMarkableSets* current = setOfMarkableSets;
    int index = 0;
    while (current != NULL) {
        if (areEqualNodes(current->set, set)) {
            return index;
        }
        index++;
        current = current->next;
    }
    return -1;
}


/**
 * This function frees the memory allocated by a set of markable sets.
 * 
 * @param setOfMarkablesSets The set of markable sets.
*/
void freeSetOfMarkableSets(SetOfMarkableSets* setOfMarkableSets) {
    SetOfMarkableSets* current = setOfMarkableSets;
    while (current != NULL) {
        SetOfMarkableSets* temp = current;
        current = current->next;
        freeNode(temp->set);
        free(temp);
    }
}