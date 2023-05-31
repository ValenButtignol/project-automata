#include "concatenation_ndfa.h"

// TODO: habria que agregarle un simbolo mas representando el lambda? que pasa si ya habia una transicion lambda en algun ndfa?
NDFA concatenateNDFA(NDFA ndfa1, NDFA ndfa2) {

    int maxSymbols = (ndfa1.numSymbols > ndfa2.numSymbols) ? ndfa1.numSymbols : ndfa2.numSymbols;

    NDFA result = createNDFA(ndfa1.numStates + ndfa2.numStates, maxSymbols, ndfa1.startState); 
    
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

    
    // Set the finalStates of the new NDFA with the finalStates of ndfa2
    Node* finalStates = ndfa2.finalStates;
    while (finalStates != NULL) {
        addFinalStateNDFA(&result, finalStates->data);
        finalStates = finalStates->next;
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

    // Add new lambda transition from the final states of ndfa1 to the startState of the ndfa2
    // We assume ndfa1 can have more than 1 final state
    finalStates = ndfa1.finalStates;
    while (finalStates != NULL) {
        insertTransitionNDFA(&result, finalStates->data, LAMBDA, ndfa2.startState + numStates1);
        finalStates = finalStates->next;
    }
    displayNDFA(result);
    return result;
}