#include "../../include/algorithms/union_ndfa.h"
#include "../../include/constants.h"
#include <stdlib.h>

NDFA unionNDFA(NDFA ndfa1, NDFA ndfa2) {
    int maxSymbols = (ndfa1.numSymbols > ndfa2.numSymbols) ? ndfa1.numSymbols : ndfa2.numSymbols;
    int initialStateUnion = ndfa1.numStates + ndfa2.numStates; // the initial state of the new NDFA
    NDFA result = createNDFA(ndfa1.numStates + ndfa2.numStates + 2, maxSymbols, initialStateUnion); 

    // Setting the final state of the union
    addNDFAFinalState(&result, initialStateUnion + 1);

    int numStates1 = ndfa1.numStates;

    renameNDFAStates(&ndfa2, numStates1);

    // Set the transitions of the new NDFA
    // First we add the transitions of the ndfa1
    NDFATransitionNode* currentTransition = ndfa1.delta;
    while (currentTransition != NULL) {
        Node* toStates = currentTransition->transition.toStates;
        while (toStates != NULL) {
            addNDFATransition(&result, currentTransition->transition.fromState, currentTransition->transition.symbol, toStates->data);
            toStates = toStates->next;
        }
        currentTransition = currentTransition->next;
    }

    // Now we add the transitions of the ndfa2
    currentTransition = ndfa2.delta;
    while (currentTransition != NULL) {
        Node* toStates = currentTransition->transition.toStates;
        while (toStates != NULL) {
            addNDFATransition(&result, currentTransition->transition.fromState,  currentTransition->transition.symbol, toStates->data);
            toStates = toStates->next;
        }
        currentTransition = currentTransition->next;
    }    

    // Adding new lambda transitions. We assume ndfa1 and ndfa2 can have more than 1 final state
    // Lambda transition from initialStateUnion to the start state of ndfa1
    addNDFATransition(&result, result.initialState, LAMBDA, ndfa1.initialState);
    addNDFATransition(&result, result.initialState, LAMBDA, ndfa2.initialState);

    // Lambda transition from the final states of 
    Node* finalStates1 = ndfa1.finalStates;
    while (finalStates1 != NULL) {
        addNDFATransition(&result, finalStates1->data, LAMBDA, result.finalStates->data);
        finalStates1 = finalStates1->next;
    }

    Node* finalStates2 = ndfa2.finalStates;
    while (finalStates2 != NULL) {
        addNDFATransition(&result, finalStates2->data, LAMBDA, result.finalStates->data);
        finalStates2 = finalStates2->next;
    }

    toStringNDFA(result);

    return result;
}