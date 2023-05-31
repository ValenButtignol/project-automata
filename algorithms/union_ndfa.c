#include "union_ndfa.h"

NDFA unionNDFA(NDFA ndfa1, NDFA ndfa2) {
    int maxSymbols = (ndfa1.numSymbols > ndfa2.numSymbols) ? ndfa1.numSymbols : ndfa2.numSymbols;
    int startStateUnion = ndfa1.numStates + ndfa2.numStates; // the start state of the new NDFA
    NDFA result = createNDFA(ndfa1.numStates + ndfa2.numStates + 2, maxSymbols, startStateUnion); 

    // Setting the final state of the union
    addFinalStateNDFA(&result, startStateUnion + 1);

    int numStates1 = ndfa1.numStates;

    // Renaming the states of the transitions of ndfa2 to avoid overlapping states
    NDFATransitionNode* current = ndfa2.transitions;
    while (current != NULL){
        current->transition.fromState += numStates1;
        
        Node* currentToStates = current->transition.toStates;
        while (currentToStates != NULL) {
            currentToStates->data += numStates1;
            currentToStates = currentToStates->next;
        }
        current = current->next;
    }

    // Renaming the finalStates of the ndfa2
    Node* currentFinalStates = ndfa2.finalStates;
    while (currentFinalStates != NULL) {
        currentFinalStates->data += numStates1;
        currentFinalStates = currentFinalStates->next;
    }

    // Set the transitions of the new NDFA
    // First we add the transitions of the ndfa1
    NDFATransitionNode* currentTransition = ndfa1.transitions;
    while (currentTransition != NULL) {
        Node* toStates = currentTransition->transition.toStates;
        while (toStates != NULL) {
            insertTransitionNDFA(&result, currentTransition->transition.fromState, currentTransition->transition.symbol, toStates->data);
            toStates = toStates->next;
        }
        currentTransition = currentTransition->next;
    }

    // Now we add the transitions of the ndfa2
    currentTransition = ndfa2.transitions;
    while (currentTransition != NULL) {
        Node* toStates = currentTransition->transition.toStates;
        while (toStates != NULL) {
            insertTransitionNDFA(&result, currentTransition->transition.fromState,  currentTransition->transition.symbol, toStates->data);
            toStates = toStates->next;
        }
        currentTransition = currentTransition->next;
    }    

    // Adding new lambda transitions. We assume ndfa1 and ndfa2 can have more than 1 final state
    // Lambda transition from startStateUnion to the start state of ndfa1
    insertTransitionNDFA(&result, result.startState, LAMBDA, ndfa1.startState);
    insertTransitionNDFA(&result, result.startState, LAMBDA, ndfa2.startState + numStates1);

    // Lambda transition from the final states of 
    Node* finalStates1 = ndfa1.finalStates;
    while (finalStates1 != NULL) {
        insertTransitionNDFA(&result, finalStates1->data, LAMBDA, result.finalStates->data);
        finalStates1 = finalStates1->next;
    }

    Node* finalStates2 = ndfa2.finalStates;
    while (finalStates2 != NULL) {
        insertTransitionNDFA(&result, finalStates2->data, LAMBDA, result.finalStates->data);
        finalStates2 = finalStates2->next;
    }

    displayNDFA(result);

    return result;
}