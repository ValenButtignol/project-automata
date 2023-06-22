#include "include/algorithms/belongs_to_language.h"
#include "include/algorithms/concatenate_ndfa.h"
#include "include/algorithms/convert_ndfa_to_dfa.h"
#include "include/algorithms/kleene_closure_ndfa.h"
#include "include/algorithms/union_ndfa.h"
#include "include/algorithms/read_and_write.h"
#include "include/algorithms/parser.h"
#include "include/algorithms/minigrep.h"
#include "include/structures/ndfa.h"
#include "include/structures/dfa.h"
#include "include/structures/node.h"
#include "include/structures/set_of_markable_sets.h"
#include "include/constants.h"
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[]) {

    /* char* cursor;
    NDFA* ndfa;
    char* regex = argv[1];
    char* text = argv[2];
    cursor = regex;

    printf("String to parse: %s\n", regex);

    if (E(&cursor, &ndfa) && *cursor == '\0') { 
        printf("String is successfully parsed\n");
        printf("Text to evaluate: %s\n", text);
        if(minigrep(regex, text, *ndfa)){
            printf("Coincidence found\n");
        }
        else{
            printf("No coincidence found\n");
        }
    }
    else {
        printf("Error in parsing string: %s\n", regex);
    }

    freeNDFA(*ndfa); */

    printf("Amount of states for the automaton: %s\n", argv[1]);
    printf("Amount of alphabet symbols: %s\n", argv[2]);
    printf("Name of the input file: %s\n", argv[3]);
    printf("String to evaluate: %s\n", argv[4]);
    printf("Name of the output file: %s\n", argv[5]);

    int numStates = atoi(argv[1]);
    int numSymbols = atoi(argv[2]);
    char* inputFileName = argv[3];
    char* string = argv[4];
    char* outputFileName = argv[5];


    NDFA ndfa;

    // leer archivo
    FILE *file;
    file = fopen(inputFileName, "r");
    if (file == NULL) {
        printf("Error\n");
        exit(1);
    }

    ndfa = createFromFile(file, numStates, numSymbols);
    fclose(file);

    DFA dfa = convertNDFAtoDFA(ndfa);
    toStringDFA(dfa);

    return 0;
}