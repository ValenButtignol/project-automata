#ifndef STRUCTURES_SET_OF_MARKABLE_SETS_H
#define STRUCTURES_SET_OF_MARKABLE_SETS_H

#include "node.h"

/**
 * This struct represents a dynamic set of markable sets. It's similar to a markable matrix.
 * 
 * @param set The current markable set.
 * @param marked The mark of the set.
 * @param next The next markable set.
*/
typedef struct SetOfMarkableSets {
    Node* set;
    int marked;
    int size;
    struct SetOfMarkableSets* next;
} SetOfMarkableSets;


/**
 * This function adds a new markable set.
 * 
 * @param setOfMarkableSets The set of markable sets.
 * @param set The new markable set.
*/
void addSet(SetOfMarkableSets** SetOfMarkableSets, Node* set);


/**
 * This function checks if a markable set is in the set of markable sets.
 * 
 * @param setOfMarkableSets The set of markable sets.
 * @param set The markable set to check if exists.
 * @return TRUE (1) if the markable set exists, FALSE (0) otherwise.
*/
int containsSet(SetOfMarkableSets* setOfMarkableSets, Node* set);


/**
 * This function checks if a markable set is marked.
 * 
 * @param setOfMarkableSets The set of markable sets.
 * @param set The markable set to check if is marked.
 * @return TRUE (1) if the markable set is marked, FALSE (0) otherwise.
*/
int isMarked(SetOfMarkableSets* setOfMarkableSets, Node* set);


/**
 * This function marks a set contained in the set of markable sets.
 * 
 * @param setOfMarkableSets The set of markable sets.
 * @param set The markable set to mark.
*/
void markSet(SetOfMarkableSets* setOfMarkableSets, Node* set);


/**
 * This function returns the first unmarked set in the set of markable sets.
 * 
 * @param setOfMarkableSets The set of markable sets.
 * @return The first unmarked set or NULL if there is no such set.
*/
Node* getUnmarkedSet(SetOfMarkableSets* setOfMarkableSets);


/**
 * This function returns the index of a particular markable set in the set of markable sets.
 * 
 * @param setOfMarkableSets The set of markable sets.
 * @param set The markable set to return.
 * @return The index of the markable set or -1 if the markable set is not in the set of markable sets.
*/
int getSetIndex(SetOfMarkableSets* setOfMarkableSets, Node* set);


/**
 * This function frees the memory allocated by a set of markable sets.
 * 
 * @param setOfMarkablesSets The set of markable sets.
*/
void freeSetOfMarkableSets(SetOfMarkableSets* setOfMarkableSets);

#endif