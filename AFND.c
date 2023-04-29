#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define MAX_ARRAY 11
#define EMPTY -1
#define LAMBDA 10

//TODO: Agregar transiciones

typedef struct List {
    int a[MAX_ARRAY];
    int quantity;
} Array;

int areEquals(Array array1, Array array2);
void arrayCopy(Array* array, Array copyArray);
void merge(Array* array, Array left, Array right);
void mergeSort(Array* array);
int isEmpty(Array array);


typedef struct NonDeterministicFiniteAutomaton {
//TODO: Agregar estados
    int states; // conjunto de estados (K)
    int symbols;        // conjunto de simbolos que representan el alfabeto
    int delta[MAX_ARRAY][MAX_ARRAY][MAX_ARRAY];    // matriz de transicion delta
    int initialState; // estado inicial del automaton
    int finalStates[MAX_ARRAY]; // conjunto de estados finales
    int quantityFinalStates;
} NDFA;

NDFA createNDFAAutomaton(int num_states, int num_symbols, int initialState, int finalStates[], int cantEstadosFinales);
void addTransitionToNDFA(NDFA *automaton, int fromState, Array toStates, int symbol);
Array lambdaClausure(NDFA automaton, Array states);
Array move(NDFA automaton, Array states, int symbol);


typedef struct DeterministicFiniteAutomaton {
//TODO: Agregar estados
    int states; // conjunto de estados (K)
    int symbols;        // conjunto de simbolos que representan el alfabeto
    int delta[MAX_ARRAY][MAX_ARRAY];    // matriz de transicion delta
    int initialState; // estado inicial del automaton
    int finalStates[MAX_ARRAY]; // conjunto de estados finales
    int quantityFinalStates;
} DFA;

typedef struct Markable {
    Array elements;
    int marked;
}Markable;

typedef struct MarkableArray {
    Markable array[MAX_ARRAY];
    int quantity;
}MarkableArray;

DFA convertToDFA(NDFA automaton);
int containsFinalState(NDFA automaton, Array states);
void mark(MarkableArray *array, int element);
int elemInSet(MarkableArray set, Markable array);
void appendSorted(MarkableArray *array, Markable otherArray);
int belongsToLanguage(NDFA automaton, char string[]);

Array stringToArray(char string[]);

int main() {

    int cantEstados = 6;
    int cantSimbolos = 10;
    int cantEstadosFinales = 2;
    int estadosFinales[cantEstadosFinales]; // inicializar estados finales.
    int estadoInicial = 1;
/* 
    NDFA automaton = createNDFAAutomaton(cantEstados, cantSimbolos, estadoInicial, estadosFinales, cantEstadosFinales);

    Array toStatesArray;
    toStatesArray.a[0] = 2;     // en un indice cero, el estado 2 va a ser un destino.
    toStatesArray.a[1] = 3;
    toStatesArray.quantity = 2;

    addTransitionToNDFA(&automaton, 0, toStatesArray, 5);
 */

    cantEstados = 4;
    cantSimbolos = 2;
    cantEstadosFinales = 1;
    estadosFinales[0] = 3;
    estadoInicial = 0;

    NDFA automaton2 = createNDFAAutomaton(cantEstados, cantSimbolos, estadoInicial, estadosFinales, cantEstadosFinales);

    // de 0 por lambda va a 1
    Array toStatesArray2;
 
    int fromState = 0;
    int symbol = LAMBDA;
    toStatesArray2.a[0] = 2;
    toStatesArray2.quantity = 1;
    symbol = 0;
    addTransitionToNDFA(&automaton2, fromState, toStatesArray2, symbol);
    
    toStatesArray2.a[0] = 3;
    fromState = 2;
    symbol = 1;
    addTransitionToNDFA(&automaton2, fromState, toStatesArray2, symbol);
    

    fromState = 3;
    symbol = 0;
    addTransitionToNDFA(&automaton2, fromState, toStatesArray2, symbol);



    toStatesArray2.a[0] = 1;
    toStatesArray2.a[1] = 3;
    toStatesArray2.quantity = 2;

    fromState = 0;
    symbol = LAMBDA;
    addTransitionToNDFA(&automaton2, fromState, toStatesArray2, symbol);


    //convertToDFA(automaton2);


    Array toWatchLambdaClausure;
    toWatchLambdaClausure.a[0] = 0;
    toWatchLambdaClausure.a[1] = 3;
    toWatchLambdaClausure.quantity = 2;

    Array result = lambdaClausure(automaton2, toWatchLambdaClausure);


    char *string = "011";
    int x = belongsToLanguage(automaton2, string);

    return 0;
}

void arrayCopy(Array* array, Array copyArray) {
    for (int i = 0; i < copyArray.quantity; i++) {
        array->a[i] = copyArray.a[i];
        array->quantity++;
    }
}

int isEmpty(Array array) {
    if (array.quantity == 0) {
        return 1;
    } else {
        return 0;
    }
}


NDFA createNDFAAutomaton(int num_states, int num_symbols, int initialState, int finalStates[], int cantEstadosFinales) {
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

void addTransitionToNDFA(NDFA *automaton, int fromState, Array toStates, int symbol){
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


DFA convertToDFA(NDFA automaton) {
    DFA result;                            
    // inicializar transiciones
    for (int i = 0; i < MAX_ARRAY; i++) {
        for (int j = 0; j < MAX_ARRAY; j++) {
            result.delta[i][j] = EMPTY;
        }
    }
    
    
    result.symbols = automaton.symbols;
    result.initialState = automaton.initialState;

    MarkableArray setOfStatesSet;
    setOfStatesSet.quantity = 0;

    // Take the initial state of the NDFA and create the initial state of the DFA with the Lambda Clausure.
    Array initialStateNDFA;
    initialStateNDFA.a[0] = automaton.initialState;
    initialStateNDFA.quantity = 1;
    Array initialStateDFA;
    arrayCopy(&initialStateDFA, lambdaClausure(automaton, initialStateNDFA));
    
    // Create Markable to insert in setOfStatesSet from initialStateDFA
    Markable arrayToInsert;
    arrayToInsert.marked = 0;
    arrayToInsert.elements = initialStateDFA;

    appendSorted(&setOfStatesSet, arrayToInsert);
    if (containsFinalState(automaton, arrayToInsert.elements) == 1) {
        result.finalStates[result.quantityFinalStates] = setOfStatesSet.quantity - 1;
        result.quantityFinalStates++;
    }
    
    int lastMarked = -1;
    while (lastMarked < setOfStatesSet.quantity - 1){

        Markable current = setOfStatesSet.array[lastMarked+1];
        mark(&setOfStatesSet, lastMarked+1);

        for (int i = 0; i < automaton.symbols; i++){
            Markable nextState;
            nextState.marked = 0;
            nextState.elements = lambdaClausure(automaton, move(automaton, current.elements, i));
            if (elemInSet(setOfStatesSet, nextState) == 0) {

                appendSorted(&setOfStatesSet, nextState);
                
                if (containsFinalState(automaton, nextState.elements) == 1) {
                    result.finalStates[result.quantityFinalStates] = setOfStatesSet.quantity - 1;
                    result.quantityFinalStates++;
                }

            }
            if(nextState.elements.quantity > 0){
                result.delta[lastMarked+1][i] = setOfStatesSet.quantity - 1;
            }
        }
        lastMarked++;
    }
    result.states = setOfStatesSet.quantity;
    return result;
}


int containsFinalState(NDFA automaton, Array states) {
    int result = 0;
    for (int i = 0; i < states.quantity && result == 0; i++) {
        for (int j = 0; j < automaton.quantityFinalStates && result == 0; j++) {
            if (states.a[i] == automaton.finalStates[j]) {
                result = 1;
            }
        }
    }
    return result;
}

void appendSorted(MarkableArray *setOfStatesSet, Markable arrayToInsert) {
    arrayCopy(&setOfStatesSet->array[setOfStatesSet->quantity].elements, arrayToInsert.elements);
    mergeSort(&setOfStatesSet->array[setOfStatesSet->quantity].elements);
    setOfStatesSet->array[setOfStatesSet->quantity].marked = 0;
    setOfStatesSet->quantity++;
}



void mergeSort(Array *array) {
    if (array->quantity > 1) {
        int middle = array->quantity / 2;
        Array left;
        Array right;

        left.quantity = middle;
        right.quantity = array->quantity - middle;

        for (int i = 0; i < middle; i++) {
            left.a[i] = array->a[i];
        }

        for (int i = middle; i < array->quantity; i++) {
            right.a[i - middle] = array->a[i];
        }

        mergeSort(&left);
        mergeSort(&right);
        merge(array, left, right);
    }
}

void merge(Array *array, Array left, Array right) {
    int i = 0;
    int j = 0;
    int k = 0;

    while (i < left.quantity && j < right.quantity) {
        if (left.a[i] < right.a[j]) {
            array->a[k] = left.a[i];
            i++;
        } else {
            array->a[k] = right.a[j];
            j++;
        }
        k++;
    }

    while (i < left.quantity) {
        array->a[k] = left.a[i];
        i++;
        k++;
    }

    while (j < right.quantity) {
        array->a[k] = right.a[j];
        j++;
        k++;
    }
}



int elemInSet(MarkableArray set, Markable array) {
    if(array.elements.quantity == 0){
        return 1;
    }
    if (set.quantity == 0){
        return 0;
    }
    int flag = 0;
    for (int i = 0; i < set.quantity; i++){
        if (areEquals(set.array[i].elements, array.elements) == 1){
            return 1;
        }
    }
    return flag;
}

int areEquals(Array array, Array otherArray) {
    int flag = 1;
    for (int i = 0; i < array.quantity && flag == 1; i++) {
        if (array.a[i] != otherArray.a[i]){
            flag = 0;
        }
    }
    return flag;
}

void mark(MarkableArray *setOfStatesSet, int index) {
    setOfStatesSet->array[index].marked = 1;
}
 

Array stringToArray(char string[]) {
    Array result;
    int length = strlen(string);
    for (int i = 0; i < length; i++){
        char stringNumber[2];
        stringNumber[0] = string[i];
        stringNumber[1] = '\0';
        result.a[i] = atoi(stringNumber);
        result.quantity++;
    }
    return result;
}


int belongsToLanguage(NDFA automaton, char string[]) {
    Array stringArray = stringToArray(string);
    DFA dfa = convertToDFA(automaton);
    int count = 0;
    int currentState = dfa.initialState;
    for (int i = 0; i < stringArray.quantity; i++) {
        if (dfa.delta[currentState][stringArray.a[i]] != EMPTY) {
            currentState = dfa.delta[currentState][stringArray.a[i]];
            count++;
        } else {
            return 0;
        }
    }
    
    for (int i = 0; i < dfa.quantityFinalStates; i++) {
        if(currentState == dfa.finalStates[i]){
            return 1;
        }
    }

    return 0;
}



/*
createFromFile()
    filename = "automaton.dot"

    FILE *archivo;
    archivo = fopen("automaton.dot", "r");

writeToFile(char filename[], AF automaton)
    filename = "output.dot"

./Main "automata.dot" "01010"

./Main



*/

NDFA createAFNDFromFile() {
    NDFA automaton;

    FILE *file;
    file = fopen("automaton.dot", "r");
    if (file == NULL) {
        printf("Error\n");
        exit(1);
    }

    char line[100];
    while (fgets(line, 100, file) != NULL) {
        printf("%s", line);
    }
    



    /**
    char linea[100]; // Buffer para almacenar la línea leída
    while (fgets(linea, 100, archivo)) { // Leemos el archivo línea por línea
        char *patron = "inic->"; // Patrón a buscar
        char *posicion = strstr(linea, patron); // Buscamos la posición del patrón en la línea actual
        if (posicion) { // Si se encontró el patrón
            sscanf(posicion + strlen(patron), "%d", &num); // Extraemos el número que sigue al patrón
            break; // Salimos del bucle si se encontró el patrón
        }
    }
    */


    
    fclose(file);
    return automaton;
}


/*
    Estado inicial: 
        cadena = "inic->0"
        char numberChar = cadena[7]
        char cadenaNumero[2];
        cadenaNumero[0] = numberChar;
        cadenaNumero[1] = '\0';
        int estadoInicial = atoi(cadenaNumero);    
    Transicion: 
        cadena = "0->1 [label="_"]"
        
        char numberChar = cadena[0]
        char cadenaNumero[2];
        cadenaNumero[0] = numberChar;
        cadenaNumero[1] = '\0';
        int from = atoi(cadenaNumero);
        
        char numberChar = cadena[3]
        char cadenaNumero[2];
        cadenaNumero[0] = numberChar;
        cadenaNumero[1] = '\0';
        int to = atoi(cadenaNumero);

        char numberChar = cadena[13]
        char cadenaNumero[2];
        cadenaNumero[0] = numberChar;
        cadenaNumero[1] = '\0';
        int label = atoi(cadenaNumero);
        
    Estado final: 
        cadena = "3[shape=doublecircle]"
        int estadoFinal = cadena[0]
*/