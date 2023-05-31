#include "read_and_write.h"

NDFA createFromFile(FILE *file, int numStates, int numSymbols) {

    NDFA ndfa;
    ndfa.numStates = numStates;
    ndfa.numSymbols = numSymbols;
    ndfa.finalStates = NULL;
    ndfa.transitions = NULL;   
    char line[100];
    while (fgets(line, 100, file) != NULL) {

        // We capture the lines with the pattern "inic->", while we are reading the file.
        char *inic = strstr(line, "inic->");
        if (inic) {
            int initialState;
            char *token2;
            token2 = strtok(line, "->");
            token2 = strtok(NULL, ";") + 1;
            initialState = atoi(token2);  
            ndfa.startState = initialState;
        }

        // We capture the lines with the pattern "[shape=doublecircle];", while we are reading the file.
        char *final = strstr(line, "[shape=doublecircle];");
        if (final) {
            int finalState;
            char *token3;
            token3 = strtok(line, "[");
            finalState = atoi(token3);
            addFinalStateNDFA(&ndfa, finalState);
        }

        // We capture the lines with the pattern "label", while we are reading the file.
        char *transition = strstr(line, "label");
        if (transition) {
            char *token;
            int count = 0;
            int fromState;
            int toState;
            char label[100];
            
            // Obtener la parte antes del símbolo "->"
            token = strtok(line, "->");
            fromState = atoi(token);

            // Obtener la parte después del símbolo "->"
            token = strtok(NULL, " ") + 1;
            toState = atoi(token);

            // Obtener los números después de "label="
            token = strtok(NULL, "\"");
            token = strtok(NULL, ",");

            while (token != NULL && count < 100) {
                if(strcmp(token, "_") == 0 || strcmp(token, "_\"];\n") == 0) {
                    label[count] = -1;
                    count++;
                } else {
                    label[count] = atoi(token);
                    count++;
                }
                token = strtok(NULL, ",");
            }
            for(int i = 0; i < count; i++) {
                insertTransitionNDFA(&ndfa, fromState, label[i], toState);
            }
        }
    }

    return ndfa;
}



void writeToFile(FILE *file, NDFA ndfa) {
    // Write the header of the file.
    fprintf(file, "digraph{\n");
    fprintf(file, "inic[shape=point];\n");
    fprintf(file, "inic->%d;\n", ndfa.startState);
    // traverse transitions and write them "%d->%d[label=\"%d\"];\n"
    NDFATransitionNode* aux2 = ndfa.transitions;
    while (aux2 != NULL) {
        int fromState = aux2->transition.fromState;
        int symbol = aux2->transition.symbol;
        // traverse toState and write them "%d->%d[label=\"%d\"];\n"
        Node* aux3 = aux2->transition.toStates;
        while (aux3 != NULL) {
            int toState = aux3->data;
            fprintf(file, "%d->%d[label=\"", fromState, toState);
            if (symbol == LAMBDA) {
                fprintf(file, "_\"];\n");
            } else {
                fprintf(file, "%d\"];\n", symbol);
            }
            aux3 = aux3->next;
        }
        aux2 = aux2->next;
    }

    //traverse final states and write them "%d[shape=doublecircle];"
    Node* aux = ndfa.finalStates;
    while (aux != NULL) {
        fprintf(file, "%d[shape=doublecircle];\n", aux->data);
        aux = aux->next;
    }
    fprintf(file, "}\n");
}