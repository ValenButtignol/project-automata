#include <stdlib.h>
#include <stdio.h>
#include "../../include/structures/dfa.h"

/**
 * This function creates a deterministic finite automata without final states and without transitions.
 * 
 * @param num_states The number of states.
 * @param num_symbols The number of symbols.
 * @param initialState The initial state of the automata.
 * @return The deterministic finite automata.
 */
DFA createDFA(int numStates, int numSymbols, int initialState) {
    DFA dfa;
    dfa.numStates = numStates;
    dfa.numSymbols = numSymbols;
    dfa.initialState = initialState;
    dfa.delta = NULL;
    dfa.finalStates = NULL;
    return dfa;
}

/**
 * This function adds a final state to the deterministic finite automata.
 * 
 * @param dfa The deterministic finite automata.
 * @param state The final state to be added.
 */
void addDFAFinalState(DFA* dfa, int state) {
    addData(&(dfa->finalStates), state);
}

/**
 * This function adds a transition to the deterministic finite automata.
 * 
 * @param dfa The deterministic finite automata.
 * @param fromState The "from" state of the transition.
 * @param symbol The symbol needed for the transition.
 * @param toState The "to" state of the transition.
*/
void addDFATransition(DFA* dfa, int fromState, int symbol, int toState) {
    DFATransition transition;
    transition.fromState = fromState;
    transition.symbol = symbol;
    transition.toState = toState;
    addDFATransitionNode(&(dfa->delta), transition);
}

/**
 * This function adds a transition to any delta function of a deterministic finite automata that owns the given delta.
 * 
 * @param head The head of the delta function.
 * @param transition The transition to be added.
*/
void addDFATransitionNode(DFATransitionNode** head, DFATransition transition) {
    DFATransitionNode* newNode = (DFATransitionNode*)malloc(sizeof(DFATransitionNode));
    if (newNode == NULL) {
        exit(1);
    }
    newNode->transition = transition;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        DFATransitionNode* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}


/**
 * This function returns the toState of the transition according to the given state and symbol.
 * 
 * @param dfa The deterministic finite automata.
 * @param fromState The "from" state of the transition.
 * @param symbol The symbol needed for the transition.
 * @return The "to" state of the transition or -1 if the transition does not exist.
*/
int searchDFATransition(DFA dfa, int fromState, int symbol){
    DFATransitionNode* current = dfa.delta;
    while (current != NULL){
        if (current->transition.fromState == fromState && current->transition.symbol == symbol){
            return current->transition.toState;
        }
        current = current->next;
    }
    return -1;
}

/**
 * This function prints all the data of the automata.
 * 
 * @param dfa The deterministic finite automata.
*/
void toStringDFA(DFA dfa) {
    printf("DFA with %d states and %d symbols.\n", dfa.numStates, dfa.numSymbols);
    printf("Start state: %d\n", dfa.initialState);
    printf("Final states: ");
    Node* current = dfa.finalStates;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
    printf("delta:\n");
    DFATransitionNode* currentTransition = dfa.delta;
    while (currentTransition != NULL) {
        printf("From: %d Symbol: %d To: %d\n", currentTransition->transition.fromState, currentTransition->transition.symbol, currentTransition->transition.toState);
        currentTransition = currentTransition->next;
    }
}

/**
 * This function frees the memory allocated for the deterministic finite automata.
 * 
 * @param dfa The non deterministic finite automata.
*/
void freeDFA(DFA dfa) {
    Node* current = dfa.finalStates;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    DFATransitionNode* currentTransition = dfa.delta;
    while (currentTransition != NULL) {
        DFATransitionNode* temp = currentTransition;
        currentTransition = currentTransition->next;
        free(temp);
    }
}


void deleteUnreachableStates(DFA* dfa){
    Node* reachableStates = getReachableStates(*dfa);
    for (int i = 0; i < dfa->numStates; i++) {
        if (!containsData(reachableStates, i)) {
            deleteDFAState(dfa, i);
            renameAfterState(dfa, i);
        }
    }
}

void deleteDFAState(DFA* dfa, int i){
    // Delete the transitions that have the state i as fromState.
    DFATransitionNode* currentTransition = dfa->delta;
    while (currentTransition != NULL) {
        if (currentTransition->transition.fromState == i) {
            deleteDFATransition(dfa, currentTransition->transition.fromState, currentTransition->transition.symbol);
        }
        currentTransition = currentTransition->next;
    }
    // Delete the transitions that have the state i as toState.
    currentTransition = dfa->delta;
    while (currentTransition != NULL) {
        if (currentTransition->transition.toState == i) {
            deleteDFATransition(dfa, currentTransition->transition.fromState, currentTransition->transition.symbol);
        }
        currentTransition = currentTransition->next;
    }
    dfa->numStates--;
}

void deleteDFATransition(DFA* dfa, int fromState, int symbol){
    DFATransitionNode* currentTransition = dfa->delta;
    DFATransitionNode* previousTransition = NULL;
    while (currentTransition != NULL) {
        if (currentTransition->transition.fromState == fromState && currentTransition->transition.symbol == symbol) {
            if (previousTransition == NULL) {
                dfa->delta = currentTransition->next;
            } else {
                previousTransition->next = currentTransition->next;
            }
            free(currentTransition);
            return;
        }
        previousTransition = currentTransition;
        currentTransition = currentTransition->next;
    }
}


Node* getReachableStates(DFA dfa) {
    // Apply a dfs algorithm to the automata and return a list with the states reached.
    
    // Create a list to store the states reached.
    Node* reachableStates = NULL;
    // Create a list to store the states that have been visited.
    Node* visitedStates = NULL;
    // Add the initial state to the list of visited states.
    addData(&visitedStates, dfa.initialState);
    // Apply the dfs algorithm to the automata.
    dfs(dfa, dfa.initialState, &reachableStates, &visitedStates);
    // Return the list of states reached.
    return reachableStates;
}


void renameAfterState(DFA* dfa, int i) {
    // This function rename all the states with the actual data - 1, that contains data greater than i.
    // Iterate the transitions of the automata.
    DFATransitionNode* currentTransition = dfa->delta;
    while (currentTransition != NULL) {
        // If the from state is greater than i, rename it.
        if (currentTransition->transition.fromState > i) {
            currentTransition->transition.fromState--;
        }
        // If the to state is greater than i, rename it.
        if (currentTransition->transition.toState > i) {
            currentTransition->transition.toState--;
        }
        currentTransition = currentTransition->next;
    }
}

void dfs(DFA dfa, int state, Node** reachableStates, Node** visitedStates) {
    // Add the state to the list of reachable states.
    addData(reachableStates, state);
    // Iterate the transitions of the automata.
    DFATransitionNode* currentTransition = dfa.delta;
    while (currentTransition != NULL) {
        // If the transition is from the state and the to state has not been visited.
        if (currentTransition->transition.fromState == state && !containsData(*visitedStates, currentTransition->transition.toState)) {
            // Add the to state to the list of visited states.
            addData(visitedStates, currentTransition->transition.toState); 
            // Apply the dfs algorithm to the automata.
            dfs(dfa, currentTransition->transition.toState, reachableStates, visitedStates);
        }
        currentTransition = currentTransition->next;
    }
}