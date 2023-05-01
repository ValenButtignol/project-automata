#include <stdio.h>
#include "data_structures/finite_automaton.h"

int main() {

    int numStates = 4;
    int numSymbols = 2;
    int initialState = 0;
    Array finalStates;
    finalStates.a[0] = 3;
    finalStates.length = 1;
    
    NDFA automaton = createNDFAAutomaton(numStates, numSymbols, initialState, finalStates);
    printf("NDFA created\n");

    Array toStatesArray;
    int fromState = 0;
    int symbol = LAMBDA;
    toStatesArray.a[0] = 2;
    toStatesArray.length = 1;
    symbol = 0;
    addTransitionToNDFA(&automaton, fromState, toStatesArray, symbol);

    toStatesArray.a[0] = 3;
    fromState = 2;
    symbol = 1;
    addTransitionToNDFA(&automaton, fromState, toStatesArray, symbol);

    toStatesArray.a[0] = 3;
    fromState = 3;
    symbol = 0;
    addTransitionToNDFA(&automaton, fromState, toStatesArray, symbol);

    toStatesArray.a[0] = 1;
    toStatesArray.a[1] = 3;
    toStatesArray.length = 2;
    fromState = 0;
    symbol = LAMBDA;
    addTransitionToNDFA(&automaton, fromState, toStatesArray, symbol);



    printf("States: %d\n", automaton.states);
    printf("Symbols: %d\n", automaton.symbols);
    printf("Initial state: %d\n", automaton.initialState);
    printf("Final states: ");
    for (int i = 0; i < automaton.finalStates.length; i++) {
        printf("%d ", automaton.finalStates.a[i]);
    }
    printf("\n");

    printf("Delta:\n");
    for (int i = 0; i < automaton.states; i++) {
        for (int j = 0; j < automaton.symbols; j++) {
            printf("%d -> %d ->: [ ", i, j);
            for (int k = 0; k < automaton.states; k++) {
                if (automaton.delta[i][j][k] != EMPTY) {
                    printf("%d ", automaton.delta[i][j][k]);
                }
            }
            printf("]\n");
        }
    }
}