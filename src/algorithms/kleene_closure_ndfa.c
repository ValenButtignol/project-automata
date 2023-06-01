#include <stdlib.h>
#include "../../include/algorithms/kleene_closure_ndfa.h"
#include "../../include/constants.h"

// TODO: habria que agregar un simbolo a la cantidad total de simbolos del nuevo NDFA
// que representa el lambda de las nuevas transiciones?
/*
    Para hacer la clausura agregamos dos estados nuevos, el nuevo inicial y el nuevo final
    El nuevo inicial sera ndfa.numSTates + 1, y el nuevo final sera ndfa.numSTates + 2
*/ 
NDFA clausuraKlenne(NDFA ndfa){
    NDFA result = createNDFA(ndfa.numStates + 2, ndfa.numSymbols, ndfa.numStates);

    // Set the final state of the new NDFA result
    addNDFAFinalState(&result, ndfa.numStates + 1);

    // Set the transitions of the new NDFA result
    // First we add the transitions of the ndfa
    NDFATransitionNode* currentTransition = ndfa.delta;
    while (currentTransition != NULL) {
        Node* toStates = currentTransition->transition.toStates;
        while (toStates != NULL) {
            addNDFATransition(&result, currentTransition->transition.fromState, currentTransition->transition.symbol, toStates->data);
            toStates = toStates->next;
        }
        currentTransition = currentTransition->next;
    }

    // Now we add the four new lambda transitions 
    addNDFATransition(&result, result.initialState, LAMBDA, ndfa.initialState);
    addNDFATransition(&result, result.initialState, LAMBDA, result.finalStates->data);

    Node* finalStates = ndfa.finalStates;
    while (finalStates != NULL) {
        addNDFATransition(&result, finalStates->data, LAMBDA, ndfa.initialState);   // we asume ndfa has only one final state
        addNDFATransition(&result, finalStates->data, LAMBDA, result.finalStates->data);
        finalStates = finalStates->next;
    }

    return result;
}