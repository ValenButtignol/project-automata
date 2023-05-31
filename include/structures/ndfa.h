#ifndef STRUCTURES_NDFA_H
#define STRUCTURES_NDFA_H

#include "node.h"

/**
 * This struct represents a non deterministic finite automata.
 * 
 * @param numStates The amount of states of the automata.
 * @param symbols The amount of symbols of the automata.
 * @param delta The transitions of the automata.
 * @param initialState The initial state of the automata.
 * @param finalStates The set of final states of the automata.
*/
typedef struct NDFA {
    int numStates;
    int numSymbols;
    NDFATransitionNode* delta;
    int initialState;
    Node* finalStates;
} NDFA;


/**
 * This struct represents the transition type of a non deterministic finite automata
 * 
 * @param fromState The "from" state of the transition.
 * @param symbol The symbol needed for the transition.
 * @param toStates The list of "to" states of the transition.
*/
typedef struct NDFATransition {
    int fromState;
    int symbol;
    Node* toStates;
} NDFATransition;


/**
 * This struct represents the delta function of a non deterministic finite automata.
 * 
 * @param transition The current transition of the non deterministic finite automata.
 * @param next The next transition of the delta function.
*/
typedef struct NDFATransitionNode {
    NDFATransition transition;
    struct NDFATransitionNode* next;
} NDFATransitionNode;


/**
 * This function creates a non deterministic finite automata without final states and without transitions.
 * 
 * @param num_states The number of states.
 * @param num_symbols The number of symbols.
 * @param initialState The initial state of the automata.
 * @return The non deterministic finite automata.
 */
NDFA createNDFA(int numStates, int numSymbols, int initialState);


/**
 * This function adds a final state to the non deterministic finite automata.
 * 
 * @param ndfa The non deterministic finite automata.
 * @param state The final state to be added.
 */
void addNDFAFinalState(NDFA* ndfa, int state);


/**
 * This function adds a transition to the non deterministic finite automata.
 * 
 * @param ndfa The non deterministic finite automata.
 * @param fromState The "from" state of the transition.
 * @param symbol The symbol needed for the transition.
 * @param toState The "to" state of the transition.
*/
void addNDFATransition(NDFA* ndfa, int fromState, int symbol, int toState);


/**
 * This function adds a transition to any delta function of a non deterministic finite automata that owns the given delta.
 * 
 * @param head The head of the delta function.
 * @param transition The transition to be added.
*/
void addNDFATransitionNode(NDFATransitionNode** head, NDFATransition transition);


/**
 * This function prints all the data of the automata.
 * 
 * @param ndfa The non deterministic finite automata.
*/
void toStringNDFA(NDFA ndfa);

/**
 * This function frees the memory allocated for the non deterministic finite automata.
 * 
 * @param ndfa The non deterministic finite automata.
*/
void freeNDFA(NDFA ndfa);

#endif