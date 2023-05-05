#include "belongs_to_language.h"

typedef struct TransitionNDFA {
    int from;
    int symbol;
    Array to;
} TransitionNDFA;

typedef struct ArrayOfTransitionsNDFA {
    TransitionNDFA array[MAX_ARRAY];
    int length;
} ArrayOfTransitionsNDFA;


NDFA createFromFile(FILE *file, int numStates, int numSymbols);

void writeToFile(NDFA ndfa);