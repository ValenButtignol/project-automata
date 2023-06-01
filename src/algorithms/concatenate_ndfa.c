#include <stdlib.h>
#include "../../include/algorithms/concatenate_ndfa.h"
#include "../../include/constants.h"

/**
* This function computes the concatenation between two given NDFA's
* 
* @param ndfa1 first NDFA in the concatenation
* @param ndfa2 second NDFA in the concatenation
* @return concatenation between the two NDFA's
*/
NDFA concatenateNDFA(NDFA ndfa1, NDFA ndfa2) {

    int maxSymbols = (ndfa1.numSymbols > ndfa2.numSymbols) ? ndfa1.numSymbols : ndfa2.numSymbols;

    NDFA result = createNDFA(ndfa1.numStates + ndfa2.numStates, maxSymbols, ndfa1.initialState); 
    
    int numStates1 = ndfa1.numStates;

    renameNDFAStates(&ndfa2, numStates1);

    
    // Set the finalStates of the new NDFA with the finalStates of ndfa2
    Node* finalStates = ndfa2.finalStates;
    while (finalStates != NULL) {
        addNDFAFinalState(&result, finalStates->data);
        finalStates = finalStates->next;
    }


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

    // Add new lambda transition from the final states of ndfa1 to the initialState of the ndfa2
    // We assume ndfa1 can have more than 1 final state
    finalStates = ndfa1.finalStates;
    while (finalStates != NULL) {
        addNDFATransition(&result, finalStates->data, LAMBDA, ndfa2.initialState);
        finalStates = finalStates->next;
    }
    return result;
}