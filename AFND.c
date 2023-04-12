#include <stdlib.h>
#include <stdio.h>
#define MAX_ARRAY 10
#define EMPTY -1
#define LAMBDA -2

//TODO: Agregar transiciones

typedef struct afnd {
//TODO: Agregar estados
    int states; // conjunto de estados (K)
    int symbols;        // conjunto de simbolos que representan el alfabeto
    int delta[MAX_ARRAY][MAX_ARRAY][MAX_ARRAY];    // matriz de transicion delta
    int initialState; // estado inicial del automaton
    int finalStates[MAX_ARRAY]; // conjunto de estados finales
    int quantityFinalStates;
} AFND;

AFND createAutomaton(int num_states, int num_symbols, int initialState, int finalStates[], int cantEstadosFinales);
void addTransition(AFND *automaton, int fromState, int toState[], int quantityToStates, int symbol);

int main() {

    int cantEstados = 6;
    int cantSimbolos = 10;
    int cantEstadosFinales = 2;
    int estadosFinales[cantEstadosFinales];
    int estadoInicial = 1;

    AFND automaton = createAutomaton(cantEstados, cantSimbolos, estadoInicial, estadosFinales, cantEstadosFinales);


    int toState[1] = {1};
    addTransition(&automaton, 0, toState, 1, 5);

    printf("por lo menos compila\n");
    return 0;
}

AFND createAutomaton(int num_states, int num_symbols, int initialState, int finalStates[], int cantEstadosFinales) {
    AFND automaton;
    automaton.states = num_states;
    automaton.symbols = num_symbols;
    automaton.initialState = initialState;
    automaton.quantityFinalStates = cantEstadosFinales;

    // inicializar transiciones
    for (int i = 0; i < num_states; i) {
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

void addTransition(AFND *automaton, int fromState, int toState[], int quantityToStates, int symbol){
    for (int i = 0; i < quantityToStates; i++) {
        automaton->delta[fromState][symbol][i] = toState[i];
    }
}