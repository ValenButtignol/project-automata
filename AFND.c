#include <stdlib.h>
#include <stdio.h>
#define MAX_ARRAY 11
#define EMPTY -1
#define LAMBDA 10

//TODO: Agregar transiciones

typedef struct array {
    int a[MAX_ARRAY];
    int quantity;
} Array;

typedef struct NonDeterministicFiniteAutomaton {
//TODO: Agregar estados
    int states; // conjunto de estados (K)
    int symbols;        // conjunto de simbolos que representan el alfabeto
    int delta[MAX_ARRAY][MAX_ARRAY][MAX_ARRAY];    // matriz de transicion delta
    int initialState; // estado inicial del automaton
    int finalStates[MAX_ARRAY]; // conjunto de estados finales
    int quantityFinalStates;
} NDFA;

NDFA createAutomaton(int num_states, int num_symbols, int initialState, int finalStates[], int cantEstadosFinales);
void addTransition(NDFA *automaton, int fromState, int toState[], int quantityToStates, int symbol);
Array lambdaClausure(NDFA* automaton, int states[], int quantityOfStates);

int main() {

    int cantEstados = 6;
    int cantSimbolos = 10;
    int cantEstadosFinales = 2;
    int estadosFinales[cantEstadosFinales];
    int estadoInicial = 1;

    NDFA automaton = createAutomaton(cantEstados, cantSimbolos, estadoInicial, estadosFinales, cantEstadosFinales);

    int toState[1] = {1};
    addTransition(&automaton, 0, toState, 1, 5);

    printf("por lo menos compila\n");
    return 0;
}

NDFA createAutomaton(int num_states, int num_symbols, int initialState, int finalStates[], int cantEstadosFinales) {
    NDFA automaton;
    automaton.states = num_states;
    automaton.symbols = num_symbols;
    automaton.initialState = initialState;
    automaton.quantityFinalStates = cantEstadosFinales;

    // inicializar transiciones
    for (int i = 0; i < num_states; i++) {
        for (int j = 0; j < num_symbols; j++) {
            for(int k = 0; k < num_states; k++){
                automaton.delta[i][j][k] = EMPTY;
            }
        }
    }

    // inicializar estados finales
    for (int i = 0; i < cantEstadosFinales; i++) {
        automaton.finalStates[i] = finalStates[i];
    }

    return automaton;
}

void addTransition(NDFA *automaton, int fromState, int toState[], int quantityToStates, int symbol){
    for (int i = 0; i < quantityToStates; i++) {
        automaton->delta[fromState][symbol][i] = toState[i];
    }
}

Array lambdaClausure(NDFA* automaton, int states[], int quantityOfStates){

    Array result;
    result.quantity = 0;

    for (int i = 0; i < quantityOfStates; i++) {
        result.a[i] = states[i];
        result.quantity++;
    }

    for (int i = 0; i < quantityOfStates; i++) {
        for (int j = 0; j < automaton->states; j++) {
            int currentState = automaton->delta[states[i]][LAMBDA][j];
            if (currentState != EMPTY) {
                int itsInResult = 0;
                for (int k = 0; k < result.quantity && itsInResult == 0; k++) {
                    if (currentState == result.a[k]){
                        itsInResult = 1;
                    }
                }
                if (itsInResult == 0) {
                    result.a[result.quantity] = automaton->delta[states[i]][LAMBDA][j];
                    result.quantity++;
                }
            }
        }
    }

    return result;
}
