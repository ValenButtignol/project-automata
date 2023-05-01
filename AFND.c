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

typedef struct TransitionNDFA {
    int from;
    int symbol;
    Array to;
} TransitionNDFA;

typedef struct ArrayOfTransitionsNDFA {
    TransitionNDFA array[MAX_ARRAY];
    int quantity;
} ArrayOfTransitionsNDFA;

int main( int argc, char *argv[]) {

    printf("Cantidad de estados: %s\n", argv[1]);
    printf("Cantidad de simbolos: %s\n", argv[2]);
    printf("Nombre del archivo: %s\n", argv[3]);
    printf("Cadena a evaluar: %s\n", argv[4]);

    int cantEstados = atoi(argv[1]);
    int cantSimbolos = atoi(argv[2]);
    int estadoInicial;
    int estadosFinales[MAX_ARRAY];
    int cantEstadosFinales;

    NDFA automaton2;
    int fromState;
    int symbol;
    Array toStatesArray;
    toStatesArray.quantity = 0;
    ArrayOfTransitionsNDFA arrayOfTransitions;
    arrayOfTransitions.quantity = 0;

    // leer archivo
    FILE *file;
    file = fopen(argv[3], "r");
    if (file == NULL) {
        printf("Error\n");
        exit(1);
    }

    char line[100];
    while (fgets(line, 100, file) != NULL) {

        //capturar estado inicial
        char *inic = strstr(line, "inic->");
        if (inic) {
            char cadenaNumero[3];
            cadenaNumero[0] = inic[7];
            cadenaNumero[1] = inic[8];
            cadenaNumero[2] = '\0';
            estadoInicial = atoi(cadenaNumero);  
        }
        //capturar estados finales
        char *final = strstr(line, "[shape=doublecircle];");
        if (final) {
            char cadenaNumero[3];
            cadenaNumero[0] = line[0];
            cadenaNumero[1] = line[1];
            cadenaNumero[2] = '\0';
            int estadoFinal = atoi(cadenaNumero);
            estadosFinales[cantEstadosFinales] = estadoFinal;
            cantEstadosFinales++;
        }

        //capturar transiciones
        char *transition = strstr(line, "label");
        if (transition) {
            char cadenaNumero[3];
            cadenaNumero[0] = line[0];
            cadenaNumero[1] = line[1];
            cadenaNumero[2] = '\0';
            int from = atoi(cadenaNumero);
            fromState = from;
            
            cadenaNumero[3];
            cadenaNumero[0] = line[4];
            cadenaNumero[1] = line[5];
            cadenaNumero[2] = '\0';
            int to = atoi(cadenaNumero);

            char label[(15 - strlen(line) - 4)]; 
            for (int i = 15; i < strlen(line) - 4; i++)
            {
                label[i - 15] = line[i];
            }
            label[strlen(line) - 4 - 15] = '\0';

            Array labels; 
            labels.quantity = 0;
            char s[2];
            s[0] = ',';
            s[1] = '\0';
            char* token = strtok(label, s);
            while( token != NULL ) {
                int label;
                if (token[0] == '_')
                {
                    label = LAMBDA;
                } else {
                    cadenaNumero[0] = token[0];
                    cadenaNumero[1] = token[1];
                    cadenaNumero[2] = '\0';
                    label = atoi(cadenaNumero);
                }
                labels.a[labels.quantity] = label;
                labels.quantity++;

                token = strtok(NULL, s);
            }
            
            int flag = 0;
            for (int i = 0; i < arrayOfTransitions.quantity; i++){
                for (int j = 0; j < labels.quantity; j++){
                    if (arrayOfTransitions.array[i].from == from && arrayOfTransitions.array[i].symbol == labels.a[j]){
                        arrayOfTransitions.array[i].to.a[arrayOfTransitions.array[i].to.quantity] = to;
                        arrayOfTransitions.array[i].to.quantity++;
                        flag = 1;
                    }
                }
            }
            if (flag == 0){
                for (int i = 0; i < labels.quantity; i++){
                    TransitionNDFA newTransition;
                    newTransition.from = from;
                    newTransition.symbol = labels.a[i];
                    newTransition.to.a[0] = to;
                    newTransition.to.quantity = 1;
                    arrayOfTransitions.array[arrayOfTransitions.quantity] = newTransition;
                    arrayOfTransitions.quantity++;
                }
            }
            
            
        }
        
    }
    fclose(file); 

    automaton2 = createNDFAAutomaton(cantEstados, cantSimbolos, estadoInicial, estadosFinales, cantEstadosFinales);
    for (int i = 0; i < arrayOfTransitions.quantity; i++){
        addTransitionToNDFA(&automaton2, arrayOfTransitions.array[i].from, arrayOfTransitions.array[i].to, arrayOfTransitions.array[i].symbol);
    }

    char* string = argv[4];
    int result = belongsToLanguage(automaton2, string);
    if (result == 1) {
        printf("La cadena es aceptada\n");
    } else {
        printf("La cadena no es aceptada\n");
    }

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
            mergeSort(&nextState.elements);
            if (elemInSet(setOfStatesSet, nextState) == 0) {

                appendSorted(&setOfStatesSet, nextState);
                
                if (containsFinalState(automaton, nextState.elements) == 1) {
                    result.finalStates[result.quantityFinalStates] = setOfStatesSet.quantity - 1;
                    result.quantityFinalStates++;
                }

            }
            // Search the index of the nextState in the setOfStatesSet using areEqual()
            int toState;
            for(int j = 0; j < setOfStatesSet.quantity; j++){
                mergeSort(&nextState.elements);
                if(areEquals(setOfStatesSet.array[j].elements, nextState.elements) == 1){
                    toState = j;
                }
            }

            if(nextState.elements.quantity > 0){
                result.delta[lastMarked+1][i] = toState;
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

    
    fclose(file);
    return automaton;
}
