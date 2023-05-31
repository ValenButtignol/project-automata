#include "klenne_clausure_ndfa.h"

// TODO: habria que agregar un simbolo a la cantidad total de simbolos del nuevo NDFA
// que representa el lambda de las nuevas transiciones?
/*
    Para hacer la clausura agregamos dos estados nuevos, el nuevo inicial y el nuevo final
    El nuevo inicial sera ndfa.numSTates + 1, y el nuevo final sera ndfa.numSTates + 2
*/ 
NDFA clausuraKlenne(NDFA ndfa){
    NDFA result = createNDFA(ndfa.numStates + 2, ndfa.numSymbols, ndfa.numStates);

    // Set the final state of the new NDFA result
    addFinalStateNDFA(&result, ndfa.numStates + 1);

    // Set the transitions of the new NDFA result
    // First we add the transitions of the ndfa
    NDFATransitionNode* currentTransition = ndfa.transitions;
    while (currentTransition != NULL) {
        Node* toStates = currentTransition->transition.toStates;
        while (toStates != NULL) {
            insertTransitionNDFA(&result, currentTransition->transition.fromState, currentTransition->transition.symbol, toStates->data);
            toStates = toStates->next;
        }
        currentTransition = currentTransition->next;
    }

    // Now we add the four new lambda transitions 
    insertTransitionNDFA(&result, result.startState, LAMBDA, ndfa.startState);
    insertTransitionNDFA(&result, result.startState, LAMBDA, result.finalStates->data);

    Node* finalStates = ndfa.finalStates;
    while (finalStates != NULL) {
        insertTransitionNDFA(&result, finalStates->data, LAMBDA, ndfa.startState);   // we asume ndfa has only one final state
        insertTransitionNDFA(&result, finalStates->data, LAMBDA, result.finalStates->data);
        finalStates = finalStates->next;
    }

    return result;
}