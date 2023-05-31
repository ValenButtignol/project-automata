#include <stdlib.h>
#include <stdio.h>
#include "../../include/structures/ndfa.h"

/**
 * This function creates a non deterministic finite automaton without final states.
 * 
 * @param num_states The number of states.
 * @param num_symbols The number of symbols.
 * @param initialState The initial state of the automaton.
 * @return The non deterministic finite automaton.
 */
NDFA createNDFA(int numStates, int numSymbols, int initialState) {
    NDFA ndfa;
    ndfa.numStates = numStates;
    ndfa.numSymbols = numSymbols;
    ndfa.initialState = initialState;
    ndfa.delta = NULL;
    ndfa.finalStates = NULL;
    return ndfa;
}


/**
 * This function adds a final state to the non deterministic finite automata.
 * 
 * @param ndfa The non deterministic finite automata.
 * @param state The final state to be added.
 */
void addNDFAFinalState(NDFA* ndfa, int state) {
    addData(&(ndfa->finalStates), state);
}


/**
 * This function adds a transition to the non deterministic finite automata.
 * 
 * @param ndfa The non deterministic finite automata.
 * @param fromState The "from" state of the transition.
 * @param symbol The symbol needed for the transition.
 * @param toState The "to" state of the transition.
*/
void addNDFATransition(NDFA* ndfa, int fromState, int symbol, int toState) {
    // Search for the transition
    NDFATransitionNode* current = ndfa->delta;
    while (current != NULL) {
        if (current->transition.fromState == fromState && current->transition.symbol == symbol) {
            addData(&(current->transition.toStates), toState);
            return;
        }
        current = current->next;
    }

    // If transition not found, create a new one
    NDFATransition transition;
    transition.fromState = fromState;
    transition.symbol = symbol;
    transition.toStates = NULL;
    addData(&(transition.toStates), toState);
    addNDFATransitionNode(&(ndfa->delta), transition);
}


/**
 * This function adds a transition to any delta function of any non deterministic finite automata.
 * 
 * @param head The head of the delta function.
 * @param transition The transition to be added.
*/
void addNDFATransitionNode(NDFATransitionNode** head, NDFATransition transition) {
    NDFATransitionNode* newNode = (NDFATransitionNode*)malloc(sizeof(NDFATransitionNode));
    if (newNode == NULL) {
        exit(1);
    }
    newNode->transition = transition;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        NDFATransitionNode* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

/**
 * This function prints all the data of the automata.
 * 
 * @param ndfa The non deterministic finite automata.
*/
void toStringNDFA(NDFA ndfa) {
    printf("NDFA with %d states and %d symbols.\n", ndfa.numStates, ndfa.numSymbols);
    printf("Initial state: %d\n", ndfa.initialState);
    printf("Final states: ");
    Node* current = ndfa.finalStates;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
    printf("Transitions:\n");
    NDFATransitionNode* currentTransition = ndfa.delta;
    while (currentTransition != NULL) {
        printf("From: %d Symbol: %d ", currentTransition->transition.fromState, currentTransition->transition.symbol);
        Node* currentToState = currentTransition->transition.toStates;
        printf("To: ");
        while (currentToState != NULL) {
            printf("%d ", currentToState->data);
            currentToState = currentToState->next;
        }
        printf("\n");
        currentTransition = currentTransition->next;
    }
}

/**
 * This function frees the memory allocated for the non deterministic finite automata.
 * 
 * @param ndfa The non deterministic finite automata.
*/
void freeNDFA(NDFA ndfa) {
    Node* current = ndfa.finalStates;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }

    NDFATransitionNode* currentTransition = ndfa.delta;
    while (currentTransition != NULL) {
        Node* currentToState = currentTransition->transition.toStates;
        while (currentToState != NULL) {
            Node* temp = currentToState;
            currentToState = currentToState->next;
            free(temp);
        }
        NDFATransitionNode* temp = currentTransition;
        currentTransition = currentTransition->next;
        free(temp);
    }
}