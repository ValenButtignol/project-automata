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

typedef struct DeterministicFiniteAutomaton {
//TODO: Agregar estados
    int states; // conjunto de estados (K)
    int symbols;        // conjunto de simbolos que representan el alfabeto
    int delta[MAX_ARRAY][MAX_ARRAY];    // matriz de transicion delta
    int initialState; // estado inicial del automaton
    int finalStates[MAX_ARRAY]; // conjunto de estados finales
    int quantityFinalStates;
} DFA;


NDFA createAutomaton(int num_states, int num_symbols, int initialState, int finalStates[], int cantEstadosFinales);
void addTransition(NDFA *automaton, int fromState, Array toStates, int symbol);
Array lambdaClausure(NDFA automaton, Array states);
Array move(NDFA automaton, Array states, int symbol);



int main() {

    int cantEstados = 6;
    int cantSimbolos = 10;
    int cantEstadosFinales = 2;
    int estadosFinales[cantEstadosFinales]; // inicializar estados finales.
    int estadoInicial = 1;
/* 
    NDFA automaton = createAutomaton(cantEstados, cantSimbolos, estadoInicial, estadosFinales, cantEstadosFinales);

    Array toStatesArray;
    toStatesArray.a[0] = 2;     // en un indice cero, el estado 2 va a ser un destino.
    toStatesArray.a[1] = 3;
    toStatesArray.quantity = 2;

    addTransition(&automaton, 0, toStatesArray, 5);
 */

    cantEstados = 4;
    cantSimbolos = 2;
    cantEstadosFinales = 1;
    estadosFinales[0] = 3;
    estadoInicial = 0;

    NDFA automaton2 = createAutomaton(cantEstados, cantSimbolos, estadoInicial, estadosFinales, cantEstadosFinales);

    // de 0 por lambda va a 1
    Array toStatesArray2;
 
    int fromState = 0;
    int symbol = LAMBDA;

    toStatesArray2.a[0] = 2;
    toStatesArray2.quantity = 1;
    symbol = 0;
    addTransition(&automaton2, fromState, toStatesArray2, symbol);
    
    toStatesArray2.a[0] = 3;
    fromState = 2;
    symbol = 1;
    addTransition(&automaton2, fromState, toStatesArray2, symbol);
    

    fromState = 3;
    symbol = 0;
    addTransition(&automaton2, fromState, toStatesArray2, symbol);



    toStatesArray2.a[0] = 1;
    toStatesArray2.a[1] = 3;
    toStatesArray2.quantity = 2;

    fromState = 0;
    symbol = LAMBDA;
    addTransition(&automaton2, fromState, toStatesArray2, symbol);


    Array toWatchLambdaClausure;
    toWatchLambdaClausure.a[0] = 0;
    toWatchLambdaClausure.a[1] = 3;
    toWatchLambdaClausure.quantity = 2;

    Array result = lambdaClausure(automaton2, toWatchLambdaClausure);


    Array toWatchMove = move(automaton2, result, 0);


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
                automaton.delta[i][LAMBDA][k] = EMPTY;
            }
        }
    }

    //inicializar las transiciones por lambda como empty??

    // inicializar estados finales
    for (int i = 0; i < cantEstadosFinales; i++) {
        automaton.finalStates[i] = finalStates[i];
    }

    return automaton;
}

void addTransition(NDFA *automaton, int fromState, Array toStates, int symbol){
    for (int i = 0; i < toStates.quantity; i++) {
        automaton->delta[fromState][symbol][i] = toStates.a[i];
    }
}

Array lambdaClausure(NDFA automaton, Array states){

    Array result;
    result.quantity = 0;


    for (int i = 0; i < MAX_ARRAY; i++) {
        result.a[i] = EMPTY;
    }

    for (int i = 0; i < states.quantity; i++) {
        result.a[i] = states.a[i];
        result.quantity++;
    }

    for (int i = 0; i < result.quantity; i++) {
        for (int j = 0; j < automaton.states; j++) {
            int currentState = automaton.delta[result.a[i]][LAMBDA][j];
            if (currentState != EMPTY) {
                // chequea si no esta agregado al resultado
                int itsInResult = 0;
                for (int k = 0; k < result.quantity && itsInResult == 0; k++) {
                    if (currentState == result.a[k]){
                        itsInResult = 1;
                    }
                }
                // Como no esta en el resultado, lo agrega
                if (itsInResult == 0) {
                    result.a[result.quantity] = automaton.delta[result.a[i]][LAMBDA][j];
                    result.quantity++;
                }
            }
        }
    }

    return result;
}


Array move(NDFA automaton, Array states, int symbol){
    Array result;
    result.quantity = 0;

    for (int i = 0; i < MAX_ARRAY; i++) {
        result.a[i] = EMPTY;
    }

    for (int i = 0; i < states.quantity; i++) {
        for (int j = 0; j < automaton.states; j++) {
            int currentState = automaton.delta[states.a[i]][symbol][j];
            if (currentState != EMPTY) {
                // chequea si no esta agregado al resultado
                int itsInResult = 0;
                for (int k = 0; k < result.quantity && itsInResult == 0; k++) {
                    if (currentState == result.a[k]){
                        itsInResult = 1;
                    }
                }
                // Como no esta en el resultado, lo agrega
                if (itsInResult == 0) {
                    result.a[result.quantity] = automaton.delta[states.a[i]][symbol][j];
                    result.quantity++;
                }
            }
        }
    }

    return result;
}


// DFA convertToDFA(NDFA automaton)
