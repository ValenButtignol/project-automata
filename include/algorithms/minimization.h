#ifndef ALGORITHMS_MINIMIZATION_H
#define ALGORITHMS_MINIMIZATION_H
#include "../structures/dfa.h"
#include "../structures/node.h"
#include "../structures/set_of_markable_sets.h"

void minimize(DFA automata, DFA* minimizedAutomata);

void resetMarks(int* arr, int size);
int itIsMarked(int arr[], int el);
int markState(int* arr, int el);
SetOfMarkableSets* quotientSet(DFA automata);
int getEquivalenceClass(SetOfMarkableSets* partitions, int state);
int getData(Node* x, int j);
void resetMarks(int* arr, int size);
Node* getSet(SetOfMarkableSets* partitions, int i);
int markState(int* arr, int el);
int itIsMarked(int arr[], int el);
Node* getFinalStates(SetOfMarkableSets* partitions, Node* finalStates);
void generateTransitions(SetOfMarkableSets* partitions, DFA* minimizedAutomata, DFA automata);

  
#endif