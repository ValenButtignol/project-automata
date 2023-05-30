#include "algorithms/read_and_write.h"

int main( int argc, char *argv[]) {

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


    // createFromFile(inputFileName; cantEstados; numSymbols)    
    NDFA ndfa;

/********************************* ACA EMPIEZA LA LECTURA *****************************************/

    // leer archivo
    FILE *file;
    file = fopen(inputFileName, "r");
    if (file == NULL) {
        printf("Error\n");
        exit(1);
    }

    ndfa = createFromFile(file, numStates, numSymbols);
    
    fclose(file);

/********************************* ACA TERMINA LA LECTURA *****************************************/



    int result = belongsToLanguage(ndfa, string);
    if (result == TRUE) {
        printf("The string is accepted.\n");
    } else {
        printf("The string is not accepted.\n");
    }

    FILE *file2;
    file2 = fopen(outputFileName, "w");
    if (file2 == NULL) {
        printf("Error\n");
        exit(1);
    }

    writeToFile(file2, ndfa);
    fclose(file2);
    freeNDFA(ndfa);

    return 0;
}