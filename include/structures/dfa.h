#ifndef STRUCTURES_DFA_H
#define STRUCTURES_DFA_H

#include "node.h"

/**
 * This struct represents the transition type of a non deterministic finite automata
 * 
 * @param fromState The "from" state of the transition.
 * @param symbol The symbol needed for the transition.
 * @param toState The list of "to" states of the transition.
*/
typedef struct DFATransition {
    int fromState;
    int symbol;
    int toState;
} DFATransition;


/**
 * This struct represents the delta function of a non deterministic finite automata.
 * 
 * @param transition The current transition of the non deterministic finite automata.
 * @param next The next transition of the delta function.
*/
typedef struct DFATransitionNode {
    DFATransition transition;
    struct DFATransitionNode* next;
} DFATransitionNode;


/**
 * This struct represents a deterministic finite automata.
 * 
 * @param numStates The amount of states of the automata.
 * @param symbols The amount of symbols of the automata.
 * @param delta The transitions of the automata.
 * @param initialState The initial state of the automata.
 * @param finalStates The set of final states of the automata.
*/
typedef struct DFA {
    int numStates;
    int numSymbols;
    DFATransitionNode* delta;
    int initialState;
    Node* finalStates;
} DFA;


/**
 * This function creates a deterministic finite automata without final states and without transitions.
 * 
 * @param num_states The number of states.
 * @param num_symbols The number of symbols.
 * @param initialState The initial state of the automata.
 * @return The deterministic finite automata.
 */
DFA createDFA(int numStates, int numSymbols, int startState);


/**
 * This function adds a final state to the deterministic finite automata.
 * 
 * @param dfa The deterministic finite automata.
 * @param state The final state to be added.
 */
void addDFAFinalState(DFA* dfa, int state);


/**
 * This function adds a transition to the deterministic finite automata.
 * 
 * @param dfa The deterministic finite automata.
 * @param fromState The "from" state of the transition.
 * @param symbol The symbol needed for the transition.
 * @param toState The "to" state of the transition.
*/
void addDFATransition(DFA* dfa, int fromState, int symbol, int toState);


/**
 * This function adds a transition to any delta function of a deterministic finite automata that owns the given delta.
 * 
 * @param head The head of the delta function.
 * @param transition The transition to be added.
*/
void addDFATransitionNode(DFATransitionNode** head, DFATransition transition);


/**
 * This function returns the toState of the transition according to the given state and symbol.
 * 
 * @param dfa The deterministic finite automata.
 * @param fromState The "from" state of the transition.
 * @param symbol The symbol needed for the transition.
 * @return The "to" state of the transition or -1 if the transition does not exist.
*/
int searchDFATransition(DFA dfa, int fromState, int symbol);


/**
 * This function prints all the data of the automata.
 * 
 * @param dfa The deterministic finite automata.
*/
void toStringDFA(DFA dfa);


/**
 * This function frees the memory allocated for the deterministic finite automata.
 * 
 * @param dfa The non deterministic finite automata.
*/
void freeDFA(DFA dfa);


void deleteUnreachableStates(DFA* dfa);
void deleteDFAState(DFA* dfa, int i);
void deleteDFATransition(DFA* dfa, int fromState, int symbol);
Node* getReachableStates(DFA dfa); 
void renameAfterState(DFA* dfa, int i); 
void dfs(DFA dfa, int state, Node** reachableStates, Node** visitedStates);



#endif