#include "read_and_write.h"

NDFA createFromFile(FILE *file, int numStates, int numSymbols) {

    NDFA ndfa;

    // This is the data to capture from the file.
    Array finalStates;
    finalStates.length = 0;
    int initialState;
    int fromState;
    int symbol;
    Array toStatesArray;
    toStatesArray.length = 0;
    ArrayOfTransitionsNDFA arrayOfTransitions;
    arrayOfTransitions.length = 0;

    

    char line[100];
    while (fgets(line, 100, file) != NULL) {

        // We capture the lines with the pattern "inic->", while we are reading the file.
        char *inic = strstr(line, "inic->");
        if (inic) {
            // The number is captured as a string, so we convert it to an integer.
            char numberString[3];
            numberString[0] = inic[7];
            numberString[1] = inic[8];
            numberString[2] = '\0';
            initialState = atoi(numberString);  
        }

        // We capture the lines with the pattern "[shape=doublecircle];", while we are reading the file.
        char *final = strstr(line, "[shape=doublecircle];");
        if (final) {
            char stringNumber[3];
            stringNumber[0] = line[0];
            stringNumber[1] = line[1];
            stringNumber[2] = '\0';
            int estadoFinal = atoi(stringNumber);
            finalStates.a[finalStates.length] = estadoFinal;
            finalStates.length++;
        }

        // We capture the lines with the pattern "label", while we are reading the file.
        char *transition = strstr(line, "label");
        if (transition) {
            char stringNumber[3];
            stringNumber[0] = line[0];
            stringNumber[1] = line[1];
            stringNumber[2] = '\0';
            int from = atoi(stringNumber);
            fromState = from;
            
            stringNumber[3];
            stringNumber[0] = line[4];
            stringNumber[1] = line[5];
            stringNumber[2] = '\0';
            int to = atoi(stringNumber);

            char label[(15 - strlen(line) - 4)]; 
            for (int i = 15; i < strlen(line) - 4; i++) {
                label[i - 15] = line[i];
            }
            label[strlen(line) - 4 - 15] = '\0';

            Array labels; 
            labels.length = 0;
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
                    stringNumber[0] = token[0];
                    stringNumber[1] = token[1];
                    stringNumber[2] = '\0';
                    label = atoi(stringNumber);
                }
                labels.a[labels.length] = label;
                labels.length++;

                token = strtok(NULL, s);
            }
            
            // Then, we add every transition captured to the array of transitions of the automaton.
            int flag = FALSE;
            for (int i = 0; i < arrayOfTransitions.length; i++){
                for (int j = 0; j < labels.length; j++){

                    // We check if a transition with the same fromState and symbol already exists.
                    if (arrayOfTransitions.array[i].from == from && arrayOfTransitions.array[i].symbol == labels.a[j]){
                        arrayOfTransitions.array[i].to.a[arrayOfTransitions.array[i].to.length] = to;
                        arrayOfTransitions.array[i].to.length++;
                        flag = TRUE;
                    }
                }
            }

            // If the transition with the same fromState and symbol doesn't exists...
            if (flag == FALSE){
                for (int i = 0; i < labels.length; i++) {
                    // We create a new transition and add it to the array of transitions of the automaton.
                    TransitionNDFA newTransition;
                    newTransition.from = from;
                    newTransition.symbol = labels.a[i];
                    newTransition.to.a[0] = to;
                    newTransition.to.length = 1;
                    arrayOfTransitions.array[arrayOfTransitions.length] = newTransition;
                    arrayOfTransitions.length++;
                }
            }
        }
    }
    
    ndfa = createNDFAAutomaton(numStates, numSymbols, initialState, finalStates);
    for (int i = 0; i < arrayOfTransitions.length; i++){
        addTransitionToNDFA(&ndfa, arrayOfTransitions.array[i].from, arrayOfTransitions.array[i].to, arrayOfTransitions.array[i].symbol);
    }

    return ndfa;
}



void writeToFile(FILE *file, NDFA ndfa) {
    // Write the header of the file.
    fprintf(file, "digraph{\n");
    fprintf(file, "inic[shape=point];\n");

    // Write the initial state.
    if (ndfa.initialState < 10){
        fprintf(file, "inic->0%d;\n", ndfa.initialState);
    } else {
        fprintf(file, "inic->%d;\n", ndfa.initialState);
    }

    // Write the transitions.
    for (int i = 0; i < ndfa.states; i++) {
        for (int k = 0; k < ndfa.states; k++) {     // CAREFUL! This is k, not j. k is for the toStates and j is for the symbols.
            for (int j = 0; j < ndfa.symbols; j++) {
                if (ndfa.delta[i][j][k] != EMPTY) {
                    // Write the fromState.
                    if (i < 10){
                        fprintf(file, "0%d->", i);
                    } else {
                        fprintf(file, "%d->", i);
                    }

                    // Write the toState.
                    if (ndfa.delta[i][j][k] < 10){
                        fprintf(file, "0%d ", ndfa.delta[i][j][k]);
                    } else {
                        fprintf(file, "%d ", ndfa.delta[i][j][k]);
                    }

                    fprintf(file, "[label=\"");
                    
                    // ATENTION: This will add all the labels different of LAMBDA, because ndfa.symbols never includes LAMBDA.
                    if (j < 10) {
                        fprintf(file, "0%d\"];\n", j);
                    } else {
                        fprintf(file, "%d\"];\n", j);
                    }

                    
                }
            }
            // Now we check for any LAMBDA transition.
            if (ndfa.delta[i][LAMBDA][k] != EMPTY) {

                // Write the fromState.
                if (i < 10){
                    fprintf(file, "0%d->", i);
                } else {
                    fprintf(file, "%d->", i);
                }

                // Write the toState.
                if (ndfa.delta[i][LAMBDA][k] < 10){
                    fprintf(file, "0%d ",ndfa.delta[i][LAMBDA][k]);
                } else {
                    fprintf(file, "%d ",ndfa.delta[i][LAMBDA][k]);
                }

                fprintf(file, "[label=\"");
                fprintf(file, "_\"];\n");
            }
        }
    }

    // Escribir los estados finales
    for (int i = 0; i < ndfa.finalStates.length; i++) {
        if (ndfa.finalStates.a[i] < 10){
            fprintf(file, "0%d[shape=doublecircle];\n", ndfa.finalStates.a[i]);
        }
        else {
            fprintf(file, "%d[shape=doublecircle];\n", ndfa.finalStates.a[i]);
        }
    }
    fprintf(file, "}\n");
}