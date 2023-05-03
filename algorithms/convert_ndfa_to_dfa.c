#include "convert_ndfa_to_dfa.h"

/**
 * This function calculates the lambda clausure of a set of states. The lambda clausure is the set 
 * of states that can be reached from each state of the set using only lambda transitions.
 * 
 * @param automaton The automaton to use.
 * @param states The set of states to calculate the lambda clausure.
 * @return The lambda clausure of the set of states.
*/
Array lambdaClausure(NDFA automaton, Array states) {

    Array result;
    result.length = 0;

    // Initialize the result array.
    for (int i = 0; i < MAX_ARRAY; i++) {
        result.a[i] = EMPTY;
    }

    // The lambda clausure of a set of states, includes those same states.
    for (int i = 0; i < states.length; i++) {
        result.a[i] = states.a[i];
        result.length++;
    }

    for (int i = 0; i < result.length; i++) {
        for (int j = 0; j < automaton.states; j++) {

            // For each state in the set of states, check if it has a lambda transition.
            int currentState = automaton.delta[result.a[i]][LAMBDA][j];
            if (currentState != EMPTY) {

                // If it has a lambda transition, check if it is already in the result.
                int itsInResult = FALSE;
                for (int k = 0; k < result.length && itsInResult == FALSE; k++) {
                    if (currentState == result.a[k]){
                        itsInResult = TRUE;
                    }
                }

                // If it is not in the result, add it.
                if (itsInResult == FALSE) {
                    result.a[result.length] = automaton.delta[result.a[i]][LAMBDA][j];
                    result.length++;
                }
            }
        }
    }

    return result;
}


/**
 * This function calculates the transition of a set of states with a symbol. The transition of the set
 * of states with a symbol is the set of states that can be reached from each state of the set using 
 * the symbol.
 * 
 * @param automaton The automaton to use.
 * @param states The set of states to calculate the transition.
 * @param symbol The symbol of the transition.
 * @return The transition of the set of states with the symbol.
*/
Array move(NDFA automaton, Array states, int symbol){
    Array result;
    result.length = 0;

    // Initialize the result array.
    for (int i = 0; i < MAX_ARRAY; i++) {
        result.a[i] = EMPTY;
    }

    for (int i = 0; i < states.length; i++) {
        for (int j = 0; j < automaton.states; j++) {

            // For each state in the set of states, check if it has a transition with the symbol.
            int currentState = automaton.delta[states.a[i]][symbol][j];
            if (currentState != EMPTY) {

                // If it has a transition with the symbol, check if it is already in the result.
                int itsInResult = FALSE;
                for (int k = 0; k < result.length && itsInResult == FALSE; k++) {
                    if (currentState == result.a[k]){
                        itsInResult = TRUE;
                    }
                }

                // If it is not in the result, add it.
                if (itsInResult == FALSE) {
                    result.a[result.length] = automaton.delta[states.a[i]][symbol][j];
                    result.length++;
                }
            }
        }
    }

    return result;
}


/**
 * This function converts a non deterministic finite automaton to a deterministic finite automaton.
 * 
 * @param automaton The non deterministic finite automaton.
 * @return The deterministic finite automaton.
*/
DFA convertToDFA(NDFA automaton) {

    // Initialize the result automaton.
    DFA result;                        

    for (int i = 0; i < MAX_ARRAY; i++) {
        for (int j = 0; j < MAX_ARRAY; j++) {
            result.delta[i][j] = EMPTY;
        }
    }
    
    result.symbols = automaton.symbols;
    result.initialState = automaton.initialState;

    SetOfMarkableArray set;
    set.length = 0;

    // Take the initial state of the NDFA and create the initial state of the DFA with the Lambda Clausure.
    Array initialStateNDFA;
    initialStateNDFA.a[0] = automaton.initialState;
    initialStateNDFA.length = 1;
    Array initialStateDFA;
    arrayCopy(&initialStateDFA, lambdaClausure(automaton, initialStateNDFA));
    
    // Create MarkableArray to insert in set from initialStateDFA
    MarkableArray arrayToInsert;
    arrayToInsert.isMarked = FALSE;
    arrayToInsert.elements = initialStateDFA;
    appendSorted(&set, arrayToInsert);

    // After the insertion, we check if the initial state is a final state.
    if (containsFinalState(automaton, arrayToInsert.elements) == TRUE) {
        // If it is, we add it to the final states of the result automaton.
        result.finalStates.a[result.finalStates.length] = set.length - 1;
        result.finalStates.length++;
    }
    
    // While there are unmarked states in the set...
    int lastMarked = -1;
    while (lastMarked < set.length - 1) {
        
        // Take an unmarked state and mark it.
        MarkableArray current = set.mArrays[lastMarked+1];
        mark(&set, lastMarked+1);

        // For each symbol in the automaton...
        for (int i = 0; i < automaton.symbols; i++) {
            
            // Calculate the lambda clausure of the move of the current state with the symbol.
            MarkableArray nextState;
            nextState.isMarked = FALSE;
            nextState.elements = lambdaClausure(automaton, move(automaton, current.elements, i));
            sort(&nextState.elements);

            // If the lambda clausure of the move of the current state with the symbol is not in the set, add it.
            if (elemInSet(set, nextState) == FALSE) {
                appendSorted(&set, nextState);
                
                // After the insertion, we check if the state is a final state.
                if (containsFinalState(automaton, nextState.elements) == TRUE) {
                    result.finalStates.a[result.finalStates.length] = set.length - 1;
                    result.finalStates.length++;
                }

            }
            
            int toState;
            // Search the index of the nextState in the set.
            for (int j = 0; j < set.length; j++) {
                sort(&nextState.elements);
                if (areEquals(set.mArrays[j].elements, nextState.elements) == TRUE) {
                    toState = j;
                }
            }

            // Add the transition to the result automaton.
            if (nextState.elements.length > 0) {
                result.delta[lastMarked+1][i] = toState;
            }
        }
        lastMarked++;
    }
    result.states = set.length;
    return result;
}
