#include "../../include/algorithms/read_and_write.h"
#include "../../include/constants.h"
#include <string.h>
#include <stdlib.h>

/**
* This function reads an NDFA from a file.dot and creates a new NDFA with that 
* information.
*
* @param file to read the NDFA from
* @param numStates number of states the NDFA has
* @param numSymbols number of symbols the NDFA has
* @return ndfa created from the file
*/
NDFA createFromFile(FILE *file, int numStates, int numSymbols) {

    NDFA ndfa;
    ndfa.numStates = numStates;
    ndfa.numSymbols = numSymbols;
    ndfa.finalStates = NULL;
    ndfa.delta = NULL;   
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
            ndfa.initialState = initialState;
        }

        // We capture the lines with the pattern "[shape=doublecircle];", while we are reading the file.
        char *final = strstr(line, "[shape=doublecircle];");
        if (final) {
            int finalState;
            char *token3;
            token3 = strtok(line, "[");
            finalState = atoi(token3);
            addNDFAFinalState(&ndfa, finalState);
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
                addNDFATransition(&ndfa, fromState, label[i], toState);
            }
        }
    }

    return ndfa;
}


/**
* This function writes a given NDFA on a file.dot
*
* @param file to write the NDFA on
* @param ndfa to write on the file
*/
void writeToFile(FILE *file, NDFA ndfa) {
    // Write the header of the file.
    fprintf(file, "digraph{\n");
    fprintf(file, "inic[shape=point];\n");
    fprintf(file, "inic->%d;\n", ndfa.initialState);
    // traverse transitions and write them "%d->%d[label=\"%d\"];\n"
    NDFATransitionNode* aux2 = ndfa.delta;
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

    // traverse final states and write them "%d[shape=doublecircle];"
    Node* aux = ndfa.finalStates;
    while (aux != NULL) {
        fprintf(file, "%d[shape=doublecircle];\n", aux->data);
        aux = aux->next;
    }
    fprintf(file, "}\n");
}