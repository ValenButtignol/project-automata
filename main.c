#include "include/algorithms/belongs_to_language.h"
#include "include/algorithms/concatenate_ndfa.h"
#include "include/algorithms/convert_ndfa_to_dfa.h"
#include "include/algorithms/kleene_closure_ndfa.h"
#include "include/algorithms/union_ndfa.h"
#include "include/algorithms/read_and_write.h"
#include "include/algorithms/parser.h"
#include "include/structures/ndfa.h"
#include "include/structures/dfa.h"
#include "include/structures/node.h"
#include "include/structures/set_of_markable_sets.h"
#include "include/constants.h"
#include <stdio.h>
#include <stdlib.h>




int main( int argc, char *argv[]) {

    /* printf("Amount of states for the automaton: %s\n", argv[1]);
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
    NDFA ndfa2;
    NDFA automataResult; */

/********************************* ACA EMPIEZA LA LECTURA *****************************************/

    // leer archivo
    /* FILE *file;
    file = fopen(inputFileName, "r");
    if (file == NULL) {
        printf("Error\n");
        exit(1);
    }
    ndfa = createFromFile(file, numStates, numSymbols);
    fclose(file);

    file = fopen("automaton2.dot", "r");
    if (file == NULL) {
        printf("Error\n");
        exit(1);
    }
    ndfa2 = createFromFile(file, numStates, numSymbols);
    fclose(file);

    automataResult = unionNDFA(ndfa, ndfa2); */

/********************************* ACA TERMINA LA LECTURA *****************************************/



    /* int result = belongsToLanguage(ndfa, string);
    if (result == TRUE) {
        printf("The string is accepted.\n");
    } else {
        printf("The string is not accepted.\n");
    } */

    /* FILE *file2;
    file2 = fopen(outputFileName, "w");
    if (file2 == NULL) {
        printf("Error\n");
        exit(1);
    }

    writeToFile(file2, automataResult);
    fclose(file2);
    freeNDFA(ndfa);
    freeNDFA(ndfa2);
    freeNDFA(automataResult); */


/********************************* PARSING *****************************************/

    char* cursor;
    char* string = "0|1";
    cursor = string;

    printf("String to parse: %s\n", string);

    if (E(&cursor) && *cursor == '\0') { 
        puts("--------------------------------");
        puts("String is successfully parsed");
        return 0;
    }
    else {
        puts("--------------------------------");
        puts("Error in parsing String");
        return 1;
    }
    return 0;
}